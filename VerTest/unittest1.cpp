#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\SCVerifier\verifier.h"
#include "..\SCVerifier\verifier.cpp"
#include "..\SCVerifier\utility.h"
#include "..\SCVerifier\utility.cpp"
#include "..\SCVerifier\json\json.h"
#include "..\SCVerifier\jsoncpp.cpp"
#include <fstream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace z3;

namespace VerTest
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			// TODO: Your test code here
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
				cout << i.encodeStr << " " << i.regEx << endl;
			for (auto j : extract_keys(verifier.expList)) {
				cout << j << " ";
				verifier.checkSas(j);
				cout << endl;
			}
			// trace: T->a->T
			expr_vector vec = readTrace("T->cde->T", verifier.ctx);
			cout << vec << endl;

			verifier.checkTrace(vec);
		}

	};
}