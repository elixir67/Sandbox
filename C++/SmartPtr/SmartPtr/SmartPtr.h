template<typename T>
class SmartPtr
{
public:
	SmartPtr(T* realPtr = 0) : pointee(realPtr){}
	~SmartPtr() {delete pointee;}

	// No const for copy ctor and assignment
	SmartPtr(SmartPtr & rhs);
	SmartPtr& operator=(SmartPtr & rhs);

	T& operator*() const {return *pointee;}
	T* operator->() const {return pointee;}
private:
	T* pointee;

};

template<typename T>
SmartPtr<T>::SmartPtr(SmartPtr<T> & rhs)
{
	pointee = rhs.pointee;
	rhs.pointee = 0;
}

template<typename T>
SmartPtr<T>& SmartPtr<T>::operator=(SmartPtr<T> & rhs)
{
	if(rhs.pointee = pointee)
		return *this;
	delete pointee;
	pointee = rhs.pointee;
	rhs.pointee = 0;
	return *this;
}