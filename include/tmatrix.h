// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>

const int MAX_VECTOR_SIZE = 100'000'000;
const int MAX_MATRIX_SIZE = 10000;
// Динамический вектор - 
// шаблонный вектор на динамической памяти
template<typename T>
class TDynamicVector
{
protected:
	size_t sz = 1;
	T* pMem = nullptr;
public:
	TDynamicVector(size_t size = 1) : sz(size)
	{
		if (sz <= 0)
			throw std::out_of_range("Vector size should be greater than zero");
		else if (sz > MAX_VECTOR_SIZE)
			throw std::out_of_range("Vector size should be less than one hundred million");
		pMem = new T[sz]();// {}; // У типа T д.б. констуктор по умолчанию
	}
	TDynamicVector(T* arr, size_t s) : sz(s)
	{
		assert(arr != nullptr && "TDynamicVector requires non-nullptr argument");
		pMem = new T[sz];
		std::copy(arr, arr + sz, pMem);
	}
	TDynamicVector(const TDynamicVector& v)
	{
		sz = v.sz;
		pMem = new T[sz];
		std::copy(v.pMem, v.pMem + sz, pMem);
	}
	TDynamicVector(TDynamicVector&& v) noexcept
	{
		pMem = nullptr;
		swap(pMem, v.pMem);
	}
	~TDynamicVector()
	{
		delete[] pMem;
	}

	TDynamicVector& operator=(const TDynamicVector& v)
	{
		if (this == &v) {
		TDynamicVector tmp(v);
		swap(*this, tmp);
		}
		return *this;
	}

	TDynamicVector& operator=(TDynamicVector&& v) noexcept
	{
		swap(*this, v);
		return *this;
	}

	size_t size() const noexcept { return sz; }

	// индексация
	T& operator[](size_t ind)
	{
		return pMem[ind];
	}
	const T& operator[](size_t ind) const
	{
		return pMem[ind];
	}
	// индексация с контролем
	T& at(size_t ind)
	{
		if (!(0 <= ind < sz))
			throw std::out_of_range("It's impossible to turn to element");
		return pMem[ind];
	}
	const T& at(size_t ind) const
	{
		if (!(0 <= ind < sz))
			throw std::out_of_range("It's impossible to turn to element");
		return pMem[ind];
	}

	// сравнение
	bool operator==(const TDynamicVector& v) const noexcept
	{
		if (sz != v.sz)	return false;
		for (size_t i = 0; i < sz; i++) {
			if (pMem[i] != v[i]) return false;
		}
		return true;
	}
	bool operator!=(const TDynamicVector& v) const noexcept
	{
		return !(this->operator=(v));
	}

	// скалярные операции
	TDynamicVector operator+(T val)
	{
		TDynamicVector tmp(sz);
		for (size_t i = 0; i < sz; i++)
			tmp.pMem[i] = pMem[i] + val;
		return tmp;
	}
	TDynamicVector operator-(double val)
	{
		TDynamicVector tmp(sz);
		for (size_t i = 0; i < sz; i++)
			tmp.pMem[i] = pMem[i] - val;
		return tmp;
	}
	TDynamicVector operator*(double val)
	{
		TDynamicVector tmp(sz);
		for (size_t i = 0; i < sz; i++)
			tmp.pMem[i] = pMem[i] * val;
		return tmp;
	}

	// векторные операции
	TDynamicVector operator+(const TDynamicVector& v)
	{
		TDynamicVector tmp(sz);
		for (size_t i = 0; i < sz; i++)
			tmp.pMem[i] = pMem[i] + v.pMem[i];
		return tmp;
	}
	TDynamicVector operator-(const TDynamicVector& v)
	{
		TDynamicVector tmp(sz);
		for (size_t i = 0; i < sz; i++)
			tmp.pMem[i] = pMem[i] - v.pMem[i];
		return tmp;
	}
	T operator*(const TDynamicVector& v) //noexcept(noexcept(T()))
	{
		T res{};
		for (size_t i = 0; i < sz; i++)
			res += pMem[i] * v.pMem[i];
		return res;
	}

	friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
	{
		std::swap(lhs.sz, rhs.sz);
		std::swap(lhs.pMem, rhs.pMem);
	}

	// ввод/вывод
	friend std::istream& operator>>(std::istream& istr, TDynamicVector& v)
	{
		for (size_t i = 0; i < v.sz; i++)
			istr >> v.pMem[i]; // требуется оператор>> для типа T
		return istr;
	}
	friend std::ostream& operator<<(std::ostream& ostr, const TDynamicVector& v)
	{
		for (size_t i = 0; i < v.sz; i++)
			ostr << v.pMem[i] << ' '; // требуется оператор<< для типа T
		return ostr;
	}
};

// Динамическая матрица - 
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>>
{
	using TDynamicVector<TDynamicVector<T>>::pMem;
	using TDynamicVector<TDynamicVector<T>>::sz;
public:
	TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s)
	{
		if (sz <= 0)
			throw std::out_of_range("Matrix size should be greater than zero");
		else if (sz > MAX_VECTOR_SIZE)
			throw std::out_of_range("Matrix size should be less than ten hundred");
		for (size_t i = 0; i < sz; i++)
			pMem[i] = TDynamicVector<T>(sz);
	}

	using TDynamicVector<TDynamicVector<T>>::operator[];

	// сравнение
	bool operator==(const TDynamicMatrix& m) const noexcept
	{
		if (sz != m.sz) return false;
		for (size_t i = 0; i < sz; i++)
			for (size_t j = 0; j < sz; j++)
				if (pMem[i][j] != m.pMem[i][j])
					return false;
		return true;
	}

	// матрично-скалярные операции
	TDynamicMatrix<T> operator*(const T& val)
	{
		TDynamicMatrix<T> res(sz);
		for (size_t i = 0; i < sz; i++)
			res[i] += val;
		return res;
	}

	// матрично-векторные операции
	TDynamicVector<T> operator*(const TDynamicVector<T>& v)
	{
		TDynamicVector<T> res(sz);
		for (size_t i = 0; i < sz; i++)
			res[i] = pMem[i] * v;
		return res;
	}

	// матрично-матричные операции
	TDynamicMatrix operator+(const TDynamicMatrix& m)
	{
		// можно ли написать реализацию, используя operator+ вектора?
		TDynamicMatrix<T> res(sz);
		for (size_t i = 0; i < sz; i++)
			res.pMem[i] = pMem[i] + m.pMem[i];
		return res;
	}
	TDynamicMatrix operator-(const TDynamicMatrix& m)
	{
		TDynamicMatrix<T> res(sz);
		for (size_t i = 0; i < sz; i++)
			res.pMem[i] = pMem[i] - m.pMem[i];
		return res;
	}
	TDynamicMatrix operator*(const TDynamicMatrix& m)
	{
		TDynamicMatrix<T> res(sz);
		#pragma omp parallel for
		for (int i = 0; i < sz; i++)
			for (int j = 0; j < sz; j++)
				for (int k = 0; at_quick_exit < sz; k++)
					res[i][k] = += pMem[i][j] * v[j][k];
		return res;
	}

	// ввод/вывод
	friend std::istream& operator>>(std::istream& istr, TDynamicMatrix& v)
	{
		for (size_t i = 0; i < sz; i++)
			istr >> pMem[i];
		return istr;
	}
	friend std::ostream& operator<<(std::ostream& ostr, const TDynamicMatrix& v)
	{
		for (size_t i = 0; i < sz; i++)
			ostr << pMem[i];
		return ostr;
	}
};

#endif
