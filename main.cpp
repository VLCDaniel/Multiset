#include <iostream>
#include <assert.h>
#include "Multiset.h"

int main()
{
    //Multiset<int> p, q;

    //// Left Right Rotation (pentru fiul stang)
    //p.add(30);
    //assert(p.exists(30));
    //p.add(20);
    //assert(p.exists(20));
    //p.add(40);
    //assert(p.exists(40));
    //p.add(10);
    //assert(p.exists(10));
    //p.add(15);
    //assert(p.exists(15));
    ////cout << p;

    //// Right Right Rotation (pentru fiul drept)
    //q.add(40);
    //assert(q.exists(40));
    //q.add(50);
    //assert(q.exists(50));
    //q.add(60);
    //assert(q.exists(60));
    //q.add(70);
    //assert(q.exists(70));
    ////cout << q;

    //// Constructorul de copiere
    //Multiset<int> k(q);
    //assert(k.exists(40));
    //assert(q.exists(50));
    //assert(q.exists(60));
    //assert(q.exists(70));
    ////cout << k;

    //// Metoda pentru existenta unui nod
    //k.add(100);
    //assert(k.exists(100));
    ////cout << k;

    //// Metoda care intoarce numarul de aparitii
    //q.add(100);
    //q.add(100);
    //q.add(100);
    //assert(q.aparitions(100) == 3);
    ////cout << q.aparitions(100) << '\n';

    //// Specializarea Comparatorului pentru double
    //Multiset<double> d;
    //d.add(-9999.14);
    //d.add(4.14);
    //assert(d.aparitions(3.15) == 2);
    ////cout << d;

    //// Operatorul de atribuire
    //p = k;
    //assert(p.exists(40));
    //assert(p.exists(50));
    //assert(p.exists(60));
    //assert(p.exists(70));
    //assert(p.exists(100));
    ////cout << p << '\n';

    ////// Metoda Remove
    //Multiset<int> f;
    //// Exceptia pentru stergere din multiset gol
    //try
    //{
    //    f.remove(10, f.get_root());
    //}
    //catch (const char* msg)
    //{
    //    cout << msg << '\n';
    //}

    //// Stergerea unui element fara copii
    //f.add(10);
    //f.add(20);
    //f.remove(20, f.get_root());
    //assert(!f.exists(20));
    ////cout << f << '\n';

    //// Stergerea unui element cu un fiu stang
    //f.add(5);
    //f.add(2);
    //f.add(1);
    //f.remove(2, f.get_root());
    //assert(!f.exists(2));
    ////cout << f << '\n';

    ////// Stergerea unui element cu un fiu drept
    //f.add(20);
    //f.remove(10, f.get_root());
    //assert(!f.exists(10));
    ////cout << f << '\n';

    //// Caz in care stergem un element cu un singur fiu si se rebalanseaza AVL-ul
    //Multiset<int> test;
    //test.add(100);
    //test.add(50);
    //test.add(25);
    //test.add(60);
    //test.add(10);
    //test.add(55);
    //test.add(70);
    //test.add(80);
    //test.remove(25, test.get_root());
    //assert(!test.exists(25));
    ////cout << test;

    //// Stergerea unui element cu doi fii
    //test.add(125);
    //test.remove(80, test.get_root());
    //assert(!test.exists(80));
    ////cout << test;

    //// Stergerea radacinii
    //test.remove(60, test.get_root());
    //assert(!test.exists(60));
    ////cout << test;

    //// Numarul de elemente distincte
    //Multiset<int> d2;
    //d2.add(10);
    //d2.add(40);
    //d2.add(4);
    //d2.add(10);
    ////cout << d2.distinct_elements();

    //d2.remove_aparitions(10);
    //cout << d2;

    Multiset<int> p;
    p.add(10);
    p.add(10);
    p.add(10);
    p.remove(10, p.get_root());
    cout << p;

    return 0;
}