#include "stdafx.h"
#include "ComplexList.h"

ComplexListNode * CreateNode(int value)
{
    ComplexListNode * pNode = new ComplexListNode();

    pNode->m_nValue = value;
    pNode->m_pNext = NULL;
    pNode->m_pSibling = NULL;

	return pNode;
}

void BuildNodes(ComplexListNode * pNode, ComplexListNode * pNext, ComplexListNode* pSibling)
{
    if(pNode)
    {
        pNode->m_pNext = pNext;
        pNode->m_pSibling = pSibling;
    }
}

void PrintList(ComplexListNode * pHead)
{
    ComplexListNode * pNode = pHead;
    while(pNode)
    {
        printf("The value of this node is %d.\n",pNode->m_nValue);

        if(pNode->m_pSibling)
            printf("The value of its sibling is %d.\n", pNode->m_pSibling->m_nValue);
        else
            printf("This node does not have a sibling.\n");

        printf("\n");
        pNode = pNode->m_pNext;
    }
}
