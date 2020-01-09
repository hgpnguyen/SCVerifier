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

using namespace std;
using namespace z3;

SolEncode convert(Json::Value ctx, Verifier& global);
string encode(string code, Verifier& global);
string getCode(Json::Value ctx, Verifier& global);
Json::Value readJson(string filename);
expr makeStringFunction(context* c, string s);
void jsonScan(Json::Value root, Verifier& global);
void split(const string& str, vector<string>& result, char delim);
void split(const std::string& str, vector<string>& cont, string delim = " ");
string getCode(Json::Value ctx, Verifier& global);
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
SolEncode convert(Json::Value ctx, Verifier& global);
string encode(string code, Verifier& global);
size_t find(string str, size_t from, map<char, string> m);
string toRawStr(std::string str);
vector<string> infixToPostfix(string str_exp);
expr_vector readTrace(string trace, context& ctx);
vector<string> splitExp(string str_exp);


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

inline expr add(expr l, expr r) { return l + r; }
inline expr minusUti(expr l, expr r) { return l - r; }
inline expr mul(expr l, expr r) { return l * r; }
inline expr div(expr l, expr r) { return l / r; }
inline expr mod(expr l, expr r) { return l % r; }
inline expr exp(expr l, expr r) { return l ^ r.get_numeral_int(); }
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



#endif // !UTILITY_H
