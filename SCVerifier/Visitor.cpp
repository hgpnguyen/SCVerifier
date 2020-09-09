#include "Visitor.h"
#include "utility.h"

antlrcpp::Any Visitor::visitStatement(SolidityParser::StatementContext* ctx)
{
	if (ctx->simpleStatement()) {
		return visitSimpleStatement(ctx->simpleStatement());
	}
	int size = ctx->getText().size();
	return ctx->getText().substr(0, size - 2) ;

}

antlrcpp::Any Visitor::visitSimpleStatement(SolidityParser::SimpleStatementContext* ctx)
{
	if (ctx->expressionStatement()) {
		return visitExpressionStatement(ctx->expressionStatement());
	}
	int size = ctx->getText().size();
	return ctx->getText().substr(0, size - 2);
}

antlrcpp::Any Visitor::visitExpressionStatement(SolidityParser::ExpressionStatementContext* ctx)
{
	return visitExpression(ctx->expression());
}

antlrcpp::Any Visitor::visitExpression(SolidityParser::ExpressionContext* ctx)
{
	string op;
	if (ctx->expression().size() == 2 && ((op = ctx->children[1]->getText()) == "=" || op == "+=" || op == "-=")) {
		if (op == "+=" || op == "-=")
			return string("a=a+n");
		string left = ctx->expression()[0]->getText();
		if (ctx->expression()[1]->expression().size() != 2)
			return ctx->getText();
		return generalizeExp(ctx->expression()[1], left) ? string("a=a+n") : ctx->getText();
	}
	return ctx->getText();
}

bool Visitor::generalizeExp(SolidityParser::ExpressionContext * ctx, string leftCode) {
	string text, temp;
	bool left, right;
	switch (ctx->expression().size())
	{
	case 1:
		if (ctx->functionCallArguments() || ctx->identifier())
			text = ctx->getText();
		else text = ctx->expression()[0]->getText();
		break;
	case 2:
		temp = ctx->children[1]->getText();
		if (temp == "[") {
			text = ctx->getText();
			break;
		}
		if (temp != "+" && temp != "-")
			return false;
		left = generalizeExp(ctx->expression()[0], leftCode);
		if (left)
			return true;
		right = generalizeExp(ctx->expression()[1], leftCode);
		return right;
	case 3:
		return false;
	default:
		if (!ctx->primaryExpression())
			return false;
		text = ctx->getText();
		break;
	}
	return text == leftCode ? true : false;
}

antlrcpp::Any CalVisitor::visitExpression(SolidityParser::ExpressionContext* ctx) {
	auto opConvert = getOpConvert();
	if (ctx->expression().size() == 2 && ctx->children[1]->accept(this).is<string>()) { // Binary Op
		expr left = ctx->expression()[0]->accept(this);
		expr right = ctx->expression()[1]->accept(this);
		string op = ctx->children[1]->getText();
		if (left.to_string() == "null" || right.to_string() == "null")
			return s->ctx().bool_val(false);
		return opConvert[op](left, right);
	}
	else if (ctx->expression().size() == 1 && ctx->children[0]->accept(this).is<string>()) { // Unary Op
		expr subExp = ctx->expression()[0]->accept(this);
		string op = ctx->children[0]->getText();
		if(subExp.to_string() == "null")
			return s->ctx().bool_val(false);
		return opConvert["u" + op](subExp, s->ctx().int_val(0));
	}
	else if (ctx->primaryExpression())
		return ctx->primaryExpression()->accept(this);
	else throw std::exception("Wrong contranst");
}

antlrcpp::Any CalVisitor::visitPrimaryExpression(SolidityParser::PrimaryExpressionContext* ctx) {
	return ctx->children[0]->accept(this);
}

antlrcpp::Any CalVisitor::visitNumberLiteral(SolidityParser::NumberLiteralContext* ctx) {
	return ctx->children[0]->accept(this);
}

antlrcpp::Any CalVisitor::visitIdentifier(SolidityParser::IdentifierContext* ctx)
{
	assert(traceToCode.find(ctx->getText()) != traceToCode.end());
	expr var = visitor->visit(traceToCode[ctx->getText()], *s);
	type = getType(traceToCode[ctx->getText()]);
	string varName = var.to_string();
	return var;
}

