#include <iostream>
#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include "stdafx.h"
using namespace std;

bool StringToInt(const char * str, int & val)
{
    if(NULL == str)
        return false;

    int temp = 0;
    while('\0' != *str)
    {
        if(*str >= '0' && *str <= '9')
            temp = temp * 10 + (*str - '0');
        else
            return false;
    }

    val = temp;
    return true;
}

void Test(const char * str, int expect)
{
    int result = 0;
    if(StringToInt(str,result) && expect == result)
        std::cout << "Convert succeed with result " + result << endl;
    else
        std::cout << "Convert fail!"  + result << endl;
}

void main()
{
    Test("1234", 1234);
    // Test("-1234", -1234);
}
