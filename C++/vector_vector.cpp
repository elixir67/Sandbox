#include <vector>
#include <string>
#include <iostream>
#include <iterator>

template<class T>
void output(const std::vector<T> & vec)
{
    std::copy(vec.cbegin(), vec.cend(), std::ostream_iterator<T>(std::cout, " "));
    std::cout << std::endl;
}

int main()
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