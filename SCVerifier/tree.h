#pragma once
#ifndef TREE_H
#define TREE_H

#include <stdio.h>
#include <iostream>
#include <list>
#include "c++/z3++.h"
#include "json/json.h"

using namespace std;
using namespace z3;

class TreeNode {
public:
	virtual string DepthFS(bool isDepth = true) = 0;
	virtual expr getExpr(context& c) = 0;
	//virtual string getValue();

};

class PathNode : public TreeNode {
public:
	virtual string DepthFS(bool isDepth = true) = 0;
	virtual expr getExpr(context& c) = 0;
};

class LeafNode : public PathNode {
	string value;
public:
	LeafNode(string value) {
		this->value = value;
	}

	string DepthFS(bool isDepth = true) { return value; };
	expr getExpr(context& c) { return to_re(c.string_val(value)); }
	string getValue() { return value; }
};

class CondNode : public PathNode {
	string cond;

public:
	CondNode(string cond) {
		this->cond = cond;
	}
	string DepthFS(bool isDepth = true) { return "{" + cond + "}"; };
	expr getExpr(context& c) { throw "CondNode in tree"; }
	string getValue() { return cond; }

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
	expr getExpr(context& c);
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
	string getValue() { return value; }
	list<TreeNode*> getChildrent() { return childrens; }
};

class OpNode : public SubNode {

public:
	OpNode(list<TreeNode*>& childrens) : SubNode(childrens) {}
	//string getValue() override { return DepthFS(); }
	virtual string DepthFS(bool isDepth = true) = 0;
	virtual expr getExpr(context& c) = 0;
};

class OrNode : public OpNode {

public:
	OrNode(list<TreeNode*>& childrens) : OpNode(childrens) {
	}
	string DepthFS(bool isDepth = true);
	expr getExpr(context& c);
};

class LoopNode : public OpNode {

public:
	LoopNode(list<TreeNode*>& childrens) : OpNode(childrens) {
	}
	string DepthFS(bool isDepth = true);
	expr getExpr(context& c);
};

class TreeRoot {
	list<TreeNode*> childrens;

public:
	TreeRoot(list<TreeNode*>& childrens) {
		this->childrens = childrens;
	}

	expr getExpr(context& c);
	string getDepth(bool isDepth = true);
};

#endif