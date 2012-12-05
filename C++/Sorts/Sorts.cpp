// Sorts.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

template<typename T>
void bubbleSort(vector<T> & a, int left, int right)
{
	bool cond;
	for(int i = left; i < right; ++i)
	{
		cond = false;
		for(int j = right; j > i; --j)
			if(a[j] < a[j-1])
			{
			swap(a[j], a[j-1]);
			cond = true;
			}
		 
	if(!cond)
		return;
	}
}

template<typename T>
void output(const vector<T> & v)
{
	for(auto i = v.cbegin(); i != v.cend(); ++i)
		cout << *i << " ";
	cout << endl;
}

int _tmain(int argc, _TCHAR* argv[])
{
	int array[] =  {3,4,7,1,6,0,2,8,5,9};
	int length = sizeof(array)/sizeof(int);
	vector<int> a(length);
	//copy(array, array + length, a);
	for(int i = 0; i < length; ++i)
		a[i] = array[i];
	output(a);
	bubbleSort(a, 0, length-1);
	output(a);
	return 0;
}

