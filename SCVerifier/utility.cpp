#include "utility.h"


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

/*void jsonScan(Json::Value root, Verifier& global) {
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
}*/

void split(const string& str, vector<string>& result, char delim) {
	stringstream ss(str);
	std::string token;
	while (getline(ss, token, delim)) {
		result.push_back(token);
	}
}

void split(const std::string& str, vector<string>& cont, string delim)
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
	string result = global.sourceCode.substr(stoi(location[0]), stoi(location[1]));
	result.erase(remove_if(result.begin(), result.end(), ::isspace), result.end());
	return result;
}

string getCode(Json::Value ctx, string sourceCode)
{
	vector<string> location;
	split(ctx["src"].asString(), location, ':');
	string result = sourceCode.substr(stoi(location[0]), stoi(location[1]));
	result.erase(remove_if(result.begin(), result.end(), ::isspace), result.end());
	return result;
}

void addExp(Json::Value exp, string codeExcute, bool isTrue, Verifier& global) {
	string codeExp = getCode(exp, global);
	if (!isTrue)
		codeExp = "!(" + codeExp + ")";
	if (global.expList.find(codeExp) == global.expList.end()) {
		ExpInfo expInfo = { { codeExcute }, exp, isTrue };
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
	if (!ctx["falseBody"].isNull()) {
		SolEncode enFalse = convert(ctx["falseBody"], global);
		falseBody = enFalse.encodeStr;
		regex = enTrue.regEx + enFalse.regEx;
	}
	else {
		//falseBody = encode("#", global);
		falseBody = "#";
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
	expr regex = body.regEx.loop(0, 10);
	addExp(ctx["condition"], body.encodeStr, true, global);
	return{ enStr, regex };
}

SolEncode doWhileStmt(Json::Value ctx, Verifier& global) {
	//string condition = getCode(ctx["condition"], global);
	SolEncode body = convert(ctx["body"], global);
	string enStr = "(" + body.encodeStr + ")+";
	expr regex = body.regEx.loop(1, 10);
	return{ enStr, regex };
}

SolEncode expressionStmt(Json::Value ctx, Verifier& global) {
	if (ctx["expression"]["nodeType"] == "Assignment") {
		if (assignment(ctx["expression"], global)) {
			string code = "a=a+n";
			cout << code << endl;
			string enStr = encode(code, global);
			expr regex = to_re(global.ctx.string_val(enStr));
			if (global.decodeSol.find(enStr) == global.decodeSol.end())
				global.decodeSol[enStr] = ctx;
			return{ enStr, regex };
		}
		return otherStmt(ctx, global);
	}
	else return otherStmt(ctx, global);
}

bool assignment(Json::Value ctx, Verifier& global) {
	string leftCode = getCode(ctx["leftHandSide"], global);
	if (ctx["operator"] == "+=" || ctx["operator"] == "-=")
		return true;
	if (ctx["rightHandSide"]["nodeType"] == "BinaryOperation") {
		return expression(ctx["rightHandSide"], global, leftCode);
	}
	else return false;
}

bool expression(Json::Value ctx, Verifier& global, string leftId) {
	if (ctx["nodeType"] == "BinaryOperation") {
		string op = ctx["operator"].asString();
		if (op != "+" && op != "-")
			return false;
		bool left = expression(ctx["leftExpression"], global, leftId);
		if (left)
			return true;
		bool right = expression(ctx["rightExpression"], global, leftId);
		return right;
	}

	if (ctx["nodeType"] == "UnaryOperation")
		return expression(ctx["expression"], global, leftId);

	return getCode(ctx, global) == leftId ? true : false;


}

SolEncode otherStmt(Json::Value ctx, Verifier& global) {
	string code = getCode(ctx, global);
	string enStr = encode(code, global);
	expr regex = to_re(global.ctx.string_val(enStr));
	if (global.decodeSol.find(enStr) == global.decodeSol.end())
		global.decodeSol[enStr] = ctx;
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
	typedef SolEncode(*pfunc)(Json::Value, Verifier& global);
	map<string, pfunc> switchCase;
	switchCase["Block"] = block;
	switchCase["ForStatement"] = forStmt;
	switchCase["IfStatement"] = ifStmt;
	switchCase["WhileStatement"] = whileStmt;
	switchCase["DoWhileStatement"] = doWhileStmt;
	string nodeType = ctx["nodeType"].asString();
	auto func = switchCase.find(nodeType) != switchCase.end() ? switchCase[nodeType] : otherStmt;
	SolEncode regularExp = func(ctx, global);
	return regularExp;
}

expr_vector readTrace(string trace, context& ctx) {
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
			exp = ctx.string_val(i);

		}
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

string toRawStr(std::string str) {
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

int prec(string op)
{
	map<string, int> switchPrec;
	switchPrec["!"] = 11;
	switchPrec["**"] = 10;
	switchPrec["*"] = 9; switchPrec["/"] = 9; switchPrec["%"] = 9;
	switchPrec["+"] = 8; switchPrec["-"] = 8;
	switchPrec["<<"] = 7; switchPrec[">>"] = 7;
	switchPrec["&"] = 6;
	switchPrec["^"] = 5;
	switchPrec["|"] = 4;
	switchPrec["<"] = 3; switchPrec[">"] = 3; switchPrec["<="] = 3; switchPrec[">="] = 3;
	switchPrec["=="] = 2; switchPrec["!="] = 2;
	switchPrec["&&"] = 1; switchPrec["||"] = 1;
	
	if (switchPrec.find(op) != switchPrec.end())
		return switchPrec[op];
	else return -1;


}

bool checkChar(char c) { // Check if char is a special character
	if (!(c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z' || c >= '0' && c <= '9'))
		return true;
	return false;
}

vector<string> splitExp(string str_exp) { // split exp string into mutiple components
	vector<string> cont;
	unsigned int start = 0;
	string op, temp;
	string op2letter[] = {"==", "&&", "||", "<=", ">=", "**", "!=", "<<", ">>"};
	char op1letter[] = { '+', '-', '*', '/', '%', '!', '~', '&', '|', '^', '<', '>', '(', ')' };
	int op2size = sizeof(op2letter)/ sizeof(*op2letter);
	int op1size = sizeof(op1letter) / sizeof(*op1letter);
	for (int i = 0; i < str_exp.size(); ++i) {
		// find operator in string and split it
		op = "";
		if (checkChar(str_exp[i])) {
			if (checkChar(str_exp[i + 1])) {
				if (find(op2letter, op2letter + op2size, str_exp.substr(i, 2)) != op2letter + op2size) 
					op = str_exp.substr(i, 2);
				else if(find(op1letter, op1letter + op1size, str_exp[i]) != op1letter + op1size)
					op  = string(1, str_exp[i]);
			}
			else {
				if (find(op1letter, op1letter + op1size, str_exp[i]) != op1letter + op1size)
					op = string(1, str_exp[i]);
			}
		}
		if (op != "") {
			temp = str_exp.substr(start, i - start);
			temp.erase(remove_if(temp.begin(), temp.end(), ::isspace), temp.end());
			if (temp != "")
				cont.push_back(temp);
			cont.push_back(op);
			start = i + op.size();
			i += op.size() - 1;
		}
	}
	temp = str_exp.substr(start, str_exp.size()
		- start);
	temp.erase(remove_if(temp.begin(), temp.end(), ::isspace), temp.end());
	if (temp != "")
		cont.push_back(temp);
	return cont;
}

void int2Bv(pair<expr*, TypeInfo>& p, int size) {
	*p.first = to_expr(p.first->ctx(), Z3_mk_int2bv(p.first->ctx(), size == NULL ? p.second.size : size, *p.first));
	p.second.type = BYTES;
}

void extend(pair<expr*, TypeInfo>& p, unsigned int i) {
	*p.first = to_expr(p.first->ctx(), Z3_mk_zero_ext(p.first->ctx(), i, *p.first));
	p.second.size += i;
}

void preCheck(pair<expr*, TypeInfo>& l, pair<expr*, TypeInfo>& r, string op) {
	string listOP[3] = { "&", "|", "^" };
	if (listOP->find(op) != string::npos && l.first->is_int() && r.first->is_int()) {
		int2Bv(l);
		int2Bv(r);
	}

	if (l.first->is_bv() && !r.first->is_bv())
		int2Bv(r, l.second.size);
	else if (!l.first->is_bv() && r.first->is_bv())
		int2Bv(l, r.second.size);
	else if (l.first->is_bv() && r.first->is_bv() && l.second.size != r.second.size)
		if (l.second.size > r.second.size)
			extend(r, l.second.size - r.second.size);
		else extend(l, r.second.size - l.second.size);
}

Json::Value createAssert(Json::Value param)
{
	Json::Value assert_, id;
	id["nodeType"] = "Identifier";
	id["name"] = "assert";

	assert_["nodeType"] = "FunctionCall";
	assert_["name"] = Json::arrayValue;
	assert_["expression"] = id;
	assert_["argumentTypes"] = Json::nullValue;
	assert_["arguments"] = Json::arrayValue;
	assert_["arguments"].append(param);
	return assert_;
}

Json::Value createUnary(Json::Value param, string op)
{
	Json::Value unary;
	unary["nodeType"] = "UnaryOperation";
	unary["subExpression"] = param;
	unary["typeDescriptions"] = param["typeDescriptions"];
	unary["operator"] = op;
	return unary;
}

Json::Value createExprStmt(Json::Value param)
{
	Json::Value exprStmt;
	exprStmt["nodeType"] = "ExpressionStatement";
	exprStmt["expression"] = param;
	return exprStmt;
}


vector<string> infixToPostfix(string str_exp) {
	vector<string> cont, result;
	stack<string> st;
	cont = splitExp(str_exp);
	for (auto i : cont) {
		switch(i[0]) {
		case '(':
			st.push("(");
			break;
		case ')':
			while (!st.empty() && st.top() != "(") {
				string temp = st.top();
				cout << temp << endl;
				st.pop();
				result.push_back(temp);
			}
			if (!st.empty() && st.top() == "(") 
				st.pop();
		
			break;
		case '+': case '-': case '*': case '/': case '=': case '%':
		case '&': case '|': case '<': case '>': case '^': case '!':
			while (!st.empty() && prec(i) <= prec(st.top()))
			{
				string temp = st.top();
				st.pop();
				result.push_back(temp);
			}
			st.push(i);
			break;
		default:
			result.push_back(i);
			break;
		}
	}
	while (!st.empty()) {
		string temp = st.top();
		st.pop();
		result.push_back(temp);
	}
	return result;
}

void getAllFunction(Json::Value ast, map<string, Json::Value>& functionsMap) {
	if (ast.isObject()) {
		if (!ast.isMember("nodeType"))
			return;
		else if (ast["nodeType"] == "FunctionDefinition" && !ast["body"].isNull()) {
			string name = ast["name"].asString();
			if (ast["kind"].asString() == "constructor")
				name += "constructor";
			functionsMap[name] = ast;
			return;
		}
		for (auto i : ast.getMemberNames()) {
			if (ast[i].isArray() || ast[i].isObject())
				getAllFunction(ast[i], functionsMap);
		}
	}
	else if (ast.isArray()) {
		for (auto i : ast)
			if (i.isArray() || i.isObject())
				getAllFunction(i, functionsMap);
	}
}

TreeRoot* convertFunction(Json::Value, int depth)
{
	return nullptr;
}


expr getVar(string varname, TypeInfo type, context& ctx) {
	string var;

	switch (type.type) {
	case UINT:
	{
		expr a = ctx.int_const(varname.c_str());
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
	case STRING:
	{
		expr a = makeStringFunction(&ctx, varname);
		return a;
	}
	case ARRAY:
	{
		expr a = ctx.constant(ctx.str_symbol(varname.c_str()), getSort(type, ctx));
		return a;
	}
	default:
	{
		throw "Wrong Type: ";

	}
	}
}

expr getVal(string value, TypeInfo type, context& ctx) {
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
	case STRING:
		return ctx.string_val(value);
	default:
		cout << "Wrong Type: " << type.type << endl;
		return ctx.int_val(0);
	}
}

z3::sort getSort(TypeInfo type, context& ctx)
{
	switch (type.type) {
	case UINT: case INT:
		return ctx.int_sort();
	case BOOL:
		return ctx.bool_sort();
	case ADDRESS:
		return ctx.bv_sort(160);
	case BYTES:
		return ctx.bv_sort(type.size);
	case STRING:
		return ctx.string_sort();
	case ARRAY:
		return ctx.array_sort(ctx.int_sort(), getSort({ type.type2, type.size }, ctx));
	default:
		throw "WRONG TYPE";
	}
}

TypeInfo getType(Json::Value exp) {
	string type = exp["typeDescriptions"]["typeString"].asString();
	bool isLiteral = exp["nodeType"].asString() == "Literal" || type.find("const") != string::npos;
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
	if (type.find("literal_string") != string::npos)
		if (exp["value"].isNull()) 
			return { BYTES, 256 }; 
		else 
			return{ STRING, 256 };
	if (type.find("string") != string::npos)
		return { STRING, 256 };
	if (type.find("tuple()") != string::npos)
		return{ VOID, 0 };
	
}

map<string, pfunc> getOpConvert()
{
	map<string, pfunc> opConvert;
	opConvert["="] = eq;
	opConvert["=="] = eq;
	opConvert["!="] = neq;
	opConvert["||"] = orOp;
	opConvert["&&"] = andOp;
	opConvert["**"] = exp;
	opConvert["<"] = lt;
	opConvert["<="] = le;
	opConvert[">"] = gt;
	opConvert[">="] = ge;
	opConvert["u<"] = ult;
	opConvert["u<="] = ule;
	opConvert["u>"] = ugt;
	opConvert["u>="] = uge;
	opConvert["+"] = add;
	opConvert["-"] = minusUti;
	opConvert["*"] = mul;
	opConvert["/"] = div;
	opConvert["%"] = mod;
	opConvert["|"] = bvor;
	opConvert["&"] = bvand;
	opConvert["^"] = bvxor;
	opConvert["u-"] = neg;
	opConvert["u!"] = notOP;
	opConvert["u~"] = bvneg;
	opConvert["u++"] = uplus2;
	opConvert["u--"] = uminus2;
	opConvert["udelete"] = udelete;
	return opConvert;
}