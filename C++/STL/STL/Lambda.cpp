#include "stdafx.h"
#include <iostream>
#include <assert.h>
#include <algorithm>
#include <vector>
using namespace std;

void LambdaWithSTL();

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
    
    LambdaWithSTL();
}   

void IsEven(int n)
{
     cout << (0 == (n & 1)? "Even": "Odd") << " ";
}

void LambdaWithSTL()
{
    int Array[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    for_each(Array, &Array[10], IsEven);
    cout << endl;

    for_each(Array, Array + 10, [](int n){ cout << n <<  " ";});
    cout << endl;

    vector<int> IntVector;
    IntVector.assign(Array, Array + 10);

    // This lambda uses multiple features:
    // -- decltype to deduce argument type!
    // -- auto keyword in for-loop for iterator
    // -- shows std namesspace is NOT inherited from outer scope!

    // If you change IntVector to something else (like std::list<float>)
    // the following code would still compile!
    auto DisplayVector = [](const decltype(IntVector) & v) 
    {
        int nPos = 0;
        for(auto it = v.cbegin(); it != v.cend(); ++it)
        {
            cout << "Element [" << nPos << "] = " << *it << endl;
            ++nPos;
        }
    };

    DisplayVector(IntVector);
    // Let's double them! NOTE the '&' in lambdas' argument.
    // IMPORTANT!
    // If you miss to put ampersand, the compiler will NOT give you any 
    // warning/error. for_each just calls the function, since it uses
    // function type as template (and not as function pointer, or function object).
    // It doesn't care if argument is int or int&. 'const' can also be put.
    for_each(IntVector.begin(), IntVector.end(), [](int & n){n *= 2;});

    DisplayVector(IntVector);

    transform(Array, Array + 10, IntVector.begin(), [](int n) {return n*100;});

    DisplayVector(IntVector);
}
