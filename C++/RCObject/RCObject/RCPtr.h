#pragma once
template <typename T>
class RCPtr
{
public:
	RCPtr(T * realPtr = 0);
	RCPtr(const RCPtr & rhs);
	~RCPtr();
	RCPtr & operator = (const RCPtr & rhs);
	T* operator ->() const;
	T& operator *() const;
private:
	T* m_pointee;
	void init();
};

template <typename T>
RCPtr<T>::RCPtr(T * realPtr)
	:m_pointee(realPtr)
{
	init();
}

template <typename T>
RCPtr<T>::RCPtr(const RCPtr & rhs)
	:m_pointee(rhs.m_pointee)
{
	init();
}

template <typename T>
void RCPtr<T>::init()
{
	if(!m_pointee)
		return;

	if(!m_pointee->IsShareable())
	{
		m_pointee = new T(*m_pointee);
	}

	m_pointee->AddReference();
}

template <typename T>
RCPtr<T>::~RCPtr()
{
	m_pointee->RemoveReference();
}

template <typename T>
T* RCPtr<T>::operator->() const
{
	return m_pointee;
}

template <typename T>
T& RCPtr<T>::operator*() const
{
	return *m_pointee;
}

template <typename T>
RCPtr<T>& RCPtr<T>::operator=(const RCPtr<T> & rhs)
{
	if(m_pointee == rhs.m_pointee)
		return *this;

	if(m_pointee)
		m_pointee->RemoveReference();
	m_pointee = rhs.m_pointee;
	init();

	return *this;
}


