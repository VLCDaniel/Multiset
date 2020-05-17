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
	void RSD_delete(Nod<T>*); // parcurcere recursiva care sterge nodurile
	void copy(Nod<T>*, Nod<T>*); // functie recursiva care copiaza elementele din nodul constant in nodul trimis prin referinta
	void insertrec(Nod<T>*, T); // parcurgerea AVL-ului recursiv pentru inserare
	void search_rec(Nod<T>*, T, unsigned&) const; // cautarea nodului in Multiset recursiv

	void L_left_rotate(Nod<T>*); // Left rotate pentru fiul stang
	void L_right_rotate(Nod<T>*); // Right rotate pentru fiul stang
	void R_left_rotate(Nod<T>*); // Left rotate pentru fiul drept
	void R_right_rotate(Nod<T>*); // Right rotate pentru fiul drept

public:
	Multiset();
	Multiset(Multiset&);
	~Multiset();
	void add(T); // adauga un element in multiset
	void remove(T, Nod<T>*); // sterge un element din multiset
	bool exists(T) const; // verifica daca un element exista in multiset
	Nod<T>* get_root() const { return this->root; };
	unsigned aparitions(T) const; // intoarce numarul de aparitii din multiset

	friend void update_height(Nod<T>*);
	const Multiset<T, F>& operator=(const Multiset<T, F>&);
	friend ostream& operator<<(ostream& out, const Multiset<T, F>& M)
	{
		M.RSD(M.root, out);
		out << '\n';
		return out;
	}
};

template <class T, class F>
void Multiset<T, F>::RSD_delete(Nod<T>* r)
{
	if (r)
	{
		RSD_delete(r->get_left());
		RSD_delete(r->get_right());
		delete r;
	}
}

template<class T, class F>
void Multiset<T, F>::copy(Nod<T>* dest, Nod<T>* source)
{
	if (source)
	{
		if (source->get_left())
		{
			Nod<T>* aux = new Nod<T>(source->get_left()->get_info(), source->get_left()->get_height());
			dest->set_left(aux);
		}
		if (source->get_right())
		{
			Nod<T>* aux = new Nod<T>(source->get_right()->get_info(), source->get_right()->get_height());
			dest->set_right(aux);
		}
		copy(dest->get_left(), source->get_left());
		copy(dest->get_right(), source->get_right());
	}
}

template <class T, class F>
bool Multiset<T, F>::exists(T x) const
{
	Nod<T>* aux = this->root;
	while (aux)
	{
		if (F::equals(x, aux->get_info()))
			return true;
		if (F::less(x, aux->get_info()))
			aux = aux->get_left();
		else
			aux = aux->get_right();
	}
	return false;
}

template<class T, class F>
unsigned Multiset<T, F>::aparitions(T x) const
{
	unsigned nr = 0;
	Nod<T>* aux = this->root;
	this->search_rec(aux, x, nr);
	return nr;
}

template<class T, class F>
const Multiset<T, F>& Multiset<T, F>::operator=(const Multiset<T, F>& source)
{
	if (this != &source) // sa nu atribuim acelasi AVL
	{
		Nod<T>* aux = this->root;
		this->RSD_delete(aux);
		aux = new Nod<T>(source.get_root()->get_info(), source.get_root()->get_height());
		this->root = aux; // creez radacina
		this->copy(this->root, source.get_root()); // copiez elementele recursiv
	}
	return *this;
}

template <class T>
void update_height(Nod<T>* x)
{
	if(x)
		x->set_height(1 + max(x->get_left()->get_height(), x->get_right()->get_height()));
}

template <class T, class F>
void Multiset<T, F>::R_left_rotate(Nod<T>* r) // il roteste pe y in locul lui x pentru radacina r (respectiv fiul drept al ei)
{
	Nod<T>* x = r->get_right();
	Nod<T>* y = x->get_right();

	r->set_right(y);
	x->set_right(y->get_left());
	y->set_left(x);

	update_height(x->get_left());
	update_height(x);
	update_height(y->get_right());
	update_height(y);
}

template <class T, class F>
void Multiset<T, F>::R_right_rotate(Nod<T>* r) // il roteste pe x in locul lui y pentru radacina r (respectiv fiul drept al ei)
{
	Nod<T>* y = r->get_right();
	Nod<T>* x = y->get_left();

	y->set_left(x->get_right());
	x->set_right(y);
	r->set_right(x);

	update_height(x->get_left());
	update_height(y->get_right());
	update_height(y);
	update_height(x);
}

template <class T, class F>
void Multiset<T, F>::L_left_rotate(Nod<T>* r) // il roteste pe y in locul lui x pentru radacina r (respectiv fiul stang al ei)
{
	Nod<T>* x = r->get_left();
	Nod<T>* y = x->get_right();

	r->set_left(y);
	x->set_right(y->get_left());
	y->set_left(x);

	update_height(x->get_left());
	update_height(x);
	update_height(y->get_right());
	update_height(y);
}

