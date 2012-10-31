#include "stdafx.h"
#include "List.h"
#include <iostream>
using namespace std;

ListNode * CreateListNode(int value) {
    ListNode * pNode = new ListNode();
    pNode->m_nValue = value;
    pNode->m_pNext = NULL;

    return pNode;
}

void ConnectListNode(ListNode * pCurrent, ListNode * pNext) {
    if(!pCurrent) {
        cout << "Error to connect two nodes\n" << endl;
    }
    pCurrent->m_pNext = pNext;
}

void PrintListNode(ListNode * pNode) {
    if(pNode)
        cout << "The node is NULL" << endl;
    else
        cout << "The value in node is " << pNode->m_nValue << endl;
}

void PrintList(ListNode * pHead) {
    cout << "PrintList starts." << endl;
    ListNode * pNode = pHead;
    while(pNode) {
        cout << pNode->m_nValue << "\t";
        pNode = pNode->m_pNext;
    }
    cout << "PrintList ends." << endl;
}

void DestroyList(ListNode * pHead) {
    ListNode * pNode = pHead;
    while(pNode) {
        pHead = pNode->m_pNext;
        delete pNode;
        pNode = pHead;
    }
}

void AddToTail(ListNode ** pHead, int value) {
    ListNode * pNode = CreateListNode(value);

    if(*pHead){
        ListNode * pCurrent = *pHead;
        while(pCurrent->m_pNext)
            pCurrent = pCurrent->m_pNext;
        pCurrent->m_pNext = pNode;

    } else {
        *pHead = pNode;
    }
}

void RemoveNode(ListNode ** pHead, int value) {
    if(!pHead || !(*pHead))
        return;

    ListNode * pToBeDeleted = NULL;
    if((*pHead)->m_nValue == value) {
        pToBeDeleted = * pHead;
        *pHead = (*pHead)->m_pNext;
    } else {
        ListNode * pNode = *pHead;
        while(pNode->m_pNext && pNode->m_pNext->m_nValue != value)
            pNode = pNode->m_pNext;

        if(pNode->m_pNext && pNode->m_pNext->m_nValue == value) {
            pToBeDeleted = pNode->m_pNext;
            pNode->m_pNext = pNode->m_pNext->m_pNext;
        }
    }

    if(pToBeDeleted) {
        delete pToBeDeleted;
        pToBeDeleted = NULL;
    }

}
