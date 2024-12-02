//
// Created by Admin on 2/12/2024.
//

#ifndef NUM_HXX
#define NUM_HXX

namespace My {
template <typename T, T N>
struct Num {
  using type = T;
  static constexpr unsigned value = N;
};

template <bool b>
using Bool = Num<bool, b>;

template <char c>
using Char = Num<char, c>;

template <short N>
using Short = Num<short, N>;

template <int N>
using Int = Num<int, N>;

template <long N>
using Long = Num<long, N>;

// std::size_t == decltype(sizeof(void*))
template <decltype(sizeof(void*)) N>
using Size = Num<decltype(sizeof(void*)), N>;
}  // namespace My

#endif  //NUM_HXX
