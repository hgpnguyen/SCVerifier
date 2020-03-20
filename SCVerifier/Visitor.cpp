#include "Visitor.h"
#include "utility.h"

antlrcpp::Any Visitor::visitStatement(SolidityParser::StatementContext* ctx)
{
	if (ctx->simpleStatement()) {
		return visitSimpleStatement(ctx->simpleStatement());
	}
	int size = ctx->getText().size();
	return ctx->getText().substr(0, size - 2) ;

}

antlrcpp::Any Visitor::visitSimpleStatement(SolidityParser::SimpleStatementContext* ctx)
{
	if (ctx->expressionStatement()) {
		return visitExpressionStatement(ctx->expressionStatement());
	}
	int size = ctx->getText().size();
	return ctx->getText().substr(0, size - 2);
}

antlrcpp::Any Visitor::visitExpressionStatement(SolidityParser::ExpressionStatementContext* ctx)
{
	return visitExpression(ctx->expression());
}

antlrcpp::Any Visitor::visitExpression(SolidityParser::ExpressionContext* ctx)
{
	string op;
	if (ctx->expression().size() == 2 && ((op = ctx->children[1]->getText()) == "=" || op == "+=" || op == "-=")) {
		if (op == "+=" || op == "-=")
			return string("a=a+n");
		string left = ctx->expression()[0]->getText();
		if (ctx->expression()[1]->expression().size() != 2)
			return ctx->getText();
		return generalizeExp(ctx->expression()[1], left) ? string("a=a+n") : ctx->getText();
	}
	return ctx->getText();
}

bool Visitor::generalizeExp(SolidityParser::ExpressionContext * ctx, string leftCode) {
	string text, temp;
	bool left, right;
	switch (ctx->expression().size())
	{
	case 1:
		if (ctx->functionCallArguments() || ctx->identifier())
			text = ctx->getText();
		else text = ctx->expression()[0]->getText();
		break;
	case 2:
		temp = ctx->children[1]->getText();
		if (temp == "[") {
			text = ctx->getText();
			break;
		}
		if (temp != "+" && temp != "-")
			return false;
		left = generalizeExp(ctx->expression()[0], leftCode);
		if (left)
			return true;
		right = generalizeExp(ctx->expression()[1], leftCode);
		return right;
	case 3:
		return false;
	default:
		if (!ctx->primaryExpression())
			return false;
		text = ctx->getText();
		break;
	}
	return text == leftCode ? true : false;
}

antlrcpp::Any CalVisitor::visitExpression(SolidityParser::ExpressionContext* ctx) {
	auto opConvert = getOpConvert();
	if (ctx->expression().size() == 2 && ctx->children[1]->accept(this).is<string>()) { // Binary Op
		expr left = ctx->expression()[0]->accept(this);
		expr right = ctx->expression()[1]->accept(this);
		string op = ctx->children[1]->getText();
		return opConvert[op](left, right);
	}
	else if (ctx->expression().size() == 1 && ctx->children[0]->accept(this).is<string>()) { // Unary Op
		expr subExp = ctx->expression()[0]->accept(this);
		string op = ctx->children[0]->getText();
		return opConvert["u" + op](subExp, s->ctx().int_val(0));
	}
	else if (ctx->primaryExpression())
		return ctx->primaryExpression()->accept(this);
	else throw "Wrong contranst";
}

antlrcpp::Any CalVisitor::visitPrimaryExpression(SolidityParser::PrimaryExpressionContext* ctx) {
	return ctx->children[0]->accept(this);
}

antlrcpp::Any CalVisitor::visitNumberLiteral(SolidityParser::NumberLiteralContext* ctx) {
	return ctx->children[0]->accept(this);
}

antlrcpp::Any CalVisitor::visitIdentifier(SolidityParser::IdentifierContext* ctx)
{
	assert(traceToCode.find(ctx->getText()) != traceToCode.end());
	expr var = visitor->visit(traceToCode[ctx->getText()], *s);
	if (var.to_string().find("temp") == string::npos)
		return var;
	else throw "ID not found";
}

antlrcpp::Any CalVisitor::visitTuppleExpression(SolidityParser::TupleExpressionContext* ctx) {
	throw "Wrong contrainst";
}
antlrcpp::Any CalVisitor::visitElementaryTypeNameExpression(SolidityParser::ElementaryTypeNameContext* ctx) {
	throw "Wrong contrainst";
}

antlrcpp::Any CalVisitor::visitTerminal(antlr4::tree::TerminalNode* ctx) {
	string text = ctx->getText();
	context* c = &s->ctx();
	switch (ctx->getSymbol()->getType())
	{
	case SolidityLexer::BooleanLiteral:
		return c->bool_val(text == "true");
	case SolidityLexer::DecimalNumber:
		return c->int_val(stoi(text));
	case SolidityLexer::HexNumber:
		return c->int_val(stoi(text, 0, 16));
	default:
		return text;
	}
}

