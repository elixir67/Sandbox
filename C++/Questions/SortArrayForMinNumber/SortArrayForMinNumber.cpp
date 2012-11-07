// SortArrayForMinNumber.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
using namespace std;

#include "string.h"

//  Decide the order of number a and b
//  if (ab > ba ) then we need use ba
//  we can use the string comparion to simple the digitals

#define MAX_NUMBER 10

char * g_strCombine1 = new char[MAX_NUMBER * 2 +1];
char * g_strCombine2 = new char[MAX_NUMBER * 2 +1];

int compare(const void * strNumber1, const void * strNumber2)
{
    strcpy(g_strCombine1, *(const char**)strNumber1);
    strcat(g_strCombine1, *(const char**)strNumber2);

    strcpy(g_strCombine2, *(const char**)strNumber2);
    strcat(g_strCombine2, *(const char**)strNumber1);

    return strcmp(g_strCombine1, g_strCombine2);
}

void SortArrayForMinNumber(int * a, int length)
{
    // first convert the  numbers to  strings
    char** array = (char**)(new int[length]);
    for(int i = 0; i < length; ++i)
    {
        array[i] = new char[MAX_NUMBER + 1];
        sprintf(array[i], "%d", a[i]);
    }

	// sort with our compare function
    qsort(array, length, sizeof(char*), compare);

    for(int i = 0; i < length; ++i)
    {
        cout << array[i] << "\t";
    }

    for(int i = 0; i < length; ++i)
    {
        delete[] array[i];
    }
    delete[] array;
}

void Test1()
{
    int a[] = {3, 32, 321};
    SortArrayForMinNumber(a, 3);
//    char * expected = "321323";
//    char * min = SortArrayForMinNumber.vcxproj.filtersinNumber(a, 3);
//    if(strcmp(min, expected))
//        cout << "Test1 passed!" << endl;
//    else
//        cout << "Test1 failed" << endl;
}

int main(int argc, char* argv[])
{
	Test1();
	return 0;
}


