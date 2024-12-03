//
// Created by Admin on 2/12/2024.
//

#ifndef BOOL_HXX
#define BOOL_HXX

#include "Num.hxx"

namespace My {
// Conjunction
template <bool v, typename LastN, typename... Ns>
struct ConjunctionRec;

template <typename LastN>
struct ConjunctionRec<true, LastN> {
  using type = LastN;
};

template <typename LastN, typename... Ns>
struct ConjunctionRec<false, LastN, Ns...> {
  using type = LastN;
};

template <typename LastN, typename NHead, typename... NTail>
struct ConjunctionRec<true, LastN, NHead, NTail...>
    : ConjunctionRec<static_cast<bool>(NHead::value), NHead, NTail...> {};

template <typename... Ns>
using Conjunction = ConjunctionRec<true, True, Ns...>;
template <typename... Ns>
using Conjunction_t = typename Conjunction<Ns...>::type;

// Disjunction
template <bool v, typename LastN, typename... Ns>
struct DisjunctionRec;

template <typename LastN>
struct DisjunctionRec<false, LastN> {
  using type = LastN;
};

template <typename LastN, typename... Ns>
struct DisjunctionRec<true, LastN, Ns...> {
  using type = LastN;
};

template <typename LastN, typename NHead, typename... NTail>
struct DisjunctionRec<false, LastN, NHead, NTail...>
    : DisjunctionRec<static_cast<bool>(NHead::value), NHead, NTail...> {};

template <typename... Ns>
using Disjunction = DisjunctionRec<false, False, Ns...>;

template <typename... Ns>
using Disjunction_t = typename Disjunction<Ns...>::type;
}  // namespace My

#endif  //BOOL_HXX
