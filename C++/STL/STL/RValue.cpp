#include "stdafx.h"
#include <vector>
#include <string>
#include <iostream>
#include <set>
using namespace std;


void RValueTest()
{
    //vector<string> v;
    //string s("meow");
    //v.push_back(s);
    //v.push_back(move(s));
    //v.push_back("Dan");
    //cout << "Meow" << endl;

    set<string> meow;
    const string c("other stuff");
    string lv("stuff");

    meow.insert(c);
    meow.insert(lv);
}
