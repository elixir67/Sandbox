// KthNodeFromEnd.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "..\Utilities\List.h"

ListNode * FindKthToTail(ListNode * pHead, unsigned int k)
{
    if(!pHead || k == 0)
        return NULL;

    ListNode * pAhead = pHead;
    ListNode * pBehind = pHead;

    for(unsigned int i = 0; i < k - 1; ++i)
    {
        if(pAhead->m_pNext)
            pAhead = pAhead->m_pNext;
        else
            return NULL;
    }

    while(pAhead->m_pNext)
    {
        pAhead = pAhead->m_pNext;
        pBehind = pBehind->m_pNext;
    }
    
    return pBehind;
}

void Test1()
{
    ListNode* pNode1 = CreateListNode(1);
    ListNode* pNode2 = CreateListNode(2);
    ListNode* pNode3 = CreateListNode(3);
    ListNode* pNode4 = CreateListNode(4);
    ListNode* pNode5 = CreateListNode(5);

    ConnectListNodes(pNode1, pNode2);
    ConnectListNodes(pNode2, pNode3);
    ConnectListNodes(pNode3, pNode4);
    ConnectListNodes(pNode4, pNode5);

    printf("Expected result: 4 \n");
    ListNode* pNode = FindKthToTail(pNode1, 2);
    PrintListNode(pNode);

    DestroyList(pNode1);
}

int _tmain(int argc, _TCHAR* argv[])
{
    Test1();
    return 0;
}

