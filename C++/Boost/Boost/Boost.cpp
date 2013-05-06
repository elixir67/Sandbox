// Boost.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <boost/timer.hpp>
using namespace boost;
int _tmain(int argc, _TCHAR* argv[])
{
	timer t;
	cout << "max timespan:" << t.elapsed_max()/3600 << "h" << endl;
	cout << "min timespan:" << t.elapsed_min() << "s" << endl;

	cout << "now time elapsed:" << t.elapsed() << "s" << endl;
	return 0;
}