expr EVisitor::visit(Json::Value code, solver& s, bool isLeft)
{
	typedef expr(EVisitor::* pfunc)(Json::Value, solver&s, bool);
	map<string, pfunc> switchCase;
	switchCase["ExpressionStatement"] = &EVisitor::exprStmt;
	switchCase["VariableDeclarationStatement"] = &EVisitor::varDeclStmt;
	switchCase["Return"] = &EVisitor::returnStmt;
	switchCase["VariableDeclaration"] = &EVisitor::varDecl;
	switchCase["Assignment"] = &EVisitor::assignment;
	switchCase["BinaryOperation"] = &EVisitor::binaryOp;
	switchCase["UnaryOperation"] = &EVisitor::unaryOp;
	switchCase["FunctionCall"] = &EVisitor::functionCall;
	switchCase["Identifier"] = &EVisitor::identifier;
	switchCase["Literal"] = &EVisitor::literal;
	switchCase["IndexAccess"] = &EVisitor::indexAccess;
	switchCase["MemberAccess"] = &EVisitor::memberAccess;
	string nodeType = code["nodeType"].asString();
	auto func = switchCase.find(nodeType) != switchCase.end() ? switchCase[nodeType] : &EVisitor::other;
	expr result = (this->*func)(code, s, isLeft);
	return result;
}

Json::Value EVisitor::toJson(string str)
{
	return decodeSol[str]; 
}

expr EVisitor::exprStmt(Json::Value code, solver& s, bool isLeft)
{
	return visit(code["expression"], s, isLeft);
}

expr EVisitor::varDeclStmt(Json::Value code, solver& s, bool isLeft)
{
	expr_vector result(s.ctx()), decls(s.ctx()), init(s.ctx());
	for (auto decl : code["declarations"]) {
		expr varDecl = visit(decl, s, isLeft);
		if (varDecl.to_string() == "null")
			return expr(s.ctx());
		decls.push_back(varDecl);
	}

	if (!code["initialValue"].isNull())
		if (code["initialValue"]["nodeType"] == "TupleExpression")
			init = tuppleExp(code["initialValue"], s);
		else 
			init.push_back(visit(code["initialValue"], s, isLeft));
	if (init.empty())
		return expr(s.ctx());
	else {
		if (decls.size() == init.size()) {
			cout << init[0].get_sort().name() << endl;
			for (int i = 0; i < decls.size(); ++i)
				result.push_back(decls[i] == init[i]);
		}
		else {
			
			if (decls[0].is_array()) {
				for (int i = 0; i < init.size(); ++i)
					result.push_back(select(decls[0], s.ctx().int_val(i)) == init[i]);
			}
		}
		if (result.size() >= 2)
			return mk_and(result);
		else return result[0];
	}
}

expr EVisitor::returnStmt(Json::Value code, solver& s, bool isLeft)
{
	return visit(code["expression"], s, isLeft);;
}

expr EVisitor::assignment(Json::Value code, solver& s, bool isLeft)
{
	string op = code["operator"].asString();
	expr right = visit(code["rightHandSide"], s, isLeft);
	expr result(s.ctx());
	if (op == "=") {
		expr left = visit(code["leftHandSide"], s, true);
		result = left == right;
	}
	else {
		expr leftOrig = visit(code["leftHandSide"], s, false);
		expr left = visit(code["leftHandSide"], s, true);
		result = op == "+=" ? left == leftOrig + right : left == leftOrig - right;
	}
	return result;
}

expr EVisitor::binaryOp(Json::Value code, solver& s, bool isLeft)
{
	auto op = getOpConvert();
	ValType* typeLeft = getType(code["leftExpression"]);
	ValType* typeRight = getType(code["rightExpression"]);
	string expOP = code["operator"].asString();
	if (typeRight.type == BYTES && (expOP == "<" || expOP == "<=" || expOP == ">" || expOP == ">=")) 
		expOP = "u" + expOP;

	expr left = visit(code["leftExpression"], s, isLeft);
	expr right = visit(code["rightExpression"], s, isLeft);

	pair<expr*, TypeInfo> pairL = { &left, typeLeft };
	pair<expr*, TypeInfo> pairR = { &right, typeRight };

	preCheck(pairL, pairR, expOP);
	expr result = op[expOP](left, right);
	return result;
}

expr EVisitor::unaryOp(Json::Value code, solver& s, bool isLeft)
{
	auto op = getOpConvert();
	expr sub = visit(code["subExpression"], s, isLeft);
	string expOP = code["operator"].asString();
	if (op.find("u" + expOP) == op.end())
		throw "New Unary OP: " + expOP;
	expr result = op["u" + expOP](sub, expr(s.ctx()));

	if (expOP == "++" || expOP == "--") {
		expr left = visit(code["subExpression"], s, true);
		result = left == result;
	}
	return result;
}

expr EVisitor::identifier(Json::Value code, solver& s, bool isLeft)
{
	string name = code["name"].asString();
	auto num = findVar(name);
	pair<TypeInfo, int>* var;
	string varname;
	TypeInfo type;
	switch(num){
	case 1: //local var
		var = &vars[prefix + name];
		varname = prefix + name ;
		break;
	case 2: //global var
		var = &Globalvars[currentContract + "." + name];
		varname = name;
		break;
	default: //cant find
		type = getType(code);
		varname = prefix + name;
		vars[varname] = { type, 0 };
		return getVar(varname + '0', type, s.ctx());
	}
	type = var->first;
	int num_ = isLeft ? ++var->second : var->second;
	varname += to_string(num_);
	return getVar(varname, type, s.ctx());
}

