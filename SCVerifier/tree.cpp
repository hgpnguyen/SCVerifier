#include "tree.h";
#include "utility.h"


/*string TreeRoot::getString()
{
	string result = "";
	for (auto i : childrens)
		result += i.getValue();
	return result;
}*/

expr TreeRoot::getExpr(context& c, solver& s)
{
	expr_vector vec(c);
	for (auto child : childrens) {
		vec.push_back(child->getExpr(c, s));
	}
	return concat(vec);
}

string TreeRoot::getDepth(bool isDepth)
{
	string result = "";
	for (auto i : childrens)
		result += i->DepthFS(isDepth);
	return result;
}

list<TreeNode*> TreeRoot::visit(Json::Value ctx, int depth)
{
	typedef list<TreeNode*>(TreeRoot::* pfunc)(Json::Value, int);
	map<string, pfunc> switchCase;
	switchCase["Block"] = &TreeRoot::block;
	switchCase["IfStatement"] = &TreeRoot::ifStmt;
	switchCase["ForStatement"] = &TreeRoot::forStmt;
	switchCase["ExpressionStatement"] = &TreeRoot::exprStmt;
	switchCase["Return"] = &TreeRoot::returnStmt;
	switchCase["FunctionCall"] = &TreeRoot::functionCall;
	switchCase["FunctionDefinition"] = &TreeRoot::functionDef;
	switchCase["Assignment"] = &TreeRoot::assignment;
	switchCase["BinaryOperation"] = &TreeRoot::binaryOp;
	switchCase["UnaryOperation"] = &TreeRoot::unaryOp;
	switchCase["ParameterList"] = &TreeRoot::parameterList;
	switchCase["WhileStatement"] = &TreeRoot::whileStmt;
	switchCase["DoWhileStatement"] = &TreeRoot::doWhileStmt;
	switchCase["PlaceholderStatement"] = &TreeRoot::placeHolderStmt;
	string nodeType = ctx["nodeType"].asString();
	auto func = switchCase.find(nodeType) != switchCase.end() ? switchCase[nodeType] : &TreeRoot::otherStmt;
	auto result = (this->*func)(ctx, depth);
	return result;
}

list<TreeNode*> TreeRoot::block(Json::Value ctx, int depth)
{
	list<TreeNode*> result;
	for (auto statement : ctx["statements"]) {
		auto stmt = visit(statement, depth);
		result.splice(result.end(), stmt);
	}
	return result;
}

/*if(b) {c1}; else {c2}; -> assert(b); c1 | assert(!b); c2*/

list<TreeNode*> TreeRoot::ifStmt(Json::Value ctx, int depth)
{
	list<TreeNode*> result, truebr, falsebr;

	list<TreeNode*> cond = visit(ctx["condition"], depth);
	list<TreeNode*> cond2(cond);
	list<TreeNode*> trueCond = visit(ctx["trueBody"], depth);
	list<TreeNode*> falseCond = !ctx["falseBody"].isNull() ? visit(ctx["falseBody"], depth) : list<TreeNode*>();

	//assert(b); c1 -> t{#b}c1
	Json::Value assert_ = createExprStmt(createAssert(ctx["condition"]));
	string cond_str = getCode(ctx["condition"]);
	string code = "assert(" + cond_str + ");stmt";
	string enStr = encodeExt(code, assert_);
	truebr.push_back(new LeafNode(enStr));
	truebr.splice(truebr.end(), cond);
	truebr.splice(truebr.end(), trueCond);
	//assert(!b); c2 -> f{#b}c2
	Json::Value unary = createUnary(ctx["condition"], "!");
	assert_ = createExprStmt(createAssert(unary));
	code = "assert(!" + cond_str + ");stmt";
	enStr = encodeExt(code, assert_);
	falsebr.push_back(new LeafNode(enStr));
	falsebr.splice(falsebr.end(), cond2);
	falsebr.splice(falsebr.end(), falseCond);

	list<TreeNode*> temp = { new SubNode(truebr), new SubNode(falsebr) };
	result.push_back(new OrNode(temp));

	return result;
}

