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

protected:
	int size;
public:
	ValType(int size) {
		this->size = size;
	}

	virtual z3::sort getSort(context& c) = 0;
	virtual expr getVar(context& c, string varName) = 0;
	virtual expr getVal(context& c, string value) = 0;
	int getSize() { return size; }
	void changeSize(int size) { this->size = size; }
};

class Int : public ValType {

public:
	Int(int size) : ValType(size) {}

	z3::sort getSort(context& c) { return  c.int_sort(); }
	expr getVar(context& c, string varName) { return c.int_const(varName.c_str()); }
	expr getVal(context& c, string value) { return c.int_val(value.substr(0, 2) == "0x" ? stoi(value, 0, 16) : stoi(value)); }
};

class UInt : public ValType {
public:
	UInt(int size) : ValType(size) {}

	z3::sort getSort(context& c) { return  c.int_sort(); }
	expr getVar(context& c, string varName) { return c.int_const(varName.c_str()); }
	expr getVal(context& c, string value) { return c.int_val(value.substr(0, 2) == "0x" ? stoi(value, 0, 16) : stoi(value)); }
};

class Bool : public ValType {
public:
	Bool() : ValType{ 1 } {}

	z3::sort getSort(context& c) { return  c.bool_sort(); }
	expr getVar(context& c, string varName) { return c.bool_const(varName.c_str()); }
	expr getVal(context& c, string value) { return c.bool_val(value == "true"); }
};

class Byte : public ValType {
public:
	Byte(int size) : ValType(size) {}

	z3::sort getSort(context& c) { return  c.bv_sort(size); }
	expr getVar(context& c, string varName) { return c.bv_const(varName.c_str(), size); }
	expr getVal(context& c, string value) { return c.bv_val(stoi(value, 0, 16), 256); }
};

class Address : public ValType {
public:
	Address() : ValType(160) {}

	z3::sort getSort(context& c) { return  c.bv_sort(size); }
	expr getVar(context& c, string varName) { return c.bv_const(varName.c_str(), size); }
	expr getVal(context& c, string value) { return c.bv_val(stoi(value, 0, 16), 160); }
};

class String : public ValType {
public:
	String() : ValType(256) {}

	z3::sort getSort(context& c) { return  c.string_sort(); }
	expr getVar(context& c, string varName) { return c.constant(c.str_symbol(varName.c_str()), c.string_sort()); }
	expr getVal(context& c, string value) { return c.string_val(value); }
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