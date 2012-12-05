// PathInTree.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "..\Utilities\BinaryTree.h"
#include <vector>

void FindPath(BinaryTreeNode * pRoot, int expectedSum, int& currentSum, std::vector<int> & path);

void FindPath(BinaryTreeNode * pRoot, int expectedSum)
{
    if(pRoot == NULL)
        return;

    std::vector<int> path;
    int currentSum = 0;
    FindPath(pRoot, expectedSum, currentSum, path);
}


void FindPath(BinaryTreeNode * pRoot, int expectedSum, int& currentSum, std::vector<int> & path)
{
    if(!pRoot)
        return;

    currentSum += pRoot->m_nValue;
    path.push_back(pRoot->m_nValue);

    bool isLeaf = !pRoot->m_pLeft && !pRoot->m_pRight;
    if(currentSum == expectedSum && isLeaf)
    {
        printf("A path is found: ");
        std::vector<int>::iterator it = path.begin();
        for(;it != path.end(); ++it)
            printf("%d\t", *it);
        printf("\n");
    }

    if(pRoot->m_pLeft)
        FindPath(pRoot->m_pLeft, expectedSum, currentSum, path);

    if(pRoot->m_pRight)
        FindPath(pRoot->m_pRight, expectedSum, currentSum, path);

    // return back to parent node
    // remove the value first
    currentSum -= pRoot->m_nValue;
    path.pop_back();

}

void Test(char * testName, BinaryTreeNode * pRoot, int expectedSum)
{
    if(testName)
        printf("%s begins:\n", testName);

    FindPath(pRoot, expectedSum);
    printf("\n");
}

//            10
//         /      \
//        5        12
//       /\
//      4  7
// 有两条路径上的结点和为22
void Test1()
{
    BinaryTreeNode* pNode10 = CreateBinaryTreeNode(10);
    BinaryTreeNode* pNode5 = CreateBinaryTreeNode(5);
    BinaryTreeNode* pNode12 = CreateBinaryTreeNode(12);
    BinaryTreeNode* pNode4 = CreateBinaryTreeNode(4);
    BinaryTreeNode* pNode7 = CreateBinaryTreeNode(7);

    ConnectTreeNodes(pNode10, pNode5, pNode12);
    ConnectTreeNodes(pNode5, pNode4, pNode7);

    printf("Two paths should be found in Test1.\n");
    Test("Test1", pNode10, 22);

    DestroyTree(pNode10);
}

int _tmain(int argc, _TCHAR* argv[])
{
	Test1();
    return 0;
}