//for(ini;b1;inc) c => ini;while b1 do {c;inc}
list<TreeNode*> TreeRoot::forStmt(Json::Value ctx, int depth)
{
	list<TreeNode*> result, loop;
	list<TreeNode*> initExpr = visit(ctx["initializationExpression"], depth);
	list<TreeNode*> cond = visit(ctx["condition"], depth);
	list<TreeNode*> cond2(cond);
	list<TreeNode*> loopExpr = visit(ctx["loopExpression"], depth);
	list<TreeNode*> body = visit(ctx["body"], depth);
	string cond_str = getCode(ctx["condition"]);

	//init => e
	result.splice(result.end(), initExpr);

	//assert(b1);c;inc => t{b1}ab
	Json::Value assert_ = createExprStmt(createAssert(ctx["condition"]));
	string code = "assert(" + cond_str + ");stmt";
	string enStr = encodeExt(code, assert_);
	loop.push_back(new LeafNode(enStr));
	loop.splice(loop.end(), cond);
	loop.splice(loop.end(), body);
	loop.splice(loop.end(), loopExpr);
	result.push_back(new LoopNode(loop));

	//assert(!b1) => f{b1}
	Json::Value unary = createUnary(ctx["condition"], "!");
	assert_ = createExprStmt(createAssert(unary));
	code = "assert(!" + cond_str + ");stmt";
	enStr = encodeExt(code, assert_);
	result.push_back(new LeafNode(enStr));
	result.splice(result.end(), cond2);

	return result;
}

//while b do c => (assert(b);c)*;assert(!b);
list<TreeNode*> TreeRoot::whileStmt(Json::Value ctx, int depth)
{
	list<TreeNode*> result, loop;
	list<TreeNode*> cond = visit(ctx["condition"], depth);
	list<TreeNode*> body = visit(ctx["body"], depth);
	list<TreeNode*> cond2(cond);
	string cond_str = getCode(ctx["condition"]);

	//(assert(b);c)* => (t{b}a)*
	Json::Value assert_ = createExprStmt(createAssert(ctx["condition"]));
	string code = "assert(" + cond_str + ");stmt";
	string enStr = encodeExt(code, assert_);
	loop.push_back(new LeafNode(enStr));
	loop.splice(loop.end(), cond);
	loop.splice(loop.end(), body);
	result.push_back(new LoopNode(loop));

	//assert(!b) => f{b}
	Json::Value unary = createUnary(ctx["condition"], "!");
	assert_ = createExprStmt(createAssert(unary));
	code = "assert(!" + cond_str + ");stmt";
	enStr = encodeExt(code, assert_);
	result.push_back(new LeafNode(enStr));
	result.splice(result.end(), cond2);

	return result;
}

//do c while b => c; while b do c
list<TreeNode*> TreeRoot::doWhileStmt(Json::Value ctx, int depth)
{
	list<TreeNode*> result;
	list<TreeNode*> body = visit(ctx["body"], depth);
	result.splice(result.end(), body);
	list<TreeNode*> while_ = whileStmt(ctx, depth);
	result.splice(result.end(), while_);

	return result;
}

list<TreeNode*> TreeRoot::returnStmt(Json::Value ctx, int depth)
{
	list<TreeNode*> expr = visit(ctx["expression"], depth);
	string code = getCode(ctx);
	string enStr = encodeExt(code, ctx);
	list<TreeNode*> result = { new LeafNode(enStr) };
	result.splice(result.end(), expr);
	return result;
}

list<TreeNode*> TreeRoot::exprStmt(Json::Value ctx, int depth)
{
	list<TreeNode*> result = otherStmt(ctx, depth);
	list<TreeNode*> expr = visit(ctx["expression"], depth);
	result.splice(result.end(), expr);
	return result;
}

list<TreeNode*> TreeRoot::assignment(Json::Value ctx, int depth)
{
	list<TreeNode*> result = visit(ctx["rightHandSide"], depth);
	return result;
}

list<TreeNode*> TreeRoot::binaryOp(Json::Value ctx, int depth)
{
	list<TreeNode*> left = visit(ctx["leftExpression"], depth);
	list<TreeNode*> right = visit(ctx["rightExpression"], depth);
	left.splice(left.end(), right);
	return left;
}

list<TreeNode*> TreeRoot::unaryOp(Json::Value ctx, int depth)
{
	return visit(ctx["subExpression"], depth);
}

list<TreeNode*> TreeRoot::placeHolderStmt(Json::Value ctx, int depth)
{
	if (func["modifiers"].empty())
		return visit(func["body"], depth);
	Json::Value mod;
	func["modifiers"].removeIndex(0, &mod);
	return modifier(mod, depth);
}

