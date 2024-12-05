//
// Created by Admin on 4/12/2024.
//

#include <array>
#include <iostream>
#include <type_traits>

#include "MyTemplate/List/TypeList.hxx"
#include "MyTemplate/Num/Num.hxx"
#include "MyTemplate/SI.hxx"

using namespace std;
using namespace My;

template <typename Base, typename Impl, typename T, typename Num>
struct IArray : Base, array<T, Num::value> {
  using Base::Base;

  IArray() {}

  template <typename... U>
  IArray(U... data) : array<T, Num::value>{static_cast<T>(data)...} {}
};

template <typename Base, typename Impl, typename T, typename Num>
struct IAdd : SIVT<Base, TypeList<Base, Impl, T, Num>, IArray> {
  using SIVT<Base, TypeList<Base, Impl, T, Num>, IArray>::SIVT;

  const Impl operator+(const Impl& y) const {
    const Impl& x = *static_cast<const Impl*>(this);
    Impl rst{};
    for (typename Num::type i = 0; i < Num::value;
         i++)  // loop will be optimized in release
      rst[i] = x[i] + y[i];
    return rst;
  }
};

template <typename Base, typename Impl, typename T, typename Num>
struct IIn : SIVT<Base, TypeList<Base, Impl, T, Num>, IArray> {
  using SIVT<Base, TypeList<Base, Impl, T, Num>, IArray>::SIVT;

  friend istream& operator>>(istream& is, Impl& x) {
    for (typename Num::type i = 0; i < Num::value;
         i++)  // loop will be optimized in release
      is >> x[i];
    return is;
  }
};

template <typename Impl, typename T, typename Num>
struct IIn<SI_Nil, Impl, T, Num>
    : SIVT<SI_Nil, TypeList<SI_Nil, Impl, T, Num>, IArray> {
  using SIVT<SI_Nil, TypeList<SI_Nil, Impl, T, Num>, IArray>::SIVT;
};

template <typename Base, typename Impl, typename T, typename Num>
struct IOut : SIVT<Base, TypeList<Base, Impl, T, Num>, IArray> {
  using SIVT<Base, TypeList<Base, Impl, T, Num>, IArray>::SIVT;

  friend ostream& operator<<(ostream& os, const Impl& x) {
    for (typename Num::type i = 0; i < Num::value - 1;
         i++)  // loop will be optimized in release
      os << x[i] << ", ";
    os << x[Num::value - 1];
    return os;
  }
};

template <typename Impl, typename T, typename Num>
struct IOut<SI_Nil, Impl, T, Num>
    : SIVT<SI_Nil, TypeList<SI_Nil, Impl, T, Num>, IArray> {
  using SIVT<SI_Nil, TypeList<SI_Nil, Impl, T, Num>, IArray>::SIVT;
};

template <typename Base, typename Impl, typename T, typename Num>
struct IInOut : SIVT<Base, TypeList<Base, Impl, T, Num>, IOut, IIn> {
  using SIVT<Base, TypeList<Base, Impl, T, Num>, IOut, IIn>::Ttype;
};

template <typename Base, typename Impl, typename T, typename Num>
struct IVal : SIVT<Base, TypeList<Base, Impl, T, Num>, IAdd, IInOut, IArray> {
  using SIVT<Base, TypeList<Base, Impl, T, Num>, IAdd, IInOut, IArray>::SIVT;
};

template <typename T, unsigned N>
struct Vec : SIIT<TemplateList<IVal>, Vec<T, N>, T, Size<N>> {
  using SIIT<TemplateList<IVal>, Vec<T, N>, T, Size<N>>::SIIT;
};

using Vecf3 = Vec<float, 3>;
using Vecf100 = Vec<float, 100>;

int main() {
  cout << sizeof(Vecf3) << endl;
  Vecf3 vs[4];

  for (size_t i = 0; i < 4; i++)
    std::cin >> vs[i];

  std::cout << Vecf3(vs[0][0] + vs[1][0], vs[0][1] + vs[1][1],
                     vs[0][2] + vs[1][2]);
  std::cout << vs[2] + vs[3];

  Vecf100 v100;
  v100.fill(2);
  cout << v100;
}