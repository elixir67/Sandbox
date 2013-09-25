#include "stdafx.h"
#include <functional> // for std::hash
#include <string>
#include <iostream>

void HashTest()
{
	std::wstring str = L"Hello world";
	std::hash<std::wstring> hash_fn;
	std::size_t str_hash = hash_fn(str);
	std::wcout << str_hash << std::endl;
}