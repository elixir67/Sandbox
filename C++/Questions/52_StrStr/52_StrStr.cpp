// 52_StrStr.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
//#include "string.h"
#include "iostream"
#include <assert.h>
using namespace std;
// Find the sub string position in source string 
// strstr("12345", "34")   return 2;

char * strstr(char * str, char * sub)
{
    if(!str || !sub)
        return nullptr;

    char * matchStarted = '\0';
    while('\0' != *str)
    {
        if('\0' == matchStarted)
        {
            if( *str == *sub)
            {
                matchStarted = str;
                ++sub;
            }
            ++str;
        }
        else
        {
            if('\0' == *sub)
                break;
            if(*sub ++ != *str)
                break;
        }
    }

    if('\0' != *sub)
        return nullptr;
    return matchStarted;
}

int _tmain(int argc, _TCHAR* argv[])
{
    char str[] = "12345";
    char * pch = strstr(str,"34");
    cout << *pch << endl;

    pch = strstr(str, "35");
    assert(!pch && "Cannot find 35 as substring of 12345");
	return 0;
}

