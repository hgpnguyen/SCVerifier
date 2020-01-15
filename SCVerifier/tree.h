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

	string getValue() { return value; }
};

class TreeRoot {
	list<TreeNode> childrens;
};

#endif