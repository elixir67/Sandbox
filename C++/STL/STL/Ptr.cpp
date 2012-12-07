#include "stdafx.h"
#include <memory>
using namespace std;

void SharedPtr_WeakPtr()
{
    shared_ptr<int> p1(new int(5));
    auto sp = make_shared<int>(5);
    auto sp2 = sp;
    auto sp3 = sp;

    weak_ptr<int> wp(sp);
    auto wp2 = wp, wp3 = wp, wp4 = wp;

    sp.reset();
    wp.reset();
}
