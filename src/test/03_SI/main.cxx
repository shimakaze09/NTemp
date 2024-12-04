//
// Created by Admin on 3/12/2024.
//

#include <array>
#include <iostream>
#include <type_traits>

#include "MyTemplate/SI.hxx"

using namespace std;
using namespace My;

template <typename Base, typename T, typename N>
struct IArray : Base, std::array<T, N::value> {};

template <typename Base, typename T, typename N>
struct IPrint : SI<TemplateList<IArray>>::Ttype<Base, T, N> {
  void Print() const {
    const auto& ArrayObj = *SI_CastC<IArray>(this);
    for (const auto& v : ArrayObj)
      cout << v << ",";
  }
};

struct Rst : SII<TemplateList<IPrint, IArray>>::Ttype<float, Size<3>> {};

int main() {
  Rst rst;
  rst.fill(2);
  rst.Print();
}