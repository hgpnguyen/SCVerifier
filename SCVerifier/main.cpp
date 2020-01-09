#include <stdio.h>
#include <iostream>
#include "c++/z3++.h"
#include "utility.h"
#include "antlr4-runtime.h"
#include "Visitor.h"

using namespace z3;
using namespace std;
using namespace antlr4;


/*void test(string trace, Verifier& ver) {

	expr_vector vec = ver.readTrace(trace);
	cout << endl;
}*/



int main() {
	string smartContract = "test8", sourceCode;
	Json::Value root;
	root = readJson(smartContract + ".sol_json.ast");
	ifstream f("resources/" + smartContract + ".sol");
	f.open("resources/" + smartContract + ".sol");
	string contents((std::istreambuf_iterator<char>(f)),
		std::istreambuf_iterator<char>());
	const char* ptn = contents.c_str();
	string rawStr = toRawStr(contents);
	Verifier verifier;
	verifier.sourceCode = rawStr;
	verifier.index = 0;
	verifier.ctx.set("timeout", 3000);
	jsonScan(root, verifier);
	for (auto i : verifier.Lencode)
		cout << i.encodeStr << " " << i.regEx  << endl;
	/*for (auto j : extract_keys(verifier.expList)) {
		cout << j << " ";
		verifier.checkSas(j);
		cout << endl;
	}*/
	// trace: T->a->T
	string trace = "T->{x == 2}x = x + 1;{x >= 3}->T";
	verifier.checkTrace(trace);

	/*string exp = "x <= 2";
	auto cont = splitExp(exp);
	for (auto i : cont)
		cout << i << " ";
	cout << endl;*/
	map<string, pair<TypeInfo, int>> var_m;
	var_m["x"] = { {UINT, 1}, 5 };
	var_m["y"] = { {UINT, 1}, 0 };
	context ctx;



	return 0;
}

