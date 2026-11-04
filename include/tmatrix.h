// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#pragma once

#include <iostream>
#include <vector>

const static int MAX_VECTOR_SIZE = 100'000'000;
const static int MAX_MATRIX_SIZE = 10'000;
// Динамический вектор - 
// шаблонный вектор на динамической памяти
template<typename T>
class TDynamicVector
{
protected:
	size_t sz = 1;
	T* pMem = nullptr;
public:
	TDynamicVector(int size = 1)
	{
		if (sz <= 0)
			throw std::out_of_range("Vector size should be greater than zero");
		else if (sz > MAX_VECTOR_SIZE)
			throw std::out_of_range("Vector size should be less than one hundred million");
		sz = static_cast<size_t>(size);
		pMem = new T[sz]();// {}; // У типа T д.б. констуктор по умолчанию
	}
	TDynamicVector(T* arr, int s)
	{
		assert(arr != nullptr && "TDynamicVector requires non-nullptr argument");
		if (sz <= 0)
			throw std::out_of_range("Vector size should be greater than zero");
		else if (sz > MAX_VECTOR_SIZE)
			throw std::out_of_range("Vector size should be less than one hundred million");
		sz = static_cast<size_t>(s);
		pMem = new T[sz];
		std::copy(arr, arr + sz, pMem);
	}
	TDynamicVector(const TDynamicVector& v)
	{
		sz = v.sz;
		pMem = new T[sz];
		std::copy(v.pMem, v.pMem + sz, pMem);
	}
	friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
	{
		std::swap(lhs.sz, rhs.sz);
		std::swap(lhs.pMem, rhs.pMem);
	}
	TDynamicVector(TDynamicVector&& v) noexcept
	{
		pMem = nullptr;
		sz = 0;
		swap(*this, v);
	}

	~TDynamicVector() { delete[] pMem; }

