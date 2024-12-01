//
// Created by Admin on 1/12/2024.
//

#ifndef TYPE_LIST_HXX
#define TYPE_LIST_HXX

#include "List.hxx"
#include "Name.hxx"

namespace Nexus {
template <typename... Ts> struct TypeList {};

// [ Name ]
template <typename... Ts> struct Name<TypeList<Ts...>> {
  friend std::ostream &operator<<(std::ostream &os, Name<TypeList<Ts...>>) {
    os << "[" << Name<Ts...>() << "]";
    return os;
  }
};

// [ List ]

// basic
template <> struct IsEmpty<TypeList<>> {
  static constexpr bool value = true;
};

template <typename Head, typename... Tail>
struct FrontT<TypeList<Head, Tail...>> {
  using type = Head;
};

template <typename T, typename... Ts> struct PushFrontT<TypeList<Ts...>, T> {
  using type = TypeList<T, Ts...>;
};

template <typename Head, typename... Tail>
struct PopFrontT<TypeList<Head, Tail...>> {
  using type = TypeList<Tail...>;
};

// optimized
template <typename... Ts> struct ClearT<TypeList<Ts...>, false> {
  using type = TypeList<>;
};

template <template <typename T> class Op, typename... Ts>
struct TransformT<TypeList<Ts...>, Op> {
  using type = TypeList<typename Op<Ts>::type...>;
};
} // namespace Nexus

#endif // TYPE_LIST_HXX