expr EVisitor::indexAccess(Json::Value code, solver& s, bool isLeft)
{
	expr baseExpr = visit(code["baseExpression"], s, false);
	expr index = visit(code["indexExpression"], s, isLeft);
	if (isLeft) {
		TypeInfo type = getType(code);
		string t = "temp" + to_string(tempIndex++);
		expr temp = s.ctx().constant(s.ctx().str_symbol(t.c_str()), baseExpr.get_sort().array_range());
		expr store_ = store(baseExpr, index, temp);
		expr newBaseExpr = visit(code["baseExpression"], s, true);
		s.add(newBaseExpr == store_);
		return temp;
	}
	else return select(baseExpr, index);

}

expr EVisitor::literal(Json::Value code, solver& s, bool isLeft)
{
	TypeInfo type = getType(code);
	string value = type.type == BYTES ? code["hexValue"].asString() : code["value"].asString();
	expr result = getVal(value, type, s.ctx());
	return result;
}

expr EVisitor::functionCall(Json::Value code, solver& s, bool isLeft)
{
	if (code["expression"]["nodeType"] == "Identifier" && code["expression"]["name"] == "assert")
		return visit(code["arguments"][0], s);
	string name = getCode(code, sourceCode);
	string varName = encode(name);
	TypeInfo type = getType(code);
	expr result(s.ctx());
	if (type.type != VOID)
		result = getVar(varName, type, s.ctx());
	else result = expr(s.ctx());

	return result;
}

expr EVisitor::varDecl(Json::Value code, solver& s, bool isLeft)
{
	string name = prefix + code["name"].asString();
	TypeInfo type;
	if (code["typeName"]["nodeType"] == "ElementaryTypeName")
		type = getType(code);
	else if (code["typeName"]["nodeType"] == "ArrayTypeName") {
		TypeInfo temp = getType(code["typeName"]["baseType"]);
		type = { ARRAY, temp.size, temp.type };
		vars[name] = { type, 0 };
		return getVar(name + '0', type, s.ctx());
	}
	else return expr(s.ctx());
	vars[name] = { type, 0 };
	return getVar(name + '0', type, s.ctx());
}

expr EVisitor::memberAccess(Json::Value code, solver& s, bool isLeft)
{
	string varName = getCode(code, sourceCode);
	varName = encode(varName);
	TypeInfo type = getType(code);
	auto var = Globalvars.find(currentContract + varName);
	int num;
	if (var == Globalvars.end()) {
		Globalvars[currentContract + varName] = { type, 0 };
		num = 0;
	}
	else num = isLeft ? ++var->second.second : var->second.second;
	varName += to_string(num);

	return getVar(varName, type, s.ctx());
}

expr EVisitor::other(Json::Value code, solver& s, bool isLeft)
{
	return expr(s.ctx());
}

expr_vector EVisitor::tuppleExp(Json::Value code, solver& s)
{
	expr_vector result(s.ctx());
	for (auto i : code["components"])
		result.push_back(visit(i, s));
	return result;
}



string EVisitor::encode(string code)
{
	if (encodeSol.find(code) != encodeSol.end())
		return encodeSol[code];
	return "temp" + to_string(tempIndex++);
}

int EVisitor::findVar(string name)
{	

	if (vars.find(prefix + name) != vars.end()) {
		return 1; //local var
	}
	else if (Globalvars.find(currentContract + "." + name) != Globalvars.end()) {
		return 2; //global var
	}
	return 3;// cant find
}

antlrcpp::Any MapVisitor::visitStatement(SolidityParser::StatementContext* ctx)
{

	if (ctx->simpleStatement()) {
		return visitSimpleStatement(ctx->simpleStatement()).as<bool>();
	}
	return false;

}

antlrcpp::Any MapVisitor::visitSimpleStatement(SolidityParser::SimpleStatementContext* ctx)
{
	return ctx->children[0]->accept(this).as<bool>();
}

antlrcpp::Any MapVisitor::visitVariableDeclarationStatement(SolidityParser::VariableDeclarationStatementContext* ctx)
{
	return false;
}

antlrcpp::Any MapVisitor::visitExpressionStatement(SolidityParser::ExpressionStatementContext* ctx)
{
	if (json["nodeType"] != "ExpressionStatement")
		return false;
	json = json["expression"];
	return ctx->expression()->accept(this);
}

antlrcpp::Any MapVisitor::visitExpression(SolidityParser::ExpressionContext* ctx)
{
	string op;
	if (ctx->expression().size() == 2 && ((op = ctx->children[1]->getText()) == "=" || op == "+=" || op == "-=")) {
		if (json["nodeType"] != "Assignment")
			return false;
		(*m)[ctx->expression(0)->getText()] = json["leftHandSide"];
		return true;
	}
	return false;
}
