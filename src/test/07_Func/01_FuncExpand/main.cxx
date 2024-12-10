#include "MyTemplate/Func.hxx"

#include <iostream>

using namespace My;
using namespace std;

int main() {
  {  // basic
    auto expandedFunc = FuncExpand<void(int&, int&, float&)>::run(
        [](int& sum, int n) { sum += n; });
    int sum = 0;
    int v = 3;
    float tmp;
    expandedFunc(sum, v, tmp);
    cout << sum << endl;
  }
  {  // return
    auto expandedFunc =
        FuncExpand<float(int)>::run([](int n) -> int { return n + 1; });
    cout << expandedFunc(3) << endl;
  }
}