#include "type.h"
#include "utility.h"


std::string bi2hex(std::string binary)
{
	std::string result = "";
	for (int i = binary.size(); i > 0; i -= 4) {
		int start = i - 4 < 0 ? 0 : i - 4;
		std::string part = binary.substr(start, i - start);
		int val = std::stoi(part, nullptr, 2);
		std::stringstream ss;
		ss << std::hex << val;
		result = ss.str() + result;
	}
	return result;
}


std::string int2hex(int val, int size)
{
	std::stringstream ss;
	ss << std::hex << val;
	std::string result = ss.str();
	if (ss.str().size() < size)
		result = std::string(size - result.size(), '0') + ss.str();
	return result;
}

expr UInt::getVal(context& c, std::string value)
{
	if (value.substr(0, 2) == "0x") {
		int length = value.length() - 2;
		if (value.length() > 16)
			return c.int_val(c.bv_val(length * 4, hex_str_to_bool_arr(length * 4, value)).get_decimal_string(0).c_str());
		else return c.int_val((int64_t)stoull(value, 0, 16));
	}
	else return c.int_val(value.c_str());
}

expr UInt::getMax(context& c)
{
	/*BigInt n = pow(Integer(2), size) - 1;
	std::stringstream result;
	result << n;
	return c.int_val(result.str().c_str());*/
	string hexMax = string(size / 4, 'f');
	return c.int_val(c.bv_val(size, hex_str_to_bool_arr(size, hexMax)).get_decimal_string(0).c_str());
}

std::pair<std::string, bool> UInt::argEncode(expr val)
{
	return { toHex(val, 64), false };
}

expr Int::getVal(context& c, std::string value)
{
	if (value.substr(0, 2) == "0x") {
		int length = value.length() - 2;
		if (value.length() > 16)
			return c.int_val(c.bv_val(length * 4, hex_str_to_bool_arr(length * 4, value)).get_decimal_string(0).c_str());
		else return c.int_val((int64_t)stoull(value, 0, 16));
	}
	else return c.int_val(value.c_str());
}

expr Int::getMax(context& c)
{
	/*BigInt n = pow(Integer(2), size - 1) - 1;
	std::stringstream result;
	result << n;
	return c.int_val(result.str().c_str());*/
	string hexMax = '7' + string(size / 4 - 1, 'f'); // max = 2 ** (size - 1) - 1;
	return c.int_val(c.bv_val(size, hex_str_to_bool_arr(size, hexMax)).get_decimal_string(0).c_str());
}

expr Int::getMin(context& c)
{
	/*BigInt n = pow(Integer(2), size - 1);
	std::stringstream result;
	result << n;
	std::string min = "-" + result.str();
	return c.int_val(min.c_str());*/
	string hexMax = '8' + string(size / 4 - 1, '0'); // min = - 2 ** (size - 1); 
	string min = '-' + c.bv_val(size, hex_str_to_bool_arr(size, hexMax)).get_decimal_string(0);
	return c.int_val(min.c_str());
}

std::pair<std::string, bool> Int::argEncode(expr val)
{
	return { toHexSigned(val, 64), false };
}

expr Struct::getMem(context& c, std::string funcName, expr var)
{
	func_decl_vector vec(c);
	reconstruct(c, vec);
	for (int i = 0; i < listType.size(); ++i) {
		if (listType[i].first == funcName)
			return vec[i](var);
	}
	throw "Dont have member of struct";
}

expr Struct::getNewStruct(context& c, std::string funcName, expr temp, expr var)
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

expr Struct::getDefault(context& c)
{
	expr_vector vec(c);
	func_decl_vector func_vec(c);
	func_decl struct_func = reconstruct(c, func_vec);
	for (int i = 0; i < listType.size(); ++i) 
		vec.push_back(listType[i].second->getDefault(c));
	return struct_func(vec);
}

func_decl Struct::reconstruct(context& c, func_decl_vector& projs)
{
	int size = listType.size();
	char* _names[20];
	z3::sort sorts[20] = { c.int_sort(), c.int_sort(), c.int_sort(), 
		c.int_sort(), c.int_sort(), c.int_sort(), c.int_sort(), c.int_sort(), c.int_sort(), c.int_sort(),
		c.int_sort(), c.int_sort(), c.int_sort(), c.int_sort(), c.int_sort(), c.int_sort(), c.int_sort(), 
		c.int_sort(), c.int_sort(), c.int_sort() };

	int i = 0;
	for (auto mem : listType) {
		_names[i] = _strdup(mem.first.c_str());
		sorts[i++] = mem.second->getSort(c);
	}
	func_decl structDecl = c.tuple_sort(name.c_str(), size, _names, sorts, projs);
	return structDecl;
}

