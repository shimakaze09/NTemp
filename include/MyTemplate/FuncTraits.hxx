//
// Created by Admin on 6/12/2024.
//

#ifndef FUNC_TRAITS_HXX
#define FUNC_TRAITS_HXX

#include "TypeList.hxx"

namespace My {
// ArgList : TypeList<Args...>
// Ret
template <typename T>
struct FuncTraits;
}  // namespace My

// ============================================================

namespace My::detail::FuncTraits {
template <typename T>
struct FuncTraits;
}  // namespace My::detail::FuncTraits

namespace My {
// ArgList, Ret
template <typename T>
struct FuncTraits : detail::FuncTraits::FuncTraits<T> {};
}  // namespace My

namespace My::detail::FuncTraits {
template <typename T>
struct FuncTraits;

template <typename _Ret, typename... Args>
struct FuncTraits<_Ret(Args...)> {
  using ArgList = TypeList<Args...>;
  using Ret = _Ret;
};

template <typename T, typename _Ret, typename... Args>
struct FuncTraits<_Ret (T::*)(Args...)> {
  using ArgList = TypeList<Args...>;
  using Ret = _Ret;
};

template <typename T, typename _Ret, typename... Args>
struct FuncTraits<_Ret (T::*)(Args...) const> {
  using ArgList = TypeList<Args...>;
  using Ret = _Ret;
};

template <typename T>
struct FuncTraits : FuncTraits<decltype(&std::decay_t<T>::operator())> {};
}  // namespace My::detail::FuncTraits

#endif  //FUNC_TRAITS_HXX