#include "stdafx.h"
#include "BinaryTree.h"
#include "stdio.h"

BinaryTreeNode * CreateBinaryTreeNode(int value)
{
    BinaryTreeNode * pNode = new BinaryTreeNode();
    pNode->m_nValue = value;
    pNode->m_pLeft = NULL;
    pNode->m_pRight = NULL;

    return pNode;
}

void ConnectTreeNodes(BinaryTreeNode * pParent, BinaryTreeNode * pLeft, BinaryTreeNode * pRight)
{
    if(pParent)
    {
        pParent->m_pLeft = pLeft;
        pParent->m_pRight = pRight;
    }
}

void PrintTreeNode(BinaryTreeNode * pNode)
{
    if(pNode)
    {
        printf("value of this node is: %d\n", pNode->m_nValue);

        //if(pNode->m_pLeft)
        //    printf("value of its left child is %d.\n",pNode->m_pLeft->m_nValue);
        //else
        //    printf("left child is null.\n");

        //if(pNode->m_pRight)
        //    printf("value of its right child is %d.\n", pNode->m_pRight->m_nValue);
        //else
        //    printf("right child is null.\n");
    }
    //else
    //    printf("this node is null\n");
}

void PrintTree(BinaryTreeNode * pRoot)
{
    PrintTreeNode(pRoot);

    if(pRoot)
    {
        if(pRoot->m_pLeft)
            PrintTree(pRoot->m_pLeft);

        if(pRoot->m_pRight)
            PrintTree(pRoot->m_pRight);
    }
}

void DestroyTree(BinaryTreeNode * pRoot)
{
    if(pRoot)
    {
        BinaryTreeNode * pLeft = pRoot->m_pLeft;
        BinaryTreeNode * pRight = pRoot->m_pRight;

        delete pRoot;
        pRoot = NULL;

        DestroyTree(pLeft);
        DestroyTree(pRight);
    }
}
