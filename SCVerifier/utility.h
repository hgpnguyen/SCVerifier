#pragma once
#ifndef UTILITY_H
#define UTILITY_H

#include <stdio.h>
#include <iostream>
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
SolEncode otherStmt(Json::Value ctx, Verifier& global);
SolEncode convert(Json::Value ctx, Verifier& global);
string encode(string code, Verifier& global);
size_t find(string str, size_t from, map<char, string> m);
string toRawStr(std::string str);
vector<string> infixToPostfix(string str_exp);
expr_vector readTrace(string trace, context& ctx);

template<typename TK, typename TV>
vector<TK> extract_keys(std::map<TK, TV> const& input_map) {
	std::vector<TK> retval;
	retval.reserve(input_map.size());
	for (auto const& element : input_map) {
		retval.push_back(element.first);
	}
	return retval;
}

#endif // !UTILITY_H
