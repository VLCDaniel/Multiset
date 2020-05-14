#include <iostream>
#include "Multiset.h"

int main()
{
    Multiset<int> p;
    p.add(5);
    p.add(6);
    p.add(7);
    p.add(1);
    p.add(0);
    p.add(4);
    p.add(-1);
    cout << p;
    return 0;
}