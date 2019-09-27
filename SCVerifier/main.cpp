#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <cmath>
#include "c++/z3++.h"
#include "json/json.h"

using namespace z3;
using namespace std;


void split(const string& str, vector<string>& result);

enum Type { UINT, INT, BOOL, ADDRESS, BYTES, STRING };

struct TypeInfo {
	Type type;
	unsigned int size;
};

struct ExpInfo {
	vector<string> codeActivates;
	Json::Value exp;
	bool isTrue;
};

struct Verifier {
	int index;
	string sourceCode;
	vector<string> Lencode;
	map<string, string> encodeSol;
	map<string, vector<string>> functionCodeList;
	map<string, ExpInfo> expList;
	typedef expr(Verifier::* pfunc) (expr l, expr r);

	void checkSas(string exp) {
		
		map<string, pfunc> opConvert;
		opConvert["=="] = &Verifier::eq;
		opConvert["!="] = &Verifier::neq;
		opConvert["||"] = &Verifier::orOp;
		opConvert["&&"] = &Verifier::andOp;
		opConvert["<"] = &Verifier::lt;
		opConvert["<="] = &Verifier::le;
		opConvert[">"] = &Verifier::gt;
		opConvert[">="] = &Verifier::ge;
		opConvert["u<"] = &Verifier::ult;
		opConvert["u<="] = &Verifier::ule;
		opConvert["u>"] = &Verifier::ugt;
		opConvert["u>="] = &Verifier::uge;
		opConvert["+"] = &Verifier::add;
		opConvert["-"] = &Verifier::minus;
		opConvert["*"] = &Verifier::mul;
		opConvert["/"] = &Verifier::div;
		opConvert["%"] = &Verifier::mod;
		opConvert["|"] = &Verifier::bvor;
		opConvert["&"] = &Verifier::bvand;
		opConvert["^"] = &Verifier::bvxor;
		opConvert["u-"] = &Verifier::neg;
		opConvert["u!"] = &Verifier::notOP;
		opConvert["u~"] = &Verifier::bvneg;
		if (expList.find(exp) == expList.end()) {
			cout << "Cant find expression" << endl;
			return;
		}
		config cfg;
		cfg.set("timeout", 3000);
		context ctx(cfg);
		func_decl_vector decls(ctx);
		sort_vector sorts(ctx);
		solver s(ctx);
		Verifier ver;
		ver.index = 0;
		Json::Value temp = expList[exp].exp;
		expr expr_ = convertToZ3(temp, ctx, s, opConvert, ver).first;
		if (!expList[exp].isTrue)
			expr_ = !expr_;
		s.add(expr_);
		cout << " " << expr_ << endl;
		
		cout << s.check();

	}
private:

	pair <expr, TypeInfo> convertToZ3(Json::Value exp, context& ctx, solver& s, map<string, pfunc> opConvert, Verifier& cToZ3) {
		if (exp["nodeType"] == "BinaryOperation") {
			string op, expOP;
			string z3Exp[3] = { "(", "", ")" };
			expOP = exp["operator"].asString();
			auto right = convertToZ3(exp["rightExpression"], ctx, s, opConvert, cToZ3);
			auto left = convertToZ3(exp["leftExpression"], ctx, s, opConvert, cToZ3);

			TypeInfo type;
			if (expOP == "<" || expOP == ">" || expOP == "<=" || expOP == ">=" || expOP == "==" || expOP == "!=")
				type = { BOOL, 1 };
			else type = right.second;

			if (right.second.type == BYTES && (expOP == "<" || expOP == "<=" || expOP == ">" || expOP == ">="))
				expOP = "u" + expOP;
			preCheck(left, right, expOP);
			pfunc temp = opConvert[expOP];
			expr expression = (this->*temp)(left.first, right.first);
			
			return { expression, type };
		}
		else  if (exp["nodeType"] == "UnaryOperation") {
			cout << "A" << endl;
			string op, expOP = exp["operator"].asString();;
			auto subExp_pair = convertToZ3(exp["subExpression"], ctx, s, opConvert, cToZ3);
			expr subExp = (this->*opConvert["u" + expOP])(subExp_pair.first, ctx.int_val(0));
			return { !subExp, subExp_pair.second };
		}
		else if (exp["nodeType"] == "TupleExpression")
			return convertToZ3(exp["components"][0], ctx, s, opConvert, cToZ3);
		else {
			string code = getCode(exp);
			string type = exp["typeDescriptions"]["typeString"].asString();
			size_t pos;
			return getVar(exp, ctx, s, cToZ3);
		}
	}

