#pragma once
#ifndef UTILITY_H
#define UTILITY_H

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <stack>
#include <cmath>
#include "c++/z3++.h"
#include "json/json.h"
#include "verifier.h"
#include "tree.h"
#include "Visitor.h"

using namespace std;
using namespace z3;

extern string sourceCode;

SolEncode convert(Json::Value ctx, Verifier& global);
string getCode(Json::Value ctx, string sourceCode);
Json::Value readJson(string filename);
expr makeStringFunction(context* c, string s);
void jsonScan(Json::Value root, Verifier& global);
void split(const string& str, vector<string>& result, char delim);
void split(const std::string& str, vector<string>& cont, string delim = " ");
void addExp(Json::Value exp, string codeExcute, bool isTrue, Verifier& global);
SolEncode block(Json::Value ctx, Verifier& global);
SolEncode ifStmt(Json::Value ctx, Verifier& global);
SolEncode forStmt(Json::Value ctx, Verifier& global);
SolEncode whileStmt(Json::Value ctx, Verifier& global);
SolEncode doWhileStmt(Json::Value ctx, Verifier& global);
SolEncode expressionStmt(Json::Value ctx, Verifier& global);
SolEncode otherStmt(Json::Value ctx, Verifier& global);
bool assignment(Json::Value ctx, Verifier& global);
bool expression(Json::Value ctx, Verifier& global, string leftId);
size_t find(string str, size_t from, map<char, string> m);
string toRawStr(std::string str);
vector<string> infixToPostfix(string str_exp);
expr_vector readTrace(string trace, context& ctx);
vector<string> splitExp(string str_exp);

void bv2int(pair<expr*, ValType*>& p);
void int2Bv(pair<expr*, ValType*>& p, int size = NULL);
void extend(pair<expr*, ValType*>& p, unsigned int i);
void preCheck(pair<expr*, ValType*>& l, pair<expr*, ValType*>& r, string op);
void misMatch(pair<expr*, ValType*>& result);

Json::Value createAssert(Json::Value param);
Json::Value createUnary(Json::Value param, string op);
Json::Value createExprStmt(Json::Value param);

void getAllFunction(Json::Value ast, map<string, Json::Value>& functionsMap);
TreeRoot* convertFunction(Json::Value, int depth);

ValType* getType(Json::Value exp);
Type* getAllType(Json::Value exp);
Type* getVarDeclType(Json::Value, solver& s, string contractName);
map<string, string> getTypeConstraint(string typeConstraint);

inline Type* eleType(Json::Value code, solver& s, string contractName) { if (code["typeDescriptions"]["typeString"].asString() != "bytes") return getType(code); else return new Array(new Byte(8)); }
inline Type* arrType(Json::Value code, solver& s, string contractName) { return new Array(getAllType(code["baseType"])); }
inline Type* mapType(Json::Value code, solver& s, string contractName) { 
	auto m = new Map(getVarDeclType(code["keyType"], s, contractName), getVarDeclType(code["valueType"], s, contractName));
	return m; }
Type* userDefType(Json::Value code, solver& s, string contractName);

template<typename TK, typename TV>
vector<TK> extract_keys(std::map<TK, TV> const& input_map) {
	std::vector<TK> retval;
	retval.reserve(input_map.size());
	for (auto const& element : input_map) {
		retval.push_back(element.first);
	}
	return retval;
}

typedef expr(*pfunc) (expr, expr);
map<string, pfunc> getOpConvert();
string getParamStr(Json::Value paramList);

inline expr add(expr l, expr r) { return l + r; }
inline expr minusUti(expr l, expr r) { return l - r; }
inline expr mul(expr l, expr r) { return l * r; }
inline expr div(expr l, expr r) { return l / r; }
inline expr mod(expr l, expr r) { return l % r; }
inline expr exp(expr l, expr r) { return l ^ r; }
inline expr neg(expr sub, expr) { return -sub; }
inline expr lt(expr l, expr r) { return l < r; }
inline expr le(expr l, expr r) { return l <= r; }
inline expr gt(expr l, expr r) { return l > r; }
inline expr ge(expr l, expr r) { return l >= r; }
inline expr eq(expr l, expr r) { return l == r; }
inline expr neq(expr l, expr r) { return l != r; }
inline expr notOP(expr sub, expr) { return !sub; }
inline expr orOp(expr l, expr r) { return l || r; }
inline expr andOp(expr l, expr r) { return l && r; }
inline expr ult(expr l, expr r) { return z3::ult(l, r); }
inline expr ule(expr l, expr r) { return z3::ule(l, r); }
inline expr ugt(expr l, expr r) { return z3::ugt(l, r); }
inline expr uge(expr l, expr r) { return z3::uge(l, r); }
inline expr bvor(expr l, expr r) { return l | r; }
inline expr bvand(expr l, expr r) { return l & r; }
inline expr bvxor(expr l, expr r) { return l ^ r; }
inline expr bvneg(expr sub, expr) { return ~sub; }
inline expr uplus2(expr sub, expr) { return sub + 1; }
inline expr uminus2(expr sub, expr) { return sub - 1; }
inline expr udelete(expr sub, expr) { return expr(sub.ctx()); }




#endif // !UTILITY_H
