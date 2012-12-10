#include <iostream>
#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include "stdafx.h"
using namespace std;

enum Status {kValid = 0, kInvalid};
int g_nStatus = kValid;

long long StrToIntCore(const char * str, bool minus);

int StrToInt(const char * str)
{
    g_nStatus = kInvalid;

    long long num = 0;

    if(str != NULL && *str != '\0')
    {
        bool minus = false;
        if('-' == *str)
        {
            minus = true;
            ++str;
        }
        else if('+' == *str)
        {
            ++str;
        }
        if('\0' != *str)
            num = StrToIntCore(str, minus);
    }
    return (int)num;
}

long long StrToIntCore(const char * str, bool minus)
{
    long long num = 0;
    while('\0' != *str)
    {
        if(*str >= '0' && *str <= '9')
        {
            int flag = minus ?  -1: 1;
            num = num * 10 + flag * (*str - '0');

            // avoid overflow
            if((!minus && num > 0x7FFFFFFF) 
                || (minus && num < (signed int)0x80000000))
            {
                num = 0;
                break;
            }

            ++str;
        }
        else
        {
            num = 0;
            break;
        }
    }
    if('\0' == *str)
        g_nStatus = kValid;
    return num;
}

// Inital implemented by Dan
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

void Test(char* string)
{
    int result = StrToInt(string);
    if(result == 0 && g_nStatus == kInvalid)
        printf("the input %s is invalid.\n", string);
    else
        printf("number for %s is: %d.\n", string, result);
}

int _tmain(int argc, _TCHAR* argv[])
{
    Test("1234", 1234);
    Test("-1234", -1234);

    Test(NULL);

    Test("");

    Test("123");

    Test("+123");

    Test("-123");

    Test("1a33");

    Test("+0");

    Test("-0");

    Test("+2147483647");    

    Test("-2147483647");

    Test("+2147483648");

    Test("-2147483648");    

    Test("+2147483649");

    Test("-2147483649");

    Test("+");

    Test("-");

    return 0;
}
