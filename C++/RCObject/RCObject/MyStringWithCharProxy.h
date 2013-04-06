#pragma once
#include "RCPtr.h"
#include "RCObject.h"
class MyStringWithCharProxy
{
public:
	MyStringWithCharProxy(const char * value);

	class CharProxy
	{
		public:
			CharProxy(MyStringWithCharProxy & str, int index);
			CharProxy& operator = (const CharProxy & rhs);
			CharProxy& operator = (char c);
			operator char() const;
		private:
			MyStringWithCharProxy & m_str;
			int m_index;
	};
public:
	CharProxy operator[](int index);
	const CharProxy operator[](int index) const;
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

