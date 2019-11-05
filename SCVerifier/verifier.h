#pragma once
#ifndef VERIFIER_H
#define VERIFIER_H

#include <stdio.h>
#include <iostream>
#include <vector>
#include <stack>
#include <map>
#include <cmath>
#include "c++/z3++.h"
#include "json/json.h"

using namespace std;
using namespace z3;

enum Type { UINT, INT, BOOL, ADDRESS, BYTES, STRING };

struct ExpInfo {
	vector<string> codeActivates;
	Json::Value exp;
	bool isTrue;
};

struct SolEncode {
	string encodeStr;
	expr regEx;
	~SolEncode() {};
};

struct TypeInfo {
	Type type;
	unsigned int size;
};

struct Verifier {
	int index;
	string sourceCode;
	context ctx;
	vector<SolEncode> Lencode;
	map<string, string> encodeSol;
	map<string, Json::Value> decodeSol;
	map<string, vector<string>> functionCodeList;
	map<string, ExpInfo> expList;
	typedef expr(Verifier::* pfunc) (expr l, expr r);

	void checkSas(string exp);
	void checkTrace(string traces_str);
	bool checkCondofTrace(string traces_str, model m, expr_vector vars);
	expr_vector readTrace(string trace);

private:

	pair <expr, TypeInfo> convertToZ3(Json::Value exp, solver& s, map<string, pfunc> opConvert,
		map<string, pair<TypeInfo, int>>& vars, bool increase = false);
	expr getVar(string varname, TypeInfo type, solver& s, bool first = false);
	expr getVal(string value, TypeInfo type, solver& s);
	map<string, pfunc> getOpConvert();
	TypeInfo getType(Json::Value exp);
	string getCode(Json::Value ctx);
	string encode(string code, Verifier& global);
	void int2Bv(pair<expr, TypeInfo>& p, int size = NULL);
	void extend(pair<expr, TypeInfo>& p, unsigned int i);
	void preCheck(pair<expr, TypeInfo>& l, pair<expr, TypeInfo>& r, string op);
	string removeCond(string encodeStr);
	vector<string> getListofCode(string traces_str, model m, expr_vector vars);
	expr convertToExp(string str, map < string, pair<TypeInfo, int>> vars);
	expr calculate(string exp, map < string, pair<TypeInfo, int>> vars);
	void increaseVar(solver& s, map < string, pair<TypeInfo, int>>& vars);

	expr add(expr l, expr r) { return l + r; }
	expr minus(expr l, expr r) { return l - r; }
	expr mul(expr l, expr r) { return l * r; }
	expr div(expr l, expr r) { return l / r; }
	expr mod(expr l, expr r) { return l % r; }
	expr neg(expr sub, expr) { return -sub; }
	expr lt(expr l, expr r) { return l < r; }
	expr le(expr l, expr r) { return l <= r; }
	expr gt(expr l, expr r) { return l > r; }
	expr ge(expr l, expr r) { return l >= r; }
	expr eq(expr l, expr r) { return l == r; }
	expr neq(expr l, expr r) { return l != r; }
	expr notOP(expr sub, expr) { return !sub; }
	expr orOp(expr l, expr r) { return l || r; }
	expr andOp(expr l, expr r) { return l && r; }
	expr ult(expr l, expr r) { return z3::ult(l, r); }
	expr ule(expr l, expr r) { return z3::ule(l, r); }
	expr ugt(expr l, expr r) { return z3::ugt(l, r); }
	expr uge(expr l, expr r) { return z3::uge(l, r); }
	expr bvor(expr l, expr r) { return l | r; }
	expr bvand(expr l, expr r) { return l & r; }
	expr bvxor(expr l, expr r) { return l ^ r; }
	expr bvneg(expr sub, expr) { return ~sub; }
};


#endif // !VERIFIER_H

