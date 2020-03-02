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
		return opConvert["u" + op](subExp, c->int_val(0));
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
	string var_name = traceToCode[ctx->getText()];
	if (var_m.find(var_name) != var_m.end()) {
		auto type = var_m[var_name].first;
		var_name += to_string(var_m[var_name].second);
		switch (type.type) {
		case UINT:
		{
			return c->int_const(var_name.c_str());
		}
		case INT:
		{
			return c->int_const(var_name.c_str());
		}
		case BOOL:
		{
			return c->bool_const(var_name.c_str());
		}
		case ADDRESS:
		{
			return c->bv_const(var_name.c_str(), 160);
		}
		case BYTES:
		{
			return c->bv_const(var_name.c_str(), type.size);
		}
		default:
		{
			throw "Wrong Type: ";
		}
		}
	}
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

expr EVisitor::visit(Json::Value code, bool isLeft)
{
	typedef expr(EVisitor::* pfunc)(Json::Value, bool);
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
	string nodeType = code["nodeType"].asString();
	auto func = switchCase.find(nodeType) != switchCase.end() ? switchCase[nodeType] : &EVisitor::other;
	expr result = (this->*func)(code, isLeft);
	return result;
}

Json::Value EVisitor::toJson(string str)
{
	return v->decodeSol[str]; 
}

context* EVisitor::getContext()
{
	return &v->ctx;
}

expr EVisitor::exprStmt(Json::Value code, bool isLeft)
{
	return visit(code["expression"], isLeft);
}

expr EVisitor::varDeclStmt(Json::Value code, bool isLeft)
{
	expr_vector result(v->ctx), decls(v->ctx), init(v->ctx);
	for (auto decl : code["declarations"]) {
		expr varDecl = visit(decl, isLeft);
		decls.push_back(varDecl);
	}

	if (!code["initialValue"].isNull())
		if (code["initialValue"]["nodeType"] == "TupleExpression")
			init = tuppleExp(code["initialValue"]);
		else
			init.push_back(visit(code["initialValue"], isLeft));
	if (init.empty())
		return expr(v->ctx);
	else {
		assert(decls.size() == init.size());
		for (int i = 0; i < decls.size(); ++i)
			result.push_back(decls[i] == init[i]);
		if (result.size() >= 2)
			return mk_and(result);
		else return result[0];
	}
}

expr EVisitor::returnStmt(Json::Value code, bool isLeft)
{
	return visit(code["expression"], isLeft);;
}

expr EVisitor::assignment(Json::Value code, bool isLeft)
{
	string op = code["operator"].asString();
	expr right = visit(code["rightHandSide"], isLeft);
	expr result(v->ctx);
	if (op == "=") {
		expr left = visit(code["leftHandSide"], true);
		result = left == right;
	}
	else {
		expr leftOrig = visit(code["leftHandSide"], false);
		expr left = visit(code["leftHandSide"], true);
		result = op == "+=" ? left == leftOrig + right : left == leftOrig - right;
	}
	return result;
}

expr EVisitor::binaryOp(Json::Value code, bool isLeft)
{
	auto op = getOpConvert();
	TypeInfo typeLeft = getType(code["leftExpression"]);
	TypeInfo typeRight = getType(code["rightExpression"]);
	string expOP = code["operator"].asString();
	if (typeRight.type == BYTES && (expOP == "<" || expOP == "<=" || expOP == ">" || expOP == ">=")) 
		expOP = "u" + expOP;

	expr left = visit(code["leftExpression"], isLeft);
	expr right = visit(code["rightExpression"], isLeft);

	pair<expr*, TypeInfo> pairL = { &left, typeLeft };
	pair<expr*, TypeInfo> pairR = { &right, typeRight };

	preCheck(pairL, pairR, expOP);
	expr result = op[expOP](left, right);
	return result;
}

expr EVisitor::unaryOp(Json::Value code, bool isLeft)
{
	auto op = getOpConvert();
	expr sub = visit(code["subExpression"], isLeft);
	string expOP = code["operator"].asString();
	expr result = op["u" + expOP](sub, expr(v->ctx));

	if (expOP == "++" || expOP == "--") {
		expr left = visit(code["subExpression"], true);
		result = left == result;
	}
	return result;
}

expr EVisitor::identifier(Json::Value code, bool isLeft)
{
	string name = code["name"].asString();
	auto var = findVar(name);
	if (var != NULL) {
		TypeInfo type = var->first;
		int num = isLeft ? ++var->second : var->second;
		name = name + to_string(num);
		return getVar(name, type, v->ctx);
	}
	else {
		TypeInfo type = getType(code);
		string newVar = prefix + name;
		vars[newVar] = { type, 0 };
		return getVar(newVar + '0', type, v->ctx);
	}
}

expr EVisitor::indexAcess(Json::Value code, bool isLeft)
{
	expr baseExpr = visit(code["baseExpression"], isLeft);
	expr index = visit(code["indexExpression"], isLeft);
	expr result = select(baseExpr, index);
	return result;
}

expr EVisitor::literal(Json::Value code, bool isLeft)
{
	TypeInfo type = getType(code);
	string value = type.type == BYTES ? code["hexValue"].asString() : code["value"].asString();
	expr result = getVal(value, type, v->ctx);
	return result;
}

expr EVisitor::functionCall(Json::Value code, bool isLeft)
{
	if (code["expression"]["nodeType"] == "Identifier" && code["expression"]["name"] == "assert")
		return visit(code["arguments"][0]);
	string name = getCode(code, *v);
	string varName = encode(name, *v);
	TypeInfo type = getType(code);
	expr result(v->ctx);
	if (type.type != VOID)
		result = getVar(varName, type, v->ctx);
	else result = expr(v->ctx);

	return result;
}

expr EVisitor::varDecl(Json::Value code, bool isLeft)
{
	string name = prefix + code["name"].asString();
	TypeInfo type = getType(code);
	vars[name] = { type, 0 };
	return getVar(name + '0', type, v->ctx);
}

expr EVisitor::other(Json::Value code, bool isLeft)
{
	return expr(v->ctx);
}

expr_vector EVisitor::tuppleExp(Json::Value code)
{
	expr_vector result(v->ctx);
	for (auto i : code["components"])
		result.push_back(visit(i));
	return result;
}

pair<TypeInfo, int>* EVisitor::findVar(string name)
{	

	if (vars.find(prefix + name) != vars.end()) {
		return &vars[prefix + name];
	}
	else if (Globalvars.find(v->currentContract + "." + name) != Globalvars.end()) {
		return &Globalvars[v->currentContract + "." + name];
	}
	return nullptr;
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
		(*m)[ctx->expression(0)->getText()] = getCode(json["leftHandSide"], sourceCode);
		return true;
	}
	return false;
}
