// PrintTreeFromTopToBottom.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "..\Utilities\BinaryTree.h"
#include <deque>
using namespace std;
void PrintTreeFromTopToBottom(BinaryTreeNode * pRoot)
{
	if(pRoot)
	{
		deque<BinaryTreeNode*> queue;
		queue.push_back(pRoot);

		while(!queue.empty())
		{
			BinaryTreeNode * pNode = queue.front();
			queue.pop_front();
			printf("%d\t",pNode->m_nValue);
			
			if(pNode->m_pLeft)
				queue.push_back(pNode->m_pLeft);
			if(pNode->m_pRight)
				queue.push_back(pNode->m_pRight);
		}
	}
}

//deque<BinaryTreeNode*> queue;
//void PrintTreeFromTopToBottom(BinaryTreeNode * pRoot)
//{
//	if(pRoot)
//	{
//
//		printf("%d\t",pRoot->m_nValue);
//			
//		if(pRoot->m_pLeft)
//			queue.push_back(pRoot->m_pLeft);
//		if(pRoot->m_pRight)
//			queue.push_back(pRoot->m_pRight);
//
//		while(!queue.empty())
//		{
//			BinaryTreeNode * pNode = queue.front();
//			queue.pop_front();
//			PrintTreeFromTopToBottom(pNode);
//		}
//	}
//}

//	   1
//	  / \
//	 2   3
//	/\  /\
//	4 5 6 7
void Test1()
{
	printf("Test1 begins:\n");
	BinaryTreeNode * p1 = CreateBinaryTreeNode(1);
	BinaryTreeNode * p2 = CreateBinaryTreeNode(2);
	BinaryTreeNode * p3 = CreateBinaryTreeNode(3);
	BinaryTreeNode * p4 = CreateBinaryTreeNode(4);
	BinaryTreeNode * p5 = CreateBinaryTreeNode(5);
	BinaryTreeNode * p6 = CreateBinaryTreeNode(6);
	BinaryTreeNode * p7 = CreateBinaryTreeNode(7);

	ConnectTreeNodes(p1, p2, p3);
	ConnectTreeNodes(p2, p4, p5);
	ConnectTreeNodes(p3, p6, p7);

	// output: 1, 2, 3, 4, 5, 6, 7
	PrintTreeFromTopToBottom(p1);
	printf("\nTest1 ends:\n");
}

int _tmain(int argc, _TCHAR* argv[])
{
	Test1();
	return 0;
}

