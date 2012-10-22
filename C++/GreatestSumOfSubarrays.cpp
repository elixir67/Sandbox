// GreatestSumOfSubarrays.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
#include <vector>
#include <iostream>
using namespace std;


int GreatestSumOfSubarrays(int a[], int length)
{
    if(NULL == a)
        throw exception("Invalid input!");

    int greatestSum = 0;
    int curSum = 0;
    for(int i = 0; i < length; ++i)
    {
        if(curSum <= 0)
            curSum = a[i];
        else
            curSum += a[i];
        if(curSum > greatestSum)
            greatestSum = curSum;
    }
    return greatestSum;
}


void test1()
{
	int a[8] = {1, -2, 3, 10, -4, 7, 2, -5};
//	vector<int> b;
	int n = GreatestSumOfSubarrays(a, 8);
    if(18 == n)
        cout << "test1 passed" << endl;
    else
        cout << "test1 failed" << endl;
}

int main(int argc, char* argv[])
{
    test1();
	return 0;
}