list<TreeNode*> TreeRoot::otherStmt(Json::Value ctx, int depth)
{
	if (ctx["nodeType"].asString().find("Statement") == string::npos) {
		return list<TreeNode*>();
	}
	list<TreeNode*> result;
	string code = getCode(ctx);
	code = code + "stmt";
	string enStr = encode(code);
	result.push_back(new LeafNode(enStr));
	if (decodeSol.find(enStr) == decodeSol.end())
		decodeSol[enStr] = ctx;
	return result;
}

list<TreeNode*> TreeRoot::functionCall(Json::Value ctx, int depth)
{
	if (ctx["expression"]["nodeType"] == "Identifier" && ctx["expression"]["name"] == "assert")
		return visit(ctx["arguments"][0], depth);
	list<TreeNode*> result;
	string funcName = ctx["expression"]["name"].isNull() ? getCode(ctx["expression"]) : ctx["expression"]["name"].asString() + "(" + getParamStr(ctx["arguments"]) + ")"; //type Conversion function dont have name
	map<string, Json::Value>::iterator iter;
	if (depth == 0 || (iter = functionsMap.find(funcName)) == functionsMap.end()) {
		return list<TreeNode*>();
	};
	Json::Value function = iter->second;
	list<TreeNode*> temp;
	temp.splice(temp.end(), visit(function["returnParameters"], depth - 1));
	temp.splice(temp.end(), varDeclList(function["parameters"]["parameters"], ctx["arguments"], depth - 1));
	if (function["modifiers"].empty())
		temp.splice(temp.end(), visit(function["body"], depth - 1));
	else {
		Json::Value tempFunc, mod;
		tempFunc = func;
		function["modifiers"].removeIndex(0, &mod);
		temp.splice(temp.end(), modifier(mod, depth - 1));
		func = tempFunc;
	}

	string code = getCode(ctx);
	string enStr = encodeExt(code, ctx);
	result.push_back(new VarNode(enStr, temp));
	return result;
}

list<TreeNode*> TreeRoot::functionDef(Json::Value ctx, int depth)
{
	list<TreeNode*> result;
	list<Json::Value> mods;
	result.splice(result.end(), visit(ctx["parameters"], depth));
	result.splice(result.end(), visit(ctx["returnParameters"], depth));
	if (func["modifiers"].empty())
		result.splice(result.end(), visit(ctx["body"], depth));
	else {
		Json::Value mod;
		func["modifiers"].removeIndex(0, &mod);
		result.splice(result.end(), modifier(mod, depth));
	}
	return result;
}

list<TreeNode*> TreeRoot::parameterList(Json::Value ctx, int depth)
{
	list<TreeNode*> result;
	string code = getCode(ctx);
	code = code;
	string enStr = encode(code);
	result.push_back(new LeafNode(enStr));
	if (decodeSol.find(enStr) == decodeSol.end())
		decodeSol[enStr] = ctx;
	return result;
}

list<TreeNode*> TreeRoot::modifier(Json::Value ctx, int depth)
{
	string id = ctx["modifierName"]["referencedDeclaration"].asString();
	Json::Value mod = functionsMap[id];
	list<TreeNode*> result;
	result.splice(result.end(), varDeclList(mod["parametes"]["parameters"], ctx["arguments"], depth));
	if (mod["body"].isNull()) {
		placeHolderStmt(Json::Value(), depth);
	}
	result.splice(result.end(), visit(mod["body"], depth));
	return result;
}

list<TreeNode*> TreeRoot::varDeclList(Json::Value parameters, Json::Value initValue, int depth)
{
	list<TreeNode*> result;
	for (int i = 0; i < parameters.size(); ++i) {
		Json::Value varDeclStmt = createVarDeclStmt(parameters[i], initValue[i]);
		result.splice(result.end(), visit(varDeclStmt, depth));
	}
	return result;
}

string TreeRoot::encode(string code)
{
	if (encodeSol.find(code) != encodeSol.end())
		return encodeSol[code];
	int mod, div;
	string encode_str;
	mod = index % 26;
	div = index / 26;
	encode_str = static_cast<char>(97 + mod);
	while (div != 0) {
		mod = div % 26;
		mod = mod != 0 ? mod - 1 : mod;
		div = div / 26;
		string temp(1, static_cast<char>(97 + mod));
		encode_str = encode_str + "_" + temp;
	}
	index++;
	encodeSol[code] = encode_str;

	return encode_str;
}

