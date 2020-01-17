#include "verifier.h"
#include "utility.h"


void Verifier::checkSas(string exp) {

	auto opConvert = getOpConvert();
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
	solver s(ctx);
	map<string, string> encodeDict;
	int index = 0;
	expr_vector traces = readTrace(traces_str, encodeDict, index);
	cout << "Trace: " << traces << endl;
	for (auto i : Lencode) {
		cout << removeCond(i.encodeStr) << " ";
		s.push();
		expr_vector vec = getAllPath(i.regEx);
		z3::check_result isSat = unsat;
		for (auto path : vec) {
			cout << path.get_string() << endl;
			expr genPath = generalization(path, encodeDict, index);
			cout << "Generalization: " << genPath << endl;;
			isSat = checkOnePath(traces, genPath, traces_str, path.get_string());
			if (isSat == sat)
				break;
		}
		cout << isSat << endl;
		s.pop();
	}

}

expr_vector Verifier::getAllPath(expr exp) {
	solver s(ctx);
	expr str_const = makeStringFunction(&ctx, "T");
	s.add(in_re(str_const, exp));
	expr_vector vec(ctx);
	while (s.check() == sat) {
		model m = s.get_model();
		expr val = m.eval(str_const);
		vec.push_back(val);
		s.add(str_const != val);
	}
	return vec;
}

check_result Verifier::checkOnePath(expr_vector trace, expr path, string traces_str, string ungenPath) {
	solver s(ctx);
	s.add(concat(trace) == path);
	while (s.check() == sat) {
		model m = s.get_model();
		cout << "Path: " << ungenPath << endl;
		if (checkCondofTrace(traces_str, m, trace, ungenPath)) {
			return sat;
		}
		else {
			expr_vector orExp(ctx);
			for (auto j : trace) {
				if (j.is_const())
					orExp.push_back(j != m.eval(j));
			}
			s.add(mk_or(orExp));
		}
	}
	return unsat;
}

expr Verifier::generalization(expr path, map<string, string>& encodeDict, int& index) {
	vector<string> splitPath;
	string strPath = path.get_string();
	expr_vector newPath(ctx);
	for (int i = 0; i < strPath.length(); i++)
		if (strPath[i] != '_')
			splitPath.push_back(string(1, strPath[i]));
		else
			splitPath.back() += strPath.substr(i++, 2);
	for (auto i : splitPath) {
		Json::Value decode = decodeSol[i];
		SolEncode temp = statementEncode(decode, encodeDict, index);
		newPath.push_back(temp.regEx);
	}
	//newPath.push_back(to_re(ctx.string_val("a")));
	//newPath.push_back(to_re(ctx.string_val("b")));
	expr result = concat(newPath);
	return result;

}

SolEncode Verifier::statementEncode(Json::Value c, map<string, string>& encodeDict, int& index) {
	if (c["nodeType"] == "ExpressionStatement" && c["expression"]["nodeType"] == "Assignment" && assignment(c["expression"])) {
		string code = "a=a+n";
		string enStr = encode(code, encodeDict, index);
		expr regex = ctx.string_val(enStr);
		return{ enStr, regex };
	}
	else {
		string code = getCode(c);
		string enStr = encode(code, encodeDict, index);
		expr regex = ctx.string_val(enStr);
		return{ enStr, regex };
	}
}

bool Verifier::assignment(Json::Value ctx) {
	string leftCode = getCode(ctx["leftHandSide"]);
	if (ctx["operator"] == "+=" || ctx["operator"] == "-=")
		return true;
	if (ctx["rightHandSide"]["nodeType"] == "BinaryOperation") {
		return expression(ctx["rightHandSide"], leftCode);
	}
	else return false;
}

bool Verifier::expression(Json::Value ctx, string leftId) {
	if (ctx["nodeType"] == "BinaryOperation") {
		string op = ctx["operator"].asString();
		if (op != "+" && op != "-")
			return false;
		bool left = expression(ctx["leftExpression"], leftId);
		if (left)
			return true;
		bool right = expression(ctx["rightExpression"], leftId);
		return right;
	}

	if (ctx["nodeType"] == "UnaryOperation")
		return expression(ctx["expression"], leftId);

	return getCode(ctx) == leftId ? true : false;
}

