// PrintListInReversedOrder.cpp : Defines the entry point for the console application.
//

// TODO: can print the values recursively instead of change the list structure?
#include "stdafx.h"
#include "..\Utilities\List.h"
#include "iostream"
using namespace std;

ListNode * ReverseList(ListNode * pHead){
    if(!pHead)
        return NULL;

    ListNode * pReversedHead = NULL;
    ListNode * pNode = pHead;
    ListNode * pPrev = NULL;
    while(pNode != NULL) {
        ListNode * pNext = pNode->m_pNext;

        if(NULL == pNext)
            pReversedHead = pNode;

        pNode->m_pNext = pPrev;

        pPrev = pNode;
        pNode = pNext;
    }
    return pReversedHead;
}

ListNode * Test(ListNode * pHead) {
    cout << "The original list is" << endl;
    PrintList(pHead);

    ListNode * pReversedHead = ReverseList(pHead);
    PrintList(pReversedHead);

	return pReversedHead;
}

void Test1(){
    ListNode * pNode1 = CreateListNode(1);
    ListNode * pNode2 = CreateListNode(2);
    ListNode * pNode3 = CreateListNode(3);
    ListNode * pNode4 = CreateListNode(4);
    ListNode * pNode5 = CreateListNode(5);

    ConnectListNodes(pNode1, pNode2);
    ConnectListNodes(pNode2, pNode3);
    ConnectListNodes(pNode3, pNode4);
    ConnectListNodes(pNode4, pNode5);

    ListNode * pReversedHead = Test(pNode1);

    DestroyList(pReversedHead);
}

int _tmain(int argc, _TCHAR* argv[]) {
    Test1();
	return 0;
}

