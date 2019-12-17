#include "Visitor.h"

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
