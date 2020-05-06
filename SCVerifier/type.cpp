#include "type.h"
#include "BigInt.h"



expr UInt::getMax(context& c)
{
	BigInt n = pow(Integer(2), size) - 1;
	stringstream result;
	result << n;
	return c.int_val(result.str().c_str());
}

expr Int::getMax(context& c)
{
	BigInt n = pow(Integer(2), size - 1) - 1;
	stringstream result;
	result << n;
	return c.int_val(result.str().c_str());
}

expr Int::getMin(context& c)
{
	BigInt n = pow(Integer(2), size - 1);
	stringstream result;
	result << n;
	string min = "-" + result.str();
	return c.int_val(min.c_str());
}

expr Struct::getMem(context& c, string funcName, expr var)
{
	func_decl_vector vec(c);
	reconstruct(c, vec);
	for (int i = 0; i < listType.size(); ++i) {
		if (listType[i].first == funcName)
			return vec[i](var);
	}
	throw "Dont have member of struct";
}

expr Struct::getNewStruct(context& c, string funcName, expr temp, expr var)
{
	expr_vector vec(c);
	func_decl_vector func_vec(c);
	func_decl struct_func = reconstruct(c, func_vec);
	for (int i = 0; i < listType.size(); ++i) {
		if (listType[i].first == funcName)
			vec.push_back(temp);
		else vec.push_back(func_vec[i](var));
	}
	return struct_func(vec);
}

func_decl Struct::reconstruct(context& c, func_decl_vector& projs)
{
	int size = listType.size();
	char* _names[10];
	z3::sort sorts[10] = { c.int_sort(), c.int_sort(), c.int_sort(), 
		c.int_sort(), c.int_sort(), c.int_sort(), c.int_sort(), c.int_sort(), c.int_sort(), c.int_sort() };

	int i = 0;
	for (auto mem : listType) {
		_names[i] = _strdup(mem.first.c_str());
		sorts[i++] = mem.second->getSort(c);
	}
	func_decl structDecl = c.tuple_sort(name.c_str(), size, _names, sorts, projs);
	return structDecl;
}
