// CopyComplexList.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ComplexList.h"

void CloneNodes(ComplexListNode * pHead);
void ConnectSiblingNodes(ComplexListNode * pHead);
ComplexListNode * ReconnectNodes(ComplexListNode * pHead);

ComplexListNode * Clone(ComplexListNode * pHead)
{
    CloneNodes(pHead);
    ConnectSiblingNodes(pHead);
    return ReconnectNodes(pHead);
}

void CloneNodes(ComplexListNode * pHead)
{
    ComplexListNode * pNode = pHead;
    while(pNode)
    {
        ComplexListNode * pCloned = CreateNode(pNode->m_nValue);
        ComplexListNode * pNext = pNode->m_pNext;
        BuildNodes(pNode, pCloned, pNode->m_pSibling);
        BuildNodes(pCloned, pNext, NULL);

        pNode = pNext;
    }
}

void ConnectSiblingNodes(ComplexListNode * pHead)
{
    ComplexListNode * pNode = pHead;
    while(pNode)
    {
        ComplexListNode * pSibling = pNode->m_pSibling;
        ComplexListNode * pCloned = pNode->m_pNext;
        if(pSibling)
        {
            pCloned->m_pSibling = pSibling->m_pNext;
        }
        pNode = pCloned->m_pNext;
    }
}

ComplexListNode * ReconnectNodes(ComplexListNode * pHead)
{
    ComplexListNode * pNode = pHead;
    ComplexListNode * pClonedNode = NULL;
    ComplexListNode * pClonedHead = NULL;

    if(pNode)
    {
        pClonedHead = pNode->m_pNext;
        pClonedNode = pClonedHead;
        pNode->m_pNext = pClonedNode->m_pNext;
        pNode =pClonedNode->m_pNext;
    }

    while(pNode)
    {
        pClonedNode->m_pNext = pNode->m_pNext;
        pClonedNode = pNode->m_pNext;

        pNode->m_pNext = pClonedNode->m_pNext;
        pNode = pClonedNode->m_pNext;
    }
    return pClonedHead;
}

void Test(char * testName, ComplexListNode * pHead)
{
    if(testName)
        printf("%s begins:\n", testName);

    printf("The original list is: \n");
    PrintList(pHead);

    ComplexListNode * pCloned = Clone(pHead);

    printf("The cloned list is: \n");
    PrintList(pCloned);
}

//          -----------------
//         \|/              |
//  1-------2-------3-------4-------5
//  |       |      /|\             /|\
//  --------+--------               |
//          -------------------------
void Test1()
{
    ComplexListNode* pNode1 = CreateNode(1);
    ComplexListNode* pNode2 = CreateNode(2);
    ComplexListNode* pNode3 = CreateNode(3);
    ComplexListNode* pNode4 = CreateNode(4);
    ComplexListNode* pNode5 = CreateNode(5);

    BuildNodes(pNode1, pNode2, pNode3);
    BuildNodes(pNode2, pNode3, pNode5);
    BuildNodes(pNode3, pNode4, NULL);
    BuildNodes(pNode4, pNode5, pNode2);

    Test("Test1", pNode1);
}

int _tmain(int argc, _TCHAR* argv[])
{
	Test1();
	return 0;
}

