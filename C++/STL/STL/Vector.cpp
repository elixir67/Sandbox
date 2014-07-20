#include "stdafx.h"
#include <vector>
#include <string>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <ctime>
#include <numeric>  // for iota
#include "Utility.h"
using namespace std;


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

void TestEmplace()
{
    //Have a look at these innocent looking pieces of code:.
    // 
    //vec.emplace_back(vec.front()); // potential crash!.
    // 
    //vec.emplace_back(vec.back());  // potential crash!.
    // 
    //vec.emplace_back(vec[i]);      // potential crash!.
    // 
    //All can lead to crashes since vec.front(), vec.back(), and vec[i] return a reference to the corresponding element of the vector which is just a “hidden pointer” to it; if the vector has not enough capacity to append a new element at the end of the allocated memory it reallocates a larger chunk of memory somewhere else and moves/copies over all existing objects of it; this invalidates the reference/pointer to the referenced element making it a dangling pointer; and then the new element is constructed via the copy-ctor using this dangling reference pointing into an invalid memory location, which might either use random values or crash the application!.
    // 
    //In order to fix this you need to call push_back() instead since that method is required by the standard to work even for this special case:.
    // 
    //vec.push_back(vec.front());

    vector<string> v;
    v.emplace_back("Hello");
    for(size_t i = 0; i < 100; ++i)
    {
        //v.emplace_back(v.front());  // crash;
        v.push_back(v.front());
    }
}

void VectorTest()
{
    //TestVectorFillWithRandomNum();
    //TestVectorFillWithRange();
    TestEmplace();
}