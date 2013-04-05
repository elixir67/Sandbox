#pragma once
class RCObject
{
public:
	void AddReference();
	void RemoveReference();
	void MarkUnshareable() {m_shareable = false;}
	bool IsShared() const {return m_refCount > 1;}
	bool IsShareable() const {return m_shareable; }
protected:
	RCObject();
	RCObject(const RCObject & rhs)
		: m_refCount(0)
		, m_shareable(true) 
	{}
	RCObject & operator = (const RCObject & rhs);
	virtual ~RCObject() = 0;
private:
	int m_refCount;
	bool m_shareable;
};

