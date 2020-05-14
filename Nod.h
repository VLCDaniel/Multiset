#pragma once

template <class T>
class Nod
{
private:
	T info;
	Nod* left, *right;

public:
	void set_info(T);
    T get_info();
	void set_right(Nod*);
	void set_left(Nod*);
	Nod* get_left();
	Nod* get_right();
};

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

