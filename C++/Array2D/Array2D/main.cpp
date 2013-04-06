// main.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Array2D.h"
#include <iostream>
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	const int ROW = 2;
	const int COLUMN = 3;
	Array2D<int> data(ROW, COLUMN);
	for(int i = 0; i < ROW; ++i)
		for(int j = 0; j < COLUMN; ++j)
			data[i][j] = i*COLUMN + j;

	for(int i = 0; i < ROW; ++i)
		for(int j = 0; j < COLUMN; ++j)
			cout << data[i][j] << endl;

	return 0;
}

