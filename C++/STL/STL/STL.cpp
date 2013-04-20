// STL.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <memory>

void SharedPtr_WeakPtr();
void LambdaExamples();
void RValueTest();
void RegexTest();

struct foo
{
	foo() {std::cout << "foo constructing" << std::endl;}
	foo(const foo & rhs) {std::cout << "foo copy constructing" << std::endl;}
	foo(const foo && rhs) {std::cout << "foo move constructing" << std::endl;}
};

struct CFoo
{
	foo m_foo;
	CFoo(){std::cout << "CFoo constructing" << std::endl;}
	CFoo(const CFoo & rhs) : m_foo(rhs.m_foo){std::cout << "CFoo copy constructing" << std::endl;}
	CFoo(const CFoo && rhs) : m_foo(std::move(rhs.m_foo)) {std::cout << "CFoo move constructing" << std::endl;}
};

void MoveTest()
{
	CFoo a;
	CFoo b(a);
	CFoo c(std::move(a));
}

struct A
{
	A(int & n)  {std::cout << "lvalue overloaded, n=" << n << std::endl;}
	A(int && n) {std::cout << "rvalue overloaded, n=" << n << std::endl;}
};

template<typename T, typename I>
std::unique_ptr<T> make_unique(I&& i)
{
	//return std::unique_ptr<T> (new T(i));
	return std::unique_ptr<T> (new T(std::forward<I>(i)));
}

void ForwardTest()
{
	//A a(5);
	//int j = 3;
	//A b(j);
	std::unique_ptr<A> pa = make_unique<A>(1);	// rvalue
	int i = 2;
	std::unique_ptr<A> pb = make_unique<A>(i);	// lvalue
}

int _tmain(int argc, _TCHAR* argv[])
{
	ForwardTest();
	return 0;
}

