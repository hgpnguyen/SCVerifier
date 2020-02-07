#pragma once
#ifndef VISITOR_H
#define VISITOR_H

#include <stdio.h>
#include <iostream>
#include "antlr4-runtime.h"
#include "SolidityBaseVisitor.h"
#include "c++/z3++.h"
#include "verifier.h"


using namespace std;
using namespace z3;

struct TypeInfo;
struct Verifier;
class Visitor : SolidityBaseVisitor {
	antlrcpp::Any global = NULL;
public:
	antlrcpp::Any visitStatement(SolidityParser::StatementContext *ctx);
	antlrcpp::Any visitSimpleStatement(SolidityParser::SimpleStatementContext* ctx);
	antlrcpp::Any visitExpressionStatement(SolidityParser::ExpressionStatementContext* ctx);
	antlrcpp::Any visitExpression(SolidityParser::ExpressionContext* ctx);
	bool generalizeExp(SolidityParser::ExpressionContext* ctx, string leftCode);
};

class CalVisitor : SolidityBaseVisitor {
	context* c;
	map < string, pair<TypeInfo, int>> var_m;
	
public:
	CalVisitor(context* ctx, map < string, pair<TypeInfo, int>> var_m) {
		c = ctx;
		this->var_m = var_m;
	}

	antlrcpp::Any visitExpression(SolidityParser::ExpressionContext* ctx);
	antlrcpp::Any visitPrimaryExpression(SolidityParser::PrimaryExpressionContext* ctx);
	antlrcpp::Any visitNumberLiteral(SolidityParser::NumberLiteralContext* ctx);
	antlrcpp::Any visitIdentifier(SolidityParser::IdentifierContext* ctx);
	antlrcpp::Any visitTuppleExpression(SolidityParser::TupleExpressionContext* ctx);
	antlrcpp::Any visitElementaryTypeNameExpression(SolidityParser::ElementaryTypeNameContext* ctx);

	antlrcpp::Any visitTerminal(antlr4::tree::TerminalNode* ctx);
};

class EVisitor {
	Verifier* v;
	map<string, string> encodeSol;
	map < string, pair<TypeInfo, int>> vars;
	context* ctx;
public:
	EVisitor(Verifier& v, map < string, pair<TypeInfo, int>>& vars) {
		this->v = &v;
		this->vars = vars;
	}

	expr visit(Json::Value code, bool isLeft = false);
private:
	expr exprStmt(Json::Value, bool isLeft = false);
	expr returnStmt(Json::Value, bool isLeft = false);
	expr assignment(Json::Value, bool isLeft = false);
	expr binaryOp(Json::Value, bool isLeft = false);
	expr unaryOp(Json::Value code, bool isLeft = false);
	expr identifier(Json::Value code, bool isLeft = false);
	expr literal(Json::Value code, bool isLeft = false);
	expr functionCall(Json::Value code, bool isLeft = false);
	expr other(Json::Value code, bool isLeft = false);



};
#endif //!VISITOR_H