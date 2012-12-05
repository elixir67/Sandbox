// 51_ConvertString.cpp : Defines the entry point for the console application.
// Convert string from abbccdde to a1b2c2d2e1

#include "stdafx.h"
#include <string.h>

char * convertString1(char * pStr)
{
    if(!pStr)
        return NULL;

    char * pCur = pStr;
    char * pNext;
    const int MAX_SIZE = 50;
    char newStr[MAX_SIZE];
    int newIndex = 0;
    int num = 0;
    while(*pCur != '\0')
    {
        pNext = pCur + 1;
        ++num;
        while(*pNext != '\0' && *pNext == *pCur)
        {
            ++num;
            ++pNext;
            ++pCur;
        }
        newStr[newIndex++] = *pCur;
        newStr[newIndex++] = num + '0';
        ++pCur;
        num = 0;
    }
    newStr[newIndex] = '\0';
    int length = strlen(newStr);
    char * pRtn = new char[length + 1];
    strcpy(pRtn, newStr);
    return pRtn;
}

int _tmain(int argc, _TCHAR* argv[])
{
    char src[] = "abbccdde";
    char expected[] = "a1b2c2d2e1";
    char * result = convertString1(src);
    if(strcmp(result, expected) == 0)
        printf("passed\n");
    else
        printf("failed\n");
	return 0;
}

