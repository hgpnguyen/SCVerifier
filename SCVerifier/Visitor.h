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
ValType* getType(Json::Value exp);

class Visitor : SolidityBaseVisitor {
	antlrcpp::Any global = NULL;
	map<string, string> type;
public:
	antlrcpp::Any visitStatement(SolidityParser::StatementContext *ctx);
	antlrcpp::Any visitSimpleStatement(SolidityParser::SimpleStatementContext* ctx);
	antlrcpp::Any visitExpressionStatement(SolidityParser::ExpressionStatementContext* ctx);
	antlrcpp::Any visitExpression(SolidityParser::ExpressionContext* ctx);
	antlrcpp::Any visitTypeDecl(SolidityParser::TypeDeclContext* ctx) { type[ctx->identifier()->getText()] = ctx->elementaryTypeName()->getText(); return NULL; }
	map<string, string> getType() { return type; }
	bool generalizeExp(SolidityParser::ExpressionContext* ctx, string leftCode);
};

class CalVisitor : SolidityBaseVisitor {
	solver* s;
	EVisitor* visitor;
	map<string, Json::Value> traceToCode;
	ValType* type;
	
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
	int tempIndex = 0; // To encode Function Call
	
	map <string, string> encodeSol; //To encode Function Call
	map < string, pair<Type*, int>> vars;
	map <string, Json::Value> decodeSol;
	unordered_set<string> init; //Use to init Globalvars in each function
	
	static map < string, pair<Type*, int>> Globalvars;
public:

	EVisitor(string prefix, map<string, Json::Value>& decodeSol, map<string, string>& encodeSol) {
		this->prefix = prefix;
		this->decodeSol = decodeSol;
		this->encodeSol = encodeSol;
	}

	expr visit(Json::Value code, solver& s, bool isLeft = false);
	map < string, pair<Type*, int>> getVars() { return vars; }
	Json::Value toJson(string str);
	static void addGlobalVar(string name, pair<Type*, int > var) { Globalvars[name] = var; }
	static pair<Type*, int > findGlobalVar(string name) { if (Globalvars.find(name) != Globalvars.end()) return Globalvars[name]; else return { NULL, -1 }; }
	void resetVar() { vars.clear(); }
	static void resetGlobalvar() { Globalvars.clear(); }
	static void resetGlobalVarIndex();

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
	expr paraList(Json::Value code, solver& s, bool isLeft = false);
	expr tupleExp(Json::Value code, solver& s, bool isLeft = false);
	expr conditional(Json::Value code, solver& s, bool isLeft = false);
	expr other(Json::Value code, solver& s, bool isLeft = false);
	expr_vector tuppleExp(Json::Value code, solver& s, bool isLeft = false);



	void initCondVar(expr var, solver& s, Type* type);
	string encode(string code);
	int findVar(string name);
	expr memberAccess2(Json::Value code, solver& s, bool isLeft = false);
	expr enumAccess(Json::Value code, solver& s, bool isLeft = false);
	expr assignTuple(Json::Value code, solver& s, bool isLeft = false);
	expr createTemp(Type* type, solver& s);

};

class MapVisitor : SolidityBaseVisitor {
	Json::Value json;
	map<string, Json::Value>* m;
	map<string, string> type;
public:
	MapVisitor(map<string, Json::Value>& m, map<string, string> &type) {
		this->m = &m;
		this->type = type;
	}

	antlrcpp::Any visitStatement(SolidityParser::StatementContext* ctx);
	antlrcpp::Any visitSimpleStatement(SolidityParser::SimpleStatementContext* ctx);
	antlrcpp::Any visitVariableDeclarationStatement(SolidityParser::VariableDeclarationStatementContext* ctx);
	antlrcpp::Any visitExpressionStatement(SolidityParser::ExpressionStatementContext* ctx);
	antlrcpp::Any visitExpression(SolidityParser::ExpressionContext* ctx);

	void setJson(Json::Value code) { json = code; }
private:
	bool mapExpression(SolidityParser::ExpressionContext* ctx, Json::Value ast);
	bool checkCompat(string, Json::Value ast);
	bool primaryExpression(SolidityParser::PrimaryExpressionContext* ctx, Json::Value ast);
};



#endif //!VISITOR_H