antlrcpp::Any CalVisitor::visitTuppleExpression(SolidityParser::TupleExpressionContext* ctx) {
	throw std::exception("Wrong contrainst");
}
antlrcpp::Any CalVisitor::visitElementaryTypeNameExpression(SolidityParser::ElementaryTypeNameContext* ctx) {
	throw std::exception("Wrong contrainst");
}

antlrcpp::Any CalVisitor::visitTerminal(antlr4::tree::TerminalNode* ctx) {
	string text = ctx->getText();
	context* c = &s->ctx();
	switch (ctx->getSymbol()->getType())
	{
	case SolidityLexer::BooleanLiteral:
		return c->bool_val(text == "true");
	case SolidityLexer::DecimalNumber:
		return c->int_val(stoi(text));
	case SolidityLexer::HexNumber:
		return c->int_val(stoi(text, 0, 16));
	case SolidityLexer::MaxKeyword:
		if (type == NULL)
			return expr(*c);
		if (typeid(*type) == typeid(UInt))
			return dynamic_cast<UInt*>(type)->getMax(*c);
		else if (typeid(*type) == typeid(Int))
			return dynamic_cast<Int*>(type)->getMax(*c);
		else throw std::exception("Wrong type for Max");

	case SolidityLexer::MinKeyword:
		if (type == NULL)
			return expr(*c);
		if (typeid(*type) == typeid(UInt)) 
			return dynamic_cast<UInt*>(type)->getMin(*c);
		else if (typeid(*type) == typeid(Int))
			return dynamic_cast<Int*>(type)->getMin(*c);

		else throw std::exception("Wrong type for Min");
	default:
		return text;
	}
}

expr EVisitor::visit(Json::Value code, solver& s, bool isLeft)
{
	typedef expr(EVisitor::* pfunc)(Json::Value, solver&s, bool);
	map<string, pfunc> switchCase;
	switchCase["ExpressionStatement"] = &EVisitor::exprStmt;
	switchCase["VariableDeclarationStatement"] = &EVisitor::varDeclStmt;
	switchCase["Return"] = &EVisitor::returnStmt;
	switchCase["VariableDeclaration"] = &EVisitor::varDecl;
	switchCase["Assignment"] = &EVisitor::assignment;
	switchCase["BinaryOperation"] = &EVisitor::binaryOp;
	switchCase["UnaryOperation"] = &EVisitor::unaryOp;
	switchCase["FunctionCall"] = &EVisitor::functionCall;
	switchCase["Identifier"] = &EVisitor::identifier;
	switchCase["Literal"] = &EVisitor::literal;
	switchCase["IndexAccess"] = &EVisitor::indexAccess;
	switchCase["MemberAccess"] = &EVisitor::memberAccess;
	switchCase["ParameterList"] = &EVisitor::paraList;
	switchCase["TupleExpression"] = &EVisitor::tupleExp;
	switchCase["Conditional"] = &EVisitor::conditional;
	string nodeType = code["nodeType"].asString();
	auto func = switchCase.find(nodeType) != switchCase.end() ? switchCase[nodeType] : &EVisitor::other;
	expr result = (this->*func)(code, s, isLeft);
	return result;
}

Json::Value EVisitor::toJson(string str)
{
	return decodeSol[str]; 
}

void EVisitor::resetGlobalVarIndex()
{
	for (auto key : extract_keys(Globalvars)) 
		Globalvars[key].second["num"] = 0;
	
}

unordered_set<string> EVisitor::getKeys()
{
	return global;
}

void EVisitor::resetVarIndex()
{
	for (auto var : extract_keys(vars)) {
		vars[var].second = 0;
	}
}

expr EVisitor::exprStmt(Json::Value code, solver& s, bool isLeft)
{
	visit(code["expression"], s, isLeft);
	return expr(s.ctx());
}

