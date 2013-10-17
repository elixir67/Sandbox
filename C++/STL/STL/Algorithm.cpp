#include "stdafx.h" 
#include <vector>
#include <numeric>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <functional>
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
}

void EraseTest()
{

}

