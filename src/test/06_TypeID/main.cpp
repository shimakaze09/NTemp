//
// Created by Admin on 6/12/2024.
//

#include "MyTemplate/TypeID/TypeID.hxx"

#include <iostream>

using namespace My;
using namespace std;

struct A {};

struct AA {};

int main() {
  static_assert(TypeID<int> != 0);
  cout << TypeID<int> << endl;
  static_assert(TypeID<float> != 0);
  cout << TypeID<float> << endl;

  static_assert(TypeID<A> != 0);
  cout << TypeID<A> << endl;
  static_assert(TypeID<A> != 0);
  cout << TypeID<A> << endl;

  static_assert(TypeID<AA> != 0);
  cout << TypeID<AA> << endl;
}