#pragma once
#include "RCPtr.h"
#include "RCObject.h"

class MyString
{
public:
	MyString(const char * value);
	char & operator[](int index);
	const char & operator[](int index) const;
private:
	struct MyStringValue : public RCObject
	{
		char * data;
		MyStringValue(const char * value);
		MyStringValue(const MyStringValue & rhs);
		void init(const char * value);
		virtual ~MyStringValue();
	};

	RCPtr<MyStringValue> m_value;
};

