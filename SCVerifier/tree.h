#pragma once
#ifndef TREE_H
#define TREE_H

#include <stdio.h>
#include <iostream>
#include <list>

using namespace std;

class TreeNode {
	string value;
	list<TreeNode> childrens;
	
public:
	TreeNode(string value) {
		this->value = value;
	}

	TreeNode(string value, list<TreeNode>& childrens) {
		this->value = value;
		this->childrens = childrens;
	}

	string getValue() { return value; }
	bool isLeaf() { return childrens.empty(); }
	string DepthFS();
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