#pragma once

template <class T>
class Nod
{
private:
	T info;
	Nod* left, *right;
	int height;

public:

	Nod() = default;
	Nod(T x, int y) : info(x), height(y) { this->left = nullptr; this->right = nullptr; };
	void set_info(T);
	void set_height(int);
	void set_right(Nod*);
	void set_left(Nod*);
	int get_height();
	T get_info();
	Nod* get_left();
	Nod* get_right();
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
T Nod<T>::get_info()
{
	return this->info;
}

template <class T>
Nod<T>* Nod<T>::get_left()
{
	return this->left;
}

template <class T>
Nod<T>* Nod<T>::get_right()
{
	return this->right;
}