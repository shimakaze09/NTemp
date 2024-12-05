#include <array>
#include <iostream>
#include <type_traits>

#include "MyTemplate/Basic.hxx"
#include "MyTemplate/Num/Num.hxx"

using namespace My;
using namespace std;

template <typename T, T... Vals>
void PrintSequence(sequence<T, Vals...>) {
  cout << Name<T>() << ": ";
  array<T, sizeof...(Vals)> vArr = {Vals...};
  for (auto v : vArr)
    cout << v << ",";
}

int main() {
  PrintSequence(MakeSequence<Size<5>>{});
  return 0;
}