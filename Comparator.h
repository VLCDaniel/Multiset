#pragma once
#include "Nod.h"
#include <algorithm>

template <class T>
class Comparator
{
public:
	static bool equals(T x, T y) { return x == y; }
	static bool greater(T, T);
	static bool less(T, T);
	static bool lesseq(T x, T y) { return x <= y; }
};

template <class T>
bool Comparator<T>::greater(T x, T y)
{
	return x > y;
}

template <class T>
bool Comparator<T>::less(T x, T y)
{
	return x < y;
}


// Specializarea clasei pentru double
bool Comparator<double>::equals(double x, double y)
{
	double a = x - float(x);
	double b = y - float(y);
	return abs(abs(a) - abs(b)) < 0.01 * (abs(x) > abs(y) ? abs(y) : abs(x));
}