z3::sort Enum::getSort(context& c)
{
	func_decl_vector enum_consts(c);
	return reconstruct(c, enum_consts);
}

expr Enum::getVal(context& c, std::string varName)
{
	func_decl_vector enum_consts(c);
	reconstruct(c, enum_consts);

	for (unsigned i = 0; i < listMem.size(); ++i)
		if (varName == listMem[i])
			return enum_consts[i]();

	return expr(c);
}

expr Enum::getDefault(context& c)
{
	func_decl_vector enum_consts(c);
	reconstruct(c, enum_consts);
	return enum_consts[0]();
}

std::pair<std::string, bool> Enum::argEncode(expr val)
{
	for (int i = 0; i < listMem.size(); ++i) {
		if (listMem[i] == val.to_string())
			return { int2hex(i, 64), false };
	}
	throw "The Enum value is wrong";
}

z3::sort Enum::reconstruct(context& c, func_decl_vector& enum_consts)
{
	char* _names[30];
	for (unsigned i = 0; i < listMem.size(); ++i)
		_names[i] = _strdup(listMem[i].c_str());

	func_decl_vector enum_testers(c);
	z3::sort s = c.enumeration_sort(name.c_str(), listMem.size(), _names, enum_consts, enum_testers);
	return s;
}

z3::sort Map::getSort(context& c)
{
	sort_vector indexs(c);
	for (auto i : list_index)
		indexs.push_back(i->getSort(c));

	return c.array_sort(indexs, array_type->getSort(c));
}

std::pair<std::string, bool> Bool::argEncode(expr val)
{
	if (val.to_string() == "true")
		return { std::string(63, '0') + '1', false };
	return { std::string(64, '0'), false };
}

expr Byte::getVal(context& c, std::string value)
{
	return c.bv_val(256, hex_str_to_bool_arr(256, value));
}

std::pair<std::string, bool> Byte::argEncode(expr val)
{
	std::string valStr = val.to_string();
	//valStr = valStr.substr(2);
	std::string hexVal = valStr[1] == 'x' ? valStr.substr(2) : bi2hex(valStr.substr(2));
	size_t index = hexVal.find_first_not_of('0', 0);
	if (index == string::npos)
		index = hexVal.size();
	int length = hexVal.size() - index;
	if (length < 64)
		hexVal = hexVal.substr(index) + std::string(64 - length, '0');
	if (bytes) {
		hexVal = int2hex(ceil(length / 2.0), 64) + hexVal;
		return { hexVal, true };
	}
	return { hexVal, false };
}

expr Address::getVal(context& c, std::string value)
{
	return c.bv_val(size, hex_str_to_bool_arr(256, value));
}

std::pair<std::string, bool> Address::argEncode(expr val)
{
	std::string valStr = val.to_string();
	std::string hexVal = valStr[1] == 'x' ? valStr.substr(2) : bi2hex(valStr.substr(2));
	if (hexVal.size() < 64)
		hexVal = std::string(64 - hexVal.size(), '0') + hexVal;

	return { hexVal, false };
}

std::pair<std::string, bool> FixArray::argEncode(expr val)
{
	std::string result = "";
	context& c = val.ctx();
	solver s(c);
	for (auto i = 0; i < length; i++) {
		expr arr_var = array_type->getVar(c, "x" + to_string(i));
		expr sel = select(val, i);
		s.add(arr_var == sel);
	}
	s.check();
	model m = s.get_model();
	for (auto i = 0; i < length; i++) {
		expr arr_val = m.eval(array_type->getVar(c, "x" + to_string(i)));
		auto temp = array_type->argEncode(arr_val);
		result += temp.first;
	}

	return { result, false };
}

std::pair<std::string, bool> DynamicArray::argEncode(expr val)
{
	std::string result = int2hex(length, 64);
	string tail = "";
	vector<std::pair<std::string, bool>> temp;
	int len = 0;
	for (auto i = 0; i < length; i++) {
		expr arr_val = select(val, i);
		auto enc = array_type->argEncode(arr_val);
		temp.push_back(enc);
		if (enc.second)
			len += 32;
		else len += enc.first.size() / 2;
	}
	for (auto i : temp) {
		int lenTail = 0;
		if (i.second) {
			result += int2hex(len + lenTail, 64);
			tail += i.first;
			lenTail += i.first.size() / 2;
		}
		else result += i.first;
	}
	result += tail;

	return { result, true };
}
