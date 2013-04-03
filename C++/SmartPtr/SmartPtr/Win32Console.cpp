// Win32Console.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream> 
#include <vector>
#include <algorithm>
#include <iterator>
#include "SmartPtr.h"
using namespace std;

class Foo
{
public:
	Foo() {cout << "Constructor" << endl;}
	~Foo() {cout << "Destructor" << endl;}
};

int _tmain(int argc, _TCHAR* argv[])
{
	SmartPtr<Foo> sp(new Foo()); 
	return 0;
}

