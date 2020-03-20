#include <stdio.h>
#include <iostream>
#include "c++/z3++.h"
#include "utility.h"
#include "antlr4-runtime.h"
#include "Visitor.h"

using namespace z3;
using namespace std;
using namespace antlr4;


/*void test(string test, Verifier& ver) {

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
}*/

map<string, Json::Value> CondNode::m{ };
map < string, pair<Type*, int>> EVisitor::Globalvars{ };
string sourceCode;

int main() {
	string smartContract = "test8";
	Json::Value root;
	root = readJson(smartContract + ".sol_json.ast");
	ifstream f("resources/" + smartContract + ".sol");
	f.open("resources/" + smartContract + ".sol");
	string contents((std::istreambuf_iterator<char>(f)),
		std::istreambuf_iterator<char>());
	const char* ptn = contents.c_str();
	string rawStr = toRawStr(contents);
	Verifier verifier;
	sourceCode =  rawStr;
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
	string trace = "T->x = x + 1;{x > 6}->T";
	verifier.getAllFunction(root, "");
	auto trace_ = verifier.getTraceContrainst(trace);
	cout << "TRACE: ";
	for (auto i : trace_) {
		cout << i.first << " ";
	}
	cout << endl;
	vector<TreeRoot> listFunc;
	vector<string> name;
	verifier.ctx.set("timeout", 3000);
	for (auto key : extract_keys(verifier.functionsMap)) {
		verifier.currentContract = key;
		cout << "Contract: " << key << endl;
		for (auto i : extract_keys(verifier.functionsMap[key])) {
			cout << "Function: " << i << endl;
			TreeRoot tree(verifier.functionsMap[key][i], 1, verifier.functionsMap[key]);
			listFunc.push_back(tree);
			name.push_back(i);
			cout << "Not Depth: " << tree.getDepth(false) << endl;
			cout << "Depth:     " << tree.getDepth() << endl;
			//verifier.checkTrace(trace_, *tree);
		}
	}

	
	cout << name[2] << endl;
	auto temp = listFunc[2];

	verifier.checkTrace(trace_, temp);

	// trace: T->a->T



	//model m = s.get_model();
	//cout << m << endl;

	context c;
	sort_vector sort_vec(c);
	sort_vec.push_back(c.bv_sort(160));
	sort_vec.push_back(c.bv_sort(160));
	z3::sort map_sort = c.array_sort(sort_vec, c.int_sort());
	expr map = c.constant(c.str_symbol("m"), map_sort);
	expr a = c.bv_const("a", 160);
	expr b = c.bv_const("b", 160);
	expr_vector vec(c);
	vec.push_back(a);
	vec.push_back(b);
	expr k = select(map, vec) == 10;
	expr const_int = c.int_val(10);
	solver s(c);
	s.add(store(map, vec, const_int) == map);
	s.add(k);
	cout << s << endl;
	cout << s.check() << endl;


	system("pause");
	return 0;
}

