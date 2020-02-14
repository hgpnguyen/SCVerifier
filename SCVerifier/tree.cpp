#include "tree.h";

/*string TreeRoot::getString()
{
	string result = "";
	for (auto i : childrens)
		result += i.getValue();
	return result;
}*/

expr TreeRoot::getExpr(context& c)
{
	expr_vector vec(c);
	for (auto child : childrens)
		vec.push_back(child->getExpr(c));
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

expr OrNode::getExpr(context& c)
{
	if (childrens.size() == 2)
		return childrens.front()->getExpr(c) + childrens.back()->getExpr(c);
	else if (childrens.size() == 1)
		return option(childrens.front()->getExpr(c));
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

expr LoopNode::getExpr(context& c)
{
	expr_vector vec(c);
	for (auto child : childrens)
		vec.push_back(child->getExpr(c));
	return concat(vec).loop(10);
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

expr SubNode::getExpr(context& c)
{
	expr_vector vec(c);
	for (auto child : childrens)
		vec.push_back(child->getExpr(c));
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


