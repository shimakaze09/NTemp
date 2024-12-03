//
// Created by Admin on 1/12/2024.
//

#include <iostream>
#include <type_traits>

#include "MyTemplate/Num/Bool.hxx"

using namespace std;
using namespace My;

int main() {
  cout << Name<Bool<true>>() << endl;
  cout << Name<Int<1>>() << endl;
  cout << Name<Size<10>>() << endl;

  cout << "Conjunction_t<>: " << endl
       << "\t" << Name<Conjunction_t<>>() << endl;
  cout << "Conjunction_t<Int<0>, Long<3>>: " << endl
       << "\t" << Name<Conjunction_t<Int<0>, Long<3>>>() << endl;
  cout << "Conjunction_t<Int<2>, Bool<true>, Size<0>, Long<1>>: " << endl
       << "\t" << Name<Conjunction_t<Int<2>, Bool<true>, Size<0>, Long<1>>>()
       << endl;

  cout << "Disjunction_t<>: " << endl
       << "\t" << Name<Disjunction_t<>>() << endl;
  cout << "Disjunction_t<Int<0>, Long<3>>: " << endl
       << "\t" << Name<Disjunction_t<Int<0>, Long<3>>>() << endl;
  cout << "Disjunction_t<Int<2>, Bool<true>, Size<0>, Long<1>>: " << endl
       << "\t" << Name<Disjunction_t<Int<2>, Bool<true>, Size<0>, Long<1>>>()
       << endl;

  return 0;
}
