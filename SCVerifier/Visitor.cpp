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
		if (right.is_bool())
			cout << "right is bool" << endl;
		if (left.is_const())
			cout << "left is const" << endl;
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
	string var_name = ctx->getText();
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
	switchCase["ExpressionStatment"] = &EVisitor::exprStmt;
	switchCase["Return"] = &EVisitor::returnStmt;
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

expr EVisitor::exprStmt(Json::Value code, bool isLeft)
{
	return visit(code["expression"], isLeft);
}

expr EVisitor::returnStmt(Json::Value code, bool isLeft)
{
	return visit(code["expression"], isLeft);;
}

expr EVisitor::assignment(Json::Value code, bool isLeft)
{
	expr left = visit(code["leftHandSide"], true);
	expr right = visit(code["rightHandSide"], isLeft);
	expr result = left == right;
	return result;
}

expr EVisitor::binaryOp(Json::Value code, bool isLeft)
{
	auto op = getOpConvert();
	expr left = visit(code["leftExpression"], isLeft);
	expr right = visit(code["rightExpression"], isLeft);
	expr result = op[code["operator"].asString()](left, right);
	return result;
}

expr EVisitor::unaryOp(Json::Value code, bool isLeft)
{
	auto op = getOpConvert();
	expr sub = visit(code["subExpression"], isLeft);
	expr result = op["u" + code["operator"].asString()](sub, expr(v->ctx));
	return result;
}

expr EVisitor::identifier(Json::Value code, bool isLeft)
{
	string name = code["name"].asString();
	if (vars.find(name) != vars.end()) {
		TypeInfo type = vars[name].first;
		int num = isLeft ? ++vars[name].second : vars[name].second;
		name = name + to_string(num);
		return getVar(name, type, v->ctx);
	}
	else {
		TypeInfo type = getType(code);
		vars[name] = { type, 0 };
		return getVar(name + '0', type, v->ctx);
	}
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
	string name = getCode(code, *v);
	string varName = encode(name, *v);
	TypeInfo type = getType(code);
	expr result = getVar(varName, type, *ctx);

	return expr(*ctx);
}

expr EVisitor::other(Json::Value code, bool isLeft)
{
	return expr(*ctx);
}



