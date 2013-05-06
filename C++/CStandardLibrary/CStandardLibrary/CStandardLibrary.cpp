// CStandardLibrary.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

extern void testCType();
extern void TestErrno();
extern void TestFloat();
extern void TestLimits();
extern void TestDiv();

int _tmain(int argc, _TCHAR* argv[])
{
	TestDiv();
	return 0;
}

