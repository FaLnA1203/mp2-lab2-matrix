// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <algorithm>
#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Динамический вектор - 
// шаблонный вектор на динамической памяти
template<typename T>
class TDynamicVector
{
protected:
  size_t sz;
  T* pMem;
public:
  TDynamicVector(size_t size = 1) : sz(size)
  {
    if (sz == 0)
      throw out_of_range("Vector size should be greater than zero");
    if (sz > static_cast<size_t>(MAX_VECTOR_SIZE))
      throw out_of_range("Vector size is too large");
    pMem = new T[sz]();// {}; // У типа T д.б. констуктор по умолчанию
  }
  TDynamicVector(T* arr, size_t s) : sz(s)
  {
    if (sz == 0)
      throw out_of_range("Vector size should be greater than zero");
    if (sz > static_cast<size_t>(MAX_VECTOR_SIZE))
      throw out_of_range("Vector size is too large");
    if (arr == nullptr)
      throw invalid_argument("Vector requires non-nullptr array");
    pMem = new T[sz];
    std::copy(arr, arr + sz, pMem);
  }
  TDynamicVector(const TDynamicVector& v)
  {
      sz = v.sz;
      pMem = new T[sz];
      for (size_t i = 0; i < sz; i++) {
          pMem[i] = v.pMem[i];
      }
  }
  TDynamicVector(TDynamicVector&& v) noexcept
  {
      sz = v.sz;
      pMem = v.pMem;
      v.pMem = nullptr;
      v.sz = 0;
  }
  ~TDynamicVector()
  {
      delete[] pMem;
      sz = 0;
  }
  TDynamicVector& operator=(const TDynamicVector& v)
  {
      if (this != &v) {
          T* tmp = new T[v.sz];
          for (size_t i = 0; i < v.sz; i++) {
              tmp[i] = v.pMem[i];
          }
          delete[] pMem;
          pMem = tmp;
          sz = v.sz;
      }
      return *this;
  }
  TDynamicVector& operator=(TDynamicVector&& v) noexcept
  {
      if (this != &v) {
          delete[] pMem;
          sz = v.sz;
          pMem = v.pMem;
          v.pMem = nullptr;
          v.sz = 0;
      }
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
      // отрицательный индекс приходит сюда как очень большое size_t
      if (ind >= sz) {
          throw out_of_range("индекс меньше нуля или больше размера массива");
      }
      return pMem[ind];
  }
  const T& at(size_t ind) const
  {
      // отрицательный индекс приходит сюда как очень большое size_t
      if (ind >= sz) {
          throw out_of_range("индекс меньше нуля или больше размера массива");
      }
      return pMem[ind];
  }

  // сравнение
  bool operator==(const TDynamicVector& v) const noexcept
  {
      if (sz != v.sz) {
          return false;
      }
      for (size_t i = 0; i < sz; i++) {
          if (pMem[i] != v.pMem[i]) {
              return false;
          }
      }
      return true;
  }
  bool operator!=(const TDynamicVector& v) const noexcept
  {
      return !(*this == v);
  }

  // скалярные операции
  TDynamicVector operator+(T val)
  {
      for (size_t i = 0; i < sz; i++) {
          pMem[i] += val;
      }
      return *this;
  }
  TDynamicVector operator-(T val)
  {
      for (size_t i = 0; i < sz; i++) {
          pMem[i] -= val;
      }
      return *this;
  }
  TDynamicVector operator*(T val)
  {
      for (size_t i = 0; i < sz; i++) {
          pMem[i] *= val;
      }
      return *this;
  }

  // векторные операции
  TDynamicVector operator+(const TDynamicVector& v)
  {
      if (sz != v.sz) {
          throw out_of_range("векторы должны иметь одинаковый размер");
      }
      for (size_t i = 0; i < sz; i++) {
          pMem[i] += v.pMem[i];
      }
      return *this;
  }
  TDynamicVector operator-(const TDynamicVector& v)
  {
      if (sz != v.sz) {
          throw out_of_range("векторы должны иметь одинаковый размер");
      }
      for (size_t i = 0; i < sz; i++) {
          pMem[i] -= v.pMem[i];
      }
      return *this;
  }
  T operator*(const TDynamicVector& v)
  {
      if (sz != v.sz) {
          throw out_of_range("векторы должны иметь одинаковый размер");
      }
      T sum = 0;
      for (size_t i = 0; i < sz; i++) {
          sum+= pMem[i] * v.pMem[i];
      }
      return sum;
  }

  friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
  {
    std::swap(lhs.sz, rhs.sz);
    std::swap(lhs.pMem, rhs.pMem);
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      istr >> v.pMem[i]; // требуется оператор>> для типа T
    return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
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
    if (s > static_cast<size_t>(MAX_MATRIX_SIZE))
      throw out_of_range("Matrix size is too large");
    for (size_t i = 0; i < sz; i++)
      pMem[i] = TDynamicVector<T>(sz);
  }

  using TDynamicVector<TDynamicVector<T>>::operator[];
  // доступ к строке матрицы с контролем индекса
  using TDynamicVector<TDynamicVector<T>>::at;
  // количество строк (столбцов) матрицы
  using TDynamicVector<TDynamicVector<T>>::size;

  TDynamicMatrix& operator=(const TDynamicMatrix& m) {
      if (this != &m) {
          if (m.sz != sz) {
              delete[] pMem;
              sz = m.sz;
              pMem = new TDynamicVector<T>[sz];
          }
          for (size_t i = 0; i < sz; i++) {
              pMem[i] = m.pMem[i];
          }
      }
      return *this;
  }
  // сравнение
  bool operator==(const TDynamicMatrix& m) const noexcept
  {
      if (sz != m.sz) {
          return false;
      }
      for (size_t i = 0; i < sz; i++) {
          if (pMem[i] != m.pMem[i]) {
              return false;
          }
      }
      return true;
  }
  bool operator!=(const TDynamicMatrix& m) const noexcept
  {
      return !(*this == m);
  }

  // матрично-скалярные операции
  TDynamicMatrix operator*(const T& val)
  {
      TDynamicMatrix res(sz);
      for (size_t i = 0; i < sz; i++) {
          for (size_t j = 0; j < sz; j++) {
              res.pMem[i][j] = pMem[i][j] * val;
          }
      }
      return res;
  }

  // матрично-векторные операции
  TDynamicVector<T> operator*(const TDynamicVector<T>& v)
  {
      if (sz != v.size()) {
          throw out_of_range("матрица и вектор должны иметь одинаковый размер");
      }
      TDynamicVector<T> sum(sz);
      for (size_t i = 0; i < sz; i++) {
          sum[i] = pMem[i] * v;
      }
      return sum;
  }

  // матрично-матричные операции
  TDynamicMatrix operator+(const TDynamicMatrix& m)
  {
      if (sz != m.sz) {
          throw out_of_range("матрицы должны иметь одинаковый размер");
      }
      TDynamicMatrix res(sz);
      for (size_t i = 0; i < sz; i++) {
          for (size_t j = 0; j < m.sz; j++) {
              res.pMem[i][j] = pMem[i][j] + m.pMem[i][j];
           }
      }
      return res;
  }
  TDynamicMatrix operator-(const TDynamicMatrix& m)
  {     
      if (sz != m.sz) {
          throw out_of_range("матрицы должны иметь одинаковый размер");
      }
      TDynamicMatrix res(sz);
      for (size_t i = 0; i < sz; i++) {
          for (size_t j = 0; j < m.pMem[i].size(); j++) {
              res.pMem[i][j] = pMem[i][j] - m.pMem[i][j];
          }
      }
      return res;
  }
  TDynamicMatrix operator*(const TDynamicMatrix& m)
  {
      if (sz != m.sz) {
          throw out_of_range("матрицы должны иметь одинаковый размер");
      }
      TDynamicMatrix res(sz);
      for (size_t i = 0; i < sz; i++) {
          for (size_t j = 0; j < sz; j++) {
              for (size_t k = 0; k < sz; k++) {
                  res.pMem[i][j] += pMem[i][k] * m.pMem[k][j];
              }
          }
      }
      return res;
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicMatrix& v)
  {
      for (size_t i = 0; i < v.sz; i++) {
          for (size_t j = 0; j < v.sz; j++) {
              istr >> v.pMem[i][j];
          }
      }
      return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
  {
      for (size_t i = 0; i < v.sz; i++) {
          for (size_t j = 0; j < v.sz; j++) {
              ostr << v.pMem[i][j] << ' ';
          }
          ostr << endl;
      }
      return ostr;
  }
};

#endif
