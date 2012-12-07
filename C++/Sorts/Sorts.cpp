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


template <typename Type>
void selectSort( vector<Type> &a, int left, int right )
{
    Type minPos;
    for( int i=left; i<right; ++i )
    {
        minPos = i;
        for( int j=i+1; j<=right; ++j )
            if( a[j] < a[minPos] )
                minPos = j;
        if( i != minPos )
            swap( a[i], a[minPos] );
    }
}

template <typename Type>
void insertSort( vector<Type> &a, int left, int right )
{
    for( int p=left+1; p<=right; p++ )
    {
        Type tmp = a[p];
        int j;
        for( j=p; j>left && tmp<a[j-1]; --j )
                    a[j] = a[j-1];
        a[j] = tmp;
    }
}


template<typename T>
void output(const vector<T> & v)
{
	for(auto i = v.cbegin(); i != v.cend(); ++i)
		cout << *i << " ";
	cout << endl;
}

template<typename T>
int binarySearch(const vector<T> & data, T v)
{
    int minIndex = 0;
    int maxIndex = data.size() - 1;
    int midIndex;
    while(minIndex < maxIndex - 1)
    {
        midIndex = minIndex + (maxIndex - minIndex)/2;
        if(data[midIndex] == v)
            return midIndex;
        if(data[midIndex] < v)
            minIndex = midIndex;
        else
            maxIndex = midIndex;
    }
    if(data[maxIndex] == v)
        return maxIndex;
    else if(data[minIndex] == v)
        return minIndex;
    return -1;
}

int _tmain(int argc, _TCHAR* argv[])
{
	//int array[] =  {3,4,7,1,6,0,2,8,5,9};
    int array[] =  {3,4,3,1,6,0,2,8,5,9};
	int length = sizeof(array)/sizeof(int);
	vector<int> a(length);
	//copy(array, array + length, a);
	for(int i = 0; i < length; ++i)
		a[i] = array[i];
	output(a);
    //bubbleSort(a, 0, length - 1);
	insertSort(a, 0, length-1);
	output(a);

    //int index = binarySearch(a, 10);
    //cout << "Find index:" << index << endl;
	return 0;
}


