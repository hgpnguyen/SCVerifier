#include <stdio.h>
#include <iostream>
#include "c++/z3++.h"
#include "utility.h"
#include "antlr4-runtime.h"
#include "Visitor.h"
#include <bitset>
#include "BigInt.h"
#include <filesystem>

namespace fs = std::filesystem;

using namespace z3;
using namespace std;
using namespace antlr4;


bool fullCheck(Verifier& verifier, string trace, string constraints, vector<string> name, vector<TreeRoot> listFunc) {
	auto trace_ = verifier.getTraceContrainst(trace);
	/*cout << "TRACE: ";
	for (auto i : trace_) {
		cout << i.first << " ";
	}
	cout << endl;*/
	for (int i = 0; i < name.size(); ++i) {
		//cout << name[i] << endl;
		auto temp = listFunc[i];

		bool check = verifier.checkTrace(trace_, constraints, temp);
		//cout << "-------------------------------------------------------------------------------" << endl;
		CondNode::m.clear();
		if (check)
			return true;
	}
	return false;
}

bool check1(Verifier& verifier, string trace, string constraints, vector<string> name, vector<TreeRoot> listFunc, int index) {
	auto trace_ = verifier.getTraceContrainst(trace);
	/*cout << "TRACE: ";
	for (auto i : trace_) {
		cout << i.first << " ";
	}
	cout << endl;*/
	string contractName = name[index].substr(0, name[index].find('.'));

	//cout << name[index] << endl;
	auto temp = listFunc[index];
	bool check = verifier.checkTrace(trace_, constraints, temp);
	//cout << "-------------------------------------------------------------------------------" << endl;
	CondNode::m.clear();
	EVisitor::resetGlobalvar();
	if (check)
		return true;
	
	return false;
}

pair<int, int> checkContract(Json::Value json) {
	Verifier verifier;


	verifier.getAllFunction(json);
	vector<TreeRoot> listFunc;
	vector<string> listContract;
	for (auto key : extract_keys(verifier.functionsMap)) {
		//cout << "Contract: " << key << endl;
			//cout << "Function: " << i << endl;
		TreeRoot tree(verifier.functionsMap[key], 1, verifier.functionsMap);
		listContract.push_back(key);
		listFunc.push_back(tree);
			//cout << "Not Depth: " << tree.getDepth(false) << endl;
			//cout << "Depth:     " << tree.getDepth() << endl;
			//verifier.checkTrace(trace_, *tree);
	}

	int num = 9;
	string trace = "T->{x <= MAX}x=E;{x > MAX}->T";
	string trace2 = "T->{x >= MIN}x=E;{x < MIN}->T";
	string typeConstraint = "int x; expr E;";
	//check1(verifier, trace2, typeConstraint, listContract, listFunc, 4);
	int max, min;

		max = fullCheck(verifier, trace, typeConstraint, listContract, listFunc);

		min = fullCheck(verifier, trace2, typeConstraint, listContract, listFunc);

	EVisitor::resetGlobalvar();
	return { max, min };
}

map<string, Json::Value> CondNode::m{ };
map < string, pair<Type*, int>> EVisitor::Globalvars{ };

int main() {
	//std::string path = "./etherscan_verified_contracts-master/output";
	std::string path = "./resources/output";
	fstream fout;
	fout.open("reportcard.csv", ios::out | ios::app);
	int start, end, i = -1;
	//start = 1213;
	//start = 294;
	start = 0;
	end = 20;
	for (const auto& entry : fs::directory_iterator(path)) {
		i++;
		if (i < start)
			continue;
		string filePath = entry.path().string();
		string smartContract = filePath.substr(path.length() + 1, filePath.find('.', path.length()) - path.length() - 1);
		cout << smartContract << " " << i << endl;
		Json::Value root;
		root = readJson(path + "/" + smartContract + ".sol_json.ast");
		pair<int, int> result;

			result = checkContract(root);

		/*catch (std::exception e) {
			cout << "ERROR: " << e.what() << endl;
			result = { 3, 3 };
		}
		catch (...) {
			cout << "ERROR" << endl;
			result = { 3, 3 };
		}*/
		fout << smartContract << "," << result.first << "," << result.second << endl;
		if (i >= end)
			break;
		/*if (result.first)
			cout << "Overflow" << endl;
		if (result.second)
			cout << "Underflow" << endl;*/
	}
	/*cout << name[num] << endl;
	auto temp = listFunc[num];

	verifier.checkTrace(trace_, typeConstraint, temp);*/

	
	// trace: T->a->T

	/*string trace = "expr x;";
	ANTLRInputStream input(trace);
	SolidityLexer lexer(&input);
	CommonTokenStream tokens(&lexer);
	SolidityParser parser(&tokens);
	SolidityParser::TypeDeclContext* tree = parser.typeDecl();
	cout << tree << endl;


	//model m = s.get_model();
	//cout << m << endl;

	/*context c;
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
	cout << s.check() << endl;*/

	/*string address = "0xd06cb7A1b2Ccd1D3AF";
	int len = 256;
	cout << address.size() << endl;

	//unsigned long long k = strtoull(address.c_str(), 0, 16);
	//cout << k << endl;
	context c;
	//string str_k = to_string(k);
	auto bool_str = hex_str_to_bool_arr(len, address);
	for (int i = 0; i < len; i++)
		cout << bool_str[i];
	cout << endl;
	expr bv = c.bv_val("1259841088174951335562403333186447673233413100463", 160);
	cout << bv << endl;
	bool bv_arr[] = { true, false, false, true , false};
	expr bv2 = c.bv_val(len, bool_str);
	cout << bv2 << endl;*/


	/*context c;
	vector<pair<string, Type*>> listType;
	func_decl_vector projs(c);
	const char* name_[3] = { "yetNeeded", "ownerDone", "index" };
	string name = "PendingState";
	listType.push_back({ "yetNeeded", new UInt(256) });
	listType.push_back({ "ownerDone", new UInt(256) });
	listType.push_back({ "index", new UInt(256) });
	int size = listType.size();
	char* _names[10];
	z3::sort sorts[10] = { c.int_sort(), c.int_sort(), c.int_sort(),
		c.int_sort(), c.int_sort(), c.int_sort(), c.int_sort(), c.int_sort(), c.int_sort(), c.int_sort() };

	int i = 0;
	for (auto mem : listType) {
		_names[i] = strdup(mem.first.c_str());
		sorts[i++] = mem.second->getSort(c);
	}

	cout << size << endl;
	func_decl structDecl = c.tuple_sort(name.c_str(), size, _names, sorts, projs);
	for (auto func : projs)
		cout << func << endl;
		*/
	

	

	system("pause");
	return 0;
}

