#include <vector>
#include <set>
#include <iostream>
using namespace std;

int main(int argc, char* argv[])
{
    int data[] = {4, 5, 1, 6, 2, 7, 3, 8};
    vector<int> v(data, data + sizeof(data)/sizeof(int));
    int * array = &v[0];
    for(size_t i = 0; i < v.size(); ++i)
        cout << array[i] << " ";
    cout << endl;

    multiset<int> s(data, data + sizeof(data)/sizeof(int));
    //make_heap(v.begin(), v.end(), compare);
    int array2[100];
    copy(s.begin(), s.end(), array2);
    for(size_t i = 0; i < v.size(); ++i)
        cout << array2[i] << " ";
    cout << endl;

	return 0;
}