string TreeRoot::encodeExt(string code, Json::Value ctx)
{
	string enStr = encode(code);
	if (decodeSol.find(enStr) == decodeSol.end())
		decodeSol[enStr] = ctx;
	return enStr;
}

string OrNode::DepthFS(bool isDepth)
{
	if (childrens.size() == 0)
		return "";

	string result = "(" + (*childrens.begin())->DepthFS(isDepth);
	for (auto i = next(childrens.begin()); i != childrens.end(); ++i)
		result += "|" + (*i)->DepthFS(isDepth);
	if (childrens.size() == 1)
		result += "|#";
	result += ")";
	return result;
}

expr OrNode::getExpr(context& c, solver& s)
{
	if (childrens.size() == 2)
		return childrens.front()->getExpr(c, s) + childrens.back()->getExpr(c, s);
	else if (childrens.size() == 1)
		return option(childrens.front()->getExpr(c, s));
	else throw "OrNode have worng number of child";

}

string LoopNode::DepthFS(bool isDepth)
{
	if (childrens.size() == 0)
		return "";
	string result = "(";
	for (auto i : childrens)
		result += i->DepthFS(isDepth);
	result += ")*";
	return result;
}

expr LoopNode::getExpr(context& c, solver& s)
{
	expr_vector vec(c);
	for (auto child : childrens)
		vec.push_back(child->getExpr(c, s));
	return concat(vec).loop(0, 3);
}

string SubNode::DepthFS(bool isDepth)
{
	if (childrens.size() == 0)
		return "";
	string result = "";
	for (auto i : childrens)
		result += i->DepthFS(isDepth);
	return result;
}

expr SubNode::getExpr(context& c, solver& s)
{
	expr_vector vec(c);
	for (auto child : childrens)
		vec.push_back(child->getExpr(c, s));
	return concat(vec);
}

/*string TreeNode::getValue()
{
	return DepthFS();
}
*/

string VarNode::DepthFS(bool isDepth)
{
	if (!isDepth)
		return "#" + value;
	if (childrens.size() == 0)
		return "";
	string result = "";
	for (auto i : childrens)
		result += i->DepthFS(isDepth);
	return result;
}

expr VarNode::getExpr(context& c, solver& s)
{	
	expr var = makeStringFunction(&c, value);
	expr_vector vec(c);

	for (auto child : childrens)
		vec.push_back(child->getExpr(c, s));
	s.add(in_re(var, concat(vec)));
	return to_re(c.string_val(value));
}

string FuncNode::DepthFS(bool isDepth)
{
	string result = "";
	for (auto i : children)
		result += i->DepthFS();
	return result;
}

expr_vector FuncNode::toZ3(EVisitor& visitor, solver& s)
{
	expr_vector result(s.ctx());
	ValType* type = getType(visitor.toJson(value));

	EVisitor newVisitor = visitor;
	newVisitor.resetVar();
	for (auto child : children) {
		expr_vector temp = child->toZ3(newVisitor, s);
		for (auto i : temp)
			result.push_back(i);
		if (newVisitor.toJson(child->getValue())["nodeType"].asString() == "Return")
			break;
	}
	if (type != NULL) {
		if (result.size() == 0)
			return result;
		expr funcVar = type->getVar(s.ctx(), value);
		expr return_ = funcVar == result[result.size() - 1];
		result.pop_back();
		result.push_back(return_);
		
	}

	return result;
}

expr_vector CondNode::toZ3(EVisitor& visitor, solver& s)
{
	expr_vector result(s.ctx());
	ANTLRInputStream input(value);
	SolidityLexer lexer(&input);
	CommonTokenStream tokens(&lexer);
	SolidityParser parser(&tokens);
	SolidityParser::ExpressionContext* tree = parser.expression();
	CalVisitor calVisitor(&s, &visitor, m);
	expr cond_expr = calVisitor.visitExpression(tree).as<expr>();
	result.push_back(cond_expr);
	return result;
}

expr_vector StmtNode::toZ3(EVisitor& visitor, solver& s)
{
	expr_vector result(s.ctx());
	expr exp = visitor.visit(visitor.toJson(value), s);
	if(exp.to_string() != "null")
		result.push_back(exp);

	return result;
}