expr EVisitor::varDeclStmt(Json::Value code, solver& s, bool isLeft)
{
	expr_vector result(s.ctx()), decls(s.ctx()), init(s.ctx());
	for (auto decl : code["declarations"]) {
		expr varDecl = declVar(decl, s, code["initialValue"].isNull());
		if (varDecl.to_string() == "null")
			return expr(s.ctx());
		decls.push_back(varDecl);
	}

	if (!code["initialValue"].isNull())
		if (code["initialValue"]["nodeType"] == "TupleExpression")
			init = tuppleExp(code["initialValue"], s);
		else if (code["initialValue"]["typeDescriptions"]["typeString"].asString().substr(0, 5) != "tuple") {
			auto temp = visit(code["initialValue"], s, isLeft);
			if(temp.to_string() != "null")
				init.push_back(temp);
		}
	if (init.empty())
		return expr(s.ctx());
	else {
		if (decls.size() == init.size()) {
			for (int i = 0; i < decls.size(); ++i) {
				try {
					result.push_back(decls[i] == init[i]);
				}
				catch (z3::exception e) {

				}
				catch (std::exception e){

				}
				catch(...){}
			}
		}
		else {
			
			if (decls[0].is_array()) {
				for (int i = 0; i < init.size(); ++i)
					result.push_back(select(decls[0], s.ctx().int_val(i)) == init[i]);
			}
		}
		if (result.size() >= 2)
			s.add(mk_and(result));
		else if(result.size() == 1) s.add(result[0]);
		return expr(s.ctx());
	}
}

expr EVisitor::returnStmt(Json::Value code, solver& s, bool isLeft)
{
	expr result = visit(code["expression"], s, isLeft);
	if (result.to_string() == "null" && !code["expression"].isNull()) {
		string temp = "temp" + to_string(tempIndex++);
		Type* type = getAllType(code["expression"]);
		if(type != NULL)
			result = type->getVar(s.ctx(), temp);
	}
	return result;
}

expr EVisitor::assignment(Json::Value code, solver& s, bool isLeft)
{
	if (code["leftHandSide"]["nodeType"].asString() == "TupleExpression")
		return assignTuple(code, s, isLeft);
	string op = code["operator"].asString();
	expr right(s.ctx());
	if (op == "=")
		right = visit(code["rightHandSide"], s, isLeft);
	else {
		string newOp = op.substr(0, op.length() - 1);
		auto binary = createBinary(code["leftHandSide"], code["rightHandSide"], code["typeDescriptions"], newOp);
		right = binaryOp(binary, s);
	}
	ValType* type = getType(code);
	if (type == NULL)
		return expr(s.ctx());
	pair<expr*, ValType*> para = { &right, type };

	if (right.to_string() == "null") {
		right = createTemp(type, s);
	}
	if ((typeid(*type) == typeid(UInt) || typeid(*type) == typeid(Int)) && right.is_bv())
		bv2int(para);
	else if (typeid(*type) != typeid(UInt) && typeid(*type) != typeid(Int) && right.is_int())
		int2Bv(para);
	/*else if (typeid(*type) == typeid(Byte) && right.is_string_value()) {
		string lit = right.get_string();
		right = s.ctx().bv_val(type->getSize(), str2bv(lit));
	}*/
	expr left = visit(code["leftHandSide"], s, true);
	if (left.to_string() == "null")
		throw std::exception("Left or Right is NULL");
	s.add(left == right);

	return left;
}

expr EVisitor::binaryOp(Json::Value code, solver& s, bool isLeft)
{
	auto op = getOpConvert();
	ValType* typeLeft = getType(code["leftExpression"]);
	ValType* typeRight = getType(code["rightExpression"]);
	ValType* type = getType(code);
	string expOP = code["operator"].asString();
	if (typeLeft == NULL || typeRight == NULL) //assgin contract situation
		return expr(s.ctx());
	if (typeid(*typeRight) == typeid(Byte) && (expOP == "<" || expOP == "<=" || expOP == ">" || expOP == ">=")) 
		expOP = "u" + expOP;

	expr left = visit(code["leftExpression"], s, isLeft);
	expr right = visit(code["rightExpression"], s, isLeft);


	pair<expr*, ValType*> pairL = { &left, typeLeft };
	pair < expr*, ValType*> pairR = { &right, typeRight };
	preCheck(pairL, pairR, expOP);
	expr result = op[expOP](left, right);
	pair<expr*, ValType*> re = { &result, type };
	misMatch(re);
	return result;
}

