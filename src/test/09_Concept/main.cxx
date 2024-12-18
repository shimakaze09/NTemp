#include "MyTemplate/Concept.hxx"

#include <iostream>

using namespace My;

template <class T>
Concept(can_speak, std::declval<T>().Speak());

class C {
 public:
  void Speak() {}
};

class D {};

int main() {
  static_assert(Require<can_speak, C> == true);
  static_assert(Require<can_speak, D> == false);
}