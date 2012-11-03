// ReverseWordsInSentence.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <stdlib.h>
#include "..\Utilities\StringUtil.h"

void ReverseWordsInSentence(char * pData)
{
    if(!pData)
        return;

    char * pBegin = pData;
    char * pEnd = pData;
    while(*pEnd != '\0')
        ++pEnd;
    --pEnd;

    Reverse(pBegin, pEnd);

    // Reverse each word in the sentence
    pBegin = pEnd = pData;
    while(*pBegin != '\0')
    {
        if(*pBegin == ' ')
        {
            ++pBegin;
            ++pEnd;
        }
        else if(*pEnd == ' ' || *pEnd == '\0')
        {
            Reverse(pBegin, --pEnd);
            pBegin = ++pEnd;
        }
        else
        {
            ++pEnd;
        }
    }
}

void Test(char * testName, char * pTest, char * pExpected)
{
	if(testName)
		printf("%s begins:\n", testName);

	ReverseWordsInSentence(pTest);
	if((!pTest && !pExpected) || strcmp(pTest, pExpected) == 0)
		printf("Pass!\n\n");
    else
        printf("Failed.\n\n");
}

void Test1()
{
	char pTest[] = "I am a student.";
	char pExpected[] = "student. a am I";
    Test("Test1", pTest, pExpected);
}

int _tmain(int argc, _TCHAR* argv[])
{
	Test1();
	return 0;
}

