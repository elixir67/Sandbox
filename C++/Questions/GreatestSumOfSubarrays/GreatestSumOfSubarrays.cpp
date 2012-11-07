// GreatestSumOfSubarrays.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>
#include <iostream>
using namespace std;


int GreatestSumOfSubarrays(int a[], int length, vector<int> & subArray)
{
    if(NULL == a)
        throw exception("Invalid input!");

    int greatestSum = 0;
    int curSum = 0;
    vector<int> maxArray;
    vector<int> curArray;
    for(int i = 0; i < length; ++i)
    {
        if(curSum <= 0)
        {
            curArray.clear();
            curArray.push_back(a[i]);
            curSum = a[i];
        }
        else
        {
            curArray.push_back(a[i]);
            curSum += a[i];
        }
        if(curSum > greatestSum)
        {
            maxArray.clear();
			maxArray.resize(curArray.size());
            copy(curArray.begin(), curArray.end(), maxArray.begin());
            greatestSum = curSum;
        }
    }
	subArray.resize(maxArray.size());
    copy(maxArray.begin(), maxArray.end(), subArray.begin());
    return greatestSum;
}


void test1()
{
	int a[8] = {1, -2, 3, 10, -4, 7, 2, -5};

	int expectedSum = 18;
	vector<int> expectedArray(5);//{3, 10, -4, 7, 2}; canot initialize it using C++11 style
	expectedArray[0] = 3;
	expectedArray[1] = 10;
	expectedArray[2] = -4;
	expectedArray[3] = 7;
	expectedArray[4] = 2;

	vector<int> subArray;
	int n = GreatestSumOfSubarrays(a, 8, subArray);
    for(vector<int>::const_iterator it = subArray.cbegin(); it != subArray.cend(); ++it)
    {
        cout << *it << endl;
    }
    if(18 == n && expectedArray == subArray)
        cout << "test1 passed" << endl;
    else
        cout << "test1 failed" << endl;
}

int main(int argc, char* argv[])
{
    test1();
	return 0;
}


