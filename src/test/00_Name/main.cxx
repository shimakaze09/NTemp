//
// Created by Admin on 1/12/2024.
//

#include <iostream>

#include "template/list/TypeList.hxx"

using namespace std;
using namespace Nexus;

int main(int argc, char **argv) {
  cout << Name<void>() << endl;
  cout << Name<int>() << endl;
  cout << Name<unsigned int>() << endl;
  cout << Name<const int>() << endl;
  cout << Name<volatile int>() << endl;
  cout << Name<int &>() << endl;
  cout << Name<int &&>() << endl;
  cout << Name<int *>() << endl;
  cout << Name<const int *&>() << endl;
  cout << Name<TypeList<int, int>>() << endl;
  cout << Name<void()>() << endl;
  cout << Name<void (*)(int, int)>() << endl;
  cout << Name<int[2]>() << endl;
  cout << Name<const int[2]>() << endl;
  cout << Name<int[]>() << endl;
  cout << Name<const int[]>() << endl;
  cout << Name<void (*const[2])(int, int)>() << endl;
  cout << Name<TypeList<int, float, bool>>() << endl;
}
