#include "stdafx.h"
#include <algorithm>
#include <functional>
#include <locale> 
#include <cctype> // for std::isspace

#include <iostream>

static inline std::string & ltrim(std::string & s)
{
    // Method 1 from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
    //s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
    s.erase(s.begin(), std::find_if_not(s.begin(), s.end(), [](int c){return std::isspace(c);}));
    return s;
}

static inline std::string & rtrim(std::string & s)
{
    // Method 1
    //s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
    
    s.erase(std::find_if_not(s.rbegin(), s.rend(), [](int c){return std::isspace(c);}).base(), s.end());
    return s;
}

static inline std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}


#define ALX_APP_NAME_SUFFIX  "2014 R4"
void SplitTest()
{
    
}

void StringTest()
{
    std::string s = " \tHello  ";
    trim(s);

    std::cout << s << std::endl;
}