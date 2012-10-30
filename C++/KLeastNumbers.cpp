// KLeastNumbers.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
#include <vector>
#include <iostream>
#include <algorithm>
#include <set>
using namespace std;

// Solution 1: Use the STL heap to do it.
void KLeastNumbers(int data[], int length, int k, vector<int>& outNumbers)
{
    if(!data || length < 0 || length < k)
        throw exception("Invalid Parameters!");

    vector<int> bucket;
    int index = 0;
    // bucket is not full, insert the number directly
    while((int)bucket.size() < k)
    {
        bucket.push_back(data[index]);
        ++index;
    }
    // bucket is full
    make_heap(bucket.begin(), bucket.end());
    while(index < length)
    {
        // compare every left number in array with the largest number in buckets
        if(data[index] < bucket.front())
        {
            // replace the largest number in bucket with the number
            pop_heap(bucket.begin(), bucket.end());
            bucket.pop_back();
            bucket.push_back(data[index]);

            push_heap(bucket.begin(), bucket.end());
        }
        ++index;
    }
    sort_heap(bucket.begin(), bucket.end());
    outNumbers = bucket;
}

// Solution 2: Use the multiset to do it
typedef multiset<int, greater<int> > intSet;
typedef multiset<int, greater<int> >::iterator setIterator;

void KLeastNumbers_2(int data[], int length, int k, vector<int>& outNumbers)
{
    if(!data || length < 0 || length < k)
        throw new exception("Invalid parameters!");

    intSet bucket;
    for(int i = 0; i < length; ++i)
    {
        if((int)bucket.size() < k)
            bucket.insert(data[i]);
        else
        {
            setIterator itGreatest = bucket.begin();
            if(data[i] < *itGreatest)
            {
                bucket.erase(itGreatest);
                bucket.insert(data[i]);
            }
        }
    }
    outNumbers.resize(bucket.size());
    copy(bucket.begin(), bucket.end(), outNumbers.begin());
}


void Test(char * testName, int data[], int length, int expected[], int expectedLength)
{
    if(testName)
        cout << testName << " begins!" << "\t";
    if(!data || !expected || length <=0 || length < expectedLength)
    {
        cout << "Invalid parameters! We don't expect any result!" << endl;
        return;
    }

    vector<int> outNumbers;
    KLeastNumbers_2(data, length, expectedLength, outNumbers);
    bool bPass = true;
    if(outNumbers.size() != expectedLength)
       bPass = false ;
    else
    {
        for(int i = 0; i < expectedLength; ++i)
        {
            if(expected[i] != outNumbers[i])
                bPass = false;
        }
    }
    if(bPass)
        cout << "Test Passed!" << endl;
    else
        cout << "Test Failed!" << endl;

}

// k is less than the data's length;
void Test1()
{
    int data[] = {4, 5, 1, 6, 2, 7, 3, 8};
    int expected[] = {1, 2, 3, 4};
    Test("Test1",data, sizeof(data)/sizeof(int), expected, sizeof(expected)/sizeof(int));
}

// k is equal to the data's length
void Test2()
{
    int data[] = {4, 5, 1, 6, 2, 7, 3, 8};
    int expected[] = {1, 2, 3, 4, 5, 6,7, 8};
    Test("Test2",data, sizeof(data)/sizeof(int), expected, sizeof(expected)/sizeof(int));
}

// k is larger than the data's length
void Test3()
{
    int data[] = {4, 5, 1, 6, 2, 7, 3, 8};
    int* expected = NULL;
    Test("Test3",data, sizeof(data)/sizeof(int), expected, 10);
}

// k is equal to 1
void Test4()
{
    int data[] = {4, 5, 1, 6, 2, 7, 3, 8};
    int expected[] = {1};
    Test("Test4",data, sizeof(data)/sizeof(int), expected, 1);
}

// k is equal to 0
void Test5()
{
    int data[] = {4, 5, 1, 6, 2, 7, 3, 8};
    int* expected = NULL;
    Test("Test5",data, sizeof(data)/sizeof(int), expected, 0);
}

// array has same number
void Test6()
{
    int data[] = {4, 5, 1, 6, 2, 7, 2, 8};
    int expected[] = {1, 2};
    Test("Test6", data, sizeof(data) / sizeof(int), expected, sizeof(expected) / sizeof(int));
}

// array is null
void Test7()
{
    int * expected = NULL;
    Test("Test7", NULL, NULL / sizeof(int), expected, sizeof(expected) / sizeof(int));
}

int compare(int a, int b)
{
    return a < b;
}

int main(int argc, char* argv[])
{
    //int data[] = {4, 5, 1, 6, 2, 7, 3, 8};
    //vector<int> v(data, data + sizeof(data)/sizeof(int));
    //make_heap(v.begin(), v.end(), compare);

    //for(size_t i = 0; i < v.size(); ++i)
    //    cout << v[i] << " ";
    //cout << endl;

    //sort_heap(v.begin(), v.end(), compare);

    //for(size_t i = 0; i < v.size(); ++i)
    //    cout << v[i] << " ";
    //cout << endl;
    Test1();
    Test2();
    Test3();
    Test4();
    Test5();
    Test6();
    Test7();

	return 0;
}

