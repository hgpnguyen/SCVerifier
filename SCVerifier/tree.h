#pragma once
#ifndef TREE_H
#define TREE_H

#include <stdio.h>
#include <iostream>
#include <list>
#include "c++/z3++.h"
#include "json/json.h"
#include "Visitor.h"
#include "antlr4-runtime.h"
#include "SolidityLexer.h"
#include "SolidityParser.h"


using namespace z3;
using namespace antlr4;

class TreeNode {
public:
	virtual string DepthFS(bool isDepth = true) = 0;
	virtual expr getExpr(context& c, solver& s) = 0;
	//virtual string getValue();

};


class LeafNode : public TreeNode {
	string value;
public:
	LeafNode(string value) {
		this->value = value;
	}

	string DepthFS(bool isDepth = true) { return value; };
	expr getExpr(context& c, solver& s) { return to_re(c.string_val(value)); }
	string getValue() { return value; }
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
	expr getExpr(context& c, solver& s);
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
	expr getExpr(context& c, solver& s);
	list<TreeNode*> getChildrent() { return childrens; }
};

class OpNode : public SubNode {

public:
	OpNode(list<TreeNode*>& childrens) : SubNode(childrens) {}
	//string getValue() override { return DepthFS(); }
	virtual string DepthFS(bool isDepth = true) = 0;
	virtual expr getExpr(context& c, solver& s) = 0;
};

class OrNode : public OpNode {

public:
	OrNode(list<TreeNode*>& childrens) : OpNode(childrens) {
	}
	string DepthFS(bool isDepth = true);
	expr getExpr(context& c, solver& s);
};

class LoopNode : public OpNode {

public:
	LoopNode(list<TreeNode*>& childrens) : OpNode(childrens) {
	}
	string DepthFS(bool isDepth = true);
	expr getExpr(context& c, solver& s);
};

class TreeRoot {
	list<TreeNode*> childrens;
	map<string, string> encodeSol;
	map<string, Json::Value> decodeSol;
	map<string, Json::Value> functionsMap;
	Json::Value func;
	int index = 0;

public:
	TreeRoot(list<TreeNode*>& childrens) {
		this->childrens = childrens;
	}
	TreeRoot(Json::Value ast, int depth, map<string, Json::Value> functionsMap) {
		this->functionsMap = functionsMap;
		this->func = ast;
		this->childrens = visit(ast, depth);
	}

	expr getExpr(context& c, solver& s);
	string getDepth(bool isDepth = true);
	map<string, string> getEncode(){ return encodeSol; }
	map<string, Json::Value>* getDecode() { return &decodeSol; }

private:
	list<TreeNode*> visit(Json::Value ctx, int depth);

	list<TreeNode*> block(Json::Value ctx, int depth);
	list<TreeNode*> ifStmt(Json::Value ctx, int depth);
	list<TreeNode*> forStmt(Json::Value ctx, int depth);
	list<TreeNode*> whileStmt(Json::Value ctx, int depth);
	list<TreeNode*> doWhileStmt(Json::Value ctx, int depth);
	list<TreeNode*> returnStmt(Json::Value ctx, int depth);
	list<TreeNode*> exprStmt(Json::Value ctx, int depth);
	list<TreeNode*> assignment(Json::Value ctx, int depth);
	list<TreeNode*> binaryOp(Json::Value ctx, int depth);
	list<TreeNode*> unaryOp(Json::Value ctx, int depth);
	list<TreeNode*> placeHolderStmt(Json::Value ctx, int depth);
	list<TreeNode*> otherStmt(Json::Value ctx, int depth);

	list<TreeNode*> functionCall(Json::Value ctx, int depth);
	list<TreeNode*> functionDef(Json::Value ctx, int depth);
	list<TreeNode*> parameterList(Json::Value ctx, int depth);

	list<TreeNode*> modifier(Json::Value ctx, int depth);
	list<TreeNode*> varDeclList(Json::Value parameters, Json::Value initValue, int depth);

	string encode(string code);
	string encodeExt(string code, Json::Value ctx);
};

class PathNode {

protected:
	string value;
public:
	//static context* ctx;

	virtual void toZ3(EVisitor& visitor, solver& s) = 0;
	virtual string DepthFS(bool isDepth = true) = 0;
	virtual string getValue() { return value; };
};

class StmtNode : public PathNode {
public:
	StmtNode(string value) {
		this->value = value;
	}
	string DepthFS(bool isDepth = true) { return value; }
	void toZ3(EVisitor& visitor, solver& s);
};


class CondNode : public PathNode {
public:
	static map<string, Json::Value> m;

	CondNode(string cond) {
		this->value = cond;
	}
	string DepthFS(bool isDepth = true) { return "{" + value + "}"; };
	void toZ3(EVisitor& visitor, solver& s);

};

class FuncNode : public PathNode {
	list<PathNode*> children;

public:
	FuncNode(string value, list<PathNode*> children) {
		this->value = value;
		this -> children = children;
	}
	string DepthFS(bool isDepth = true);
	list<PathNode*> getChildrent() { return children; }
	void toZ3(EVisitor& visitor, solver& s);
};
#endif