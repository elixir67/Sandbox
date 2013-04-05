#include "stdafx.h"
#include "MyString.h"
#include <string.h>

// Error	1	error C4996: 'strcpy': This function or variable may be unsafe. Consider using strcpy_s instead. To disable deprecation, use _CRT_SECURE_NO_WARNINGS. See online help for details.	c:\users\dan\documents\github\sandbox\c++\rcobject\rcobject\main.cpp	143	1	RCObject
#define _CRT_SECURE_NO_WARNINGS 1

void MyString::MyStringValue::init(const char * value)
{
	data = new char[strlen(value) + 1];
	// strcpy(data, value);
	strncpy_s(data, strlen(value) + 1, value, strlen(value) + 1);
}

MyString::MyStringValue::MyStringValue(const char * value)
{
	init(value);
}

MyString::MyStringValue::MyStringValue(const MyStringValue & rhs)
{
	init(rhs.data);
}

MyString::MyStringValue::~MyStringValue()
{
	delete[] data;
}

MyString::MyString(const char * value)
	: m_value(new MyStringValue(value))
{
}

const char & MyString::operator[] (int index) const
{
	return m_value->data[index];
}

char & MyString::operator[](int index)
{
	if(m_value->IsShareable())
	{
		m_value = new MyStringValue(m_value->data);
		m_value->MarkUnshareable();
	}
	return m_value->data[index];
}