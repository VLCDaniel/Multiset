#pragma once
#include <iostream>
#include "Comparator.h"
#include "Nod.h"
using namespace std;

template <class T, class F = Comparator<T>>
class Multiset
{
private:
	Nod<T>* root;

	void RSD(Nod<T>*, ostream&) const;

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
		out << r->get_info() << ' ';
		this->RSD(r->get_left(), out);
		this->RSD(r->get_right(), out);
	}
}

template <class T, class F>
Multiset<T, F>::Multiset()
{
	this->root = nullptr;
}

template <class T, class F>
void Multiset<T, F>::add(T x)
{
	if (this->root)
	{
		Nod<T>* p = new Nod<T>();
		p->set_info(x);
		Nod<T>* aux = root;
		Nod<T>* parent = aux;

		while (aux != nullptr)
		{
			parent = aux;
			if (F::less(aux->get_info(), x))
			{
				aux = aux->get_right();
			}
			else
			{
				aux = aux->get_left();
			}
		}

		if (F::less(parent->get_info(), x))
		{
			parent->set_right(p);
		}
		else
		{
			parent->set_left(p);
		}
	}
	else
	{
		root = new Nod<T>();
		this->root->set_info(x);
	}
}

template <class T, class F>
void Multiset<T, F>::remove(T x)
{

}

