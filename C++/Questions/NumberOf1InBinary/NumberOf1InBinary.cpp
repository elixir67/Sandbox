// NumberOf1InBinary.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

// TODO: why not iterate one by one
// TODO: how to compute how many bits in a number
unsigned int NumberOf1_Solution1(int n)
{
    unsigned int count = 0;
    while(n)
    {
        ++count;
        n = n & (n - 1);
    }

    return count;
}

void Test(int number, unsigned expected)
{
    unsigned int result = NumberOf1_Solution1(number);
    if(result == expected)
        printf("Solution1: Test for %p passed!\n", number);
    else
        printf("Solution1: Test for %p failed!\n", number);
}


int _tmain(int argc, _TCHAR* argv[])
{
    Test(0, 0);
    Test(1, 1);
    Test(10, 2);
    Test(0x7FFFFFFF, 31);
    Test(0xFFFFFFFF, 32);
    Test(0x80000000, 1);
	return 0;
}

