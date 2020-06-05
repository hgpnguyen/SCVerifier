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
	map<string, pair<Type*, int>> vars;
	Json::Value temp = expList[exp].exp;
	expr expr_ = convertToZ3(temp, s, opConvert, vars).first;
	if (!expList[exp].isTrue)
		expr_ = !expr_;
	s.add(expr_);
	cout << " " << expr_ << endl;

	cout << s.check();

}

/*void Verifier::checkTrace(string traces_str) {
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

}*/

Report Verifier::checkTrace(vector<pair<string, string>> traces, string typeConstaint, TreeRoot& functionTree) {
	solver s(ctx);
	expr_vector traces_expr(ctx);
	ctx.set("timeout", 3000);

	expr union_ = ctx.int_val(1);
	map<string, string> typeConst = getTypeConstraint(typeConstaint);
	map<string, Json::Value>* decodeSol = functionTree.getDecode();
	for (auto key : UTILITY_H::extract_keys(*decodeSol)) {
		expr re = to_re(ctx.string_val(key));
		if (union_.is_re())
			union_ = union_ + re;
		else union_ = re;
	}

	for (auto t : traces) 
		if (t.first[0] == 'T') {
			expr exp = makeStringFunction(&ctx, t.first);
			traces_expr.push_back(exp);
			s.add(!prefixof(ctx.string_val("_"), exp)); // remove situation W1 = "e" and T1 = "_a"
			s.add(!suffixof(ctx.string_val("_"), exp)); // remove situation W1 = "e_" and T1 = "a"
		}
		else if (t.first[0] == 'W') {
			int num = count(t.second.begin(), t.second.end(), ';');
			expr exp = makeStringFunction(&ctx, t.first);
			if (!union_.is_re())					//Function with empty block
				return false;
			s.add(in_re(exp, union_.loop(num, num)));
			traces_expr.push_back(exp);
		}
	
	
	expr func = functionTree.getExpr(ctx, s);
	s.add(in_re(concat(traces_expr), func));
	//cout << functionTree.getDepth(true) << endl;
	check_result result;
	auto start = Clock::now();

	while ((result = s.check()) == sat) {
		model m = s.get_model();
		int index = 0;
		list<PathNode*> path;
		bool checkTrToCode = false;
		for (auto i : traces) {
			if (i.first[0] == 'T')
				path.splice(path.end(), convertToPath(m.eval(traces_expr[index++]).get_string(), m));
			else if (i.first[0] == 'W') {
				auto temp = convertToPath(m.eval(traces_expr[index++]).get_string(), m);
				checkTrToCode = mapTraceToCode(temp, i.second, typeConst, *decodeSol);
				path.splice(path.end(), temp);
			}
			else path.push_back(new CondNode(i.second));
		}
		/*if (checkTrToCode) {
			cout << "Model: " << m << endl;
			cout << "Path: ";
			for (auto i : path)
				cout << i->DepthFS() << " ";
			cout << endl;
		}
		*/
		Report re(false);
		if (!checkTrToCode || !(re = solvePath(path, *decodeSol, functionTree.getEncode())).result) {
			auto end = Clock::now();
			long long timeLimit = 100000 * TIMELIMIT;
			if ((end - start).count() / 1000 > timeLimit)
				return Report(false);
			s.add(removeOldSol(m, traces_expr));
		}
		else {
			return re;

		}
	}
	//cout << endl;
	return Report(false);
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

/*check_result Verifier::checkOnePath(expr_vector trace, expr path, string traces_str, string ungenPath) {
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
}*/

/*expr Verifier::generalization(expr path, map<string, string>& encodeDict, int& index) {
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

}*/

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

Report Verifier::solvePath(list<PathNode*> path, map<string, Json::Value> decodeSol, map<string, string> encodeSol)
{
	solver s(ctx);
	EVisitor visitor("", decodeSol, encodeSol);
	for (auto i : path) {
		i->toZ3(visitor, s);
	}
	auto result = s.check();
	//cout << s << endl;
	EVisitor::resetGlobalVarIndex();
	if (result == sat) {
		cout << "SAT" << endl;
		Report report(true, s.get_model());
		return report;
	}
	
	return Report(false);
}


list<PathNode*> Verifier::convertToPath(string path, model m)
{
	if(path == "")
		return list<PathNode*>();
	list<PathNode*> result;
	string statement = string(1, path[0]);
	for (int i = 1; i < path.size(); ++i) {
		if (path[i] == '_') {
			statement += path.substr(i++, 2);
		}
		else {
			expr funcVar = m.eval(makeStringFunction(&ctx, statement));
			if (funcVar.is_string_value()) {		//Check if statement is a FuntionCall or not/Check if it is a stirng var in model m
				auto l = convertToPath(funcVar.get_string(), m);
				result.push_back(new FuncNode(statement, l));
			}
			else result.push_back(new StmtNode(statement));
			statement = string(1, path[i]);
		}
	}
	expr funcVar = m.eval(makeStringFunction(&ctx, statement));
	if (funcVar.is_string_value()) {
		auto l = convertToPath(funcVar.get_string(), m);
		result.push_back(new FuncNode(statement, l));
	}
	else result.push_back(new StmtNode(statement));
	return result;
}

expr_vector Verifier::convertFuncCall(string var)
{
	return expr_vector(ctx);
}

bool Verifier::mapTraceToCode(list<PathNode*> path, string traces, map<string, string> typeConst, map<string, Json::Value>& decodeSol)
{
	vector<string> cont;
	split(traces, cont, ';');
	assert(path.size() == cont.size());
	int index = 0;
	MapVisitor visitor(CondNode::m, typeConst);
	for (auto p : path) {
		ANTLRInputStream input(cont[index++] + ';');
		SolidityLexer lexer(&input);
		CommonTokenStream tokens(&lexer);
		SolidityParser parser(&tokens);
		SolidityParser::StatementContext* tree = parser.statement();
		Json::Value code = decodeSol[p->getValue()];
		visitor.setJson(code);
		bool result = visitor.visitStatement(tree).as<bool>();
		if (!result)
			return false;
	}
	return true;
}

expr Verifier::removeOldSol(model& m, expr_vector vars)
{
	expr_vector orExp(ctx);
	for (int i = 0; i < m.size(); i++) {
		orExp.push_back(m[i]() != m.eval(m[i]()));
	}
	return mk_or(orExp);
}

void Verifier::scanContract(Json::Value ast, vector<pair<string, Json::Value>>& vars)
{
	if (ast.isObject()) {
		if (!ast.isMember("nodeType"))
			return;
		if (ast["nodeType"] == "ContractDefinition") {
			string contractName = ast["name"].asString();
			solver s(ctx);
			for (auto node : ast["nodes"])
				if (node["nodeType"] == "FunctionDefinition" && !node["body"].isNull()) {
					string name = node["id"].asString();
					functionsMap[name] = node;
				}
				else if (node["nodeType"] == "StructDefinition") {
					try {
						string name = node["name"].asString();
						vector<pair<string, Type*>> vec;
						for (auto mem : node["members"]) {

							Type* type = getVarDeclType(mem["typeName"], s);
							if (type == NULL)
								continue;
							vec.push_back({ mem["name"].asString(), type });
						}

						Struct* structType = new Struct(name, vec);
						EVisitor::addGlobalVar(contractName + "." + name + ".Struct", { structType, 0 });
					}
					catch (std::exception e) {
						ast["nodes"].append(node);
					}
				}
				else if (node["nodeType"] == "ModifierDefinition") {
					string id = node["id"].asString();
					functionsMap[id] = node;
				}
				else if (node["nodeType"] == "EnumDefinition") {
					string name = node["name"].asString();
					vector<string> vec;
					for (auto mem : node["members"])
						vec.push_back(mem["name"].asString());
					Enum* _enum = new Enum(name, vec);
					EVisitor::addGlobalVar(contractName + "." + name + ".Enum", { _enum, 0 });
				}
				else if (node["nodeType"] == "VariableDeclaration")
					vars.push_back(make_pair(contractName, node));


			return;
		}
		for (auto i : ast.getMemberNames()) {
			if (ast[i].isArray() || ast[i].isObject())
				scanContract(ast[i], vars);
		}
	}
	else if (ast.isArray()) {
		for (auto i : ast)
			if (i.isArray() || i.isObject())
				scanContract(i, vars);
	}
}



vector<pair<string, string>> Verifier::getTraceContrainst(string traces)
{
	vector<pair<string, string>> result;
	vector <string> cont;
	expr_vector vec(ctx);
	int index1 = 1, index2 = 1;
	split(traces, cont, "->");
	for (int i = 0; i < cont.size(); i++) {
		if (cont[i] == "T") {
			result.push_back({ "T" + to_string(index1++), "" });
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
						result.push_back({ "W" + to_string(index2++), get });
					else result.push_back({ "C", get });
				}

		}
	}
	return result;
}


