// 54_8Queens.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>
#include <math.h>
#include <iostream>
using namespace std;

bool isConflict(const vector<int> & states, int nextX)
{
	int nextY = states.size();
	for(auto i = 0; i < nextY; ++i)
	{
		if(abs(nextX - states[i]) == nextY - i || nextX - states[i] == 0)
			return true;
	}
	return false;
}

void queens(int num, vector<int> & states)
{
	for(auto i = 0; i < num; ++i)
	{
		states.clear();
		states.push_back(i);
		int pos = 0;
		while(states.size() != num)
		{
			if(isConflict(states, pos))
			{
				if(pos == num - 1)
				{
					states.pop_back();
					break;
				}
				++pos;
				continue;
			}
			else
			{
				states.push_back(pos);
				pos = 0;
			}
		}
		if(states.size() == num)
			return;
	}
}

void prettyprint(int num, const vector<int> & result)
{
	for(size_t i = 0; i < result.size(); ++i)
	{
		for(auto j = 0; j < result[i]; ++j)
			cout << ".";
		cout << "X";
		for(auto j = 0; j < num - result[i] -1; ++j)
			cout << ".";
		cout << endl;
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	const int n = 8;
	vector<int> states;
	queens(n, states);
	prettyprint(n, states);
	return 0;
}

