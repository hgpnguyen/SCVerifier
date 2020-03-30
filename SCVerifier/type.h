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

	bool* hex_str_to_bool_arr(unsigned n, string hex) {
		bool* arr = new bool[n] {false};
		string bin_str = hex_str_to_bin_str(hex);

		for (int i = 0; i < bin_str.size(); ++i) {
			arr[i] = bin_str[bin_str.size() - i - 1] == '0' ? false : true;
		}
		return arr;
	}
	const char* hex_char_to_bin(char c) {
		switch (toupper(c))
		{
		case '0': return "0000";
		case '1': return "0001";
		case '2': return "0010";
		case '3': return "0011";
		case '4': return "0100";
		case '5': return "0101";
		case '6': return "0110";
		case '7': return "0111";
		case '8': return "1000";
		case '9': return "1001";
		case 'A': return "1010";
		case 'B': return "1011";
		case 'C': return "1100";
		case 'D': return "1101";
		case 'E': return "1110";
		case 'F': return "1111";
		default: throw "invalid char";
		}
	}
	string hex_str_to_bin_str(const std::string& hex) {
		std::string bin;
		string _hex = hex.substr(0, 2) == "0x" ? hex.substr(2) : hex;
		for (unsigned i = 0; i != _hex.length(); ++i)
			bin += hex_char_to_bin(_hex[i]);
		return bin;
	}
};

class Int : public ValType {

public:
	Int(int size) : ValType(size) {}

	z3::sort getSort(context& c) { return  c.int_sort(); }
	expr getVar(context& c, string varName) { return c.int_const(varName.c_str()); }
	expr getVal(context& c, string value) { 
		return value.substr(0, 2) == "0x" ? c.int_val((int64_t)stoull(value, 0, 16)) : c.int_val(value.c_str());; }
};

class UInt : public ValType {
public:
	UInt(int size) : ValType(size) {}

	z3::sort getSort(context& c) { return  c.int_sort(); }
	expr getVar(context& c, string varName) { return c.int_const(varName.c_str()); }
	expr getVal(context& c, string value) { 
		return value.substr(0, 2) == "0x" ? c.int_val((uint64_t)stoull(value, 0, 16)) : c.int_val(value.c_str()); }
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
	expr getVal(context& c, string value) { return c.bv_val(256, hex_str_to_bool_arr(256, value)); }
};

class Address : public ValType {
public:
	Address() : ValType(160) {}

	z3::sort getSort(context& c) { return  c.bv_sort(size); }
	expr getVar(context& c, string varName) { return c.bv_const(varName.c_str(), size); }
	expr getVal(context& c, string value) { return c.bv_val(size, hex_str_to_bool_arr(256, value)); }
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