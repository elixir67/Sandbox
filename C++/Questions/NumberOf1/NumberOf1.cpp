// NumberOf1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
using namespace std;

int NumberOf1(int n)
{
    int iFactor = 1;
    int iCount = 0;
    while(n/iFactor != 0)
    {
        int low = n - (n/iFactor) * iFactor;
        int current = (n/iFactor) % 10;
        int high = (n/iFactor) / 10;
        switch(current)
        {
            case 0:
                iCount += high * iFactor;
                break;
            case 1:
                iCount += high * iFactor + (low + 1);
                break;
            default:
                iCount += (high + 1) * iFactor;
                break;
        }
        iFactor *= 10;
    }
    return iCount;
}

void Test1(int n,int expected)
{
    if(expected == NumberOf1(n))
        cout << "Test1 passed!" << endl;
    else
        cout << "Test1 failed!" << endl;
}

int main(int argc, char* argv[])
{
    Test1(21345,18821);
	return 0;
}