template <class T, class F>
void Multiset<T, F>::L_right_rotate(Nod<T>* r) // il roteste pe x in locul lui y pentru radacina r (respectiv fiul stang al ei)
{
	Nod<T>* y = r->get_left();
	Nod<T>* x = y->get_left();

	y->set_left(x->get_right());
	x->set_right(y);
	r->set_left(x);

	update_height(x->get_left());
	update_height(y->get_right());
	update_height(y);
	update_height(x);
}

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
void Multiset<T, F>::insertrec(Nod<T>* p, T x)  // parcurgere recursiva
{
	if (F::less(p->get_info(), x)) // valoarea din x e mai mare
	{
		if (p->get_right()) // exista nodul drept
		{
			this->insertrec(p->get_right(), x);
		}
		else
		{
			Nod<T>* y = new Nod<T>(x, 1);
			p->set_right(y);
		}
	}
	else // valoarea din x e mai mica
	{
		if (p->get_left()) // exista nodul stang
		{
			this->insertrec(p->get_left(), x);
		}
		else
		{
			Nod<T>* y = new Nod<T>(x, 1);
			p->set_left(y);
		}
	}
	p->set_height(max(p->get_left()->get_height(), p->get_right()->get_height()) + 1); // setez height-ul fiecarui nod

	// Pentru ca nu pot modifica adresa nodului transmis in aceasta functie, voi modifica nodurile left si right ale nodului curent
	// (de asta folosesc aux mai jos, pentru a verifica daca se mentine structura de AVL pentru fiul stang si fiul drept)
	// Aceasta metoda nu aplica rebalancing pentru radacina (ceea ce nu afecteaza complexitatea)
	if (p->get_left())
	{
		Nod<T>* aux = p->get_left(); // fiul stang

		int balance = aux->get_left()->get_height() - aux->get_right()->get_height(); // daca balance depaseste intervalul [-1, 1], trebuiesc facute rotatii

		if (aux->get_left())
		{
			// Left Left Case Rotation (pentru fiul stang)
			if (balance > 1 && F::lesseq(x, aux->get_left()->get_info()))
				this->L_right_rotate(p);

			// Left Right Case Rotation (pentru fiul stang)
			else if (balance > 1 && F::lesseq(aux->get_left()->get_info(), x))
			{
				this->L_left_rotate(aux);
				this->L_right_rotate(p);
			}
		}

		if (aux->get_right())
		{
			// Right Right Case Rotation (pentru fiul stang)
			if (balance < -1 && F::lesseq(aux->get_right()->get_info(), x))
				this->L_left_rotate(p);

			// Right Left Case Rotation (pentru fiul stang)
			else if (balance < -1 && F::lesseq(x, aux->get_right()->get_info()))
			{
				this->L_left_rotate(p);
				this->L_left_rotate(p->get_left());
				this->L_right_rotate(p);
			}
		}
	}

	// analog, pentru fiul drept
	if (p->get_right())
	{
		Nod<T>* aux = p->get_right();

		int balance = aux->get_left()->get_height() - aux->get_right()->get_height();

		if (aux->get_left())
		{
			// Left Left Case Rotation (pentru fiul drept)
			if (balance > 1 && F::lesseq(x, aux->get_left()->get_info()))
				this->R_right_rotate(p);

			// Left Right Case Rotation (pentru fiul drept)
			else if (balance > 1 && F::lesseq(aux->get_left()->get_info(), x))
			{
				this->R_right_rotate(p);
				this->R_right_rotate(p->get_right());
				this->R_left_rotate(p);
			}
		}

		if (aux->get_right())
		{
			// Right Right Case Rotation (pentru fiul drept)
			if (balance < -1 && F::lesseq(aux->get_right()->get_info(), x))
				this->R_left_rotate(p);

			// Right Left Case Rotation (pentru fiul drept)
			else if (balance < -1 && F::lesseq(x, aux->get_right()->get_info()))
			{
				this->R_right_rotate(p->get_right());
				this->R_left_rotate(p);
			}
		}
	}
}

template<class T, class F>
void Multiset<T, F>::search_rec(Nod<T>* r, T x, unsigned& nr) const
{
	if (r)
	{
		if (F::equals(r->get_info(), x))
		{
			nr++;
			search_rec(r->get_left(), x, nr);
			search_rec(r->get_right(), x, nr);
		}
		else if (F::less(r->get_info(), x))
			search_rec(r->get_right(), x, nr);
		else
			search_rec(r->get_left(), x, nr);
	}
}

template <class T, class F>
Multiset<T, F>::Multiset()
{
	this->root = nullptr;
}

template<class T, class F>
Multiset<T, F>::Multiset(Multiset& x)
{
	Nod<T>* aux = this->root;
	this->RSD_delete(aux); // sterg AVL-ul curent
	this->add(x.get_root()->get_info()); // creez radacina
	this->copy(this->root, x.get_root()); // copiez elementele recursiv
}

template <class T, class F>
void Multiset<T, F>::add(T x)
{
	if (!this->root) // adaugam radacina
	{
		this->root = new Nod<T>(x, 1);
		return;
	}
	this->insertrec(this->root, x);
}

template <class T, class F>
void Multiset<T, F>::remove(T x, Nod<T>* r)
{
	if (!r)
	{
		cout << "Can not remove from an empty Multiset!\n";
		return;
	}

}

template <class T, class F>
Multiset<T, F>::~Multiset()
{
	Nod<T>* aux = this->root;
	this->RSD_delete(aux);
}