// SequenceOfBST.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "..\Utilities\BinaryTree.h"

bool VerifySequenceOfBST(int data[], int length)
{
	if(!data || length <=0)
		return false;

	int rootValue = data[length-1];
	// left sub tree's value should be less than the root value
	int i = 0;
	for(; i < length-1; ++i)
	{
		if(data[i] > rootValue)
			break;
	}
	// right sub tree's value should be more than the root value
	int j = i;
	for(; j < length-1; ++j)
	{
		if(data[i] < rootValue)
			return false;
	}

	// Verify the left sub tree is BST
	if(i> 0 && !VerifySequenceOfBST(data, i))
		return false;

	// Verify the right sub tree is BST
	if(i < length -1 && !VerifySequenceOfBST(data + i, length - 1 - i))
		return false;

	return true;
}

void Test(char * testName, int data[], int length, bool expected)
{
	if(testName)
		printf("%s begins:\n", testName);

	bool result = VerifySequenceOfBST(data, length);
	if(expected == result)
		printf("Passed!\n");
	else
		printf("Failed!\n");
}

//            10
//         /      \
//        6        14
//       /\        /\
//      4  8     12  16
void Test1()
{
    int data[] = {4, 8, 6, 12, 16, 14, 10};
    Test("Test1", data, sizeof(data)/sizeof(int), true);
}

//           5
//          / \
//         4   7
//            /
//           6
void Test2()
{
    int data[] = {4, 6, 7, 5};
    Test("Test2", data, sizeof(data)/sizeof(int), true);
}

int _tmain(int argc, _TCHAR* argv[])
{
	Test1();
	Test2();
	return 0;
}