	TDynamicVector& operator=(const TDynamicVector& v)
	{
		if (this != &v) {
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
	T& at(int ind)
	{
		if (!(0 <= ind && ind < sz))
			throw std::out_of_range("It's impossible to turn to element");
		return pMem[static_cast<size_t>(ind)];
	}
	const T& at(int ind) const
	{
		if (!(0 <= ind && ind < sz))
			throw std::out_of_range("It's impossible to turn to element");
		return pMem[static_cast<size_t<ind>];
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
		return !(this->operator==(v));
	}

	// скалярные операции
	TDynamicVector operator+(T val)
	{
		TDynamicVector tmp(sz);
		for (size_t i = 0; i < sz; i++)
			tmp.pMem[i] = pMem[i] + val;
		return tmp;
	}
	TDynamicVector& operator+=(T val) {
		for (size_t i = 0; i < sz; i++)
			pMem[i] += val;
		return *this;
	}
	TDynamicVector operator-(double val)
	{
		TDynamicVector tmp(sz);
		for (size_t i = 0; i < sz; i++)
			tmp.pMem[i] = pMem[i] - val;
		return tmp;
	}
	TDynamicVector& operator-=(T val) {
		for (size_t i = 0; i < sz; i++)
			pMem[i] -= val;
		return *this;
	}
	TDynamicVector operator*(double val)
	{
		TDynamicVector tmp(sz);
		for (size_t i = 0; i < sz; i++)
			tmp.pMem[i] = pMem[i] * val;
		return tmp;
	}
	TDynamicVector& operator*=(T val) {
		for (size_t i = 0; i < sz; i++)
			pMem[i] *= val;
		return *this;
	}
	// векторные операции
	TDynamicVector operator+(const TDynamicVector& v)
	{
		TDynamicVector tmp(sz);
		for (size_t i = 0; i < sz; i++)
			tmp.pMem[i] = pMem[i] + v.pMem[i];
		return tmp;
	}
	TDynamicVector& operator+=(const TDynamicVector& v) {
		for (size_t i = 0; i < sz; i++)
			pMem[i] += v.pMem[i];
		return *this;
	}
	TDynamicVector operator-(const TDynamicVector& v)
	{
		TDynamicVector tmp(sz);
		for (size_t i = 0; i < sz; i++)
			tmp.pMem[i] = pMem[i] - v.pMem[i];
		return tmp;
	}
	TDynamicVector& operator-=(const TDynamicVector& v) {
		for (size_t i = 0; i < sz; i++)
			pMem[i] -= v.pMem[i];
		return *this;
	}
	T operator*(const TDynamicVector& v) //noexcept(noexcept(T()))
	{
		T res{};
		for (size_t i = 0; i < sz; i++)
			res += pMem[i] * v.pMem[i];
		return res;
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
	TDynamicMatrix(int s = 1) : TDynamicVector<TDynamicVector<T>>(s)
	{
		if (sz <= 0)
			throw std::out_of_range("Matrix size should be greater than zero");
		else if (sz > MAX_MATRIX_SIZE)
			throw std::out_of_range("Matrix size should be less than ten hundred");
		for (size_t i = 0; i < sz; i++)
			pMem[i] = TDynamicVector<T>(static_cact<size_t>(sz));
	}
	friend TDynamicMatrix(const SparseMatrixCoo<T>& sm) : TDynamicVector<TDynamicVector<T>>(std::max(sm.row, sm.col)) {
		size_t row = sm.row, col = sm.col;
		;
		for (size_t i = 0; i < sz; i++)
			pMem[i] = TDynamicVector<T>(sz);
		for (size_t i = 0; i < row; i++) {
			pMem[sm.rowInd[i]][sm.colInd[i]] = sm.data[i];
		}
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
	bool operator!=(const TDynamicMatrix& m) const noexcept
	{
		if (sz != m.sz) return true;
		for (size_t i = 0; i < sz; i++)
			if (*this[i] != m[i])
				return true;
		return false;
	}

	// матрично-скалярные операции
	TDynamicMatrix<T> operator*(const T& val)
	{
		TDynamicMatrix<T> res(sz);
		for (size_t i = 0; i < sz; i++)
			res[i] += val;
		return res;
	}
	TDynamicMatrix<T>& operator*=(const T& val)
	{
		for (size_t i = 0; i < sz; i++)
			*this[i] += val;
		return *this;
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
	TDynamicMatrix& operator+=(const TDynamicMatrix& m)
	{
		for (size_t i = 0; i < sz; i++)
			pMem[i] += m.pMem[i];
		return *this;
	}
	TDynamicMatrix operator-(const TDynamicMatrix& m)
	{
		TDynamicMatrix<T> res(sz);
		for (size_t i = 0; i < sz; i++)
			res.pMem[i] = pMem[i] - m.pMem[i];
		return res;
	}
	TDynamicMatrix& operator-=(const TDynamicMatrix& m)
	{
		for (size_t i = 0; i < sz; i++)
			pMem[i] -= m.pMem[i];
		return *this;
	}
	TDynamicMatrix operator*(const TDynamicMatrix& m)
	{
		TDynamicMatrix<T> res(sz);
		#pragma omp parallel for
		for (int i = 0; i < sz; i++)
			for (size_t j = 0; j < sz; j++)
				for (size_t k = 0; k < sz; k++)
					res[i][k] += pMem[i][j] * m[j][k];
		return res;
	}

	// ввод/вывод
	friend std::istream& operator>>(std::istream& istr, TDynamicMatrix& m)
	{
		for (size_t i = 0; i < sz; i++)
			istr >> m.pMem[i];
		return istr;
	}
	friend std::ostream& operator<<(std::ostream& ostr, const TDynamicMatrix& m)
	{
		for (size_t i = 0; i < sz; i++)
			ostr << m.pMem[i];
		return ostr;
	}
};

template<class T> class SparseMatrixCoo {
	std::vector<T> data;
	std::vector<size_t> rowInd;
	std::vector<size_t> colInd;
	size_t row, col;
public:
	SparseMatrixCoo(int rows, int cols) {
		if (rows >= 0 && cols >= 0) {
			row = static_cast<size_t>(rows);
			col = static_cast<size_t>(cols);
		}
		else
			throw std::out_of_range("Sparse matrix size should be greater than zero");
	}
	SparseMatrix(const TDynamicMatrix& m, int rows = m.size(), int cols = m.size()) : row(rows), col(cols) {
		if (rows < 0 && cols < 0)
			throw std::out_of_range("Sparse matrix size should be greater than zero");
		else {
			size_t r = 
			for (size_t r = 0; r < row; r++) {
				for (size_t c = 0; c < col; c++) {
					if (m[r][c] != T(0)) { //тип T должен иметь конструктор преобразования типов
						data.push_back(m[r][c]);
						rowInd.push_back(r);
						colInd.push_back(c);
					}
				}
			}
		}
	}
	size_t rows() { return row; }
	size_t cols() { return col; }
	size_t values() { return data.size(); }
	const T& operator[](size_t r, size_t c) const {
		int val = data.size();
		for (size_t i = 0; i < val; i++) {
			if (rowInd[i] == r) {
				for (size_t j = i; (j < val && rowInd[j] == r); j++) {
					if (colInd[i] == c)
						return data[j];
				}
				return 0;
			}
		}
	}
	const T& at(size_t r, size_t c) const {
		if (r > row || c > col) throw std::out_of_range("It's impossible to turn to element");
		int val = data.size();
		for (size_t i = 0; i < val; i++) {
			if (rowInd[i] == r) {
				for (size_t j = i; (j < val && rowInd[j] == r); j++) {
					if (colInd[i] == c)
						return data[j];
				}
				return 0;
			}
		}
	}
	void add_element(size_t r, size_t c, const T& value) {
		if (r > row || c > col) throw std::out_of_range("It's impossible to turn to element");
		int val = data.size();
		for (size_t i = 0; i < val; i++) {
			if (rowInd[i] == r) {
				size_t j = i
				for (; (j < val && rowInd[j] == r); j++) {
					if (colInd[i] == c) {
						data[j] = value;
						return;
					}
				}
				data.push_back(data[val - 1]);
				for (int u = val - 1; u > j; u++) {
					data[u] = data[u - 1];
				}
				data[j] = value;
				row.push_back(row[val - 1]);
				for (int u = val - 1; u > j; u++) {
					row[u] = row[u - 1];
				}
				row[j] = r;
				col.push_back(col[val - 1]);
				for (int u = val - 1; u > j; u++) {
					col[u] = col[u - 1];
				}
				col[j] = c;
				return;
			}
		}
	}
	SparseMatrixCoo operator+(const SparseMatrixCoo& sm) {
		TDynamicMatrix<T> resm(std::max(row, col));
		TDynamicMatrix<T> tmp1(std::max(row, col));
		for (size_t i = 0; i < data.size(); i++) {
			tmp1[rowInd[i]][colInd[i]] = data[i];
		}
		TDynamicMatrix<T> tmp2(std::max(row, col));
		for (size_t i = 0; i < sm.data.size(); i++) {
			tmp1[sm.rowInd[i]][sm.colInd[i]] = sm.data[i];
		}
		res = tmp1 + tmp2;
		SparseMatrixCoo<T> res(resm, row, col);
		return res;
	}
	friend std::ostream operator<<(std::ostream& ostr, const SparseMatrixCoo& sm) {
		int val = data.size();
		for (int i = 0; i < val; i++) {
			for (size_t r = 0; r < rowInd[i]; r++) {
				for (size_t c = 0; c < colInd[i]; c++) {
					ostr << T(0) << ' ';
					if (c == col - 1) ostr << '\n';
				}
			}
			ostr << data[i];
		}
		return istr;
	}
	friend std::istream& operator>>(std::istream& istr, const SparseMatrixCoo& sm) {
		for (size_t r = 0; r < row; r++) {
			for (size_t c = 0; c < col; c++) {
				T x;
				istr >> x; //тип T должен иметь operator>>
				if (x != T(0)) { //тип T должен иметь конструктор преобразования типов
					data.push_back(x);
					rowInd.push_back(r);
					colInd.push_back(c);
				}
			}
		}
		return istr;
	}
};
