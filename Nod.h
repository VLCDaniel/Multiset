#pragma once

template <class T>
class Nod
{
private:
	T info;
	Nod* left, *right;
	int height;

public:

	Nod() : info(0), left(nullptr), right(nullptr), height(1) {};
	Nod(T x, int y) : info(x), height(y) { this->left = nullptr; this->right = nullptr; };
	void set_info(T);
	void set_height(int);
	void set_right(Nod*);
	void set_left(Nod*);
	int get_height();
	T get_info() const;
	Nod* get_left() const;
	Nod* get_right() const;
};

template<class T>
int Nod<T>::get_height()
{
	if (this) // daca exista obiectul
	{
		return this->height;
	}
	return 0;
}

template<class T>
void Nod<T>::set_height(int x)
{
	this->height = x;
}

template <class T>
void Nod<T>::set_info(T x)
{
	this->info = x;
}

template <class T>
void Nod<T>::set_left(Nod* N)
{
	this->left = N;
}

template <class T>
void Nod<T>::set_right(Nod* N)
{
	this->right = N;
}

template <class T>
T Nod<T>::get_info() const
{
	return this->info;
}

template <class T>
Nod<T>* Nod<T>::get_left() const
{
	return this->left;
}

template <class T>
Nod<T>* Nod<T>::get_right() const
{
	return this->right;
}