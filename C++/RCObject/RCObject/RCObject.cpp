#include "stdafx.h"
#include "RCObject.h"


RCObject::RCObject()
	: m_refCount(0)
	, m_shareable(true)
{}

RCObject& RCObject::operator=(const RCObject & rhs)
{
	return * this;
}

void RCObject::AddReference()
{
	++m_refCount;
}

void RCObject::RemoveReference()
{
	if( --m_refCount == 0)
		delete this;
}

RCObject::~RCObject() {}