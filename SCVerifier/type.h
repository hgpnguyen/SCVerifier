#pragma once
#ifndef TYPE_H
#define TYPE_H

#include <stdio.h>
#include "c++/z3++.h"
#include <list>
#include <vector>
#include <bitset> 


using namespace z3;

class Type {
public:
	virtual z3::sort getSort(context& c) = 0;
	virtual expr getVar(context& c, std::string varName) = 0;
	virtual expr getDefault(context& c) = 0;
	virtual std::pair<std::string, bool> argEncode(expr val) = 0;
};

class ValType : public Type {

protected:
	int size;
public:
	ValType(int size) {
		this->size = size;
	}

	virtual z3::sort getSort(context& c) = 0;
	virtual expr getVar(context& c, std::string varName) = 0;
	virtual expr getVal(context& c, std::string value) = 0;
	int getSize() { return size; }
	void changeSize(int size) { this->size = size; }

};

class Int : public ValType {

public:
	Int(int size) : ValType(size) {}

	z3::sort getSort(context& c) { return  c.int_sort(); }
	expr getVar(context& c, std::string varName) { return c.int_const(varName.c_str()); }
	expr getVal(context& c, std::string value);
	expr getMax(context& c);
	expr getMin(context& c);
	expr getDefault(context& c) { return c.int_val(0); }
	std::pair<std::string, bool> argEncode(expr val);
};

class UInt : public ValType {
public:
	UInt(int size) : ValType(size) {}

	z3::sort getSort(context& c) { return  c.int_sort(); }
	expr getVar(context& c, std::string varName) { return c.int_const(varName.c_str()); }
	expr getVal(context& c, std::string value);
	expr getMax(context& c);
	expr getMin(context& c) { return c.int_val(0); }
	expr getDefault(context& c) { return c.int_val(0); }
	std::pair<std::string, bool> argEncode(expr val);
};

class Bool : public ValType {
public:
	Bool() : ValType{ 1 } {}

	z3::sort getSort(context& c) { return  c.bool_sort(); }
	expr getVar(context& c, std::string varName) { return c.bool_const(varName.c_str()); }
	expr getVal(context& c, std::string value) { return c.bool_val(value == "true"); }
	expr getDefault(context& c) { return c.bool_val(0); }
	std::pair<std::string, bool> argEncode(expr val);
};

class Byte : public ValType {
	bool bytes;

public:
	Byte(int size, bool bytes = false) : ValType(size) {
		this->bytes = bytes;
	}

	z3::sort getSort(context& c) { return  c.bv_sort(size); }
	expr getVar(context& c, std::string varName) { return c.bv_const(varName.c_str(), size); }
	expr getVal(context& c, std::string value);
	expr getDefault(context& c) { return c.bv_val(0, size); }
	std::pair<std::string, bool> argEncode(expr val);
};

class Address : public ValType {
public:
	Address() : ValType(160) {}

	z3::sort getSort(context& c) { return  c.bv_sort(size); }
	expr getVar(context& c, std::string varName) { return c.bv_const(varName.c_str(), size); }
	expr getVal(context& c, std::string value);
	expr getDefault(context& c) { return c.bv_val(0, 160); }
	std::pair<std::string, bool> argEncode(expr val);
};

/*class String : public ValType {
public:
	String() : ValType(256) {}

	z3::sort getSort(context& c) { return  c.string_sort(); }
	expr getVar(context& c, string varName) { 	return c.constant(c.str_symbol(varName.c_str()), c.string_sort()); }
	expr getVal(context& c, string value) { 

		return c.bv_val(256, str2bv(value)); }
};*/

class RefType : public Type {
public:
	virtual z3::sort getSort(context& c) = 0;
	expr getVar(context& c, std::string varName) { return c.constant(c.str_symbol(varName.c_str()), getSort(c)); };
};

class Array : public RefType {
protected:
	Type* array_type;
	int length = 0;

public:
	Array(Type* array_type) {
		this->array_type = array_type;
	}

	Array(Type* array_type, int length) {
		this->array_type = array_type;
		this->length = length;
	}

	z3::sort getSort(context& c) { return c.array_sort(c.int_sort(), array_type->getSort(c)); }
	expr getDefault(context& c) { return z3::const_array(c.int_sort(), array_type->getDefault(c)); }

};

class FixArray : public Array {
public:
	FixArray(Type* array_type, int length) : Array(array_type, length) {}
	std::pair<std::string, bool> argEncode(expr val);
};

class DynamicArray : public Array {
public:
	DynamicArray(Type* array_type) : Array(array_type) {
		length = 5;
	}

	std::pair<std::string, bool> argEncode(expr val);
};

class Map : public RefType {
	Type* index_type;
	std::vector<Type*> list_index;
	Type* array_type;

public:
	Map(Type* index_type, Type* array_type) {
		this->index_type = index_type;
		this->array_type = array_type;
	}

	Map(std::vector<Type*> list_index, Type* array_type) {
		this->list_index = list_index;
		this->array_type = array_type;
	}

	//z3::sort getSort(context& c) { return c.array_sort(index_type->getSort(c), array_type->getSort(c)); }
	z3::sort getSort(context& c);
	std::vector<Type*> getIndex() { return list_index; }
	Type* getArray() {	return array_type; }
	expr getDefault(context& c) { return z3::const_array(getSort(c).array_domain(), array_type->getDefault(c)); }
	std::pair<std::string, bool> argEncode(expr val) { throw "Can't have Map in parameter"; }
};

class Struct : public RefType {
	std::string name;
	std::vector<std::pair<std::string, Type*>> listType;

public:
	Struct(std::string name, std::vector<std::pair<std::string, Type*>> & listType) {
		this->listType = listType;
		this->name = name;
	}

	z3::sort getSort(context& c) { func_decl_vector vec(c);  return reconstruct(c, vec).range(); };
	expr getMem(context& c, std::string funcName, expr var);
	expr getMem(context& c, int index, expr var) { func_decl_vector vec(c); reconstruct(c, vec); return vec[index](var); }
	expr getNewStruct(context& c, std::string funcName, expr temp, expr var);
	void getFuncVec(func_decl_vector& vec) { reconstruct(vec.ctx(), vec); }
	func_decl getStruct(context& c) { func_decl_vector vec(c);  return reconstruct(c, vec); }
	std::vector<std::pair<std::string, Type*>> getListType() { return listType; }
	expr getDefault(context& c);
	std::pair<std::string, bool> argEncode(expr val) { throw "May not have Struct in parameter"; }
private:
	func_decl reconstruct(context& c, func_decl_vector& projs);

};

class Enum : public ValType {
	std::string name;
	std::vector<std::string> listMem;

public:
	Enum(std::string name, std::vector<std::string>& listType) : ValType(256) {
		this->listMem = listType;
		this->name = name;
	}

	z3::sort getSort(context& c);
	expr getVal(context& c, std::string varName);
	expr getVar(context& c, std::string varName) { return c.constant(c.str_symbol(varName.c_str()), getSort(c)); };
	expr getDefault(context& c);
	std::pair<std::string, bool> argEncode(expr val);
private:
	z3::sort reconstruct(context& c, func_decl_vector& enum_consts);
};

#endif