#include "tree.h";

/*string TreeRoot::getString()
{
	string result = "";
	for (auto i : childrens)
		result += i.getValue();
	return result;
}*/

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

string SubNode::DepthFS(bool isDepth)
{
	if (childrens.size() == 0)
		return "";
	string result = "";
	for (auto i : childrens)
		result += i->DepthFS(isDepth);
	return result;
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

expr LeafNode::decodeNconvert(map<string, Json::Value> decode, context ctx)
{
	Json::Value code = decode[value];

	return expr(ctx);
}