	pair<expr, TypeInfo> getVar(Json::Value exp, context& ctx, solver& s, Verifier& cToZ3) {

		string code = getCode(exp), var;
		int val;
		string type = exp["typeDescriptions"]["typeString"].asString();
		TypeInfo typeInfo;
		typeInfo = getType(exp);
		if (exp["nodeType"].asString() == "Literal") {
			string value = exp["value"].asString();
			switch (typeInfo.type) {
			case UINT: case INT:
				val = value.substr(0, 2) == "0x" ? stoi(value, 0, 16) : stoi(value);
				return { ctx.int_val(val), typeInfo };
			case BOOL:
				return { ctx.bool_val(exp["value"].asString() == "true"), typeInfo };
			case ADDRESS:
				return { ctx.bv_val(stoi(exp["value"].asString(), 0, 16), 160), typeInfo };
			case BYTES:
				return { ctx.bv_val(stoi(exp["hexValue"].asString(), 0, 16), 256), typeInfo };
			default:
				cout << "Wrong Type: " << typeInfo.type << endl;
			}
		}

		switch (typeInfo.type) {
		case UINT: 
		{
			var = encode(code, cToZ3);
			expr a = ctx.int_const(var.c_str());
			s.add(a >= 0);
			return { a, typeInfo };
		}
		case INT:
		{
			var = encode(code, cToZ3);
			expr a = ctx.int_const(var.c_str());
			return { a, typeInfo };
		}
		case BOOL:
		{
			var = encode(code, cToZ3);
			expr a = ctx.bool_const(var.c_str());
			return { a, typeInfo };
		}
		case ADDRESS: 
		{
			var = encode(code, cToZ3);
			expr a = ctx.bv_const(var.c_str(), 160);
			return { a, typeInfo };
		}
		case BYTES:
		{
			var = encode(code, cToZ3);
			expr a = ctx.bv_const(var.c_str(), typeInfo.size);
			return { a, typeInfo };
		}
		default: 
		{
			cout << "Wrong Type: " << typeInfo.type << endl;
			expr a = ctx.int_val(1);
			return { a, typeInfo };
		}
		}
	}

	TypeInfo getType(Json::Value exp) {
		string type = exp["typeDescriptions"]["typeString"].asString();
		bool isLiteral = exp["nodeType"].asString() == "Literal";
		if (type.find("uint") != string::npos) 
			return { UINT, isLiteral ? 256 : stoul(type.substr(4, type.length())) };
		if (type.find("int") != string::npos)
			return { INT, isLiteral ? 256 : stoul(type.substr(3, type.length())) };
		if (type.find("bool") != string::npos)
			return { BOOL, 1 };
		if (type.find("address") != string::npos)
			return { ADDRESS, 160 };
		if (type.find("bytes") != string::npos)
			return { BYTES, stoul(type.substr(5, type.length())) * 8 };
		if (type.find("string") != string::npos)
			return { BYTES, 256 };

	}

	string getCode(Json::Value ctx) {
		vector<string> location;
		split(ctx["src"].asString(), location);
		return sourceCode.substr(stoi(location[0]), stoi(location[1]));
	}

