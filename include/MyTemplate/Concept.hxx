//
// Created by Admin on 18/12/2024.
//

#pragma once

#include <type_traits>

#define Concept(name, expr) using name = decltype(expr)

namespace My::detail::Concept_ {
template <template <class...> class Trait, class Enabler, class... Args>
struct Require;
}

namespace My {
template <template <class...> class Trait, class... Args>
constexpr bool Require = detail::Concept_::Require<Trait, void, Args...>::value;
}

namespace My::detail::Concept_ {
template <template <class...> class Trait, class Enabler, class... Args>
struct Require : std::false_type {};

template <template <class...> class Trait, class... Args>
struct Require<Trait, std::void_t<Trait<Args...>>, Args...> : std::true_type {};
}  // namespace My::detail::Concept_
