// main.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "MyString.h"
#include "MyStringWithCharProxy.h"
#include <iostream>

int _tmain(int argc, _TCHAR* argv[])
{
	MyString a("Dan");
	MyString b(a);
	MyString c = b;

	// Creates a new instance even it's a read operation
	std::cout << c[2] << std::endl;
	c[2] = 'd';

	MyStringWithCharProxy ap("Dan");
	MyStringWithCharProxy bp(ap);
	MyStringWithCharProxy cp = bp;

	// Doesn't create instance when it's a read operaton
	std::cout << cp[2] << std::endl;
	// Creates a new instance when it's assignment operation, lazy creation
	cp[2] = 'e';

	return 0;
}

