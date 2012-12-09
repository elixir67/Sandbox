// 17_MergeSortedLists.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "List.h"

// Designed it by Dan
ListNode * MergeIteratively(ListNode * pHead1, ListNode * pHead2)
{
	if(!pHead1 && !pHead2)
		return	nullptr;
	ListNode * pMergedHead = NULL;
	ListNode * pMergedTail = NULL;
	ListNode * p1 = pHead1;
	ListNode * p2 = pHead2;
	while(p1 && p2)
	{
		ListNode * p;
		if(p1->m_nValue < p2->m_nValue)
		{
			p = p1;
			p1 = p1->m_pNext;
		}
		else
		{
			p = p2;
			p2 = p2->m_pNext;
		}
		if(!pMergedHead)
		{
			pMergedHead = p;
			pMergedTail = p;
		}
		else
		{
			pMergedTail ->m_pNext = p;
			pMergedTail = p;
		}
	}

	ListNode * p = (!p1)? p1: p2;
	if(p)
	{
		if(!pMergedHead)
			pMergedHead = p;
		else
			pMergedTail ->m_pNext = p;
	}

	return pMergedHead;
}

// Shorter one
ListNode * MergeRecursively(ListNode * pHead1, ListNode * pHead2)
{
	if(!pHead1)
		return pHead2;
	else if(!pHead2)
		return pHead1;

	ListNode * pMergedHead = NULL;
	if(pHead1->m_nValue < pHead2->m_nValue)
	{
		pMergedHead = pHead1;
		pMergedHead->m_pNext = MergeRecursively(pHead1->m_pNext, pHead2);
	}
	else
	{
		pMergedHead = pHead2;
		pMergedHead->m_pNext = MergeRecursively(pHead1, pHead2->m_pNext);
	}
	return pMergedHead;
}

ListNode* Test(char* testName, ListNode* pHead1, ListNode* pHead2)
{
    if(testName != NULL)
        printf("%s begins:\n", testName);

    printf("The first list is:\n");
    PrintList(pHead1);

    printf("The second list is:\n");
    PrintList(pHead2);

    printf("The merged list is:\n");
	ListNode* pMergedHead = MergeIteratively(pHead1, pHead2);
    PrintList(pMergedHead);
    
    printf("\n\n");

    return pMergedHead;
}

// list1: 1->3->5
// list2: 2->4->6
void Test1()
{
    ListNode* pNode1 = CreateListNode(1);
    ListNode* pNode3 = CreateListNode(3);
    ListNode* pNode5 = CreateListNode(5);

    ConnectListNodes(pNode1, pNode3);
    ConnectListNodes(pNode3, pNode5);

    ListNode* pNode2 = CreateListNode(2);
    ListNode* pNode4 = CreateListNode(4);
    ListNode* pNode6 = CreateListNode(6);

    ConnectListNodes(pNode2, pNode4);
    ConnectListNodes(pNode4, pNode6);

    ListNode* pMergedHead = Test("Test1", pNode1, pNode2);

    DestroyList(pMergedHead);
}

// 两个链表中有重复的数字
// list1: 1->3->5
// list2: 1->3->5
void Test2()
{
    ListNode* pNode1 = CreateListNode(1);
    ListNode* pNode3 = CreateListNode(3);
    ListNode* pNode5 = CreateListNode(5);

    ConnectListNodes(pNode1, pNode3);
    ConnectListNodes(pNode3, pNode5);

    ListNode* pNode2 = CreateListNode(1);
    ListNode* pNode4 = CreateListNode(3);
    ListNode* pNode6 = CreateListNode(5);

    ConnectListNodes(pNode2, pNode4);
    ConnectListNodes(pNode4, pNode6);

    ListNode* pMergedHead = Test("Test2", pNode1, pNode2);

    DestroyList(pMergedHead);
}

// 两个链表都只有一个数字
// list1: 1
// list2: 2
void Test3()
{
    ListNode* pNode1 = CreateListNode(1);
    ListNode* pNode2 = CreateListNode(2);

    ListNode* pMergedHead = Test("Test3", pNode1, pNode2);

    DestroyList(pMergedHead);
}

// 一个链表为空链表
// list1: 1->3->5
// list2: 空链表
void Test4()
{
    ListNode* pNode1 = CreateListNode(1);
    ListNode* pNode3 = CreateListNode(3);
    ListNode* pNode5 = CreateListNode(5);

    ConnectListNodes(pNode1, pNode3);
    ConnectListNodes(pNode3, pNode5);

    ListNode* pMergedHead = Test("Test4", pNode1, NULL);

    DestroyList(pMergedHead);
}

// 两个链表都为空链表
// list1: 空链表
// list2: 空链表
void Test5()
{
    ListNode* pMergedHead = Test("Test5", NULL, NULL);
}

int _tmain(int argc, _TCHAR* argv[])
{
    Test1();
    Test2();
    Test3();
    Test4();
    Test5();

    return 0;
}