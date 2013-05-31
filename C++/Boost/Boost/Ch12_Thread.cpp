#include "stdafx.h"
//#define BOOST_ALL_NO_LIB 
//
//#define BOOST_DATE_TIME_SOURCE
//#define BOOST_THREAD_NO_LIB
//extern "C" void tss_cleanup_implemented(void) {}
//#include <libs/thread/src/win32/thread.cpp>
//#include <libs/thread/src/win32/tss_dll.cpp>
//#include <libs/thread/src/win32/tss_pe.cpp>

#include <boost/thread.hpp>

void testThread()
{
	boost::this_thread::sleep(boost::posix_time::seconds(2));
}

void testCh12()
{
	testThread();
}