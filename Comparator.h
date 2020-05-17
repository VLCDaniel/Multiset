#pragma once
#include "Nod.h"

template <class T>
class Comparator
{
public:
	static bool equals(T, T);
	static bool greater(T, T);
	static bool less(T, T);
	static bool lesseq(T, T);
};

template <class T>
bool Comparator<T>::equals(T x, T y)
{
	return x == y;
}

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

template <class T>
bool Comparator<T>::lesseq(T x, T y)
{
	return x <= y;
}

// Specializarea clasei pentru double
template<> class Comparator<double>
{
public:
	static bool equals(double x, double y)
	{
		return (int)x == (int)y;
	}

	static bool less(double x, double y)
	{
		return x < y;
	}

	static bool lesseq(double x, double y)
	{
		return x <= y;
	}
};