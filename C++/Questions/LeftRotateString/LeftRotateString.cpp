// LeftRotateString.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "stdlib.h"
#include "string.h"
#include "..\Utilities\StringUtil.h"

char * LeftRotateString(char * pStr, int n)
{
    if(!pStr)
        return NULL;

    int length = strlen(pStr);
    if(length > 0 && n > 0 && n < length)
    {
        char * pFirstStart = pStr;
        char * pFirstEnd = pStr + n -1;
        char * pSecondStart = pStr + n;
        char * pSecondEnd = pStr + length -1;

        Reverse(pFirstStart, pFirstEnd);
        Reverse(pSecondStart, pSecondEnd);
        Reverse(pFirstStart, pSecondEnd);
    }

    return pStr;
}

void Test(char * testName, char * input, int num, char * expected)
{
    if(testName)
        printf("%s begins:\n", testName);

    char * result = LeftRotateString(input, num);

    if((!result && !expected) || strcmp(result, expected) == 0)
        printf("Passed!");
    else
        printf("Failed!");

}
void Test1()
{
    char input[] = "abcdefg";
    char expected[] = "cdefgab";

    Test("Test1", input, 2, expected);
}

int _tmain(int argc, _TCHAR* argv[])
{
	Test1();
	return 0;
}