void Verifier::getAllFunction(Json::Value ast)
{
	vector<pair<string, Json::Value>> vars;
	scanContract(ast, vars);
	solver s(ctx);
	for (auto var : vars) {
		Type* type = getVarDeclType(var.second["typeName"], s);
		if (type != NULL) {
			EVisitor::addGlobalVar(var.second["id"].asString(), { type, 0 });
		}
	}
}


void Verifier::testSolvePath(list<PathNode*> path)
{
	//solvePath(path, NULL);
}

/*bool Verifier::checkCondofTrace(string traces_str, model m, expr_vector vars, string path) {
	auto listContraint = getConstraints(traces_str, m, vars);
	map<string, pfunc> opConvert = getOpConvert();
	map<string, pair<TypeInfo, int>> vars_m;
	solver s(ctx);
	int j = 0;
	for (auto i : listContraint) {
		for (;j < i.second; ++j)
			if (decodeSol[string(1, path[j])]["nodeType"] == "ExpressionStatement") {
				auto expr = convertToZ3(decodeSol[string(1, path[j])]["expression"], s, opConvert, vars_m);
				s.add(expr.first);
				
			}
		try {
			increaseVar(s, vars_m);
			expr exp = calculate(i.first, vars_m);
			s.add(exp);
		}
		catch (const char* msg) {
			return false;
		}

	}
	cout << "Solver: " << s << endl;
	cout << s.check() << endl;
	if (s.check() == sat)
		return true;
	else return false;
}*/

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