expr EVisitor::unaryOp(Json::Value code, solver& s, bool isLeft)
{
	auto op = getOpConvert();
	expr sub = visit(code["subExpression"], s, isLeft);
	expr result(s.ctx());
	ValType* type = getType(code["subExpression"]);
	string expOP = code["operator"].asString();
	if (op.find("u" + expOP) == op.end())
		throw std::exception("New Unary OP: ");
	if (expOP == "~" && sub.is_int()) {
		pair<expr*, ValType*> temp = { &sub, type };
		int2Bv(temp);
		result = op["u" + expOP](sub, expr(s.ctx()));
		pair<expr*, ValType*> temp2 = { &result, type };
		bv2int(temp2);
		//cout << result << endl;
	}
	else result = op["u" + expOP](sub, expr(s.ctx()));
	if (expOP == "++" || expOP == "--") {
		expr left = visit(code["subExpression"], s, true);
		s.add(left == result);
		result = code["prefix"].asBool() ? left : sub; // ++a or a++
	}
	return result;
}

expr EVisitor::identifier(Json::Value code, solver& s, bool isLeft)
{

	string name = code["name"].asString();
	string id = code["referencedDeclaration"].asString();
	int num = findVar(id), num_;
	string varname;
	Type* type;
	expr newVar(s.ctx());
	switch(num){
	case 1: //local var
		pair<Type*, int> * var;
		var = &vars[id];
		varname = prefix + name ;
		type = var->first;
		num_ = isLeft ? ++var->second : var->second;

		varname += "_" + to_string(num_);

		return type->getVar(s.ctx(), varname);

	case 2: //global var
		pair<Type*, Json::Value> * glovar;
		glovar = &Globalvars[id];
		varname = name;
		type = glovar->first;
		if (glovar->second["constant"].asBool()) { //constant value
			newVar = type->getVar(s.ctx(), varname + "_" + glovar->second["num"].asString());
			if (init.find(varname) == init.end()) {
				expr val = visit(glovar->second["value"], s);
				s.add(newVar == val);
				init.insert(varname);
			}
		}
		else { //not constant
			if (init.find(varname) == init.end()) {
				initCondVar(glovar->first->getVar(s.ctx(), varname + "_" + glovar->second["num"].asString()), s, glovar->first);
				init.insert(varname);
			}
			if(glovar->second["typeName"]["nodeType"].asString() != "Mapping")
				global.insert(varname);
			if (isLeft)
				glovar->second["num"] = glovar->second["num"].asInt() + 1;
			newVar = type->getVar(s.ctx(), varname + "_" + glovar->second["num"].asString());
		}
		return newVar;
	default: //cant find
		type = getType(code);
		if (type == NULL)
			return expr(s.ctx());
		varname = prefix + name;
		vars[id] = { type, 0 };
		newVar = type->getVar(s.ctx(), varname + "_0");
		initCondVar(newVar, s, type);
		init.insert(varname);
		return newVar;
	}
}

