#include "tree.h";

string TreeNode::DepthFS()
{
	if (isLeaf())
		return value;
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
