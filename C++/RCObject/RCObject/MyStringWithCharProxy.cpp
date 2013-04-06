#include "stdafx.h"
#include "MyStringWithCharProxy.h"


#include "stdafx.h"
#include "MyString.h"
#include <string.h>

// Error	1	error C4996: 'strcpy': This function or variable may be unsafe. Consider using strcpy_s instead. To disable deprecation, use _CRT_SECURE_NO_WARNINGS. See online help for details.	c:\users\dan\documents\github\sandbox\c++\rcobject\rcobject\main.cpp	143	1	RCObject
#define _CRT_SECURE_NO_WARNINGS 1

MyStringWithCharProxy::CharProxy::CharProxy(MyStringWithCharProxy & str, int index)
	: m_str(str)
	, m_index(index)
{}

MyStringWithCharProxy::CharProxy & MyStringWithCharProxy::CharProxy::operator=(const MyStringWithCharProxy::CharProxy & rhs)
{
	if(m_str.m_value->IsShareable())
	{
		m_str.m_value = new MyStringValue(m_str.m_value->data);
	}
	// now assignment
	m_str.m_value->data[m_index] = rhs.m_str.m_value->data[m_index];
	return *this;
}

MyStringWithCharProxy::CharProxy & MyStringWithCharProxy::CharProxy::operator=(char c)
{
	if(m_str.m_value->IsShareable())
	{
		m_str.m_value = new MyStringValue(m_str.m_value->data);
	}
	// now assignment
	m_str.m_value->data[m_index] = c;
	return *this;
}


MyStringWithCharProxy::CharProxy::operator char() const
{
	return m_str.m_value->data[m_index];
}

void MyStringWithCharProxy::MyStringValue::init(const char * value)
{
	data = new char[strlen(value) + 1];
	// strcpy(data, value);
	strncpy_s(data, strlen(value) + 1, value, strlen(value) + 1);
}

MyStringWithCharProxy::MyStringValue::MyStringValue(const char * value)
{
	init(value);
}

MyStringWithCharProxy::MyStringValue::MyStringValue(const MyStringValue & rhs)
{
	init(rhs.data);
}

MyStringWithCharProxy::MyStringValue::~MyStringValue()
{
	delete[] data;
}

MyStringWithCharProxy::MyStringWithCharProxy(const char * value)
	: m_value(new MyStringValue(value))
{
}

const MyStringWithCharProxy::CharProxy MyStringWithCharProxy::operator[] (int index) const
{
	return CharProxy(const_cast<MyStringWithCharProxy&>(*this), index);
}

MyStringWithCharProxy::CharProxy MyStringWithCharProxy::operator[](int index)
{
	return CharProxy(*this, index);
}
