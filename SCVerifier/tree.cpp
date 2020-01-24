#include "tree.h";

string VarNode::DepthFS()
{
	string result = "";
	for (auto i : childrens)
		result += i.DepthFS();
	return result;
}

string TreeRoot::getString()
{
	string result = "";
	for (auto i : childrens)
		result += i.getValue();
	return result;
}

string TreeRoot::getDepth()
{
	string result = "";
	for (auto i : childrens)
		result += i.DepthFS();
	return result;
}

string OrNode::DepthFS()
{
	if (childrens.size() == 0)
		return "";
	string result = "(" + childrens.begin()->DepthFS();
	for (auto i = next(childrens.begin()); i != childrens.end(); ++i)
		result = "|" + i->DepthFS;
	if (childrens.size() == 1)
		result += "|#";
	result += ")";
	return result;
}

string LoopNode::DepthFS()
{
	if (childrens.size() == 0)
		return "";
	string result = "";
	for (auto i : childrens)
		result += i.DepthFS();
	result += ")*";
	return result;
}
