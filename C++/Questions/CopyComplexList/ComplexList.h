#pragma once

struct ComplexListNode
{
    int m_nValue;
    ComplexListNode* m_pNext;
    ComplexListNode* m_pSibling;
};

ComplexListNode * CreateNode(int nValue);
void BuildNodes(ComplexListNode* pNode, ComplexListNode * pNext, ComplexListNode* pSibling);
void PrintList(ComplexListNode* pHead);
