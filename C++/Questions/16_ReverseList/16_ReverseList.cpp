// 16_ReverseList.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "List.h"


// If using resursive method, then the method returns the end of the list every time
// we may lost the head, if we don't use the static variable to record the last item(new head)
ListNode * ReverseListRecursive(ListNode * pHead);

ListNode * ReverseListIterative(ListNode * pHead)
{
	if(!pHead)
		return NULL;

	ListNode * pPrev = NULL;
	ListNode * pCur = pHead;
	ListNode * pReversedHead = NULL;

	while(pCur)
	{
		ListNode * pNext = pCur->m_pNext;
		if(!pNext)
			pReversedHead = pCur;
		pCur->m_pNext = pPrev;
		pPrev = pCur;
		pCur = pNext;
	}
	return pReversedHead;
}

// ====================测试代码====================
ListNode* Test(ListNode* pHead)
{
    printf("The original list is: \n");
    PrintList(pHead);

    ListNode* pReversedHead = ReverseListIterative(pHead);

    printf("The reversed list is: \n");
    PrintList(pReversedHead);

    return pReversedHead;
}

// 输入的链表有多个结点
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

    ListNode* pReversedHead = Test(pNode1);

    DestroyList(pReversedHead);
}

// 输入的链表只有一个结点
void Test2()
{
    ListNode* pNode1 = CreateListNode(1);

    ListNode* pReversedHead = Test(pNode1);

    DestroyList(pReversedHead);
}

// 输入空链表
void Test3()
{
    Test(NULL);
}

int _tmain(int argc, _TCHAR* argv[])
{
	Test1();
	Test2();
	Test3();
	return 0;
}

