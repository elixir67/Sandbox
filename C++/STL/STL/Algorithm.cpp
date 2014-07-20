#include "stdafx.h" 
#include <vector>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <functional>
#include <string>
#include <numeric>  // for iota, partial_sum
#include "Utility.h"
using namespace std;

 void AllOfTest()
 {
     std::vector<int> v(10, 2);
     std::partial_sum(v.cbegin(), v.cend(), v.begin());
     std::cout << "Among the numbers: ";
     std::copy(v.cbegin(), v.cend(), std::ostream_iterator<int>(std::cout, " "));
     std::cout << '\n';
 
     if (std::all_of(v.cbegin(), v.cend(), [](int i){ return i % 2 == 0; })) {
         std::cout << "All numbers are even\n";
     }
     if (std::none_of(v.cbegin(), v.cend(), std::bind(std::modulus<int>(), 
                                                      std::placeholders::_1, 2))) {
         std::cout << "None of them are odd\n";
     }
     struct DivisibleBy
     {
         const int d;
         DivisibleBy(int n) : d(n) {}
         bool operator()(int n) const { return n % d == 0; }
     };
 
     if (std::any_of(v.cbegin(), v.cend(), DivisibleBy(7))) {
         std::cout << "At least one number is divisible by 7\n";
     }
 }

int MODTest()
{
    auto f = std::modulus<int>();
    std::cout << f(10, 2) << std::endl;
    return 0;
}

void ForEachTest()
{
   char s[]="Hello World!";
   int Uppercase = 0; //modified by the lambda
   for_each(s, s+sizeof(s), [&Uppercase] (char c) {
    if (isupper(c))
     Uppercase++;
    });
    cout<< Uppercase<<" uppercase letters in: "<< s<<endl;
}
void MinMaxTest()
{
    vector<int> v(20);
    iota(std::begin(v), std::end(v), 0);
    random_shuffle(std::begin(v), std::end(v));

    const int max_value = *max_element(v.begin(), v.end());
    cout << "MAX:" << max_value << endl;
    
    const int min_value =  *min_element(v.begin(), v.end());
    cout << "MIN:" << min_value << endl;

    auto min_max = minmax_element(v.begin(), v.end());
    cout << "MIN:" << *min_max.first << endl;
    cout << "MAX:" << *min_max.second << endl;
}

void EraseTest()
{
    vector<string> data(20);
    // Given a set of strings (stored in a std::vector<std::string>) containing the strings “0”, “1”, “2”, …, “999”, …, you want to remove all strings from the vector which contain the digit ‘4’.
    int i = 0;
    generate(data.begin(), data.end(), [&i](){return std::to_string(i++);});

    auto erase_begin = remove_if(data.begin(), data.end(), [](const string & s){return (s.find('4') != s.npos);});
    data.erase(erase_begin, data.end());

    for(auto n: data)
        cout << n << " ";
    cout << endl;

    // test with out utility function
    vector<int> values(20);
    iota(values.begin(), values.end(), 0);

    auto divisibleBy7 = [](int i){return i%7 == 0;};
    delete_from_if(values, divisibleBy7);

    output(values);
}

void SwapTest1()
{
    //http://baike.baidu.com/view/674171.htm?fromtitle=%E5%BC%82%E6%88%96%E8%BF%90%E7%AE%97&fromid=720417&type=syn
    int a = 3;  //11
    int b = 2;  //10
    cout << "before a,b:\t" << a << "," << b << endl;
    a^=b; // =>  a = a^b 
    b^=a; // =>  b = b^(a^b) = a
    a^=b; //  =>  a = a^b^a = b

    cout << "after a,b:\t" << a << "," << b << endl;
}

void SwapTest2()
{
    int a = 3;  //11
    int b = 2;  //10
    cout << "before a,b:\t" << a << "," << b << endl;
    
    a^=b^=a^=b;

    cout << "after a,b:\t" << a << "," << b << endl;
}

void SwapTest3()
{
    int a = 3;  //11
    int b = 2;  //10
    cout << "before a,b:\t" << a << "," << b << endl;
    
    std::swap(a, b);

    cout << "after a,b:\t" << a << "," << b << endl;
}

void SwapTest4()
{
    // http://blog.csdn.net/lpt19832003/article/details/5334688
    int a = 3;  //11
    int b = 2;  //10
    cout << "before a,b:\t" << a << "," << b << endl;
    
    a += b;
    b = a - b;
    a = a - b;

    cout << "after a,b:\t" << a << "," << b << endl;
}

void AlgoTest()
{
    //EraseTest();
    //MinMaxTest();

    SwapTest4();
}


