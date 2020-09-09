#include "utility.h"
#include "verifier.h"
#include "Visitor.h"
#include "type.h"


Json::Value readJson(string filename) {
	ifstream file(filename);
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

string getCode(Json::Value ctx)
{
	typedef string(*pfunc)(Json::Value);
	map<string, pfunc> switchCase;

	switchCase["ExpressionStatement"] = getExprStmtStr;
	switchCase["Identifier"] = getIdStr;
	switchCase["FunctionCall"] = getFuncCallStr;
	switchCase["Assignment"] = getAssignStr;
	switchCase["BinaryOperation"] = getBinaryOpStr;
	switchCase["UnaryOperation"] = getUnaryOpStr;
	switchCase["IndexAccess"] = getIndexAccessStr;
	switchCase["MemberAccess"] = getMemberAccessStr;
	switchCase["ParameterList"] = getParaListStr;
	switchCase["VariableDeclaration"] = getVarDeclStr;
	switchCase["Literal"] = getLitStr;
	switchCase["TupleExpression"] = getTupleExpStr;
	switchCase["ElementaryTypeName"] = getEleTypeNameStr;
	switchCase["UserDefinedTypeName"] = getUserDefTypeNameStr;
	switchCase["ArrayTypeName"] = getArrayTypeNameStr;
	switchCase["EmitStatement"] = getEmitStmtStr;
	switchCase["Return"] = getReturnStr;
	switchCase["ElementaryTypeNameExpression"] = getEleTypeNameExpStr;
	switchCase["VariableDeclarationStatement"] = getVarDeclStmtStr;
	switchCase["NewExpression"] = getNewExpStr;
	switchCase["Conditional"] = getCondStr;
	switchCase["Mapping"] = getMappingStr;
	string nodeType = ctx["nodeType"].asString();
	auto func = switchCase.find(nodeType) != switchCase.end() ? switchCase[nodeType] : getOtherStr;
	string result = func(ctx);
	return result;
}

void addExp(Json::Value exp, string codeExcute, bool isTrue, Verifier& global) {
	string codeExp = getCode(exp);
	if (!isTrue)
		codeExp = "!(" + codeExp + ")";
	if (global.expList.find(codeExp) == global.expList.end()) {
		ExpInfo expInfo = { { codeExcute }, exp, isTrue };
		global.expList[codeExp] = expInfo;
	}
	else global.expList[codeExp].codeActivates.push_back(codeExcute);
}

/*SolEncode block(Json::Value ctx, Verifier& global) {
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
}*/

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

size_t find(string str, size_t from, map<string, string> m) {
	for (size_t i = from; i < str.length(); i++)
		if (m.find(str.substr(i, 2)) != m.end())
			return i;
	return string::npos;
}

string toRawStr(std::string str) {
	/*size_t start_pos = 0;
	map<char, string> spChar;
	spChar['\n'] = "\\n"; spChar['\t'] = "\\t";
	while ((start_pos = find(str, start_pos, spChar)) != std::string::npos) {
		string to = spChar[str[start_pos]];
		str.replace(start_pos, 1, to);
		start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
	}
	return str;*/
	Json::Value raw(str);
	stringstream r;
	r << raw;
	return r.str();
}

std::string replaceAll(std::string str)
{
	size_t start_pos = 0;
	map<string, string> spChar;
	spChar["\\n"] = "\n"; spChar["\\t"] = "\t"; spChar["\\v"] = "\v"; spChar["\\f"] = "\f";
	spChar["\\r"] = "\r"; spChar["\\b"] = "\b"; spChar["\\\""] = "\"";
	while ((start_pos = find(str, start_pos, spChar)) != std::string::npos) {
		string to = spChar[str.substr(start_pos, 2)];
		str.replace(start_pos, 2, to);
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

string exec(const char* cmd) {
	std::array<char, 128> buffer;
	std::string result;
	std::shared_ptr<FILE> pipe(_popen(cmd, "r"), _pclose);
	if (!pipe) throw std::runtime_error("popen() failed!");
	while (!feof(pipe.get())) {
		if (fgets(buffer.data(), 128, pipe.get()) != nullptr)
			result += buffer.data();
	}
	return result;
}

void bv2int(pair<expr*, ValType*>& p)
{
	context& c = p.first->ctx();
	if (typeid(*p.second) == typeid(UInt)) {
		*p.first = to_expr(c, Z3_mk_bv2int(c, *p.first, false));
	}
	else if (typeid(*p.second) == typeid(Int)) {
		*p.first = to_expr(c, Z3_mk_bv2int(c, *p.first, true));
	}
}

void int2Bv(pair<expr*, ValType*>& p, int size) {
	*p.first = to_expr(p.first->ctx(), Z3_mk_int2bv(p.first->ctx(), size == NULL ? p.second->getSize() : size, *p.first));
	p.second = &Byte(p.second->getSize());
}

bool* str2bv(string str)
{
	bool* bv = new bool[str.size() * 8];
	for(size_t i = 0; i < str.size(); ++i)
	{
		string temp = bitset<8>(str.c_str()[i]).to_string();
		for (size_t j = 0; j < temp.size(); ++j)
			bv[8 * i + j] = temp[j] == '1';
	}
	return bv;
}

std::string str2hex(std::string str)
{
	auto bi = str2bv(str);
	string temp = "";
	for (auto i = 0; i < str.size() * 8; ++i)
		temp += to_string(bi[i]);
	return "0x" + bi2hex(temp);
}

const char* hex_char_to_bin(char c)
{
	switch (toupper(c)) 
	{
	case '0': return "0000";
	case '1': return "0001";
	case '2': return "0010";
	case '3': return "0011";
	case '4': return "0100";
	case '5': return "0101";
	case '6': return "0110";
	case '7': return "0111";
	case '8': return "1000";
	case '9': return "1001";
	case 'A': return "1010";
	case 'B': return "1011";
	case 'C': return "1100";
	case 'D': return "1101";
	case 'E': return "1110";
	case 'F': return "1111";
	default: throw "invalid char";
	}
}

std::string hex_str_to_bin_str(const std::string& hex)
{
	std::string bin;
	std::string _hex = hex.substr(0, 2) == "0x" ? hex.substr(2) : hex;
	for (unsigned i = 0; i != _hex.length(); ++i)
		bin += hex_char_to_bin(_hex[i]);
	return bin;
}

bool* hex_str_to_bool_arr(unsigned n, std::string hex)
{
	bool* arr = new bool[n] {false};
	std::string bin_str = hex_str_to_bin_str(hex);

	for (int i = 0; i < bin_str.size(); ++i) {
		arr[i] = bin_str[bin_str.size() - i - 1] == '0' ? false : true;
	}
	return arr;
}

std::string toHex(expr a, int size)
{
	context& c = a.ctx();
	expr hexVal = c.bv_val(a.get_decimal_string(0).c_str(), size * 4);
	std::string hexStr = hexVal.to_string().substr(2);
	if (a.get_decimal_string(0) != "0" & hexStr == string(size, '0')) // for the overflow of a;
		hexStr = string(size, 'f');
	return hexStr;
}

std::string toHexSigned(expr a, int size)
{
	if (a.get_decimal_string(0)[0] != '-')
		return toHex(a, size);
	string temp = '1' + string(size * 4, '0'); // 2 ^ (size * 4);
	context& c = a.ctx();
	expr x = c.int_const("x");
	expr twoComp = c.int_val(c.bv_val(temp.c_str(), size * 4 + 1).get_decimal_string(0).c_str()) + a;
	solver s(c);
	s.add(x == twoComp);
	s.check();
	if (s.check())
		cout << s.get_model() << endl;
	else cout << "Error" << endl;
	model m = s.get_model();
	expr hexVal = c.bv_val(m.eval(x).get_decimal_string(0).c_str(), size * 4);

	return hexVal.to_string().substr(2);
}

void extend(pair<expr*, ValType*>& p, unsigned int i) {
	*p.first = to_expr(p.first->ctx(), Z3_mk_zero_ext(p.first->ctx(), i, *p.first));
	p.second->changeSize(p.second->getSize() + i);
}

void preCheck(pair<expr*, ValType*>& l, pair<expr*, ValType*>& r, string op) {
	vector<string> vec = { "&", "|", "^", "**", ">>", "<<" };
	if (find(vec.begin(), vec.end(), op) != vec.end() && l.first->is_int() && r.first->is_int()) {
		int2Bv(l);
		int2Bv(r);
	}


	if (l.first->is_bv() && !r.first->is_bv())
		int2Bv(r, l.second->getSize());
	else if (!l.first->is_bv() && r.first->is_bv())
		int2Bv(l, r.second->getSize());
	else if (l.first->is_bv() && r.first->is_bv() && l.second->getSize() != r.second->getSize())
		if (l.second->getSize() > r.second->getSize())
			extend(r, l.second->getSize() - r.second->getSize());
		else extend(l, r.second->getSize() - l.second->getSize());
}

void misMatch(pair<expr*, ValType*>& result)
{
	if (result.first->is_bv() && typeid(*result.second) != typeid(Byte)) {
		bv2int(result);
	}
	else if (result.first->is_int() && typeid(*result.second) == typeid(Byte)) {
		int2Bv(result);
	}
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

Json::Value createBinary(Json::Value left, Json::Value right, Json::Value type, string op)
{
	Json::Value binary;
	binary["nodeType"] = "BinaryOperation";
	binary["leftExpression"] = left;
	binary["rightExpression"] = right;
	binary["operator"] = op;
	binary["typeDescriptions"] = type;
	return binary;
}

Json::Value createExprStmt(Json::Value param)
{
	Json::Value exprStmt;
	exprStmt["nodeType"] = "ExpressionStatement";
	exprStmt["expression"] = param;
	return exprStmt;
}

Json::Value createVarDeclStmt(Json::Value varDecl, Json::Value init)
{
	Json::Value varDeclStmt;
	varDeclStmt["declarations"] = Json::arrayValue;
	varDeclStmt["declarations"].append(varDecl);
	varDeclStmt["initialValue"] = init;
	varDeclStmt["nodeType"] = "VariableDeclarationStatement";

	return varDeclStmt;
}

Json::Value createAssign(Json::Value left, Json::Value right, string op)
{
	Json::Value assign;
	assign["nodeType"] = "Assignment";
	assign["leftHandSide"] = left;
	assign["rightHandSide"] = right;
	assign["operator"] = op;
	assign["typeDescriptions"] = left["typeDescriptions"];

	return assign;
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

ValType* getType(Json::Value exp) {
	string type = exp["typeDescriptions"]["typeString"].asString();
	bool isLiteral = exp["nodeType"].asString() == "Literal" || type.find("const") != string::npos;
	vector<string> cont;
	split(type, cont, " ");
	if (cont[0] == "enum") {
		string enumName = cont[1] + ".Enum";
		auto enumType = EVisitor::findGlobalVar(enumName);
		if (enumType.first == NULL)
			throw std::exception("Can't find Struc: ");
		return dynamic_cast<Enum*>(enumType.first);
	}
	if (cont[0] == "bytes")
		return NULL;
	type = cont[0];
	if(type.find("[") != string::npos)
		return NULL;
	/*if (type.find("tuple") != string::npos)
		return NULL;*/
	if (type.substr(0, 3) == "int")
		return new Int(isLiteral ? 256 : stoul(type.substr(3, type.length())));
	if (type.substr(0, 4) == "uint")
		return new UInt(isLiteral ? 256 : stoul(type.substr(4, type.length())) );
	if (type.substr(0, 4) == "bool")
		return new Bool() ;
	if (type.substr(0, 7) == "address")
		return new Address();
	if (type.substr(0, 5) == "bytes")
		return new Byte(stoul(type.substr(5, type.length())) * 8);
	if (type.substr(0, 14) == "literal_string")
			return new Byte(256, true); 
	if (type.substr(0, 6) == "string")
		return  new Byte(256, true);
	/*if (type.find("tuple()") != string::npos)
		return NULL;
	if (type.find("msg") != string::npos)
		return NULL;
	if (type.find("block") != string::npos)
		return NULL;*/
	return NULL;
	//throw "Other type: " + type;
}

Type* getType(string type) {

	if (type.substr(0, 3) == "int")
		return new Int(stoul(type.substr(3, type.length())));
	if (type.substr(0, 4) == "uint")
		return new UInt(stoul(type.substr(4, type.length())));
	if (type.substr(0, 4) == "bool")
		return new Bool();
	if (type.substr(0, 7) == "address")
		return new Address();
	if (type.substr(0, 5) == "bytes")
		return new Byte(stoul(type.substr(5, type.length())) * 8);
	vector<string> cont;
	split(type, cont, " ");
	if (cont[0] == "enum") {
		string enumName = cont[1] + ".Enum";
		auto enumType = EVisitor::findGlobalVar(enumName);
		if (enumType.first == NULL)
			throw std::exception("Can't find Enum: ");
		return dynamic_cast<Enum*>(enumType.first);
	}
	else if (cont[0] == "struct") {
		string structName = cont[1] + ".Struct";
		auto structType = EVisitor::findGlobalVar(structName);
		if (structType.first == NULL)
			throw std::exception("Can't find Struct: ");
		return dynamic_cast<Struct*>(structType.first);
	}
	return NULL;
}

Type* getAllType(Json::Value exp)
{
	string typeName = exp["typeDescriptions"]["typeString"].asString();
	vector<string> cont;
	size_t t;
	split(typeName, cont, " ");
	if ((t = typeName.find("[")) != string::npos) {
		auto temp = getType(typeName.substr(0, t));
		if (temp == NULL)
			return NULL;
		return new DynamicArray(temp);
	}
	if (cont[0] == "struct") {
		string structName = cont[1] + ".Struct";
		auto type = EVisitor::findGlobalVar(structName);
		if (type.first == NULL)
			throw std::exception("Can't find Struc: ");
		return type.first;
	}
	if (cont[0] == "enum") {
		string enumName = cont[1] + ".Enum";
		auto type = EVisitor::findGlobalVar(enumName);
		if (type.first == NULL)
			throw std::exception("Can't find Struc: ");
		return type.first;
	}
	if (cont[0] == "bytes")
		return new Byte(256, true);
	if (cont[0] == "class")
		return NULL;
	
	return getType(exp);

}

Type* getVarDeclType(Json::Value code, solver& s)
{
	typedef Type* (*pfunc)(Json::Value, solver& s);
	map<string, pfunc> switchCase;
	switchCase["ElementaryTypeName"] = eleType;
	switchCase["ArrayTypeName"] = arrType;
	switchCase["Mapping"] = mapType;
	switchCase["UserDefinedTypeName"] = userDefType;
	if (switchCase.find(code["nodeType"].asString()) == switchCase.end())
		return NULL; //User Define Type;
	auto func = switchCase[code["nodeType"].asString()];
	return (*func)(code, s);
}

map<string, string> getTypeConstraint(string typeConstraint)
{
	vector<string> cont;
	split(typeConstraint, cont, ';');
	Visitor visitor;
	for (auto i : cont) {
		ANTLRInputStream input(i + ';');
		SolidityLexer lexer(&input);
		CommonTokenStream tokens(&lexer);
		SolidityParser parser(&tokens);
		SolidityParser::TypeDeclContext* tree = parser.typeDecl();
		visitor.visitTypeDecl(tree);
	}


	return visitor.getType();
}

Type* mapType(Json::Value code, solver& s)
{
	vector<Type*> list_index;
	list_index.push_back(getVarDeclType(code["keyType"], s));
	Json::Value array_type = code["valueType"];
	while (array_type["nodeType"] == "Mapping") {
		list_index.push_back(getVarDeclType(array_type["keyType"], s));
		array_type = array_type["valueType"];
	}
	Type* value_type = getVarDeclType(array_type, s);
	//auto m = new Map(getVarDeclType(code["keyType"], s), getVarDeclType(code["valueType"], s));
	auto m = new Map(list_index, value_type);
	return m;
}

Type* userDefType(Json::Value code, solver& s)
{
	vector<string> cont;
	split(code["typeDescriptions"]["typeString"].asString(), cont, " ");
	string name;
	if (cont[0] == "struct")
		name = cont[1] + ".Struct";
	else if (cont[0] == "enum")
		name = cont[1] + ".Enum";
	else return NULL;
	auto userType = EVisitor::findGlobalVar(name);
	if (userType.first == NULL) {
		throw std::exception("Not found Struct or Enum");
	}
	return userType.first;
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
	opConvert[">>"] = rightShift;
	opConvert["<<"] = leftShift;
	opConvert["u-"] = neg;
	opConvert["u!"] = notOP;
	opConvert["u~"] = bvneg;
	opConvert["u++"] = uplus2;
	opConvert["u--"] = uminus2;
	opConvert["udelete"] = udelete;
	return opConvert;
}

string getParamStr(Json::Value paramList)
{
	string result = "";
	for (auto param : paramList) {
		result += param["typeDescriptions"]["typeString"].asString() + ",";
	}
	if (!result.empty())
		result.pop_back();
	return result;
}

string getIdStr(Json::Value json)
{
	return json["name"].asString();
}

string getLitStr(Json::Value json)
{
	return json["value"].isNull() ? json["hexValue"].asString() : json["value"].asString();;
}

string getCondStr(Json::Value json)
{
	string cond = getCode(json["condition"]);
	string trueExpr = getCode(json["trueExpression"]);
	string falseExpr = getCode(json["falseExpression"]);
	string result = cond + "?" + trueExpr + ":" + falseExpr;
	return result;
}

string getNewExpStr(Json::Value json)
{
	string result = "new" + getCode(json["typeName"]);
	return result;
}

string getAssignStr(Json::Value json)
{
	string left = getCode(json["leftHandSide"]);
	string right = getCode(json["rightHandSide"]);
	string result = left + json["operator"].asString() + right;
	return result;
}

string getReturnStr(Json::Value json)
{
	string exp = json["expression"].isNull() ? "" : getCode(json["expression"]);
	string result = "return" + exp + ";";
	return result;
}

string getVarDeclStr(Json::Value json)
{
	string typeName = json["typeName"].isNull() ? "var" : getCode(json["typeName"]);
	string result = typeName + " " + json["name"].asString();
	return result;
}

string getUnaryOpStr(Json::Value json)
{
	string sub = getCode(json["subExpression"]);
	string result = json["operator"].asString() + sub;
	return result;
}

string getBinaryOpStr(Json::Value json)
{
	string left = getCode(json["leftExpression"]);
	string right = getCode(json["rightExpression"]);
	string result = left + json["operator"].asString() + right;
	return result;
}

string getTupleExpStr(Json::Value json)
{
	string comps = "";
	for (auto comp : json["components"])
		comps += getCode(comp) + ";";
	string result = "(" + comps + ")";
	return result;
}

string getFuncCallStr(Json::Value json)
{
	string funName = getCode(json["expression"]);
	string args = "";
	for (auto arg : json["arguments"])
		args += getCode(arg) + ";";
	if (!args.empty())
		args.pop_back();
	string result = funName + "(" + args + ")";
	return result;
}

string getExprStmtStr(Json::Value json)
{
	return getCode(json["expression"]) + ";";
}

string getParaListStr(Json::Value json)
{
	string params = "";
	for (auto param : json["parameters"])
		params += getCode(param) + ",";
	if (!params.empty())
		params.pop_back();
	return params;
}

string getEmitStmtStr(Json::Value json)
{
	string result = "event" + getCode(json["eventCall"]) + ";";
	return result;
}

string getVarDeclStmtStr(Json::Value json)
{
	string varDecls = "";
	for (auto decl : json["declarations"])
		varDecls += getCode(decl) + ",";
	if (!varDecls.empty())
		varDecls.pop_back();
	string init = json["initialValue"].isNull() ? "" : "=" + getCode(json["initialValue"]);
	string result = varDecls + init + ";";
	return result;
}

string getEleTypeNameStr(Json::Value json)
{
	return json["name"].asString();
}

string getIndexAccessStr(Json::Value json)
{
	string baseExpr = getCode(json["baseExpression"]);
	string index = getCode(json["indexExpression"]);
	string result = baseExpr + "[" + index + "]";
	return result;
}

string getMemberAccessStr(Json::Value json)
{
	string expr = getCode(json["expression"]);
	string result = expr + "." + json["memberName"].asString();
	return result;
}

string getArrayTypeNameStr(Json::Value json)
{
	string baseType = getCode(json["baseType"]);
	string length = json["length"].isNull() ? "" : getCode(json["length"]);
	string result = baseType + "[" + length + "]";
	return result;
}

string getEleTypeNameExpStr(Json::Value json)
{
	return json["typeName"].asString();
}

string getUserDefTypeNameStr(Json::Value json)
{
	return json["name"].asString();
}

string getMappingStr(Json::Value json)
{
	string key = getCode(json["keyType"]);
	string value = getCode(json["valueType"]);
	string result = "mapping(" + key + "=>" + value + ")";
	return result;
}

string getOtherStr(Json::Value json)
{
	if (json["nodeType"].isNull())
		return "";
	string excep = "getString of other Nodetype: " + json["nodeType"].asString();
	cout << excep << endl;
	//throw std::exception(excep.c_str());
	string result = json["nodeType"].asString() + json["id"].asString();
	return result;
}
