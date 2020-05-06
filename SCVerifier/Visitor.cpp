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
	else throw std::exception("Wrong contranst");
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
	type = getType(traceToCode[ctx->getText()]);
	if (var.to_string().substr(0, 4) != "temp")
		return var;
	else throw std::exception("ID not found");
}

antlrcpp::Any CalVisitor::visitTuppleExpression(SolidityParser::TupleExpressionContext* ctx) {
	throw std::exception("Wrong contrainst");
}
antlrcpp::Any CalVisitor::visitElementaryTypeNameExpression(SolidityParser::ElementaryTypeNameContext* ctx) {
	throw std::exception("Wrong contrainst");
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
	case SolidityLexer::MaxKeyword:
		if (typeid(*type) == typeid(UInt))
			return dynamic_cast<UInt*>(type)->getMax(*c);
		else if (typeid(*type) == typeid(Int))
			return dynamic_cast<Int*>(type)->getMax(*c);
		else throw std::exception("Wrong type for Max");

	case SolidityLexer::MinKeyword:
		
		if (typeid(*type) == typeid(UInt)) 
			return dynamic_cast<UInt*>(type)->getMin(*c);
		else if (typeid(*type) == typeid(Int))
			return dynamic_cast<Int*>(type)->getMin(*c);

		else throw std::exception("Wrong type for Min");
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
	switchCase["ParameterList"] = &EVisitor::paraList;
	switchCase["TupleExpression"] = &EVisitor::tupleExp;
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
		else if (code["initialValue"]["typeDescriptions"]["typeString"].asString().substr(0, 5) != "tuple")
			init.push_back(visit(code["initialValue"], s, isLeft));
	if (init.empty())
		return expr(s.ctx());
	else {
		if (decls.size() == init.size()) {
			for (int i = 0; i < decls.size(); ++i) {
				try {
					result.push_back(decls[i] == init[i]);
				}
				catch (z3::exception e){

				}
			}
		}
		else {
			
			if (decls[0].is_array()) {
				for (int i = 0; i < init.size(); ++i)
					result.push_back(select(decls[0], s.ctx().int_val(i)) == init[i]);
			}
		}
		if (result.size() >= 2)
			return mk_and(result);
		else if(result.size() == 1) return result[0];
		return expr(s.ctx());
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
	ValType* type = getType(code);
	pair<expr*, ValType*> para = { &right, type };
	if (type != NULL && (typeid(*type) == typeid(UInt) || typeid(*type) == typeid(Int)) && right.is_bv())
		bv2int(para);
	else if (type != NULL && typeid(*type) != typeid(UInt) && typeid(*type) != typeid(Int) && right.is_int())
		int2Bv(para);
	expr result(s.ctx());
	if (op == "=") {
		expr left = visit(code["leftHandSide"], s, true);
		if (left.to_string() == "null" || right.to_string() == "null")
			throw std::exception("Left or Right is NULL");
		result = left == right;
	}
	else {
		expr leftOrig = visit(code["leftHandSide"], s, false);
		expr left = visit(code["leftHandSide"], s, true);
		if (left.to_string() == "null" || right.to_string() == "null")
			throw std::exception("Left or Right is NULL");
		result = op == "+=" ? left == leftOrig + right : left == leftOrig - right;
	}
	return result;
}

expr EVisitor::binaryOp(Json::Value code, solver& s, bool isLeft)
{
	auto op = getOpConvert();
	ValType* typeLeft = getType(code["leftExpression"]);
	ValType* typeRight = getType(code["rightExpression"]);
	ValType* type = getType(code);
	string expOP = code["operator"].asString();
	if (typeid(*typeRight) == typeid(Byte) && (expOP == "<" || expOP == "<=" || expOP == ">" || expOP == ">=")) 
		expOP = "u" + expOP;

	expr left = visit(code["leftExpression"], s, isLeft);
	expr right = visit(code["rightExpression"], s, isLeft);


	pair<expr*, ValType*> pairL = { &left, typeLeft };
	pair < expr*, ValType*> pairR = { &right, typeRight };

	
	preCheck(pairL, pairR, expOP);
	expr result = op[expOP](left, right);
	pair<expr*, ValType*> re = { &result, type };
	misMatch(re);
	return result;
}

expr EVisitor::unaryOp(Json::Value code, solver& s, bool isLeft)
{
	auto op = getOpConvert();
	expr sub = visit(code["subExpression"], s, isLeft);
	string expOP = code["operator"].asString();
	if (op.find("u" + expOP) == op.end())
		throw std::exception("New Unary OP: ");
	expr result = op["u" + expOP](sub, expr(s.ctx()));

	if (expOP == "++" || expOP == "--") {
		expr left = visit(code["subExpression"], s, true);
		s.add(left == result);
		result = code["prefix"].asBool() ? left : sub; // ++a or a++
	}
	return result;
}

expr EVisitor::identifier(Json::Value code, solver& s, bool isLeft)
{

	string name = code["name"].asString();
	string id = code["referencedDeclaration"].asString();
	auto num = findVar(id);
	pair<Type*, int>* var;
	string varname;
	Type* type;
	switch(num){
	case 1: //local var
		var = &vars[id];
		varname = prefix + name ;
		break;
	case 2: //global var
		var = &Globalvars[id];
		varname = name;
		if (init.find(varname) == init.end()) {
			initCondVar(var->first->getVar(s.ctx(), varname + to_string(var->second)), s, var->first);
			init.insert(varname);
		}
		break;
	default: //cant find
		type = getType(code);
		if (type == NULL)
			return expr(s.ctx());
		varname = prefix + name;
		vars[id] = { type, 0 };
		expr newVar = type->getVar(s.ctx(), varname + '0');
		initCondVar(newVar, s, type);
		init.insert(varname);
		return newVar;
	}
	type = var->first;
	int num_ = isLeft ? ++var->second : var->second;

	varname += to_string(num_);

	return type->getVar(s.ctx(), varname);
}

expr EVisitor::indexAccess(Json::Value code, solver& s, bool isLeft)
{
	expr baseExpr = visit(code["baseExpression"], s, false);
	expr index = visit(code["indexExpression"], s, false);
	if (index.to_string() == "null")
		throw std::exception("Index is null");
	if (isLeft) {
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
	ValType* type = getType(code);
	string value = typeid(*type) == typeid(Byte) ? code["hexValue"].asString() : code["value"].asString();
	expr result = type->getVal(s.ctx(), value);
	return result;
}

expr EVisitor::functionCall(Json::Value code, solver& s, bool isLeft)
{
	if (code["expression"]["nodeType"] == "Identifier" && (code["expression"]["name"] == "assert" || code["expression"]["name"] == "require"))
		return visit(code["arguments"][0], s);
	if (code["kind"].asString() == "structConstructorCall") {
		Type* type = getAllType(code);
		if (typeid(*type) != typeid(Struct))
			throw std::exception("Some thing worng or cant find Struct");
		Struct* strucT = dynamic_cast<Struct*>(type);
		expr_vector vec(s.ctx());
		for (auto arg : code["arguments"])
			vec.push_back(visit(arg, s, false));
		return strucT->getStruct(s.ctx())(vec);
	}
	string name = getCode(code, sourceCode);
	string varName = encode(name);
	Type* type = getAllType(code);
	expr result(s.ctx());
	if (type != NULL)
		result = type->getVar(s.ctx(), varName);
	else return expr(s.ctx());

	if (init.find(varName) == init.end()) {
		init.insert(varName);
		initCondVar(result, s, type);
	}

	return result;
}

expr EVisitor::varDecl(Json::Value code, solver& s, bool isLeft)
{
	string name = prefix + code["name"].asString();
	Type* type;
	if (!code["typeName"].isNull())
		type = getVarDeclType(code["typeName"], s, currentContract);
	else type = getAllType(code);
	if (type == NULL)
		return expr(s.ctx()); //User Define Type
	vars[code["id"].asString()] = { type, 0 };
	expr newVar = type->getVar(s.ctx(), name + '0');
	initCondVar(newVar, s, type);
	init.insert(name);
	return newVar;
}

expr EVisitor::memberAccess2(Json::Value code, solver& s, bool isLeft)
{
	string varName = getCode(code, sourceCode);
	ValType* type = getType(code);
	auto var = Globalvars.find(currentContract + varName);
	int num;
	if (var == Globalvars.end()) {
		Globalvars[currentContract + varName] = { type, 0 };
		num = 0;
	}
	else num = isLeft ? ++var->second.second : var->second.second;
	string newName = varName + to_string(num);
	expr var_ = type->getVar(s.ctx(), newName);
	if (init.find(varName) == init.end()) {
		initCondVar(var_, s, type);
		init.insert(varName);
	}

	return var_;
}

expr EVisitor::memberAccess(Json::Value code, solver& s, bool isLeft)
{
	context& c = s.ctx();
	
	Type* type = getAllType(code["expression"]);
	expr expression = visit(code["expression"], s, false);
	if(type == NULL || expression.to_string() == "null")
		return memberAccess2(code, s, isLeft);
	if(typeid(*type) != typeid(Struct) || !expression.get_sort().is_datatype())
		return memberAccess2(code, s, isLeft);
	Struct* structType = dynamic_cast<Struct*>(type);
	expr memAccess = structType->getMem(s.ctx(), code["memberName"].asString(), expression);
	if (isLeft) {
		Type* assignType = getAllType(code);
		expr temp = assignType->getVar(s.ctx(), "temp" + to_string(tempIndex++));
		expr newValue = structType->getNewStruct(s.ctx(), code["memberName"].asString(), temp, expression);
		expr newStruct = visit(code["expression"], s, true);
		s.add(newStruct == newValue);
		return temp;
	}

	return memAccess;
}

expr EVisitor::paraList(Json::Value code, solver& s, bool isLeft)
{
	for (auto para : code["parameters"])
		visit(para, s, isLeft);
	return expr(s.ctx());
}

expr EVisitor::tupleExp(Json::Value code, solver& s, bool isLeft)
{
	expr result = visit(code["components"][0], s, isLeft);
	return result;
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



void EVisitor::initCondVar(expr var, solver& s, Type* type)
{
	context& c = s.ctx();
	if (typeid(*type) == typeid(UInt)) {
		UInt* u = dynamic_cast<UInt*>(type);
		expr cond = var >= u->getMin(c) && var <= u->getMax(c);
		s.add(cond);
	}else if (typeid(*type) == typeid(Int)) {
		Int* i = dynamic_cast<Int*>(type);
		expr cond = var >= i->getMin(c) && var <= i->getMax(c);
		s.add(cond);
	}
	else if (typeid(*type) == typeid(Struct)) {
		Struct* strt = dynamic_cast<Struct*>(type);
		func_decl_vector vec(c);
		strt->getFuncVec(vec);
		vector<pair<string, Type*>> listType = strt->getListType();
		for (int i = 0; i < vec.size(); ++i)
			initCondVar(vec[i](var), s, listType[i].second);
	}
}

string EVisitor::encode(string code)
{
	if (encodeSol.find(code) != encodeSol.end())
		return encodeSol[code];
	string temp = "temp" + to_string(tempIndex++);
	encodeSol[code] = temp;
	return temp;
}

int EVisitor::findVar(string name)
{	

	if (vars.find(name) != vars.end()) {
		return 1; //local var
	}
	else if (Globalvars.find(name) != Globalvars.end()) {
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
	if (json["nodeType"] != "ExpressionStatement" || json["expression"]["nodeType"] != "Assignment")
		return false;
	json = json["expression"];
	return ctx->expression()->accept(this);
}

antlrcpp::Any MapVisitor::visitExpression(SolidityParser::ExpressionContext* ctx)
{
	string op;
	if (ctx->expression().size() == 2 && ((op = ctx->children[1]->getText()) == json["operator"].asString() || op == "=")) {
		bool left = mapExpression(ctx->expression()[0], json["leftHandSide"]);
		bool right = mapExpression(ctx->expression()[1], json["rightHandSide"]);
		return left && right;
	}
	return false;
}

bool MapVisitor::mapExpression(SolidityParser::ExpressionContext* ctx, Json::Value ast)
{

	if (ctx->primaryExpression()) {
		return primaryExpression(ctx->primaryExpression(), ast);
	}

	if (ctx->expression().size() == 2 && ast["nodeType"] == "BinaryOperation" && (ctx->children[1]->getText() == ast["operator"].asString()) ) {
		return mapExpression(ctx->expression()[0], ast["leftExpression"]) && mapExpression(ctx->expression()[1], ast["rightExpression"]);
	}
	if (ctx->expression().size() == 1 && ast["nodeType"] == "UnaryOperation" && (ctx->children[0]->getText() == ast["operator"].asString()))
		return mapExpression(ctx->expression()[0], ast["subExpression"]);


	return false;
}

bool MapVisitor::checkCompat(string id, Json::Value ast)
{
	if (type.find(id) == type.end())
		throw std::exception("Missing type decl for var: ");
	if (type[id] != "expr" && ast["typeDescriptions"]["typeString"].asString().find(type[id]) == string::npos) //check type compatitlity
		return false;
	if (type[id] == "expr" && m->find(id) == m->end()) //type Expr for all kind of expression
		return true;
	if (m->find(id) != m->end() && getCode((*m)[id], sourceCode) == getCode(ast, sourceCode)) //check if the var already assignen
		return true;
	if (ast["nodeType"] != "BinaryOperation" && ast["nodeType"] != "UnaryOperation" && m->find(id) == m->end())
		return true;
	return false;
}

bool MapVisitor::primaryExpression(SolidityParser::PrimaryExpressionContext* ctx, Json::Value ast)
{
	string text = ctx->getText();
	if (ctx->identifier()) {
		bool result = checkCompat(text, ast);
		if(result && m->find(text) == m->end())
			(*m)[text] = ast;
		return result;
	}
	return text == getCode(ast, sourceCode);
}
