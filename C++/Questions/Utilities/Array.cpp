#include "stdafx.h"
#include "Array.h"
#include <exception>
#include <stdlib.h>

int RandomInRange(int min, int max)
{
    int random = rand() % (max - min + 1) + min;
    return random;
}

void Swap(int & a, int & b)
{
    int temp = a;
    a = b;
    b = temp;
}

int Partition(int data[], int length, int start, int end)
{
    if(!data || length <= 0 || start < 0 || end >=length)
        throw new std::exception("Invalid parameters");

    int index = RandomInRange(start, end);
    Swap(data[index] , data[end]);

    int small = start - 1;
    for(index = start; index < end; ++index)
    {
        if(data[index] < data[end])
        {
            ++small;
            if(index != small)
                Swap(data[index], data[small]);
        }
    }

    ++small;
    Swap(data[small], data[end]);

    return small;
}