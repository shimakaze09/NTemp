//
// Created by Admin on 2/12/2024.
//

#ifndef NUM_HXX
#define NUM_HXX

#include "Basic.hxx"

namespace My {
// type, value
template <typename T, T N>
struct Num;

template <bool b>
using Bool = Num<bool, b>;
using True = Num<bool, true>;
using False = Num<bool, false>;

template <char c>
using Char = Num<char, c>;
template <short N>
using Short = Num<short, N>;
template <int N>
using Int = Num<int, N>;
template <long N>
using Long = Num<long, N>;
template <size_t N>
using Size = Num<size_t, N>;
}  // namespace My

// ============================================================

namespace My {
template <typename T, T N>
struct Num {
  using type = T;
  static constexpr unsigned value = N;
};

template <typename... Ts>
struct Name;

template <>
struct Name<bool> {
  friend std::ostream& operator<<(std::ostream& os, Name<bool>) {
    os << "bool";
    return os;
  }
};

template <typename T, T N>
struct Name<Num<T, N>> {
  friend std::ostream& operator<<(std::ostream& os, Name<Num<T, N>>) {
    os << "Num<" << Name<T>() << ", " << N << ">";
    return os;
  }
};

template <bool b>
struct Name<Num<bool, b>> {
  friend std::ostream& operator<<(std::ostream& os, Name<Num<bool, b>>) {
    os << "Num<" << Name<bool>() << ", " << (b ? "true" : "false") << ">";
    return os;
  }
};
}  // namespace My

#endif  //NUM_HXX