	string encode(string code, Verifier& global) {
		if (global.encodeSol.find(code) != global.encodeSol.end())
			return global.encodeSol[code];
		int& index = global.index;
		int mod, div;
		string encode_str;
		mod = index % 26;
		div = index / 26;
		encode_str = static_cast<char>(97 + mod);
		while (div != 0) {
			mod = div % 26;
			mod = mod != 0 ? mod - 1 : mod;
			div = div / 26;
			string temp(1, static_cast<char>(97 + mod));
			encode_str += "_" + temp;
		}
		index++;
		global.encodeSol[code] = encode_str;

		return encode_str;
	}

	void int2Bv(pair<expr, TypeInfo>& p, int size = NULL) {
		p.first = to_expr(p.first.ctx(), Z3_mk_int2bv(p.first.ctx(), size == NULL ? p.second.size : size, p.first));
		p.second.type = BYTES;
	}

	void extend(pair<expr, TypeInfo>& p, unsigned int i) {
		p.first = to_expr(p.first.ctx(), Z3_mk_zero_ext(p.first.ctx(), i, p.first));
		p.second.size += i;
	}

	void preCheck(pair<expr, TypeInfo>& l, pair<expr, TypeInfo>& r, string op) {
		string listOP[3] = { "&", "|", "^" };
		if (listOP->find(op) != string::npos && l.first.is_int() && r.first.is_int()) {
			int2Bv(l);
			int2Bv(r);
		}
		if (l.first.is_bv() && !r.first.is_bv()) 
			int2Bv(r, l.second.size);

		else if (!l.first.is_bv() && r.first.is_bv()) 
			int2Bv(l, r.second.size);
		else if (l.first.is_bv() && r.first.is_bv() && l.second.size != r.second.size)
			if (l.second.size > r.second.size)
				extend(r, l.second.size - r.second.size);
			else extend(l, r.second.size - l.second.size);
	}

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

string convert(Json::Value ctx, Verifier& global); 
string encode(string code, Verifier& global);
string getCode(Json::Value ctx, Verifier& global);

template<typename TK, typename TV>
std::vector<TK> extract_keys(std::map<TK, TV> const& input_map) {
	std::vector<TK> retval;
	retval.reserve(input_map.size());
	for (auto const& element : input_map) {
		retval.push_back(element.first);
	}
	return retval;
}

Json::Value readJson(string filename) {
	ifstream file("resources/" + filename);
	Json::Value root;
	Json::Reader reader;
	if (!reader.parse(file, root)) {
		cout << "Failed to parse configuration\n"
			<< reader.getFormattedErrorMessages();
	}
	return root;
}

void jsonScan(Json::Value root, Verifier& global) {
	if (root.isObject()) {
		if (!root.isMember("nodeType")) 
			return;
		else if (root["nodeType"] == "FunctionDefinition" && !root["body"].isNull()) {
			string encode = convert(root["body"], global);
			global.Lencode.push_back(encode);
			global.functionCodeList[root["name"].asString()].push_back(encode);
			return;
		}
		for (auto i : root.getMemberNames()) {
			if (root[i].isArray() || root[i].isObject())
				jsonScan(root[i], global);
		}
	}
	else if (root.isArray()) {
		for (auto i : root)
			if (i.isArray() || i.isObject())
				jsonScan(i, global);
	}
}

void split(const string& str, vector<string>& result) {
	stringstream ss(str);
	std::string token;
	while (getline(ss, token, ':')) {
		result.push_back(token);
	}
}


string getCode(Json::Value ctx, Verifier& global) {
	vector<string> location;
	split(ctx["src"].asString(), location);
	cout << global.sourceCode.substr(stoi(location[0]), stoi(location[1])) << endl;
	return global.sourceCode.substr(stoi(location[0]), stoi(location[1]));
}

void addExp(Json::Value exp, string codeExcute, bool isTrue, Verifier& global) {
	string codeExp = getCode(exp, global);
	if (!isTrue)
		codeExp = "!(" + codeExp + ")";
	if (global.expList.find(codeExp) == global.expList.end()) {
		ExpInfo expInfo = { {codeExcute}, exp, isTrue };
		global.expList[codeExp] = expInfo;
	}
	else global.expList[codeExp].codeActivates.push_back(codeExcute);
}

string block(Json::Value ctx, Verifier& global) {
	string regularExp = "";
	for (auto statement : ctx["statements"])
		regularExp += convert(statement, global);
	return regularExp;
}

string ifStmt(Json::Value ctx, Verifier& global) {
	string condition = getCode(ctx["condition"], global);
	string elseCondition = "!(" + condition + ")";
	string trueBody = convert(ctx["trueBody"], global);
	string falseBody = !ctx["falseBody"].isNull() ? convert(ctx["falseBody"], global) : encode("#", global);
	string regularExp = "({" + condition + "}" + trueBody + "|{" + elseCondition + "}" + falseBody + ")";
	addExp(ctx["condition"], trueBody, true, global);
	addExp(ctx["condition"], falseBody, false, global);
	return regularExp;
}

string forStmt(Json::Value ctx, Verifier& global) {
	string body = convert(ctx["body"], global);
	string loopExp = convert(ctx["loopExpression"], global);
	string regularExp = "(" + body + loopExp + ")*";
	return regularExp;
}

string whileStmt(Json::Value ctx, Verifier& global) {
	string condition = getCode(ctx["condition"], global);
	string body = convert(ctx["body"], global);
	string regularExp = "({" + condition + "}(" + body + ")*)";
	addExp(ctx["condition"], body, true, global);
	return regularExp;
}

string doWhileStmt(Json::Value ctx, Verifier& global) {
	//string condition = getCode(ctx["condition"], global);
	string body = convert(ctx["body"], global);
	string regularExp = "(" + body + ")+";
	return regularExp;
}

string otherStmt(Json::Value ctx, Verifier& global) {
	string code = getCode(ctx, global);
	return encode(code, global);
}

string encode(string code, Verifier& global) {
	if (global.encodeSol.find(code) != global.encodeSol.end())
		return global.encodeSol[code];
	int& index = global.index;
	int mod, div;
	string encode_str;
	mod = index % 26;
	div = index / 26;
	encode_str = static_cast<char>(97 + mod);
	cout << index << " " << mod << encode_str << endl;
	while (div != 0) {
		mod = div % 26;
		mod = mod != 0 ? mod - 1 : mod;
		div = div / 26;
		string temp(1, static_cast<char>(97 + mod));
		encode_str = encode_str + "_" + temp;
	}
	index++;
	global.encodeSol[code] = encode_str;

	return encode_str;
}

string convert(Json::Value ctx, Verifier& global) {
	string regularExp;
	typedef string (*pfunc)(Json::Value, Verifier& global);
	map<string, pfunc> switchCase;
	switchCase["Block"] = block;
	switchCase["ForStatement"] = forStmt;
	switchCase["IfStatement"] = ifStmt;
	switchCase["WhileStatement"] = whileStmt;
	switchCase["DoWhileStatement"] = doWhileStmt;
	string nodeType = ctx["nodeType"].asString();
	auto func = switchCase.find(nodeType) != switchCase.end() ? switchCase[nodeType] : otherStmt;
	//cout << ctx << endl;
	regularExp = func(ctx, global);
	return regularExp;
}

size_t find(string str, size_t from, map<char, string> m) {
	for (size_t i = from; i < str.length(); i++)
		if (m.find(str[i]) != m.end())
			return i;
	return string::npos;
}

std::string toRawStr(std::string str) {
	size_t start_pos = 0;
	map<char, string> spChar;
	spChar['\n'] = "\\n"; spChar['\t'] = "\\t";
	while ((start_pos = find(str, start_pos, spChar)) != std::string::npos) {
		string to = spChar[str[start_pos]];
		str.replace(start_pos, 1, to);
		start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
	}
	return str;
}

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
	jsonScan(root, verifier);
	for (auto i : verifier.Lencode)
		cout << i << endl;
	for (auto j : extract_keys(verifier.expList)) {
		cout << j << " ";
		verifier.checkSas(j);
		cout << endl;
	}

	return 0;
}