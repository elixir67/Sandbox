// 46_Accumulate.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
using namespace std;

template<int n>struct Accumulate
{
	//enum Value {N = Accumulate<n-1>::N + n};
	static const int Value = Accumulate<n-1>::Value + n;
};

template<> struct Accumulate<1>
{
	//enum Value {N = 1};
	static const int Value = 1;
};

void Test(const int n)
{
	int expected = 0;
	for(int i = 1; i <= n; ++i)
		expected += i;
	// Template must use const 
	const int number = 5;
	// It cannot debug into the code
	int result = Accumulate<number>::Value;
	cout << "Test " << n;
	if(result == expected)
		cout << " passed!" << endl;
	else
		cout << " failed!" << endl;
}

int _tmain(int argc, _TCHAR* argv[])
{
	Test(5);
	return 0;
}

