#include <iostream>

template <class T>
    // T must have default ctor and copy assignment
class Stack
{
public:
    Stack();
    ~Stack();
    Stack(const Stack&);
    Stack& operator=(const Stack&);

    unsigned Count();   // returns # of T's in the stack
    void     Push(const T&);
    T        Pop();     // if empty, returns default-
                        // constructed T

private:
    T*       v_;        // pointer to a memory area big
                        //  enough for 'vsize_' T objects
    unsigned vsize_;    // the size of the 'v_' area
    unsigned vused_;    // the number of T's actually
                        //  used in the 'v_' area
};

int main()
{
    std::cout << "This is a native C++ program." << std::endl;
    auto maton = 112; // maton is type int
    auto pt = &maton; // pt is type int *
    std::cout << *pt << std::endl;
    // double fm(double, int);
    // auto pf = fm; // pf is type double (*)(double,int)
    return 0;
}