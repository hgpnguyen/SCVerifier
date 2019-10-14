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


void split(const string& str, vector<string>& result, char delim);

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

struct SolEncode {
	string encodeStr;
	expr regEx;
	~SolEncode() {};
};

struct Verifier {
	int index;
	string sourceCode;
	context ctx;
	vector<SolEncode> Lencode;
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

	void checkTrace(expr_vector traces) {
		solver s(ctx);
		for (auto i : Lencode) {
			cout << removeCond(i.encodeStr) << " ";
			expr str_val = ctx.string_val(removeCond(i.encodeStr));
			s.push();
			s.add(in_re(concat(traces), i.regEx));
			if (s.check() == sat)
				cout << sat << endl << s.get_model() << endl;
			else
				cout << s.check() << endl;
			s.pop();
		}

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
		split(ctx["src"].asString(), location, ':');
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


	string removeCond(string encodeStr) {
		size_t start_pos = 0;
		while ((start_pos = encodeStr.find('{', start_pos)) != string::npos) {
			size_t end_pos = encodeStr.find('}', start_pos);
			encodeStr.erase(start_pos, end_pos - start_pos + 1);
		};
		return encodeStr;
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

SolEncode convert(Json::Value ctx, Verifier& global);
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

expr makeStringFunction(context* c, string s) {
	z3::sort sort = c->string_sort();
	symbol name = c->str_symbol(s.c_str());
	return c->constant(name, sort);
}

void jsonScan(Json::Value root, Verifier& global) {
	if (root.isObject()) {
		if (!root.isMember("nodeType")) 
			return;
		else if (root["nodeType"] == "FunctionDefinition" && !root["body"].isNull()) {
			SolEncode encode = convert(root["body"], global);
			global.Lencode.push_back(encode);
			global.functionCodeList[root["name"].asString()].push_back(encode.encodeStr);
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

void split(const string& str, vector<string>& result, char delim) {
	stringstream ss(str);
	std::string token;
	while (getline(ss, token, delim)) {
		result.push_back(token);
	}
}

void split(const std::string& str, vector<string>& cont, string delim = " ")
{
	std::size_t current, previous = 0;
	current = str.find(delim);
	while (current != std::string::npos) {
		cont.push_back(str.substr(previous, current - previous));
		previous = current + delim.length();
		current = str.find(delim, previous);
	}
	cont.push_back(str.substr(previous, current - previous));
}


string getCode(Json::Value ctx, Verifier& global) {
	vector<string> location;
	split(ctx["src"].asString(), location, ':');
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

SolEncode block(Json::Value ctx, Verifier& global) {
	string enStr = "";
	expr_vector vec(global.ctx);
	for (auto statement : ctx["statements"]) {
		SolEncode en = convert(statement, global);
		enStr += en.encodeStr;
		vec.push_back(en.regEx);
	}
	return{ enStr, concat(vec) };
}

SolEncode ifStmt(Json::Value ctx, Verifier& global) {
	SolEncode enTrue = convert(ctx["trueBody"], global);
	string condition = getCode(ctx["condition"], global);
	string elseCondition = "!(" + condition + ")";
	string trueBody = enTrue.encodeStr, falseBody;
	expr regex(global.ctx);
	if (ctx["falseBody"].isNull()) {
		SolEncode enFalse = convert(ctx["trueBody"], global);
		falseBody = enFalse.encodeStr;
		regex = enTrue.regEx + enFalse.regEx;
	}
	else {
		falseBody = encode("#", global);
		regex = option(enTrue.regEx);
	}
	string enStr = "({" + condition + "}" + trueBody + "|{" + elseCondition + "}" + falseBody + ")";
	addExp(ctx["condition"], trueBody, true, global);
	addExp(ctx["condition"], falseBody, false, global);

	return{ enStr, regex };
}

SolEncode forStmt(Json::Value ctx, Verifier& global) {
	SolEncode body = convert(ctx["body"], global), lpExp = convert(ctx["loopExpression"], global);
	string enStr = "(" + body.encodeStr + lpExp.encodeStr + ")*";
	expr regex = star(concat(body.regEx, lpExp.regEx));
	return{ enStr, regex };
}

SolEncode whileStmt(Json::Value ctx, Verifier& global) {
	SolEncode body = convert(ctx["body"], global);
	string condition = getCode(ctx["condition"], global);
	string enStr = "({" + condition + "}(" + body.encodeStr + ")*)";
	expr regex = star(body.regEx);
	addExp(ctx["condition"], body.encodeStr, true, global);
	return{ enStr, regex };
}

SolEncode doWhileStmt(Json::Value ctx, Verifier& global) {
	//string condition = getCode(ctx["condition"], global);
	SolEncode body = convert(ctx["body"], global);
	string enStr = "(" + body.encodeStr + ")+";
	expr regex = z3::plus(body.regEx);
	return{ enStr, regex };
}

SolEncode otherStmt(Json::Value ctx, Verifier& global) {
	string code = getCode(ctx, global);
	string enStr = encode(code, global);
	expr regex = to_re(global.ctx.string_val(enStr));
	return{ enStr, regex };
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
		encode_str = encode_str + "_" + temp;
	}
	index++;
	global.encodeSol[code] = encode_str;

	return encode_str;
}

SolEncode convert(Json::Value ctx, Verifier& global) {
	typedef SolEncode (*pfunc)(Json::Value, Verifier& global);
	map<string, pfunc> switchCase;
	switchCase["Block"] = block;
	switchCase["ForStatement"] = forStmt;
	switchCase["IfStatement"] = ifStmt;
	switchCase["WhileStatement"] = whileStmt;
	switchCase["DoWhileStatement"] = doWhileStmt;
	string nodeType = ctx["nodeType"].asString();
	auto func = switchCase.find(nodeType) != switchCase.end() ? switchCase[nodeType] : otherStmt;
	//cout << ctx << endl;
	SolEncode regularExp = func(ctx, global);
	return regularExp;
}

expr_vector readTrace(string trace, context& ctx) {
	vector <string> cont;
	expr_vector vec(ctx);
	unsigned int index = 1;
	split(trace, cont, "->");
	cout << "split " << endl;
	for (auto i : cont) {
		cout << i << endl;
		expr exp(ctx);
		if (i == "T") {
			exp = makeStringFunction(&ctx, "T" + to_string(index));
			index++;
		}
		else exp = ctx.string_val(i);
		vec.push_back(exp);
	}
	return vec;
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
	verifier.ctx.set("timeout", 3000);
	jsonScan(root, verifier);
	for (auto i : verifier.Lencode)
		cout << i.encodeStr << " " << i.regEx  << endl;
	for (auto j : extract_keys(verifier.expList)) {
		cout << j << " ";
		verifier.checkSas(j);
		cout << endl;
	}
	// trace: T->a->T
	/*expr t1 = makeStringFunction(&verifier.ctx, "t1");
	expr t2 = makeStringFunction(&verifier.ctx, "t2");
	expr a = verifier.ctx.string_val("a");*/
	expr_vector vec = readTrace("T->cde->T", verifier.ctx);
	cout << vec << endl;
	/*vec.push_back(t1);
	vec.push_back(a);
	vec.push_back(t2);*/
	verifier.checkTrace(vec);



	system("pause");
	return 0;
}

