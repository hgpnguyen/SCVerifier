#include "verifier.h"
#include "utility.h"


void Verifier::checkSas(string exp) {

	map<string, pfunc> opConvert = getOpConvert();
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
	map<string, pair<TypeInfo, int>> vars;
	Json::Value temp = expList[exp].exp;
	expr expr_ = convertToZ3(temp, s, opConvert, vars).first;
	if (!expList[exp].isTrue)
		expr_ = !expr_;
	s.add(expr_);
	cout << " " << expr_ << endl;

	cout << s.check();

}

void Verifier::checkTrace(string traces_str) {
	expr_vector traces = readTrace(traces_str);
	cout << "Trace: " << traces << endl;
	solver s(ctx);
	for (auto i : Lencode) {
		cout << removeCond(i.encodeStr) << " ";
		expr str_val = ctx.string_val(removeCond(i.encodeStr));
		s.push();
		s.add(in_re(concat(traces), i.regEx));
		if (s.check() == sat) {
			model m = s.get_model();
			cout << sat << endl << m << endl;
			checkCondofTrace(traces_str, m, traces);
		}
		else
			cout << s.check() << endl;
		s.pop();
	}

}

void Verifier::checkCondofTrace(string traces_str, model m, expr_vector vars) {
	vector <string> listCode = getListofCode(traces_str, m, vars);
	map<string, pfunc> opConvert = getOpConvert();
	map<string, pair<TypeInfo, int>> vars_m;
	solver s(ctx);
	for (auto i : listCode) {
		if (decodeSol.find(i) != decodeSol.end() && decodeSol[i]["nodeType"] == "ExpressionStatement") {
			auto expr = convertToZ3(decodeSol[i]["expression"], s, opConvert, vars_m);
			cout << expr.first << endl;
			s.add(expr.first);
		}
	}
	cout << "Solver: " << s << endl;
	cout << s.check() << endl;
}

vector<string> Verifier::getListofCode(string traces_str, model m, expr_vector vars) {
	vector <string> cont, result;
	expr_vector vec(ctx);
	unsigned int index = 1;
	split(traces_str, cont, "->");
	for (auto i : cont)
		cout << i << " ";
	cout << endl;
	for (int i = 0; i < cont.size(); i++) {
		if (cont[i] == "T") {
			string T = m.eval(vars[i]).get_string();
			cout << "T: " << T << endl;
			for (auto j : T)
				result.push_back(string(1, j));
		}
		else {
			int start = 0;
			for (int j = 0; j < cont[i].size(); j++)
				if (cont[i][j] == '{' || cont[i][j] == '}') {
					string get = cont[i].substr(start, j - start);
					start = j + 1;
					if (get == "")
						continue;
					vector <string> cont2;
					split(get, cont2, ';');
					for (auto k : cont2) {
						string encode = encodeSol.find(k) != encodeSol.end() ? encodeSol[k] : k;
						result.push_back(encode);
					}
				}

		}
	}
	for (auto i : result)
		cout << i << " ";
	return result;
}

pair <expr, TypeInfo> Verifier::convertToZ3(Json::Value exp, solver& s, map<string, pfunc> opConvert,
	map<string, pair<TypeInfo, int>>& vars, bool increase) {
	if (exp["nodeType"] == "BinaryOperation") {
		string op, expOP;
		string z3Exp[3] = { "(", "", ")" };
		expOP = exp["operator"].asString();
		auto right = convertToZ3(exp["rightExpression"], s, opConvert, vars);
		auto left = convertToZ3(exp["leftExpression"], s, opConvert, vars);

		TypeInfo type;
		if (expOP == "<" || expOP == ">" || expOP == "<=" || expOP == ">=" || expOP == "==" || expOP == "!=")
			type = { BOOL, 1 };
		else type = right.second;

		if (right.second.type == BYTES && (expOP == "<" || expOP == "<=" || expOP == ">" || expOP == ">="))
			expOP = "u" + expOP;
		preCheck(left, right, expOP);
		pfunc temp = opConvert[expOP];
		expr expression = (this->*temp)(left.first, right.first);

		return{ expression, type };
	}
	else  if (exp["nodeType"] == "UnaryOperation") {
		cout << "A" << endl;
		string op, expOP = exp["operator"].asString();;
		auto subExp_pair = convertToZ3(exp["subExpression"], s, opConvert, vars);
		expr subExp = (this->*opConvert["u" + expOP])(subExp_pair.first, ctx.int_val(0));
		return{ !subExp, subExp_pair.second };
	}
	else if (exp["nodeType"] == "TupleExpression")
		return convertToZ3(exp["components"][0], s, opConvert, vars);
	else if (exp["nodeType"] == "Assignment") {
		auto right = convertToZ3(exp["rightHandSide"], s, opConvert, vars, false);
		auto left = convertToZ3(exp["leftHandSide"], s, opConvert, vars, true);
		preCheck(left, right, "==");
		expr exp = left.first == right.first;
		return{ exp , {BOOL, 1} };
	}
	else {
		TypeInfo type = getType(exp);
		if (exp["nodeType"].asString() == "Literal") {
			string value = type.type == BYTES ? exp["hexValue"].asString() : exp["value"].asString();
			return{ getVal(value, type, s), type };
		}
		else {
			string code = getCode(exp);
			int num = 0;
			if (vars.find(code) == vars.end())
				vars[code] = { type, 0 };
			else {
				if (increase)
					vars[code].second++;
				num = vars[code].second;
			}
			string varname = code + to_string(num);
			return{ getVar(varname, type, s), type };
		}
	}
}

