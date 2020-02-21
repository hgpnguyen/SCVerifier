#include <stdio.h>
#include <iostream>
#include "c++/z3++.h"
#include "utility.h"
#include "antlr4-runtime.h"
#include "Visitor.h"

using namespace z3;
using namespace std;
using namespace antlr4;


void test(string test, Verifier& ver) {

	vector<string> cont;
	split(test, cont, ";");
	cont.pop_back();
	list<PathNode*> test_list;

	for (auto i : cont) {
		string temp = i;
		temp.erase(remove_if(temp.begin(), temp.end(), ::isspace), temp.end());
		string enStr = encode(temp, ver);
		cout << temp << " " << enStr << endl;
		test_list.push_back(new StmtNode(enStr));
	}


	test_list.push_back(new CondNode("x < 10"));
	ver.testSolvePath(test_list);
	cout << endl;
}

map<string, string> CondNode::m{ };


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
	/*jsonScan(root, verifier);
	for (auto i : verifier.Lencode)
		cout << i.encodeStr << " " << i.regEx  << endl;
	/*for (auto j : extract_keys(verifier.expList)) {
		cout << j << " ";
		verifier.checkSas(j);
		cout << endl;
	}*/

	/*string exp = "x <= 2";
	auto cont = splitExp(exp);
	for (auto i : cont)
		cout << i << " ";
	cout << endl;*/
	string trace = "T->x = x + 1;{x >= 3}->T";
	verifier.getAllFunction(root);
	auto trace_ = verifier.getTraceContrainst(trace);
	for (auto i : trace_)
		cout << i.first << " " <<  i.second << endl;
	vector<TreeRoot *> listFunc;
	vector<string> name;
	for (auto key : extract_keys(verifier.functionsMap)) {
		cout << key << " " << verifier.functionsMap[key]["name"].asString() << endl;
		auto tree = verifier.convertFunction(verifier.functionsMap[key], 1);
		listFunc.push_back(tree);
		name.push_back(key);
		cout << "Not Depth: " << tree->getDepth(false) << endl;
		cout << "Depth:     " << tree->getDepth() << endl;
	}
	cout << name[1] << endl;
	verifier.checkTrace(trace_, *listFunc[1]);

	//string test_str = "uint y; uint x; y = 0; x = y + 1; x = x + 1; x = x + 1; x = simple();";
	//test(test_str, verifier);

	// trace: T->a->T
	context ctx;
	solver s(ctx);
	expr A = makeStringFunction(&ctx, "A");
	expr var = to_re(A);
	expr val = to_re(ctx.string_val("B"));
	expr str_var = makeStringFunction(&ctx, "W");
	expr_vector vec(ctx);
	expr temp = concat(var, val);
	cout << temp << endl;
	s.add(in_re(A, to_re(ctx.string_val("CDF"))));
	s.add(in_re(str_var, temp));
	cout << "Model: " << endl;
	cout << s << endl;
	cout << s.check() << endl;
	if (s.check() == sat) {
		model m = s.get_model();
		cout << m << endl;
		cout << m.eval(str_var) << endl;
	}

	system("pause");
	return 0;
}

