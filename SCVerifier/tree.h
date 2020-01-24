#pragma once
#ifndef TREE_H
#define TREE_H

#include <stdio.h>
#include <iostream>
#include <list>

using namespace std;

class TreeNode {
public:
	virtual string DepthFS();
	virtual string getValue();
};

class LeafNode : TreeNode {
	string value;
public:
	string DepthFS() { return value; };
	string getValue() override { return value; }
};

class SubNode : public TreeNode {
protected:
	list<TreeNode> childrens;

public :
	SubNode() {}

	SubNode(list<TreeNode>& childrens) {
		this->childrens = childrens;
	}
};

class VarNode : public SubNode {
	string value;
public:
	VarNode(string value) : SubNode() {
		this->value = value;
	}

	VarNode(string value, list<TreeNode>& childrens) : SubNode(childrens) {
		this->value = value;
	}
	string DepthFS() override;
	string getValue() override { return value; }
};

class OpNode : public SubNode {
	string getValue() override { return DepthFS(); }
};

class OrNode : public OpNode {
	string DepthFS() override;
};

class LoopNode : public OpNode {
	string DepthFS() override;
};

class TreeRoot {
	list<TreeNode> childrens;

public:
	TreeRoot(list<TreeNode>& childrens) {
		this->childrens = childrens;
	}

	string getString();
	string getDepth();
};

#endif