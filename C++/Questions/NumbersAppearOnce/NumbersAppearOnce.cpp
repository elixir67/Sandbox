// NumbersAppearOnce.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

unsigned int FindFirstBitIs1(int num)
{
    int indexBit = 0;
    while((num & 1 == 0) && (indexBit <8 * sizeof(int)))
    {
        num = num>> 1;
        ++indexBit;
    }
    return indexBit;
}

bool IsBit1(int num, unsigned int indexOf1)
{
    num = num >> indexOf1;
    return (num & 1);
}

void FindNumsAppearOnce(int data[], int length, int * num1, int * num2)
{
    if(data == NULL || length < 2)
        return;

    int resultExclusiveOR = 0;
    for(int i = 0; i < length; ++i)
        resultExclusiveOR ^= data[i];

    unsigned int indexOf1 = FindFirstBitIs1(resultExclusiveOR);
	*num1 = 0;
	*num2 = 0;
    for(int i = 0; i < length; ++i)
    {
        if(IsBit1(data[i], indexOf1))
            *num1 ^= data[i];
        else
            *num2 ^= data[i];
    }
}

void Test(char * testName, int data[], int length, int expected1, int expected2)
{
    if(testName)
        printf("%s begins:\n", testName);

    int result1, result2;
    FindNumsAppearOnce(data, length, &result1, &result2);
    if((expected1 == result1 && expected2 == result2) ||
        (expected1 == result2 && expected2 == result1))
        printf("Passed.\n");
    else
        printf("Failed.\n");
}

void Test1()
{
    int data[] = {2 ,4, 3, 6, 3, 2, 5, 5};
    Test("Test1", data, sizeof(data)/sizeof(int), 4, 6);
}

int _tmain(int argc, _TCHAR* argv[])
{
	Test1();
	return 0;
}