expr EVisitor::indexAccess(Json::Value code, solver& s, bool isLeft)
{
	if (code["baseExpression"]["typeDescriptions"]["typeString"].asString().substr(0, 7) != "mapping")
		return indexAccess2(code, s, isLeft);
	Json::Value baseValue = code["baseExpression"];
	vector<Json::Value> list_index;
	while (baseValue["nodeType"] == "IndexAccess") {
		list_index.push_back(baseValue["indexExpression"]);
		baseValue = baseValue["baseExpression"];
	}
	list_index.push_back(code["indexExpression"]);
	expr baseExpr = visit(baseValue, s, false);
	expr_vector index_vec(s.ctx());
	Type* type = getTypeId(baseValue);
	vector<Type*> listType;
	if (typeid(*type) == typeid(Map))
		listType = dynamic_cast<Map*>(type)->getIndex();
	else throw std::exception("Not Map in IndexAccess");
	mapVar[code["id"].asString()] = code;
	int i = 0;
	for (auto in : list_index) {
		expr tempIn = visit(in, s, false);
		if (tempIn.to_string() == "null" && in["typeDescriptions"]["typeString"].asString().substr(0, 8) == "contract") {
			//Contract in place of address
			string in = getCode(code["indexExpression"]) + "_0";
			Address address;
			tempIn = address.getVar(s.ctx(), in);
		}
		else if (tempIn.to_string() == "null")
			throw std::exception("Index is null");
		if (tempIn.get_sort().is_int() && listType[i]->getSort(s.ctx()).is_bv())
			tempIn = int2bv(listType[i]->getSort(s.ctx()).bv_size(), tempIn);
		index_vec.push_back(tempIn);
		++i;
	}
	if (isLeft) {
		string t = "temp" + to_string(tempIndex++);
		expr temp = s.ctx().constant(s.ctx().str_symbol(t.c_str()), baseExpr.get_sort().array_range());
		expr store_ = store(baseExpr, index_vec, temp);
		expr newBaseExpr = visit(baseValue, s, true);
		s.add(newBaseExpr == store_);
		return temp;
	}
	string name = baseExpr.decl().name().str();
	if (name.substr(name.find_last_of('_') + 1) == "0") 
		initCondVar(select(baseExpr, index_vec), s, dynamic_cast<Map*>(type)->getArray());


	return select(baseExpr, index_vec);

}

expr EVisitor::literal(Json::Value code, solver& s, bool isLeft)
{
	ValType* type = getType(code);
	string value;
	if (typeid(*type) == typeid(Byte))
		value = code["hexValue"].asString();
	else if (code["subdenomination"].isNull()) {
		value = code["value"].asString();
	}
	else { // unit like ether, ..
		vector<string> vec;
		split(code["typeDescriptions"]["typeString"].asString(), vec, " ");
		value = vec[1];
	}
	if (code["kind"].asString() == "string")
		return s.ctx().bv_val(256, str2bv(value));
	expr result = type->getVal(s.ctx(), value);
	return result;
}

expr EVisitor::functionCall(Json::Value code, solver& s, bool isLeft)
{
	if (code["expression"]["nodeType"] == "Identifier" && (code["expression"]["name"] == "assert" || code["expression"]["name"] == "require")) {
		s.add(visit(code["arguments"][0], s));
		return expr(s.ctx());
	}
	if (code["kind"].asString() == "structConstructorCall") {
		Type* type = getAllType(code);
		if (typeid(*type) != typeid(Struct))
			throw std::exception("Some thing worng or cant find Struct");
		Struct* strucT = dynamic_cast<Struct*>(type);
		expr_vector vec(s.ctx());
		map<string, Json::Value> m;
		for (int i = 0; i < code["arguments"].size(); ++i) {
			if (!code["names"][i].isNull())
				m[code["names"][i].asString()] = code["arguments"][i];
			else
				vec.push_back(visit(code["arguments"][i], s, isLeft));
		}
		for (auto k : strucT->getListType())
			if(m.find(k.first) != m.end())
				vec.push_back(visit(m[k.first], s, isLeft));

		func_decl structDecl = strucT->getStruct(s.ctx());
		return structDecl(vec);
	}
	string name = getCode(code);
	//string varName = encode(name);
	string varName = name + "_" + to_string(0);
	Type* type = getAllType(code);
	expr result(s.ctx());
	if (type != NULL)
		result = type->getVar(s.ctx(), varName);
	else return expr(s.ctx());

	if (init.find(name) == init.end()) {
		init.insert(name);
		initCondVar(result, s, type);
	}

	return result;
}

expr EVisitor::varDecl(Json::Value code, solver& s, bool isLeft)
{
	return declVar(code, s, true);
}

