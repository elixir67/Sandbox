#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <list>
#include <iterator>
#include <algorithm>
using namespace std;
void IfstreamTest()
{
    ifstream dataFile("ints.dat");
    //list<int> data(istream_iterator<int>(dataFile),istream_iterator<int>());  // compile error
    auto begin = istream_iterator<int>(dataFile);
    auto end = istream_iterator<int>();
    list<int> data(begin, end);
    for_each(data.begin(), data.end(), [](int i){cout << i << endl;});

    cout << "Test2" << endl;
    dataFile.seekg(0);//rewind
    list<int> data2((istream_iterator<int>(dataFile)),istream_iterator<int>());
    // output nothing since data2 is empty which is different with Itemy6 in Effective STL
    // Be alert for C++'s most vexing parse
    for_each(data2.begin(), data2.end(), [](int i){cout << i << endl;});
}