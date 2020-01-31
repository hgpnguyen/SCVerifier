#pragma once
#ifndef TREE_H
#define TREE_H

#include <stdio.h>
#include <iostream>
#include <list>

using namespace std;

class TreeNode {
public:
	virtual string DepthFS(bool isDepth = true) = 0;
	//virtual string getValue();
};

class LeafNode : public TreeNode {
	string value;
public:
	LeafNode(string value) {
		this->value = value;
	}

	string DepthFS(bool isDepth = true) { return value; };
	//string getValue() override { return value; }
};

class SubNode : public TreeNode {
protected:
	list<TreeNode*> childrens;

public :
	SubNode() {}

	SubNode(list<TreeNode*>& childrens) {
		this->childrens = childrens;
	}
	string DepthFS(bool isDepth = true);
};

class VarNode : public SubNode {
	string value;
public:
	VarNode(string value) : SubNode() {
		this->value = value;
	}

	VarNode(string value, list<TreeNode*>& childrens) : SubNode(childrens) {
		this->value = value;
	}
	string DepthFS(bool isDepth = true);
	//string getValue() override { return value; }
};

class OpNode : public SubNode {

public:
	OpNode(list<TreeNode*>& childrens) : SubNode(childrens) {}
	//string getValue() override { return DepthFS(); }
	virtual string DepthFS(bool isDepth = true) = 0;
};

class OrNode : public OpNode {

public:
	OrNode(list<TreeNode*>& childrens) : OpNode(childrens) {
	}
	string DepthFS(bool isDepth = true);
};

class LoopNode : public OpNode {

public:
	LoopNode(list<TreeNode*>& childrens) : OpNode(childrens) {
	}
	string DepthFS(bool isDepth = true);
};

class TreeRoot {
	list<TreeNode*> childrens;

public:
	TreeRoot(list<TreeNode*>& childrens) {
		this->childrens = childrens;
	}

	string getString();
	string getDepth(bool isDepth = true);
};

#endif