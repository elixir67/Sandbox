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
    bool isNegative = false;

    // consider the negative number
    if(*str == '-')
    {
        isNegative = true;
        ++str;
    }
    else if(*str == '+')
    {
        isNegative = false;
        ++str;
    }

    while('\0' != *str)
    {
        if(*str >= '0' && *str <= '9')
            temp = temp * 10 + (*str - '0');
        else
            return false;
        ++str;
    }

    val = isNegative? temp*(-1): temp;
    return true;
}

void Test(const char * str, int expect)
{
    int result = 0;
    if(StringToInt(str,result) && expect == result)
        cout << "Convert succeed with result " << result << endl;
    else
        cout << "Convert fail!"  + result << endl;
}

void main()
{
    Test("1234", 1234);
    Test("-1234", -1234);
}
