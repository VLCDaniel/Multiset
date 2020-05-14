#include <iostream>
#include "Multiset.h"

int main()
{
    Multiset<int> p;
    p.add(13);
    p.add(10);
    p.add(15);
    p.add(5);
    p.add(11);
    p.add(16);
    p.add(4);
    p.add(6);
    cout << p;
    return 0;
}