#pragma once
#include <iostream>
#include <algorithm>
#include "Comparator.h"
#include "Nod.h"
using namespace std;

template <class T, class F = Comparator<T>>
class Multiset
{
private:
	Nod<T>* root; // radacina AVL-ului

	void RSD(Nod<T>*, ostream&) const; // parcurgere recursiva Radacina - Stanga - Dreapta (pentru afisare)
	void foo(Nod<T>*, int);

public:
	Multiset();
	void add(T);
	void remove(T);

	friend ostream& operator<<(ostream& out, const Multiset<T, F>& M)
	{
		M.RSD(M.root, out);
		return out;
	}
};

template <class T, class F>
void Multiset<T, F>::RSD(Nod<T>* r, ostream& out) const
{
	if (r)
	{
		out << r->get_info() << ' ' << "Height: " << r->get_height() << '\n';
		this->RSD(r->get_left(), out);
		this->RSD(r->get_right(), out);
	}
}

template <class T, class F>
void Multiset<T, F>::foo(Nod<T>* p, int x)
{
	if (F::less(p->get_info(), x))
	{
		if (p->get_right())
		{
			this->foo(p->get_right(), x);
		}
		else
		{
			Nod<T>* y = new Nod<T>(x, 0);
			p->set_right(y);
		}
	}
	else
	{
		if (p->get_left())
		{
			this->foo(p->get_left(), x);
		}
		else
		{
			Nod<T>* y = new Nod<T>(x, 0);
			p->set_left(y);
		}
	}
	p->set_height(max(p->get_left()->get_height(), p->get_right()->get_height()) + 1);
}

template <class T, class F>
Multiset<T, F>::Multiset()
{
	this->root = nullptr;
}

template <class T, class F>
void Multiset<T, F>::add(T x)
{
	if (!this->root) // adaugam radacina
	{
		this->root = new Nod<T>(x, 0);
		return;
	}
	this->foo(this->root, x);



	//Nod<T>* p = this->root;
	//p = new Nod<T>;
	//p->set_height(x);
	//p->set_info(x);
	//cout << root->get_info();
	//this->foo(p, x);
	//cout << p;
	//cout << p->get_info();



	/*if (this->root)
	{
		Nod<T>* p = new Nod<T>();
		p->set_info(x);
		p->set_height(0);
		Nod<T>* aux = root;
		Nod<T>* parent = aux;

		while (aux != nullptr)
		{
			parent = aux;
			if (F::less(aux->get_info(), x)) // valoarea din x e mai mare
			{
				aux = aux->get_right();
			}
			else // valoarea din x e mai mica
			{
				aux = aux->get_left();
			}
		}

		if (F::less(parent->get_info(), x)) // valoarea din nod < x
		{
			parent->set_right(p);
		}
		else
		{
			parent->set_left(p);
		}
	}
	else // adaugam radacina
	{
		root = new Nod<T>();
		this->root->set_info(x);
		this->root->set_height(0);
	}*/
}

template <class T, class F>
void Multiset<T, F>::remove(T x)
{

}

