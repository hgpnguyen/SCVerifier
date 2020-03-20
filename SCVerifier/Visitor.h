#pragma once
#ifndef VISITOR_H
#define VISITOR_H

#include <stdio.h>
#include <iostream>
#include "antlr4-runtime.h"
#include "SolidityBaseVisitor.h"
#include "c++/z3++.h"
#include "json/json.h"
#include "type.h"


using namespace std;
using namespace z3;

struct Verifier;
class EVisitor;
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
	solver* s;
	EVisitor* visitor;
	map<string, Json::Value> traceToCode;
	
public:
	CalVisitor(solver* s, EVisitor* visitor, map<string, Json::Value> traceToCode) {
		this->s = s;
		this->visitor = visitor;
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
	string prefix;
	string currentContract;
	int tempIndex = 0; // To encode Function Call
	
	map <string, string> encodeSol; //To encode Function Call
	map < string, pair<Type, int>> vars;
	map <string, Json::Value> decodeSol;
	
	static map < string, pair<Type*, int>> Globalvars;
public:

	EVisitor(string prefix, map<string, Json::Value>& decodeSol, map<string, string>& encodeSol, string currentContract) {
		this->prefix = prefix;
		this->decodeSol = decodeSol;
		this->encodeSol = encodeSol;
		this->currentContract = currentContract;
	}

	expr visit(Json::Value code, solver& s, bool isLeft = false);
	map < string, pair<Type, int>> getVars() { return vars; }
	Json::Value toJson(string str);
	static void addGlobalVar(string name, pair<Type*, int > var) { Globalvars[name] = var; }
	void resetVar() { vars.clear(); }

private:
	expr exprStmt(Json::Value, solver& s, bool isLeft = false);
	expr varDeclStmt(Json::Value, solver& s, bool isLeft = false);
	expr returnStmt(Json::Value, solver& s, bool isLeft = false);
	expr assignment(Json::Value, solver& s, bool isLeft = false);
	expr binaryOp(Json::Value, solver& s, bool isLeft = false);
	expr unaryOp(Json::Value code, solver& s, bool isLeft = false);
	expr identifier(Json::Value code, solver& s, bool isLeft = false);
	expr indexAccess(Json::Value code, solver& s, bool isLeft = false);
	expr literal(Json::Value code, solver& s, bool isLeft = false);
	expr functionCall(Json::Value code, solver& s, bool isLeft = false);
	expr varDecl(Json::Value code, solver& s, bool isLeft = false);
	expr memberAccess(Json::Value code, solver& s, bool isLeft = false);
	expr other(Json::Value code, solver& s, bool isLeft = false);
	expr_vector tuppleExp(Json::Value code, solver& s);



	string encode(string code);
	int findVar(string name);

};

class MapVisitor : SolidityBaseVisitor {
	Json::Value json;
	map<string, Json::Value>* m;
public:
	MapVisitor(Json::Value json, map<string, Json::Value>& m) {
		this->json = json;
		this->m = &m;
	}

	antlrcpp::Any visitStatement(SolidityParser::StatementContext* ctx);
	antlrcpp::Any visitSimpleStatement(SolidityParser::SimpleStatementContext* ctx);
	antlrcpp::Any visitVariableDeclarationStatement(SolidityParser::VariableDeclarationStatementContext* ctx);
	antlrcpp::Any visitExpressionStatement(SolidityParser::ExpressionStatementContext* ctx);
	antlrcpp::Any visitExpression(SolidityParser::ExpressionContext* ctx);

};
#endif //!VISITOR_H