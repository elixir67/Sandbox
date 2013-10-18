#include "stdafx.h"
#include <vector>
#include <string>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <ctime>
#include <numeric>  // for iota
using namespace std;

template<class T>
void output(const std::vector<T> & vec)
{
    std::copy(vec.cbegin(), vec.cend(), std::ostream_iterator<T>(std::cout, " "));
    std::cout << std::endl;
}

int TestVectorInit()
{
    // VC10 doesn't support initialize list
    // std::vector<std::string> words1 {"the", "frought", "is", "also", "cursed"};
    std::vector<std::string> words2(5, "NO");
    output(words2);
    
    std::vector<std::string> words3(words2.cbegin(), words2.cend());
    output(words3);
    
    std::vector<std::string> words4(words2);
    output(words4);
    return 0;
}

void TestVectorFillWithRandomNum()
{
    srand(static_cast<unsigned int>(time(0))); //seed random number function
    const int size = 20;
    vector<int> v(size, 0);
    generate(v.begin(), v.end(), [](){return std::rand()%100;});
    output(v);

    vector<int> v2;
    //v2.reserve(size); //crash
    v2.resize(size);
    generate_n(v2.begin(), size, [](){return std::rand()%50;});
    output(v2);
}

void TestVectorFillWithRange()
{
    //c++11 std::iota
    //http://stackoverflow.com/questions/13152252/is-there-a-compact-equivalent-to-python-range-in-c-stl
    //http://stackoverflow.com/questions/17694579/use-stdfill-to-populate-vector-with-increasing-numbers
    vector<int> v(10);
    int startNum = 5;
    iota(v.begin(), v.end(), startNum);
    output(v);

    std::random_shuffle(v.begin(), v.end());
    output(v);

    for(auto n: v)
        cout << n << ' ';
    cout << endl;
}

void VectorTest()
{
    //TestVectorFillWithRandomNum();
    TestVectorFillWithRange();
}