list<TreeNode> Verifier::visit(Json::Value ctx, int depth)
{
	typedef list<TreeNode> (Verifier::* pfunc)(Json::Value, int);
	map<string, pfunc> switchCase;
	switchCase["Block"] = &Verifier::block;
	switchCase["IfStatement"] = &Verifier::ifStmt;
	switchCase["ForStatement"] = &Verifier::forStmt;
	switchCase["ExpressionStatement"] = &Verifier::exprStmt;
	switchCase["FunctionCall"] = &Verifier::functionCall;
	switchCase["FunctionDefinition"] = &Verifier::functionDef;
	string nodeType = ctx["nodeType"].asString();
	auto func = switchCase.find(nodeType) != switchCase.end() ? switchCase[nodeType] : &Verifier::otherStmt;
	auto result = (this->*func)(ctx, depth);

	return result;
}

list<TreeNode> Verifier::block(Json::Value ctx, int depth)
{
	list<TreeNode> result;
	for (auto statement : ctx["statements"]) {
		auto stmt = visit(statement, depth);
		result.splice(result.end(), stmt);
	}
	return result;
}

list<TreeNode> Verifier::ifStmt(Json::Value ctx, int depth)
{
	list<TreeNode> result;
	list<TreeNode> cond = visit(ctx["condition"], depth);
	list<TreeNode> cond2(cond);
	list<TreeNode> trueCond = visit(ctx["trueBody"], depth);
	list<TreeNode> falseCond = !ctx["falseBody"].isNull() ? visit(ctx["falseBody"], depth) : list<TreeNode>();
	result.push_back(TreeNode("assert("));
	result.splice(result.end(), cond);
	result.push_back(TreeNode(");"));
	result.splice(result.end(), trueCond);
	result.push_back(TreeNode("+assert(!"));
	result.splice(result.end(), cond2);
	result.push_back(TreeNode(");"));
	result.splice(result.end(), falseCond);

	return result;
}

list<TreeNode> Verifier::forStmt(Json::Value ctx, int depth)
{
	list<TreeNode> result;
	list<TreeNode> initExpr = visit(ctx["initializationExpression"], depth);
	list<TreeNode> cond = visit(ctx["condition"], depth);
	list<TreeNode> cond2(cond);
	list<TreeNode> loopExpr = visit(ctx["loopExpression"], depth);
	list<TreeNode> body = visit(ctx["body"], depth);

	result.splice(result.end(), initExpr);
	result.push_back(TreeNode(";(assert("));
	result.splice(result.end(), cond);
	result.push_back(TreeNode(");"));
	result.splice(result.end(), body);
	result.splice(result.end(), loopExpr);
	result.push_back(TreeNode(")*;assert(!"));
	result.splice(result.end(), cond2);
	result.push_back(TreeNode(")"));

	return result;
}

list<TreeNode> Verifier::whileStmt(Json::Value ctx, int depth)
{
	list<TreeNode> result;
	list<TreeNode> cond = visit(ctx["condition"], depth);
	list<TreeNode> body = visit(ctx["body"], depth);
	list<TreeNode> cond2(cond);
	result.push_back(TreeNode(";(assert("));
	result.splice(result.end(), cond);
	result.push_back(TreeNode(");"));
	result.splice(result.end(), body);
	result.push_back(TreeNode(")*;assert(!"));
	result.splice(result.end(), cond2);
	result.push_back(TreeNode(")"));

	return result;
}

list<TreeNode> Verifier::doWhileStmt(Json::Value ctx, int depth)
{
	list<TreeNode> result;
	list<TreeNode> body = visit(ctx["body"], depth);
	result.splice(result.end(), body);
	list<TreeNode> while_ = whileStmt(ctx, depth);
	result.splice(result.end(), while_);

	return result;
}

list<TreeNode> Verifier::exprStmt(Json::Value ctx, int depth)
{
	return visit(ctx["expression"], depth);
}