expr Verifier::getVar(string varname, TypeInfo type, solver& s) {
	string var;

	switch (type.type) {
	case UINT:
	{
		expr a = ctx.int_const(varname.c_str());
		s.add(a >= 0);
		return a;
	}
	case INT:
	{
		expr a = ctx.int_const(varname.c_str());
		return a;
	}
	case BOOL:
	{
		expr a = ctx.bool_const(varname.c_str());
		return a;
	}
	case ADDRESS:
	{
		expr a = ctx.bv_const(varname.c_str(), 160);
		return a;
	}
	case BYTES:
	{
		expr a = ctx.bv_const(varname.c_str(), type.size);
		return a;
	}
	default:
	{
		cout << "Wrong Type: " << type.type << endl;
		expr a = ctx.int_val(1);
		return a;
	}
	}
}

expr Verifier::getVal(string value, TypeInfo type, solver& s) {
	int val;
	switch (type.type) {
	case UINT: case INT:
		val = value.substr(0, 2) == "0x" ? stoi(value, 0, 16) : stoi(value);
		return ctx.int_val(val);
	case BOOL:
		return ctx.bool_val(value == "true");
	case ADDRESS:
		return ctx.bv_val(stoi(value, 0, 16), 160);
	case BYTES:
		return ctx.bv_val(stoi(value, 0, 16), 256);
	default:
		cout << "Wrong Type: " << type.type << endl;
		return ctx.int_val(0);
	}
}

TypeInfo Verifier::getType(Json::Value exp) {
	string type = exp["typeDescriptions"]["typeString"].asString();
	bool isLiteral = exp["nodeType"].asString() == "Literal";
	if (type.find("uint") != string::npos)
		return{ UINT, isLiteral ? 256 : stoul(type.substr(4, type.length())) };
	if (type.find("int") != string::npos)
		return{ INT, isLiteral ? 256 : stoul(type.substr(3, type.length())) };
	if (type.find("bool") != string::npos)
		return{ BOOL, 1 };
	if (type.find("address") != string::npos)
		return{ ADDRESS, 160 };
	if (type.find("bytes") != string::npos)
		return{ BYTES, stoul(type.substr(5, type.length())) * 8 };
	if (type.find("string") != string::npos)
		return{ BYTES, 256 };

}

string Verifier::getCode(Json::Value ctx) {
	vector<string> location;
	split(ctx["src"].asString(), location, ':');
	return sourceCode.substr(stoi(location[0]), stoi(location[1]));
}

string Verifier::encode(string code, Verifier& global) {
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

void Verifier::int2Bv(pair<expr, TypeInfo>& p, int size) {
	p.first = to_expr(p.first.ctx(), Z3_mk_int2bv(p.first.ctx(), size == NULL ? p.second.size : size, p.first));
	p.second.type = BYTES;
}

void Verifier::extend(pair<expr, TypeInfo>& p, unsigned int i) {
	p.first = to_expr(p.first.ctx(), Z3_mk_zero_ext(p.first.ctx(), i, p.first));
	p.second.size += i;
}

void Verifier::preCheck(pair<expr, TypeInfo>& l, pair<expr, TypeInfo>& r, string op) {
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


string Verifier::removeCond(string encodeStr) {
	size_t start_pos = 0;
	while ((start_pos = encodeStr.find('{', start_pos)) != string::npos) {
		size_t end_pos = encodeStr.find('}', start_pos);
		encodeStr.erase(start_pos, end_pos - start_pos + 1);
	};
	return encodeStr;
}

expr_vector Verifier::readTrace(string trace) {
	vector <string> cont;
	expr_vector vec(ctx);
	unsigned int index = 1;
	split(trace, cont, "->");
	for (auto i : cont) {
		expr exp(ctx);
		if (i == "T") {
			exp = makeStringFunction(&ctx, "T" + to_string(index));
			index++;
		}
		else {
			vector <string> cont2;
			i = removeCond(i);
			split(i, cont2, ';');
			string result = "";
			for (auto j : cont2) {
				j = encode(j, *this);
				result += j;
			}
			exp = ctx.string_val(result);

		}
		vec.push_back(exp);
	}
	return vec;
}

map<string, Verifier::pfunc> Verifier::getOpConvert() {
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
	return opConvert;
}