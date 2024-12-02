//
// Created by Admin on 2/12/2024.
//

#ifndef NUM_HXX
#define NUM_HXX

namespace My {
template <unsigned N>
struct Num {
  static constexpr unsigned value = N;
  using type = unsigned;
};
}  // namespace My

#endif  //NUM_HXX
