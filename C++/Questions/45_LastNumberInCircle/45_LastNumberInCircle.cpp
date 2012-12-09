// 45_LastNumberInCircle.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <list>
using namespace std;

// There's a circle from 0 to n-1 initially,
// If we delete the m-th number from 0
// Get the last number remaining in the circle
int LastNumber(int n, int m)
{
	if(n < 0 || m < 0 || n < m)
		return -1;

	// Use list to simulate the circle
	list<int> circle;
	for(auto i = 0; i < n; ++i)
		circle.push_back(i);

	auto it = circle.begin();
	while(circle.size() > 1)
	{

		// Finds the m-th number if it hits the end
		// then moves to the beginning
		for(auto i = 0; i < m; ++i)
		{
			if(it != circle.end())
				++it;
			else
				it = circle.begin();
		}

		// Remove the m-th number
		circle.erase(it);
		++it;	;
	}

	return circle.front();
}

// ====================²âÊÔ´úÂë====================
void Test(char* testName, unsigned int n, unsigned int m, int expected)
{
    if(testName != NULL)
        printf("%s begins: \n", testName);

	if(LastNumber(n, m) == expected)
        printf("Solution1 passed.\n");
    else
        printf("Solution1 failed.\n");

    printf("\n");
}

void Test1()
{
    Test("Test1", 5, 3, 3);
}

void Test2()
{
    Test("Test2", 5, 2, 2);
}

void Test3()
{
    Test("Test3", 6, 7, 4);
}

void Test4()
{
    Test("Test4", 6, 6, 3);
}

void Test5()
{
    Test("Test5", 0, 0, -1);
}

void Test6()
{
    Test("Test6", 4000, 997, 1027);
}

int _tmain(int argc, _TCHAR* argv[])
{
    Test1();
    Test2();
    Test3();
    Test4();
    Test5();
    Test6();

    return 0;
}
