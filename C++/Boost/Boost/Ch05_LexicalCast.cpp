#include "stdafx.h"
#include <boost/lexical_cast.hpp>
#include <boost/format.hpp>
#include <string>
void testLexicalCastTest()
{
	std::wstring jobId = L"9";
	int a = boost::lexical_cast<int>(jobId);
	cout << a << endl;
}

void testFormat()
{
	int jobId = 9;
	const char * s = ".job";
	boost::format fmt("%d%s");
	fmt %jobId %s;
	std::string filename = fmt.str();
	cout << filename << endl;
}

void testCh05()
{
	testLexicalCastTest();
	testFormat();
}