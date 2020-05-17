#include <iostream>
#include <assert.h>
#include "Multiset.h"

int main()
{
    Multiset<int> p, q;

    // Left Right Rotation (pentru fiul stang)
    p.add(30);
    assert(p.exists(30));
    p.add(20);
    assert(p.exists(20));
    p.add(40);
    assert(p.exists(40));
    p.add(10);
    assert(p.exists(10));
    p.add(15);
    assert(p.exists(15));
    cout << p;

    // Right Right Rotation (pentru fiul drept)
    q.add(40);
    assert(q.exists(40));
    q.add(50);
    assert(q.exists(50));
    q.add(60);
    assert(q.exists(60));
    q.add(70);
    assert(q.exists(70));
    cout << q;

    // Constructorul de copiere
    Multiset<int> k(q);
    assert(k.exists(40));
    assert(q.exists(50));
    assert(q.exists(60));
    assert(q.exists(70));
    cout << k;

    // Metoda pentru existenta unui nod
    k.add(100);
    assert(k.exists(100));
    cout << k;

    // Metoda care intoarce numarul de aparitii
    q.add(100);
    q.add(100);
    q.add(100);
    assert(q.aparitions(100));
    cout << q.aparitions(100) << '\n';

    return 0;
}