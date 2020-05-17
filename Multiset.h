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
	void distinct_rec(Nod<T>*, int&) const;

	void L_left_rotate(Nod<T>*); // Left rotate pentru fiul stang
	void L_right_rotate(Nod<T>*); // Right rotate pentru fiul stang
	void R_left_rotate(Nod<T>*); // Left rotate pentru fiul drept
	void R_right_rotate(Nod<T>*); // Right rotate pentru fiul drept

	void balance_left(Nod<T>*, T); // Balanseaza subarborele stang al radacinii
	void balance_right(Nod<T>*, T); // Balanseaza subarborele drept al radacinii

	Nod<T>* in_order(Nod<T>*) const; // Returneaza valoarea celui mai mic nod(frunza) din subarborele drept

public:
	Multiset();
	Multiset(Multiset&);
	~Multiset();
	void add(T); // adauga un element in multiset
	void remove(T, Nod<T>*); // sterge un element din multiset
	bool exists(T) const; // verifica daca un element exista in multiset
	Nod<T>* get_root() const { return this->root; };
	unsigned aparitions(T) const; // intoarce numarul de aparitii din multiset
	unsigned distinct_elements() const;

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
unsigned Multiset<T, F>::distinct_elements() const
{
	int nr = 0;
	Nod<T>* aux = this->root;
	this->distinct_rec(aux, nr);
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
void Multiset<T, F>::balance_left(Nod<T>* p, T x)
{
	if (p == this->root) // Daca nodul curent este radacina, ne folosim de un nod auxiliar pentru a-l balansa
	{
		Nod<T>* rad_partiala = new Nod<T>(p->get_info() + 1, p->get_height() + 1);
		rad_partiala->set_left(p);

		balance_left(rad_partiala, x);
		this->root = rad_partiala->get_left();

		rad_partiala->set_left(nullptr);
		delete rad_partiala;
		update_height(root);
	}
// Pentru ca nu pot modifica adresa nodului transmis in aceasta functie, voi modifica nodurile left si right ale nodului curent
// (de asta folosesc aux mai jos, pentru a verifica daca se mentine structura de AVL pentru fiul stang si fiul drept)
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
}

template<class T, class F>
void Multiset<T, F>::balance_right(Nod<T>* p, T x)
{
	if (p == this->root)
	{
		Nod<T>* rad_partiala = new Nod<T>(p->get_info() + 1, p->get_height() + 1);
		rad_partiala->set_right(p);

		balance_right(rad_partiala, x);
		this->root = rad_partiala->get_right();

		rad_partiala->set_right(nullptr);
		delete rad_partiala;
		update_height(root);
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
Nod<T>* Multiset<T, F>::in_order(Nod<T>* p) const
{
	if (p->get_left()) // exista nodul stang
		in_order(p->get_left());
	else
	{
		return p;
	}
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

		balance_left(p, x);
		balance_right(p, x);
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

template<class T, class F>
void Multiset<T, F>::distinct_rec(Nod<T>* r, int& nr) const
{
	if (r)
	{
		nr++;
		distinct_rec(r->get_left(), nr);
		distinct_rec(r->get_right(), nr);
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
	if (!r) // Exceptia pentru stergere din multiset gol
		throw("Can not remove an element from an empty Multiset!\n");

	if (F::less(x, r->get_info())) // x < nodul curent -> se afla in subarborele stang
	{
		if (F::equals(x, r->get_left()->get_info())) // am gasit nodul pe care vrem sa-l stergem
		{
			Nod<T>* left_son = r->get_left();
			if (!left_son->get_left() || !left_son->get_right()) // cazul cu niciun fiu sau cu un fiu
			{
				if (!left_son->get_left() && !left_son->get_right()) // cazul cu niciun fiu
				{
					r->set_left(nullptr);
					delete left_son;
					update_height(r);
				}
				else // cazul cu un fiu
				{
					if (left_son->get_left()) // fiul stang
					{
						Nod<T>* aux = left_son->get_left();
						r->set_left(aux);
						left_son->set_left(nullptr);
						delete left_son;
						update_height(aux);
						update_height(r);
					}
					else // fiul drept
					{
						Nod<T>* aux = left_son->get_right();
						r->set_left(aux);
						left_son->set_right(nullptr);
						delete left_son;
						update_height(aux);
						update_height(r);
					}
				}
			}

			else// cazul cu doi fii
			{
				Nod<T>* i = in_order(left_son->get_right());
				T x = i->get_info();
				remove(x, left_son);
				left_son->set_info(x);

				update_height(left_son);
			}

			balance_left(r, x);
			balance_right(r, x);
		}
		else
		{
			this->remove(x, r->get_left());
			balance_left(r, x);
			balance_right(r, x);
		}
	}

	else if(F::less(r->get_info(), x)) // x > nodul curent -> se afla in subarborele drept
	{
		if (F::equals(x, r->get_right()->get_info())) // am gasit nodul pe care vrem sa-l stergem
		{
			Nod<T>* right_son = r->get_right();
			if (!right_son->get_left() || !right_son->get_right()) // cazul cu niciun fiu sau cu un fiu
			{
				if (!right_son->get_left() && !right_son->get_right()) // cazul cu niciun fiu
				{
					r->set_right(nullptr);
					delete right_son;
					update_height(r);
				}
				else // cazul cu un fiu
				{
					if (right_son->get_left()) // fiul stang
					{
						Nod<T>* aux = right_son->get_left();
						r->set_left(aux);
						right_son->set_left(nullptr);
						delete right_son;
						update_height(aux);
						update_height(r);
					}
					else // fiul drept
					{
						Nod<T>* aux = right_son->get_right();
						r->set_right(aux);
						right_son->set_right(nullptr);
						delete right_son;
						update_height(aux);
						update_height(r);
					}
				}
			}
			else // cazul cu doi fii
			{
				Nod<T>* i = in_order(right_son->get_right());
				T x = i->get_info();
				remove(x, right_son);
				right_son->set_info(x);
				
				update_height(right_son);
			}

			balance_left(r, x);
			balance_right(r, x);
		}
		else
		{
			this->remove(x, r->get_right());
			balance_left(r, x);
			balance_right(r, x);
		}
	}

	else // altfel nodul e chiar radacina
	{
		Nod<T>* aux = new Nod<T>(r->get_info() + 1, r->get_height() + 1);
		aux->set_left(r);
		this->remove(x, aux);
		this->root = aux->get_left();
		aux->set_left(nullptr);
		aux->set_right(nullptr);
		delete aux;
		update_height(root);
	}
}

template <class T, class F>
Multiset<T, F>::~Multiset()
{
	Nod<T>* aux = this->root;
	this->RSD_delete(aux);
}