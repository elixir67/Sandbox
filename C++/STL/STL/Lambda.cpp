#include "stdafx.h"
#include <iostream>
#include <assert.h>
using namespace std;
void LambdaExamples()
{
    // Defining and calling a lambda
    double pi = []{return 3.14159;}();  // Returns double
    int n = [](int n){return --n;}(5);

    // Defining and storing the lambda in auto variable
    auto IsEven = [](int n) {return 0 == (n&1);};

    // calling it now
    IsEven(21);
    IsEven(24);

    // Lambda with two parameters
    int nMax = [](int n1, int n2)
    {
        return (n1 > n2)? n1: n2;
    }
    (56, 11);// calling here

    cout << nMax << endl;

    auto Min = [](int n1, int n2)
    {
        return (n1 < n2)? n1: n2;
    };
    cout << Min(56, 11) << endl;

    // Lambda that returns sum of all elements
    auto Sum = [](int data[], int length) -> __int64
    {
        __int64 nSum = 0;
        for(int i = 0; i < length; ++i)
            nSum += data[i];
        return nSum;
    };

    int data1[5] = {1, 2, 3, 4, 5};
    cout << Sum(data1, 5) << endl;

    int data2[5] = {83844, 18000000, 0xFFF0000, 190000012, 1234567890};
    cout << Sum(data2, 5) << endl;
    assert(false);
}   