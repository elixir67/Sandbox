#include "stdafx.h"
//#define BOOST_ALL_NO_LIB 
//
//#define BOOST_DATE_TIME_SOURCE
//#define BOOST_THREAD_NO_LIB
//extern "C" void tss_cleanup_implemented(void) {}
//#include <libs/thread/src/win32/thread.cpp>
//#include <libs/thread/src/win32/tss_dll.cpp>
//#include <libs/thread/src/win32/tss_pe.cpp>
#include "stdafx.h"
#include <boost/thread.hpp>
#include <boost/atomic.hpp>
#include <boost/ref.hpp>

void testThreadSleep()
{
	boost::this_thread::sleep(boost::posix_time::seconds(2));
}

boost::mutex io_mu;

void printing(boost::atomic_int & x, const string &str)
{
	for(int i = 0; i < 5; ++i)
	{
		boost::mutex::scoped_lock lock(io_mu);
		cout << str << ++x << endl;
	}
}

void testCreateThreadWithParameter()
{
	boost::atomic_int x;

	boost::thread(printing, boost::ref(x), "hello");
	boost::thread(printing, boost::ref(x), "boost");
}

void helloworld()
{
	cout << "hello world" << endl;
}

void testJoin()
{
	boost::thread thrd(&helloworld);
	thrd.join();
}

void testCh12()
{
	testCreateThreadWithParameter();
	testThreadSleep();
	testJoin();
}