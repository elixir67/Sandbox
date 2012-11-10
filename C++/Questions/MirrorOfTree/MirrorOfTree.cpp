// MirrorOfTree.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "..\Utilities\BinaryTree.h"

// MirrorIteratively
BinaryTreeNode * MirrorOfTree(BinaryTreeNode * pRoot)
{
	if(pRoot)
	{
		BinaryTreeNode * temp = pRoot->m_pLeft;
		pRoot->m_pLeft = pRoot->m_pRight;
		pRoot->m_pRight = temp;

		MirrorOfTree(pRoot->m_pLeft);
		MirrorOfTree(pRoot->m_pRight);
	}

	return pRoot;
}

//		   1
//		  /\
//		 2  3
//		/\
//		4 5

//		  1
//		 /\
//		 3 2
//		   /\
//		   5 4
void Test1()
{
	printf("Test1 begins:\n");
	BinaryTreeNode * p1 = CreateBinaryTreeNode(1);
	BinaryTreeNode * p2 = CreateBinaryTreeNode(2);
	BinaryTreeNode * p3 = CreateBinaryTreeNode(3);
	BinaryTreeNode * p4 = CreateBinaryTreeNode(4);
	BinaryTreeNode * p5 = CreateBinaryTreeNode(5);

	ConnectTreeNodes(p1, p2, p3);
	ConnectTreeNodes(p2, p4, p5);

	printf("Before Mirror:\n");
	// output: 1,2,4,5,3
	PrintTree(p1);

	BinaryTreeNode * pResult = MirrorOfTree(p1);
	printf("After Mirror:\n");
	// output: 1,3,2,5,4
	PrintTree(pResult);
}

// 测试二叉树：出叶子结点之外，左右的结点都有且只有一个左子结点
//            8
//          7   
//        6 
//      5
//    4
void Test2()
{
	printf("Test1 begins:\n");
	BinaryTreeNode * p1 = CreateBinaryTreeNode(8);
	BinaryTreeNode * p2 = CreateBinaryTreeNode(7);
	BinaryTreeNode * p3 = CreateBinaryTreeNode(6);
	BinaryTreeNode * p4 = CreateBinaryTreeNode(5);
	BinaryTreeNode * p5 = CreateBinaryTreeNode(4);

	ConnectTreeNodes(p1, p2, NULL);
	ConnectTreeNodes(p2, p3, NULL);
	ConnectTreeNodes(p3, p4, NULL);
	ConnectTreeNodes(p4, p5, NULL);

	printf("Before Mirror:\n");
	// output: 8,7,6,5,4
	PrintTree(p1);

	BinaryTreeNode * pResult = MirrorOfTree(p1);
	printf("After Mirror:\n");
	// output: 8,7,6,5,4
	PrintTree(pResult);
}
int _tmain(int argc, _TCHAR* argv[])
{
	Test1();
	Test2();
	return 0;
}

