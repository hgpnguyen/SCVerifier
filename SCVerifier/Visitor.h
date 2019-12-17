#pragma once

#include "antlr4-runtime.h"
#include "SolidityBaseVisitor.h"

using namespace std;

class Visitor : SolidityBaseVisitor {
	antlrcpp::Any global = NULL;
public:
	antlrcpp::Any visitStatement(SolidityParser::StatementContext *ctx);
	antlrcpp::Any visitSimpleStatement(SolidityParser::SimpleStatementContext* ctx);
	antlrcpp::Any visitExpressionStatement(SolidityParser::ExpressionStatementContext* ctx);
	antlrcpp::Any visitExpression(SolidityParser::ExpressionContext* ctx);
	bool generalizeExp(SolidityParser::ExpressionContext* ctx, string leftCode);
	string processText(string text);
};