expr EVisitor::memberAccess2(Json::Value code, solver& s, bool isLeft)
{
	string varName = getCode(code);
	ValType* type = getType(code);
	if (type == NULL)
		return expr(s.ctx());
	auto var = vars.find(prefix + varName);
	int num;
	if (var == vars.end()) {
		vars[prefix + varName] = { type, 0 };
		num = 0;
	}
	else num = isLeft ? ++var->second.second : var->second.second;
	
	string newName = varName + "_" + to_string(num);
	expr var_ = type->getVar(s.ctx(), newName);
	if (init.find(varName) == init.end()) {
		initCondVar(var_, s, type);
		init.insert(varName);
	}
	string expName = getCode(code["expression"]);
	if (expName == "msg" || expName == "block" || varName == "address(this).balance")
		global.insert(varName);

	return var_;
}

expr EVisitor::indexAccess2(Json::Value code, solver& s, bool isLeft)
{
	//IndexAccess for array
	expr baseExpr = visit(code["baseExpression"], s, false);
	expr index = visit(code["indexExpression"], s, false);
	if (index.to_string() == "null" && code["indexExpression"]["typeDescriptions"]["typeString"].asString().substr(0, 8) == "contract") {
		//Contract in place of address
		string in = getCode(code["indexExpression"]) + "_0";
		Address address;
		index = address.getVar(s.ctx(), in);
	}
	else if (index.to_string() == "null") {
		throw std::exception("Index is null");
	}
	if (baseExpr.get_sort().array_domain().is_bv() && index.get_sort().is_int())
		index = int2bv(baseExpr.get_sort().array_domain().bv_size(), index);
	if (isLeft) {
		string t = "temp_" + to_string(tempIndex++);
		expr temp = s.ctx().constant(s.ctx().str_symbol(t.c_str()), baseExpr.get_sort().array_range());
		expr store_ = store(baseExpr, index, temp);
		expr newBaseExpr = visit(code["baseExpression"], s, true);
		s.add(newBaseExpr == store_);
		return temp;
	}
	else return select(baseExpr, index);
}

expr EVisitor::enumAccess(Json::Value code, solver& s, bool isLeft)
{
	vector<string> cont;
	split(code["typeDescriptions"]["typeString"].asString(), cont, " ");
	string enumName = cont[1];
	auto type = EVisitor::findGlobalVar(enumName + ".Enum");
	if (type.first == NULL)
		return memberAccess2(code, s, isLeft);
	Enum* _enum = dynamic_cast<Enum*>(type.first);
	string memName = code["memberName"].asString();
	expr result = _enum->getVal(s.ctx(), memName);
	if(result.to_string() == "null")
		return memberAccess2(code, s, isLeft);
	return result;
}

expr EVisitor::assignTuple(Json::Value code, solver& s, bool isLeft)
{
	Json::Value left = code["leftHandSide"];
	Json::Value right = code["rightHandSide"];
	expr_vector result(s.ctx());
	if (right["nodeType"].asString() == "TupleExpression") {
		for (int i = 0; i < left["components"].size(); ++i) {
			if (left["components"][i].isNull())
				continue;
			auto assign = createAssign(left["components"][i], right["components"][i]);
			expr temp = assignment(assign, s, isLeft);
			result.push_back(temp);
		}
		s.add(mk_and(result));
		return expr(s.ctx());
	}
	else {
		for (auto i : left["components"]) {
			if (i.isNull())
				continue;
			Type* type = getAllType(i);
			expr com = visit(i, s, true);
			expr val = createTemp(type, s);
			result.push_back(com == val);
		}
		s.add(mk_and(result));
		return expr(s.ctx());
	}

}

expr EVisitor::createTemp(Type* type, solver& s)
{
	string varName = "temp_" + to_string(tempIndex++);
	expr temp = type->getVar(s.ctx(), varName);
	initCondVar(temp, s, type);
	init.insert(varName);
	return temp;
}

Type* EVisitor::getTypeId(Json::Value code)
{
	if (code["nodeType"] == "Identifier") {
		string id = code["referencedDeclaration"].asString();
		auto num = findVar(id);
		switch (num) {
		case 1:
			return vars[id].first;
		case 2:
			return Globalvars[id].first;
		default:
			return getAllType(code);
		}
	}
	return getAllType(code);
}

