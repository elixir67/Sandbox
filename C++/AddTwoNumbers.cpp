// AddTwoNumbers.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
#include <iostream>
using namespace std;

int AddTwoNumbers(int a, int b)
{
    do
    {

         int sum = a ^ b; // don't carry
         int carry = (a & b) << 1;

         a = sum;
         b = carry;
    }while(b != 0);

    return a;
}

void Test(int a, int b, int expected)
{
    int sum = AddTwoNumbers(a, b);
    char str[20];
    sprintf(str, "%d + %d = %d ", a, b, expected);
    if(sum == expected)
        cout << str << "passed!" << endl;
    else
        cout << str << "failed" << endl;
}

int main(int argc, char* argv[])
{
    Test(7, 5, 12);
	Test(5, -1, 4);
	return 0;
}

