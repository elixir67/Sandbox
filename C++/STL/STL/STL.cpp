// STL.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>
#include <algorithm>
#include <iostream>
// #include <ios>
using namespace std;

void SharedPtr_WeakPtr();
void LambdaExamples();
void RValueTest();

int _tmain(int argc, _TCHAR* argv[])
{
	vector<int> v(10);
	//iota(v.begin(), v.end(), 0);
	for(int i = 0; i < 10; ++i)
		v[i] = i;
	for_each(v.begin(), v.end(), [](int n){cout << n << " ";});
	cout << endl;
	auto it = v.begin();
	advance(it,5);
	cout << *it << endl;

	auto v2 = v;
	cout << boolalpha;
	cout << equal(v.begin(), v.begin() + 5, v2.begin()) << endl;
	return 0;
}