expr EVisitor::declVar(Json::Value code, solver& s, bool isInit)
{
string name = prefix + code["name"].asString();
if (code["name"].asString() == "")
return expr(s.ctx());
Type* type;
//cout << code << endl;
if (!code["typeName"].isNull())
type = getVarDeclType(code["typeName"], s);
else {
	type = getAllType(code);
}
if (type == NULL) {
	return expr(s.ctx()); //contract Type
}
vars[code["id"].asString()] = { type, 0 };
expr newVar = type->getVar(s.ctx(), name + "_0");
if (isInit) {
	s.add(newVar == type->getDefault(s.ctx()));
}
else
initCondVar(newVar, s, type);
return newVar;
}

expr EVisitor::memberAccess(Json::Value code, solver& s, bool isLeft)
{

	string typeName = code["expression"]["typeDescriptions"]["typeString"].asString();
	if (typeName.substr(0, 9) == "type(enum")
		return enumAccess(code, s, isLeft);

	Type* type = getAllType(code["expression"]);
	expr expression = visit(code["expression"], s, false);
	if (type == NULL || expression.to_string() == "null")
		return memberAccess2(code, s, isLeft);
	if (typeid(*type) != typeid(Struct) || !expression.get_sort().is_datatype())
		return memberAccess2(code, s, isLeft);
	Struct* structType = dynamic_cast<Struct*>(type);
	expr memAccess = structType->getMem(s.ctx(), code["memberName"].asString(), expression);
	if (isLeft) {
		Type* assignType = getAllType(code);
		string tempName = "temp" + to_string(tempIndex++);
		expr temp = s.ctx().constant(tempName.c_str(), memAccess.get_sort());
		expr newValue = structType->getNewStruct(s.ctx(), code["memberName"].asString(), temp, expression);
		expr newStruct = visit(code["expression"], s, true);
		s.add(newStruct == newValue);
		return temp;
	}

	return memAccess;
}

expr EVisitor::paraList(Json::Value code, solver& s, bool isLeft)
{
	for (auto para : code["parameters"])
		if (para["nodeType"] == "VariableDeclaration")
			declVar(para, s, false);
		else
			visit(para, s, isLeft);
	return expr(s.ctx());
}

expr EVisitor::tupleExp(Json::Value code, solver& s, bool isLeft)
{
	if (code["components"].size() > 1)
		return expr(s.ctx());
	expr result = visit(code["components"][0], s, isLeft);
	return result;
}

expr EVisitor::conditional(Json::Value code, solver& s, bool isLeft)
{
	ValType* type = getType(code);
	expr trueExp = visit(code["trueExpression"], s, isLeft);
	expr falseExp = visit(code["falseExpression"], s, isLeft);
	string name = "temp" + to_string(tempIndex++);
	expr cond = s.ctx().constant(name.c_str(), trueExp.get_sort());
	expr result = (cond == trueExp) || (cond == falseExp);
	s.add(result);
	return cond;
}

expr EVisitor::other(Json::Value code, solver& s, bool isLeft)
{
	return expr(s.ctx());
}

expr_vector EVisitor::tuppleExp(Json::Value code, solver& s, bool isLeft)
{
	expr_vector result(s.ctx());
	for (auto i : code["components"])
		result.push_back(visit(i, s, isLeft));
	return result;
}



void EVisitor::initCondVar(expr var, solver& s, Type* type)
{
	context& c = s.ctx();
	string varName = var.decl().name().str();
	if (varName.substr(0, varName.find('_')) == "msg.value"){
		UInt* u = new UInt(64);
		expr cond = var >= 0 && var <= u->getMax(c);
		s.add(cond);
		return;
	}
	if (typeid(*type) == typeid(UInt)) {
		UInt* u = dynamic_cast<UInt*>(type);
		expr cond = var >= u->getMin(c) && var <= u->getMax(c);
		s.add(cond);
	}else if (typeid(*type) == typeid(Int)) {
		Int* i = dynamic_cast<Int*>(type);
		expr cond = var >= i->getMin(c) && var <= i->getMax(c);
		s.add(cond);
	}
	else if (typeid(*type) == typeid(Struct)) {
		Struct* strt = dynamic_cast<Struct*>(type);
		func_decl_vector vec(c);
		strt->getFuncVec(vec);
		vector<pair<string, Type*>> listType = strt->getListType();
		for (int i = 0; i < vec.size(); ++i)
			initCondVar(vec[i](var), s, listType[i].second);
	}
}

