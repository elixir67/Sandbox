#include "StdAfx.h"
#include "Tree.h"
#include <iostream>
using namespace std;

TreeNode* CreateTreeNode(int value)
{
	TreeNode * pNode = new TreeNode();
	pNode->m_nValue = value;

	return pNode;
}

void ConnectTreeNodes(TreeNode * pParent, TreeNode * pChild)
{
	if(pParent)
		pParent->m_vChildren.push_back(pChild);
}

void PrintTreeNode(TreeNode * pNode)
{
	if(pNode)
	{
		cout << "value of this node is; " << pNode->m_nValue << endl;
		cout << "its children is as the following:" << endl;
		for(vector<TreeNode*>::const_iterator it = pNode->m_vChildren.begin();
			it != pNode->m_vChildren.end(); ++it)
		{
			if(*it)
				cout << (*it)->m_nValue << "\t";
		}
		cout << endl;
	}
	{
		cout << "this node is null" <<endl;	}
	cout << endl;
}

void PrintTree(TreeNode * pRoot)
{
    PrintTreeNode(pRoot);

    if(pRoot)
    {
       vector<TreeNode*>::iterator i = pRoot->m_vChildren.begin();
       while(i < pRoot->m_vChildren.end())
       {
            PrintTree(*i);
            ++i;
       }
    }
}

void DestroyTree(TreeNode * pRoot)
{
    if(pRoot)
    {
        vector<TreeNode*>::iterator it = pRoot->m_vChildren.begin();
        while(it < pRoot->m_vChildren.end())
        {
            DestroyTree(*it);
            ++it;
        }
        delete pRoot;
    }
}
