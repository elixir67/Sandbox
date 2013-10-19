#pragma once
#include <vector>
#include <algorithm>

template<class T>
void output(const std::vector<T> & vec)
{
    std::copy(vec.cbegin(), vec.cend(), std::ostream_iterator<T>(std::cout, " "));
    std::cout << std::endl;
}

template<typename CONTAINER, typename PREDICATE>
inline void delete_from_if(CONTAINER& cont, const PREDICATE & pred)
{
    auto&& erase_begin = std::remove_if(std::begin(cont), std::end(cont), pred);
    cont.erase(erase_begin, std::end(cont));
}
