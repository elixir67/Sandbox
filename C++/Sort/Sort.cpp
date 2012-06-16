// Sort.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

void swap(int & a, int & b)
{
	int temp = a;
	a = b;
	b = temp;
}

void output(int array[], int left, int right)
{
	for(int i = left; i <= right; i++)
	{
		std::cout << array[i] << " ";
	}
	std::cout << std::endl;
}

int Partition(int array[], int left, int right)
{
	if(NULL == array || left < 0 || left >= right)
		throw new std::exception("Invalid Parameters");

	int pivot = left;
    if(left<right)
    {
        //p <- Get a number from array
		int & p = array[left];
        //Put elements <= p to the left side
        //Put elements >= p to the right side
		for(int i = left + 1; i <= right; ++i)
		{
			int & element = array[i];
			if(element < p)
			{
				++pivot;
				swap(element, array[pivot]);
			}
		}
        //Put p in the middle slot which index is pivot
		swap(p, array[pivot]);
    }

	//output(array, left, right);
	return pivot;
}

void QuickSort(int array[], int left, int right)
{
	if(left < right)
	{
		int pivot = Partition(array, left, right);
        //Recursive quicksort the left parts and right parts
		QuickSort(array, left, pivot - 1);
		QuickSort(array, pivot + 1, right);
	}
}


int _tmain(int argc, _TCHAR* argv[])
{
	int array[] =  {3,4,7,1,6,0,2,8,5,9};
	output(array, 0, 9);
	QuickSort(array, 0, 9);
	output(array, 0, 9);

	return 0;
}

