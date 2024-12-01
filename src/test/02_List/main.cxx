//
// Created by Admin on 2/12/2024.
//

#include <iostream>
#include <type_traits>

#include <MyTemplate/List/TypeList.hxx>

using namespace std;
using namespace My;

int main() {
  using list0 = TypeList<int, float, bool>;

  cout << "list0: " << Name<list0>() << endl;
  cout << "Front<list0>: " << Name<Front<list0>>() << endl;
  cout << "PushFront<list0, double>: " << Name<PushFront<list0, double>>()
       << endl;
  cout << "PushFront<list0, double, char>: "
       << Name<PushFront<list0, double, char>>() << endl;
  cout << "PopFront<list0>: " << Name<PopFront<list0>>() << endl;
  cout << "Clear<list0>: " << Name<Clear<list0>>() << endl;
  cout << "At<list0, 1>: " << Name<At<list0, 1>>() << endl;
  cout << "Reverse<list0>: " << Name<Reverse<list0>>() << endl;
  cout << "PushBack<list0, double>: " << Name<PushBack<list0, double>>()
       << endl;

  cout << "Transform<list0, add_const>: " << Name<Transform<list0, add_const>>()
       << endl;

  cout << "Select<list0, 0, 2>: " << Name<Select<list0, 0, 2>>() << endl;

  cout << "Contain<list0, int>::value: " << Contains<list0, int>::value << endl;
  cout << "Contain<list0, long>::value: " << Contains<list0, long>::value
       << endl;

  return 0;
}
