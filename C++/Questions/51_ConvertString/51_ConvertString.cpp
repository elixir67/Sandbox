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
        //if(num < 10)
        //    newStr[newIndex++] = num + '0';
        //else
        {
            newStr[newIndex++] = '\0';
            sprintf(newStr, "%s%d", newStr, num);
            newIndex = strlen(newStr);
        }
        ++pCur;
        num = 0;
    }
    newStr[newIndex] = '\0';
    int length = strlen(newStr);
    char * pRtn = new char[length + 1];
    strcpy(pRtn, newStr);
    return pRtn;
}

void Test(char * testName, char * src, char * expected)
{
    if(testName)
        printf("%s :",testName);

    char * result = convertString1(src);
    if(strcmp(result, expected) == 0)
        printf("passed\n");
    else
        printf("failed\n");
}

void Test1()
{
    char src[] = "abbccdde";
    char expected[] = "a1b2c2d2e1";

    Test("Test1", src, expected);
}

void Test2()
{
    char src[] = "aaaaaaaaaab";
    char expected[] = "a10b1";

    Test("Test1", src, expected);
}

void Test_Others()
{
    char str[]="a=";
    char buff[256];
    int i=4;
    sprintf(buff,"%s%d",str,i);
    printf("%s",buff);
}

int _tmain(int argc, _TCHAR* argv[])
{
    Test1();
    Test2();
    return 0;
}

