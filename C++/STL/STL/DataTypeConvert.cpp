#include "stdafx.h"
#include <string>   // for stoi
#include <cstdlib>  // for atoi
#include <sstream> // for stringstream
using namespace std;

void NumToString()
{
    int i = 10;

    {
        //char * intStr = itoa(i);//? cannot compile
        //string str = string(intStr);
    }


    {
        stringstream ss;
        ss << i;
        string str = ss.str();
    }

    {
        // C++11
        string str = to_string(i);
    }
}

void StringToNum()
{
    string s = "10";

    {
        // deprecated
        int i = atoi(s.c_str()); 
    }

    {
        // C++11
        int i = stoi(s);
    }
}

void ConvertTest()
{
    NumToString();
    StringToNum();
}