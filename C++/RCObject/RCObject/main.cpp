// main.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "MyString.h"

int _tmain(int argc, _TCHAR* argv[])
{
	MyString a("Dan");
	MyString b(a);
	MyString c = b;

	c[2] = 'd';

	return 0;
}

