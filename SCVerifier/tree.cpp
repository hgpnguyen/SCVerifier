#include "tree.h";
#include "utility.h"


/*string TreeRoot::getString()
{
	string result = "";
	for (auto i : childrens)
		result += i.getValue();
	return result;
}*/

expr TreeRoot::getExpr(context& c, solver& s)
{
	expr_vector vec(c);
	for (auto child : childrens)
		vec.push_back(child->getExpr(c, s));
	return concat(vec);
}

string TreeRoot::getDepth(bool isDepth)
{
	string result = "";
	for (auto i : childrens)
		result += i->DepthFS(isDepth);
	return result;
}

string OrNode::DepthFS(bool isDepth)
{
	if (childrens.size() == 0)
		return "";

	string result = "(" + (*childrens.begin())->DepthFS(isDepth);
	for (auto i = next(childrens.begin()); i != childrens.end(); ++i)
		result += "|" + (*i)->DepthFS(isDepth);
	if (childrens.size() == 1)
		result += "|#";
	result += ")";
	return result;
}

expr OrNode::getExpr(context& c, solver& s)
{
	if (childrens.size() == 2)
		return childrens.front()->getExpr(c, s) + childrens.back()->getExpr(c, s);
	else if (childrens.size() == 1)
		return option(childrens.front()->getExpr(c, s));
	else throw "OrNode have worng number of child";

}

string LoopNode::DepthFS(bool isDepth)
{
	if (childrens.size() == 0)
		return "";
	string result = "(";
	for (auto i : childrens)
		result += i->DepthFS(isDepth);
	result += ")*";
	return result;
}

expr LoopNode::getExpr(context& c, solver& s)
{
	expr_vector vec(c);
	for (auto child : childrens)
		vec.push_back(child->getExpr(c, s));
	return concat(vec).loop(0, 5);
}

string SubNode::DepthFS(bool isDepth)
{
	if (childrens.size() == 0)
		return "";
	string result = "";
	for (auto i : childrens)
		result += i->DepthFS(isDepth);
	return result;
}

expr SubNode::getExpr(context& c, solver& s)
{
	expr_vector vec(c);
	for (auto child : childrens)
		vec.push_back(child->getExpr(c, s));
	return concat(vec);
}

/*string TreeNode::getValue()
{
	return DepthFS();
}
*/

string VarNode::DepthFS(bool isDepth)
{
	if (!isDepth)
		return "#" + value;
	if (childrens.size() == 0)
		return "";
	string result = "";
	for (auto i : childrens)
		result += i->DepthFS(isDepth);
	return result;
}

expr VarNode::getExpr(context& c, solver& s)
{	
	
	expr var = makeStringFunction(&c, value);
	expr_vector vec(c);

	for (auto child : childrens)
		vec.push_back(child->getExpr(c, s));
	s.add(in_re(var, concat(vec)));
	return to_re(c.string_val(value));
}

string FuncNode::DepthFS(bool isDepth)
{
	string result = "";
	for (auto i : children)
		result += i->DepthFS();
	return result;
}

expr_vector FuncNode::toZ3(EVisitor& visitor)
{
	context* ctx = visitor.getContext();
	expr_vector result(*ctx);
	TypeInfo type = getType(visitor.toJson(value));

	map< string, pair<TypeInfo, int>> vars;
	EVisitor newVistor(*visitor.getVer(), vars, value + ".");
	for (auto child : children) {
		expr_vector temp = child->toZ3(newVistor);
		for (auto i : temp)
			result.push_back(i);
	}
	if (type.type != VOID) {
		expr funcVar = getVar(value, type, *ctx);
		expr return_ = funcVar == result[result.size() - 1];
		result.pop_back();
		result.push_back(return_);
	}

	return result;
}

expr_vector CondNode::toZ3(EVisitor& visitor)
{
	context *ctx = visitor.getContext();
	expr_vector result(*ctx);
	ANTLRInputStream input(value);
	SolidityLexer lexer(&input);
	CommonTokenStream tokens(&lexer);
	SolidityParser parser(&tokens);
	SolidityParser::ExpressionContext* tree = parser.expression();
	CalVisitor calVisitor(ctx, visitor.getVars(), m);
	expr cond_expr = calVisitor.visitExpression(tree).as<expr>();
	result.push_back(cond_expr);
	return result;
}

expr_vector StmtNode::toZ3(EVisitor& visitor)
{
	context* ctx = visitor.getContext();
	expr_vector result(*ctx);
	expr exp = visitor.visit(visitor.toJson(value));
	if(exp.to_string() != "null")
		result.push_back(exp);

	return result;
}
