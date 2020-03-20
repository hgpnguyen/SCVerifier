#pragma once
#ifndef TYPE_H
#define TYPE_H

#include <stdio.h>
#include "c++/z3++.h"

using namespace std;
using namespace z3;

class Type {
public:
	virtual z3::sort getSort(context& c) = 0;
	virtual expr getVar(context& c, string varName) = 0;
};

class ValType : public Type {
public:
	virtual z3::sort getSort(context& c) = 0;
	virtual expr getVar(context& c, string varName) = 0;
};

class Int : public ValType {
public:
	z3::sort getSort(context& c) { return  c.int_sort(); }
	expr getVar(context& c, string varName) { return c.int_const(varName.c_str()); }
};

class UInt : public ValType {
public:
	z3::sort getSort(context& c) { return  c.int_sort(); }
	expr getVar(context& c, string varName) { return c.int_const(varName.c_str()); }
};

class Bool : public ValType {
public:
	z3::sort getSort(context& c) { return  c.bool_sort(); }
	expr getVar(context& c, string varName) { return c.bool_const(varName.c_str()); }
};

class Byte : public ValType {
	int size;
public:
	
	Byte(int size) {
		this->size = size;
	}

	z3::sort getSort(context& c) { return  c.bv_sort(size); }
	expr getVar(context& c, string varName) { return c.bv_const(varName.c_str(), size); }
};

class Addresss : public ValType {
	int size = 160;
public:
	z3::sort getSort(context& c) { return  c.bv_sort(size); }
	expr getVar(context& c, string varName) { return c.bv_const(varName.c_str(), size); }
};

class String : public ValType {
public:
	z3::sort getSort(context& c) { return  c.string_sort(); }
	expr getVar(context& c, string varName) { return c.constant(c.str_symbol(varName.c_str()), c.string_sort()); }
};

class RefType : public Type {
public:
	virtual z3::sort getSort(context& c) = 0;
	virtual expr getVar(context& c, string varName) = 0;
};

class Array : public RefType {
	Type* array_type;

public:
	Array(Type* array_type) {
		this->array_type = array_type;
	}

	z3::sort getSort(context& c) { return c.array_sort(c.int_sort(), array_type->getSort(c)); }
	expr getVar(context& c, string varName) { return c.constant(c.str_symbol(varName.c_str()), getSort(c)); }

};

class Map : public RefType {
	Type* index_type;
	Type* array_type;

public:
	Map(Type* index_type, Type* array_type) {
		this->index_type = index_type;
		this->array_type = array_type;
	}

	z3::sort getSort(context& c) { return c.array_sort(index_type->getSort(c), array_type->getSort(c)); }
	expr getVar(context& c, string varName) { return c.constant(c.str_symbol(varName.c_str()), getSort(c)); }
};

#endif