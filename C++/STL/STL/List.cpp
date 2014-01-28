#include "stdafx.h"
#include <list>
#include <iostream>

using namespace std;

void ListTest()
{
    list<int> l;
    l.insert(l.end(), 5);
    for each (auto var in l)
    {
        cout << var << endl;
    }
}