list<TreeNode> Verifier::otherStmt(Json::Value ctx, int depth)
{
	list<TreeNode> result;
	string code = getCode(ctx);
	result.push_back(TreeNode(encode(code, encodeSol, index)));
	return result;
}

list<TreeNode> Verifier::functionCall(Json::Value ctx, int depth)
{
	list<TreeNode> result;
	string name = ctx["expression"]["name"].asString();
	map<string, Json::Value>::iterator iter;
	if (depth == 0 || (iter = functionsMap.find(name)) == functionsMap.end()) {
		return otherStmt(ctx, depth);
	};
	auto temp = visit(iter->second, depth - 1);
	result.push_back(TreeNode("#t", temp));
	return result;
}

list<TreeNode> Verifier::functionDef(Json::Value ctx, int depth)
{
	return visit(ctx["body"], depth);
}

void Verifier::getAllFunction(Json::Value ast)
{
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
				getAllFunction(ast[i]);
		}
	}
	else if (ast.isArray()) {
		for (auto i : ast)
			if (i.isArray() || i.isObject())
				getAllFunction(i);
	}
}

TreeRoot* Verifier::convertFunction(Json::Value func, int depth)
{
	auto listTree = visit(func, depth);
	return new TreeRoot(listTree);
}

bool Verifier::checkCondofTrace(string traces_str, model m, expr_vector vars, string path) {
	auto listContraint = getConstraints(traces_str, m, vars);
	map<string, pfunc> opConvert = getOpConvert();
	map<string, pair<TypeInfo, int>> vars_m;
	solver s(ctx);
	int j = 0;
	for (auto i : listContraint) {
		for (;j < i.second; ++j)
			if (decodeSol[string(1, path[j])]["nodeType"] == "ExpressionStatement") {
				auto expr = convertToZ3(decodeSol[string(1, path[j])]["expression"], s, opConvert, vars_m);
				cout << expr.first << endl;
				s.add(expr.first);
				
			}
		try {
			increaseVar(s, vars_m);
			expr exp = calculate(i.first, vars_m);
			cout << exp << endl;
			s.add(exp);
		}
		catch (const char* msg) {
			cout << msg << endl;
			return false;
		}

	}
	cout << "Solver: " << s << endl;
	cout << s.check() << endl;
	if (s.check() == sat)
		return true;
	else return false;
}

vector<pair<string, int>> Verifier::getConstraints(string traces_str, model m, expr_vector vars) {
	vector <string> cont;
	vector <pair<string, int>> result;
	expr_vector vec(ctx);
	unsigned int index = 1;
	int pos = 0;
	split(traces_str, cont, "->");
	for (int i = 0; i < cont.size(); i++) {
		if (cont[i] == "T") {
			string T = m.eval(vars[i]).get_string();
			pos += T.length();
		}
		else {
			int start = 0;
			for (int j = 0; j < cont[i].size(); j++)
				if (cont[i][j] == '{' || cont[i][j] == '}') {
					string get = cont[i].substr(start, j - start);
					start = j + 1;
					if (get == "")
						continue;
					if (cont[i][j] == '{') 
						pos += count(get.begin(), get.end(), ';');
					else result.push_back({ get, pos });
				}

		}
	}
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
		expr expression = temp(left.first, right.first);

		return{ expression, type };
	}
	else  if (exp["nodeType"] == "UnaryOperation") {
		cout << "A" << endl;
		string op, expOP = exp["operator"].asString();;
		auto subExp_pair = convertToZ3(exp["subExpression"], s, opConvert, vars);
		expr subExp = opConvert["u" + expOP](subExp_pair.first, ctx.int_val(0));
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
			bool first = true;
			int num = 0;
			if (vars.find(code) == vars.end())
				vars[code] = { type, 0 };
			else {
				if (increase)
					vars[code].second++;
				else first = false;
				num = vars[code].second;
			}
			string varname = code + to_string(num);
			return{ getVar(varname, type, s, first), type };
		}
	}
}

