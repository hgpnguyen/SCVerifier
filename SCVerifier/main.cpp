#include <stdio.h>
#include <cstdio>
#include <iostream>
#include "c++/z3++.h"
#include "antlr4-runtime.h"
#include "Visitor.h"
#include <bitset>
#include "BigInt.h"
#include "synthesis.h"
#include "verifier.h"




using namespace z3;
using namespace antlr4;


Report fullCheck(Verifier& verifier, string trace, string constraints, vector<string> name, vector<TreeRoot> listFunc) {
	auto trace_ = verifier.getTraceContrainst(trace);
	/*std::std::cout << "TRACE: ";
	for (auto i : trace_) {
		std::cout << i.first << " ";
	}
	std::cout << endl;*/
	auto start = Clock::now();
	for (int i = 0; i < name.size(); ++i) {
		//std::cout << name[i] << endl;
		auto temp = listFunc[i];
		//cout << verifier.functionsMap[name[i]]["name"] << endl;
		Report report = verifier.checkTrace(trace_, constraints, temp);
		auto end = Clock::now();
		auto lengthOfTime = std::chrono::duration_cast<std::chrono::seconds>(end - start).count();
		if(lengthOfTime > 300)
			return Report(false, verifier.ctx);
		bool check = report.result;
		//std::cout << "-------------------------------------------------------------------------------" << endl;
		CondNode::m.clear();
		if (check) {
			report.functionIndex = i;
			return report;
		}
	}
	return Report(false, verifier.ctx);
}

/*bool check1(Verifier& verifier, string trace, string constraints, vector<string> name, vector<TreeRoot> listFunc, int index) {
	auto trace_ = verifier.getTraceContrainst(trace);
	/*std::cout << "TRACE: ";
	for (auto i : trace_) {
		std::cout << i.first << " ";
	}
	std::cout << endl;*/
	/*string contractName = name[index].substr(0, name[index].find('.'));

	//std::cout << name[index] << endl;
	auto temp = listFunc[index];
	bool check = verifier.checkTrace(trace_, constraints, temp);
	//std::cout << "-------------------------------------------------------------------------------" << endl;
	CondNode::m.clear();
	EVisitor::resetGlobalvar();
	if (check)
		return true;
	
	return false;
}*/

tuple<int, int> temp(Verifier& verifier, string trace, string constraints, vector<string> name, vector<TreeRoot> listFunc, ofstream& myfile, Bug bug) {
	int result, syn = 0;
	Report re = fullCheck(verifier, trace, constraints, name, listFunc);
	if (re.result) {
		try {
		re.genReport();
		re.bug = bug;
		Json::Value func = verifier.functionsMap[name[re.functionIndex]];
		//cout << func["contract"].asString() << endl;
		Json::Value constr = verifier.contractContruct[func["contract"].asString()];
			re.synthesis(func, constr);
			myfile << "Function: " + func["name"].asString() + "(" + getParamStr(func["parameters"]["parameters"]) + ")\n";
			myfile << re.report;
			myfile << "\n";
			if (!re.result)
				syn = 1;
		}
		catch (std::exception e) {
			std::cout << "ERROR: " << e.what() << endl;
		}
		catch (...) {

		}
	}
	result = re.result;
	return make_tuple(result, syn);
}

tuple<int, int, int, int> checkContract(Json::Value json, string smartContract) {
	Verifier verifier;
	context& c = verifier.ctx;

	verifier.getAllFunction(json);
	vector<TreeRoot> listFunc;
	vector<string> listContract;
	for (auto key : extract_keys(verifier.functionsMap)) {
		//std::cout << "Contract: " << key << endl;
			//std::cout << "Function: " << i << endl;
		TreeRoot tree(verifier.functionsMap[key], 2, verifier.functionsMap);
		listContract.push_back(key);
		listFunc.push_back(tree);
			//std::cout << "Not Depth: " << tree.getDepth(false) << endl;
			//std::cout << "Depth:     " << tree.getDepth() << endl;
			//verifier.checkTrace(trace_, *tree);
	}

	string trace = "T->{x <= MAX}x=E;{x > MAX}->T";
	string trace2 = "T->{x >= MIN}x=E;{x < MIN}->T";
	string typeConstraint = "int x; expr E;";
	//check1(verifier, trace2, typeConstraint, listContract, listFunc, 4);
	tuple<int, int> max, min;
	ofstream myfile;
	myfile.open("./resources/report/" + smartContract + "2.txt");
	myfile << "Overflow: \n";
	try {
		max = temp(verifier, trace, typeConstraint, listContract, listFunc, myfile, Overflow);
	}
	catch (std::exception e) {
		std::cout << "ERROR: " << e.what() << endl;
		max = { 3, 0 };
	}
	catch (...) {
		std::cout << "ERROR" << endl;
		max = { 3, 0,};
	}
	myfile << "Underflow: \n";
	try {
		min = temp(verifier, trace2, typeConstraint, listContract, listFunc, myfile, Underflow);
	}
	catch (std::exception e) {
		std::cout << "ERROR: " << e.what() << endl;
		min = { 3, 0 };
	}
	catch (...) {
		std::cout << "ERROR" << endl;
		min = { 3, 0, };
	}
	myfile.close();
	EVisitor::resetGlobalvar();
	return { get<0>(max), get<1>(max), get<0>(min), get<1>(min) };
}

void read_directory(const std::string& name, vector<string>& v)
{
	std::string pattern(name);
	pattern.append("\\*");
	WIN32_FIND_DATA data;
	HANDLE hFind;
	if ((hFind = FindFirstFile(pattern.c_str(), &data)) != INVALID_HANDLE_VALUE) {
		do {
			if (!(data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
				v.push_back(data.cFileName);
		} while (FindNextFile(hFind, &data) != 0);
		FindClose(hFind);
	}
}

string sourceCode;
map<string, Json::Value> CondNode::m{ };
map < string, pair<Type*, Json::Value>> EVisitor::Globalvars{ };

int main() {
	std::string path = "./etherscan_verified_contracts-master";
	//std::string path = "./resources";
	fstream fout;
	
	fout.open("reportcard.csv", ios::out | ios::app);
	int start, end, i = -1;
	//start = 299;
	start = 4539;
	end = 5000;
	vector<string> fileNames;
	read_directory(path + "/output", fileNames);
	for (const auto& entry : fileNames) {
		i++;
		if (i < start)
			continue;
		string filePath = entry;
		string smartContract = filePath.substr(0, filePath.find('.'));
		std::cout << smartContract << " " << i << endl;
		Json::Value root;
		root = readJson(path + "/output/" + smartContract + ".sol_json.ast");
		ifstream f(path + "/contracts/" + smartContract + ".sol");
		string contents((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());
		sourceCode = toRawStr(contents);
		tuple<int, int, int, int> result;
		try {
			result = checkContract(root, smartContract);
		}
		catch (std::exception e) {
			std::cout << "ERROR: " << e.what() << endl;
			result = { 3, 0, 3, 0 };
		}
		catch (...) {
			std::cout << "ERROR" << endl;
			result = { 3, 0, 3, 0 };
		}
		fout << smartContract << "," << get<0>(result) << "," << get<1>(result) << "," << get<2>(result) << "," << get<3>(result) << endl;
	if (i >= end)
			break;

	}


	std::system("pause");
	return 0;
}