string EVisitor::encode(string code)
{
	if (encodeSol.find(code) != encodeSol.end())
		return encodeSol[code];
	string temp = "temp" + to_string(tempIndex++);
	encodeSol[code] = temp;
	return temp;
}

int EVisitor::findVar(string name)
{	

	if (vars.find(name) != vars.end()) {
		return 1; //local var
	}
	else if (Globalvars.find(name) != Globalvars.end()) {
		return 2; //global var
	}
	return 3;// cant find
}

antlrcpp::Any MapVisitor::visitStatement(SolidityParser::StatementContext* ctx)
{

	if (ctx->simpleStatement()) {
		return visitSimpleStatement(ctx->simpleStatement()).as<bool>();
	}
	return false;

}

antlrcpp::Any MapVisitor::visitSimpleStatement(SolidityParser::SimpleStatementContext* ctx)
{
	return ctx->children[0]->accept(this).as<bool>();
}

antlrcpp::Any MapVisitor::visitVariableDeclarationStatement(SolidityParser::VariableDeclarationStatementContext* ctx)
{
	return false;
}

antlrcpp::Any MapVisitor::visitExpressionStatement(SolidityParser::ExpressionStatementContext* ctx)
{
	if (json["nodeType"] != "ExpressionStatement" || json["expression"]["nodeType"] != "Assignment")
		return false;
	(*m)[ctx->getText()] = json;
	json = json["expression"];
	return ctx->expression()->accept(this);
}

antlrcpp::Any MapVisitor::visitExpression(SolidityParser::ExpressionContext* ctx)
{
	string op;
	if (ctx->expression().size() == 2 && ((op = ctx->children[1]->getText()) == json["operator"].asString() || op == "=")) {
		bool left = mapExpression(ctx->expression()[0], json["leftHandSide"]);
		bool right = mapExpression(ctx->expression()[1], json["rightHandSide"]);
		return left && right;
	}
	return false;
}

bool MapVisitor::mapExpression(SolidityParser::ExpressionContext* ctx, Json::Value ast)
{

	if (ctx->primaryExpression()) {
		return primaryExpression(ctx->primaryExpression(), ast);
	}

	if (ctx->expression().size() == 2 && ast["nodeType"] == "BinaryOperation" && (ctx->children[1]->getText() == ast["operator"].asString()) ) {
		return mapExpression(ctx->expression()[0], ast["leftExpression"]) && mapExpression(ctx->expression()[1], ast["rightExpression"]);
	}
	if (ctx->expression().size() == 1 && ast["nodeType"] == "UnaryOperation" && (ctx->children[0]->getText() == ast["operator"].asString()))
		return mapExpression(ctx->expression()[0], ast["subExpression"]);


	return false;
}

bool MapVisitor::checkCompat(string id, Json::Value ast)
{
	if (type.find(id) == type.end())
		throw std::exception("Missing type decl for var: ");
	string typeName = ast["typeDescriptions"]["typeString"].asString(); 
	if (typeName.find('[') != string::npos) //find array
		return false;
	if (type[id] != "expr" && typeName.find(type[id]) == string::npos) //check type compatitlity
		return false;
	if (type[id] == "expr" && m->find(id) == m->end()) //type Expr for all kind of expression
		return true;
	if (m->find(id) != m->end() && getCode((*m)[id]) == getCode(ast)) //check if the var already assignen
		return true;
	if (ast["nodeType"] != "BinaryOperation" && ast["nodeType"] != "UnaryOperation" && m->find(id) == m->end())
		return true;
	return false;
}

bool MapVisitor::primaryExpression(SolidityParser::PrimaryExpressionContext* ctx, Json::Value ast)
{
	string text = ctx->getText();
	if (ctx->identifier()) {
		bool result = checkCompat(text, ast);
		if(result && m->find(text) == m->end())
			(*m)[text] = ast;
		return result;
	}
	return text == getCode(ast);
}