pair <expr, ValType*> Verifier::convertToZ3(Json::Value exp, solver& s, map<string, pfunc> opConvert,
	map<string, pair<Type*, int>>& vars, bool increase) {
	if (exp["nodeType"] == "BinaryOperation") {
		string op, expOP;
		string z3Exp[3] = { "(", "", ")" };
		expOP = exp["operator"].asString();
		auto right = convertToZ3(exp["rightExpression"], s, opConvert, vars);
		auto left = convertToZ3(exp["leftExpression"], s, opConvert, vars);

		ValType *type;
		if (expOP == "<" || expOP == ">" || expOP == "<=" || expOP == ">=" || expOP == "==" || expOP == "!=")
			type = new Bool();
		else type = right.second;

		if (typeid(*right.second) == typeid(Byte) && (expOP == "<" || expOP == "<=" || expOP == ">" || expOP == ">="))
			expOP = "u" + expOP;
		pair<expr*, ValType*> nLeft = { &left.first, left.second };
		pair<expr*, ValType*> nRight = { &right.first, right.second };
		preCheck(nLeft, nRight, expOP);
		pfunc temp = opConvert[expOP];
		expr expression = temp(left.first, right.first);

		return{ expression, type };
	}
	else  if (exp["nodeType"] == "UnaryOperation") {
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
		pair<expr*, ValType*> nLeft = { &left.first, left.second };
		pair<expr*, ValType*> nRight = { &right.first, right.second };
		preCheck(nLeft, nRight, "==");
		expr exp = left.first == right.first;
		return { exp , new Bool() };
	}
	else {
		ValType* type = getType(exp);
		if (exp["nodeType"].asString() == "Literal") {
			string value = typeid(*type) == typeid(Byte) ? exp["hexValue"].asString() : exp["value"].asString();
			return { type->getVal(ctx, value), type };
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
			return{ type->getVar(ctx, varname), type };
		}
	}
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



string Verifier::removeCond(string encodeStr) {
	size_t start_pos = 0;
	while ((start_pos = encodeStr.find('{', start_pos)) != string::npos) {
		size_t end_pos = encodeStr.find('}', start_pos);
		encodeStr.erase(start_pos, end_pos - start_pos + 1);
	};
	return encodeStr;
}

/*expr_vector Verifier::readTrace(string trace, map<string, string>& encodeDict, int& index) {
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
}*/

expr_vector Verifier::readTrace(string trace, solver& s) {
	vector <string> cont;
	expr_vector vec(ctx);
	unsigned int ind = 1, ind2 = 1;
	split(trace, cont, "->");
	for (auto i : cont) {
		expr exp(ctx);
		if (i == "T")
			exp = makeStringFunction(&ctx, "T" + to_string(ind++));
		else {
			exp = makeStringFunction(&ctx, "W" + to_string(ind2++));
			vector <string> cont2;
			int size = count(i.begin(), i.end(), ';');
			s.add(exp.length() == size);
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

expr Verifier::convertToExp(string str, map < string, pair<ValType*, int>> vars)  {
	solver s(ctx);
	if (vars.find(str) != vars.end()) {
		string varname = str + to_string(vars[str].second);
		return vars[str].first->getVar(ctx, varname);
	} else {
		ValType* type;
		if (str == "true" || str == "false")
			type =  new Bool();
		else if (str[0] >= '0' && str[0] <= '9')
			type = new Int(256);
		else {
			throw std::exception("ID not found");

		}
		return type->getVal(ctx, str);
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

/*expr Verifier::calculate(string exp, map < string, pair<TypeInfo, int>> vars) {
	ANTLRInputStream input(exp);
	SolidityLexer lexer(&input);
	CommonTokenStream tokens(&lexer);
	SolidityParser parser(&tokens);
	SolidityParser::ExpressionContext* tree = parser.expression();
	map<string, string> m;
	solver s(ctx);
	CalVisitor visitor(&s, vars, m);
	expr result = visitor.visitExpression(tree).as<expr>();

	return result;
}*/

void Verifier::increaseVar(solver& s, map < string, pair<ValType*, int>>& vars) {
	for (auto i : extract_keys(vars)) {
		string oldVarname = i + to_string(vars[i].second), newVarname = i + to_string(vars[i].second + 1);
		vars[i].second++;
		expr old = vars[i].first->getVar(ctx, oldVarname);
		expr newV = vars[i].first->getVar(ctx, newVarname);
		s.add(old == newV);
	}
}