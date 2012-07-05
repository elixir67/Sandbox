#include <functional>
#include <iostream>

void print_num(int i)
{
    std::cout << i <<'\n';
}

struct Foo {
    Foo(int num) 
    : _num(num){}
    
    void print_num(){
        std::cout << _num << std::endl;
    }
    
    void print_add(int i){
        std::cout<< _num + i << std::endl;
    }
    int _num;
};

int main()
{
    std::function<void(int)> f1 = print_num;
    f1(1);

    std::function<void()> f2 = std::bind(print_num, 2);
    f2();
    
    std::function<void()> f3 = [](){print_num(3);};
    f3();
    
    // why it cannot use const Foo& in VC10
    std::function<void(Foo&)> f4 = &Foo::print_num;
    Foo foo(4);
    f4(foo);
    
    // why it cannot use const Foo& in VC10
    std::function<void(Foo&, int)> f5 = &Foo::print_add;
    f5(foo, 1);
}