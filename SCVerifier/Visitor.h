#pragma once
#ifndef VISITOR_H
#define VISITOR_H

#include <stdio.h>
#include <iostream>
#include "antlr4-runtime.h"
#include "SolidityBaseVisitor.h"
#include "c++/z3++.h"
#include "json/json.h"



using namespace std;
using namespace z3;

enum Type { UINT, INT, BOOL, ADDRESS, BYTES, STRING, VOID, ARRAY };

struct TypeInfo {
	Type type;
	unsigned int size;
	Type type2 = VOID;
};

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
	map<string, string> traceToCode;
	
public:
	CalVisitor(context* ctx, map < string, pair<TypeInfo, int>> var_m, map<string, string> traceToCode) {
		c = ctx;
		this->var_m = var_m;
		this->traceToCode = traceToCode;
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
	string prefix;
	map < string, pair<TypeInfo, int>> vars;
	static map < string, pair<TypeInfo, int>> Globalvars;
public:

	EVisitor(Verifier& v, map < string, pair<TypeInfo, int>>& vars, string prefix) {
		this->v = &v;
		this->vars = vars;
		this->prefix = prefix;
	}

	expr visit(Json::Value code, bool isLeft = false);
	map < string, pair<TypeInfo, int>> getVars() { return vars; }
	Verifier* getVer() { return v; }
	Json::Value toJson(string str);
	context* getContext();
	static void addGlobalVar(string name, pair<TypeInfo, int > var) { Globalvars[name] = var; }

private:
	expr exprStmt(Json::Value, bool isLeft = false);
	expr varDeclStmt(Json::Value, bool isLeft = false);
	expr returnStmt(Json::Value, bool isLeft = false);
	expr assignment(Json::Value, bool isLeft = false);
	expr binaryOp(Json::Value, bool isLeft = false);
	expr unaryOp(Json::Value code, bool isLeft = false);
	expr identifier(Json::Value code, bool isLeft = false);
	expr indexAcess(Json::Value code, bool isLeft = false);
	expr literal(Json::Value code, bool isLeft = false);
	expr functionCall(Json::Value code, bool isLeft = false);
	expr varDecl(Json::Value code, bool isLeft = false);
	expr other(Json::Value code, bool isLeft = false);
	expr_vector tuppleExp(Json::Value code);

	pair<TypeInfo, int>* findVar(string name);

};

class MapVisitor : SolidityBaseVisitor {
	Json::Value json;
	map<string, string>* m;
	string sourceCode;
public:
	MapVisitor(Json::Value json, map<string, string>& m, string sourceCode) {
		this->json = json;
		this->m = &m;
		this->sourceCode = sourceCode;
	}

	antlrcpp::Any visitStatement(SolidityParser::StatementContext* ctx);
	antlrcpp::Any visitSimpleStatement(SolidityParser::SimpleStatementContext* ctx);
	antlrcpp::Any visitVariableDeclarationStatement(SolidityParser::VariableDeclarationStatementContext* ctx);
	antlrcpp::Any visitExpressionStatement(SolidityParser::ExpressionStatementContext* ctx);
	antlrcpp::Any visitExpression(SolidityParser::ExpressionContext* ctx);

};
#endif //!VISITOR_H