#include "stdafx.h"
#include <boost/timer.hpp>
#include <boost/progress.hpp>

void testTimer()
{
	boost::timer t;
	cout << "max timespan:" << t.elapsed_max()/3600 << "h" << endl;
	cout << "min timespan:" << t.elapsed_min() << "s" << endl;
	cout << "now time elapsed:" << t.elapsed() << "s" << endl;
}

void testProgressTimer()
{
	boost::progress_timer t; 
	//testTimer();

}

void testCh02()
{
	testTimer();
	testProgressTimer();
}