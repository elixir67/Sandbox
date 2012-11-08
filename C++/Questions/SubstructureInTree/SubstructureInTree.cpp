// SubstructureInTree.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "..\Utilities\BinaryTree.h"

bool DoesTree1HaveTree2(BinaryTreeNode * pRoot1, BinaryTreeNode * pRoot2);
// TODO: TEST CASE
bool HasSubtree(BinaryTreeNode * pRoot1, BinaryTreeNode * pRoot2)
{
    bool result = false;

    if(pRoot1 && pRoot2)
    {
        if(pRoot1->m_nValue == pRoot2->m_nValue)
            result = DoesTree1HaveTree2(pRoot1, pRoot2);
        if(!result)
            result = HasSubtree(pRoot1->m_pLeft, pRoot2);
        if(!result)
            result = HasSubtree(pRoot2->m_pRight, pRoot2);
    }
    return result;
}

bool DoesTree1HaveTree2(BinaryTreeNode * pRoot1, BinaryTreeNode * pRoot2)
{
    if(!pRoot2)
        return true;

    if(!pRoot1)
        return false;

    if(pRoot1->m_nValue != pRoot2->m_nValue)
        return false;

    return DoesTree1HaveTree2(pRoot1->m_pLeft, pRoot2->m_pLeft) &&
        DoesTree1HaveTree2(pRoot1->m_pRight, pRoot2->m_pRight);

}

int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