expr Verifier::getVar(string varname, TypeInfo type, solver& s, bool first) {
	string var;

	switch (type.type) {
	case UINT:
	{
		expr a = ctx.int_const(varname.c_str());
		if (first)
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
	if (location.size() == 0)
		cout << ctx << endl;
	return sourceCode.substr(stoi(location[0]), stoi(location[1]));
}

string Verifier::encode(string code, map<string, string> & encodeDict, int& i) {
		if (encodeDict.find(code) != encodeDict.end())
			return encodeDict[code];
		int& index = i;
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
		encodeDict[code] = encode_str;

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

expr_vector Verifier::readTrace(string trace, map<string, string>& encodeDict, int& index) {
	vector <string> cont;
	expr_vector vec(ctx);
	unsigned int ind = 1;
	split(trace, cont, "->");
	for (auto i : cont) {
		expr exp(ctx);
		if (i == "T") {
			exp = makeStringFunction(&ctx, "T" + to_string(ind));
			ind++;
		}
		else {
			vector <string> cont2;
			i = removeCond(i);
			split(i, cont2, ';');
			string result = "";
			for (auto j : cont2) {
				ANTLRInputStream input(j + ";");
				SolidityLexer lexer(&input);
				CommonTokenStream tokens(&lexer);
				SolidityParser parser(&tokens);
				SolidityParser::StatementContext* tree = parser.statement();
				Visitor visitor;
				string code = visitor.visitStatement(tree).as<string>();
				code = encode(code, encodeDict, index);
 				result += code;
			}
			exp = ctx.string_val(result);

		}
		vec.push_back(exp);
	}
	return vec;
}

bool isOperator(string str) {
	if (str[0] >= 'a' && str[0] <= 'z' || str[0] >= 'A' && str[0] <= 'Z' || str[0] >= '0' && str[0] <= '9')
		return false;
	else return true;
}

expr Verifier::convertToExp(string str, map < string, pair<TypeInfo, int>> vars)  {
	solver s(ctx);
	if (vars.find(str) != vars.end()) {
		string varname = str + to_string(vars[str].second);
		return getVar(varname, vars[str].first, s);
	} else {
		TypeInfo type;
		if (str == "true" || str == "false")
			type = { BOOL, 1 };
		else if (str[0] >= '0' && str[0] <= '9')
			type = { INT, 256 };
		else {
			throw "ID not found";

		}
		return getVal(str, type, s);
	}
}

/*expr Verifier::calculate(string exp, map < string, pair<TypeInfo, int>> vars) {
	vector<string> postfix = infixToPostfix(exp);
	map<string, pfunc> opConvert = getOpConvert();
	stack<expr> st;
	expr sub(ctx);
	for (auto i : postfix) {
		if (isOperator(i)) {
			if (i == "!") {
				//Unary
				sub = st.top();
				st.pop();
				st.push(!sub);
				break;
			}
			else {  //Binary
				expr r = st.top();
				st.pop();
				expr l = st.top();
				st.pop();
				pfunc op = opConvert[i];
				expr exp = (this->*op)(l, r);
				st.push(exp);
				break;
			}
			
		}
		else st.push(convertToExp(i, vars));
	}
	expr result = st.top();
	st.pop();
	if (!st.empty())
		cout << "ERROR" << endl;
	return result;
}*/

expr Verifier::calculate(string exp, map < string, pair<TypeInfo, int>> vars) {
	ANTLRInputStream input(exp);
	SolidityLexer lexer(&input);
	CommonTokenStream tokens(&lexer);
	SolidityParser parser(&tokens);
	SolidityParser::ExpressionContext* tree = parser.expression();
	CalVisitor visitor(&ctx, vars);
	expr result = visitor.visitExpression(tree).as<expr>();

	return result;
}

void Verifier::increaseVar(solver& s, map < string, pair<TypeInfo, int>>& vars) {
	for (auto i : extract_keys(vars)) {
		string oldVarname = i + to_string(vars[i].second), newVarname = i + to_string(vars[i].second + 1);
		vars[i].second++;
		expr old = getVar(oldVarname, vars[i].first, s);
		expr newV = getVar(newVarname, vars[i].first, s, true);
		s.add(old == newV);
	}
}