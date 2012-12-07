// LValue/RValue is meaningful to expression not object
#include "stdafx.h"
#include <vector>
#include <string>
#include <iostream>
#include <set>
using namespace std;

char * fun() {return "Hello";}

void RValueTest()
{
    //vector<string> v;
    //string s("meow");
    //v.push_back(s);
    //v.push_back(move(s));
    //v.push_back("Dan");
    //cout << "Meow" << endl;

    //set<string> meow;
    //const string c("other stuff");
    //string lv("stuff");

    //meow.insert(c);
    //meow.insert(lv);

    int n, *p;
    p= &n;
    // &n = p;

    // ++nCount is lvalue
    int nCount = 0;
    ++nCount;
    ++nCount = 5;

    char * q = fun();
    // Exception is throwed here as fun() returns an temporary memory
    // q[0] = 'c';

    // nCount++is an Rvalue, we can not do the below operation
    // nCount++ = 5; //Error
}
