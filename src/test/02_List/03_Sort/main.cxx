#include <iostream>

#include "MyTemplate/Name.hxx"
#include "MyTemplate/TypeID.hxx"
#include "MyTemplate/TypeList.hxx"

using namespace My;
using namespace std;

int main() {
  using list = TypeList<int, float, double, TypeList<>>;
  cout << "TypeID<int>        : " << TypeID<int> << endl;
  cout << "TypeID<float>      : " << TypeID<float> << endl;
  cout << "TypeID<double>     : " << TypeID<double> << endl;
  cout << "TypeID<TypeList<>> : " << TypeID<TypeList<>> << endl;

  cout << Name<QuickSort_t<list, TypeID_Less>>() << endl;
}