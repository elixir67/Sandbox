// CommonParentInTree.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "..\Utilities\Tree.h"
#include <iostream>
#include <list>
using namespace std;

bool GetNodePath(TreeNode * pRoot, TreeNode * pNode, list<TreeNode*> & path)
{
    if(pRoot == pNode)
        return true;

    path.push_back(pRoot);

    bool found = false;

    vector<TreeNode*>::iterator i = pRoot->m_vChildren.begin();
    while(!found && i < pRoot->m_vChildren.end())
    {
        found = GetNodePath(*i, pNode, path);
        ++i;
    }

    if(!found)
        path.pop_back();

    return found;
}

TreeNode * GetLastCommonNode
(
    const list<TreeNode*>& path1,
    const list<TreeNode*>& path2
)
{
    list<TreeNode*>::const_iterator it1 = path1.begin();
    list<TreeNode*>::const_iterator it2 = path2.begin();

    TreeNode* pLast = NULL;
    while((it1 != path1.end())&&(it2 != path2.end()))
    {
        if(*it1 == *it2)
            pLast = *it1;

        ++it1;
        ++it2;
    }

    return pLast;
}

TreeNode * CommonParentInTree(TreeNode * pRoot, TreeNode * pNode1, TreeNode * pNode2)
{
    if(!pRoot || !pNode1 || !pNode2)
		return NULL;

    list<TreeNode*> path1;
    GetNodePath(pRoot, pNode1, path1);
    list<TreeNode*> path2;
    GetNodePath(pRoot, pNode2, path2);

    return GetLastCommonNode(path1, path2);
}

void Test(char * testName, TreeNode * pRoot, TreeNode * pNode1, TreeNode * pNode2, TreeNode * pExpected)
{
    if(testName)
        cout << testName << " begins:"  << endl;

    TreeNode * pResult = CommonParentInTree(pRoot, pNode1, pNode2);

    if(pExpected == pResult)
        cout << "Passed." << endl;
    else
        cout << "Failed" << endl;
}

//       1
//      / \
//      2  3
//     /  \
//    4    5
//    /\  / |\
//   6 7 8 9 10
void Test1()
{
    TreeNode * pNode1 = CreateTreeNode(1);
    TreeNode * pNode2 = CreateTreeNode(2);
    TreeNode * pNode3 = CreateTreeNode(3);
    TreeNode * pNode4 = CreateTreeNode(4);
    TreeNode * pNode5 = CreateTreeNode(5);
    TreeNode * pNode6 = CreateTreeNode(6);
    TreeNode * pNode7 = CreateTreeNode(7);
    TreeNode * pNode8 = CreateTreeNode(8);
    TreeNode * pNode9 = CreateTreeNode(9);
    TreeNode * pNode10 = CreateTreeNode(10);

    ConnectTreeNodes(pNode1, pNode2);
    ConnectTreeNodes(pNode1, pNode3);

    ConnectTreeNodes(pNode2, pNode4);
    ConnectTreeNodes(pNode2, pNode5);

    ConnectTreeNodes(pNode4, pNode6);
    ConnectTreeNodes(pNode4, pNode7);

    ConnectTreeNodes(pNode5, pNode8);
    ConnectTreeNodes(pNode5, pNode9);
    ConnectTreeNodes(pNode5, pNode10);

    Test("Test1", pNode1, pNode6, pNode8, pNode2);
}


int _tmain(int argc, _TCHAR* argv[])
{
    Test1();
	return 0;
}

