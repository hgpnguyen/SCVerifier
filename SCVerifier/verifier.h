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
#include "antlr4-runtime.h"
#include "SolidityLexer.h"
#include "SolidityParser.h"
#include "Visitor.h"
#include "tree.h"
#include "type.h"
#include <chrono>


using namespace std;
using namespace z3;
using namespace antlr4;

#define TIMELIMIT 120;

typedef std::chrono::system_clock Clock;
class EVisitor;
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


struct Verifier {
	context ctx;
	vector<SolEncode> Lencode; //remove
	map<string, vector<string>> functionCodeList;
	map<string, ExpInfo> expList;
	map<string, Json::Value> functionsMap;
	typedef expr(* pfunc) (expr l, expr r);


	void checkSas(string exp);
	vector<pair<string, string>> getTraceContrainst(string traces);
	bool checkTrace(vector<pair<string, string>> traces, string typeCOnstraint, TreeRoot& functionTree);
	bool checkCondofTrace(string traces_str, model m, expr_vector vars, string path);
	expr_vector readTrace(string trace, solver& s);
	void getAllFunction(Json::Value ast);
	void testSolvePath(list<PathNode*> path);
private:

	pair <expr, ValType*> convertToZ3(Json::Value exp, solver& s, map<string, pfunc> opConvert,
		map<string, pair<Type*, int>>& vars, bool increase = false);
	string encode(string code, map<string, string>& encodeDict, int& index);
	string removeCond(string encodeStr);
	vector<pair<string, int>> getConstraints(string traces_str, model m, expr_vector vars);
	expr convertToExp(string str, map < string, pair<ValType*, int>> vars);
	expr calculate(string exp, map < string, pair<ValType*, int>> vars);
	void increaseVar(solver& s, map < string, pair<ValType*, int>>& vars);
	expr_vector getAllPath(expr exp);
	check_result checkOnePath(expr_vector traces, expr path, string traces_string, string ungenPath);
	//expr generalization(expr path, map<string, string>& encodeDict, int& index);
	SolEncode statementEncode(Json::Value ctx, map<string, string>& encodeDict, int& index);
	bool assignment(Json::Value ctx);
	bool expression(Json::Value ctx, string leftId);
	//string encodeExt(string code, Json::Value ctx);

	bool solvePath(list<PathNode*> path, map<string, Json::Value> decodeSol, map<string, string> encodeSol);
	list<PathNode*> convertToPath(string path, model m);
	expr_vector convertFuncCall(string var);
	bool mapTraceToCode(list<PathNode*> path, string traces, map<string, string> typeConstranit, map<string, Json::Value>& decodeSol);
	expr removeOldSol(model& m, expr_vector vars);
	void scanContract(Json::Value ast, vector<pair<string, Json::Value>>& vars);


};


#endif // !VERIFIER_H

