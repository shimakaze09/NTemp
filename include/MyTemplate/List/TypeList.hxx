//
// Created by Admin on 1/12/2024.
//

#ifndef TYPE_LIST_HXX
#define TYPE_LIST_HXX

#include "../Basic.hxx"
#include "../Name.hxx"
#include "../Num/Bool.hxx"

namespace My {
/*
 * [ Interface ]
 *
 * T    Front<List>
 * List PushFront<List, Ts...>
 * List PopFront<List, T>
 * bool IsEmpty<List>::value
 *
 * List Clear<List>
 * T At<List, N>
 * I Accumulate<List, <I, T> Op, I>
 * List Reverse<List>
 * List PushBack<List, T>
 * List Transform<List, <T> Op>
 * List Select<List, Size...>
 * bool Contains<List, T>::value
 */

template <typename... Ts>
struct TypeList {
  static constexpr size_t size() noexcept { return sizeof...(Ts); }
};

// [ Name ]
template <typename... Ts>
struct Name<TypeList<Ts...>> {
  friend std::ostream& operator<<(std::ostream& os, Name<TypeList<Ts...>>) {
    os << "[" << Name<Ts...>() << "]";
    return os;
  }
};

// [ List ]

template <typename List>
struct Rotate;

template <typename Head, typename... Tail>
struct Rotate<TypeList<Head, Tail...>> {
  using type = TypeList<Tail..., Head>;
};

// Empty
template <typename List>
struct IsEmpty {
  static constexpr bool value = false;
};

template <>
struct IsEmpty<TypeList<>> {
  static constexpr bool value = true;
};

template <typename List>
constexpr bool IsEmpty_v = IsEmpty<List>::value;

// Front
template <typename List>
struct Front;

template <typename Head, typename... Tail>
struct Front<TypeList<Head, Tail...>> {
  using type = Head;
};

template <typename List>
using Front_t = typename Front<List>::type;

// PushFront
template <typename List, typename T>
struct PushFront;

template <typename List, typename... Ts>
using PushFront_t = typename PushFront<List, Ts...>::type;

template <typename T, typename... Ts>
struct PushFront<TypeList<Ts...>, T> {
  using type = TypeList<T, Ts...>;
};

// PopFront
template <typename List>
struct PopFront;

template <typename List>
using PopFront_t = typename PopFront<List>::type;

template <typename Head, typename... Tail>
struct PopFront<TypeList<Head, Tail...>> {
  using type = TypeList<Tail...>;
};

// At
template <typename List, size_t N>
struct At;

template <typename List>
struct At<List, 0> {
  using type = Front_t<List>;
};

template <typename List, size_t N>
struct At : At<PopFront_t<List>, N - 1> {};

template <typename List, size_t N>
using At_t = typename At<List, N>::type;

// Find
namespace detail {
template <typename List, typename T, size_t N, bool found>
struct Find;

template <typename T, size_t N, typename... Ts>
struct Find<TypeList<Ts...>, T, N, true> {
  static constexpr size_t value = N - 1;
};

template <typename T, size_t N>
struct Find<TypeList<>, T, N, false> {
  static constexpr size_t value = static_cast<size_t>(-1);
};

template <typename T, typename Head, size_t N, typename... Tail>
struct Find<TypeList<Head, Tail...>, T, N, false>
    : Find<TypeList<Tail...>, T, N + 1, std::is_same_v<T, Head>> {};
}  // namespace detail

template <typename List, typename T>
using Find = detail::Find<List, T, 0, false>;
template <typename List, typename T>
constexpr size_t Find_v = Find<List, T>::value;

// Accumulate : list
template <typename List, template <typename I, typename X> class Op, typename I,
          bool = IsEmpty_v<List>>
struct Accumulate;

template <typename List, template <typename I, typename X> class Op, typename I>
struct Accumulate<List, Op, I, false>
    : Accumulate<PopFront_t<List>, Op, typename Op<I, Front_t<List>>::type> {};

template <typename List, template <typename X, typename Y> class Op, typename I>
struct Accumulate<List, Op, I, true> {
  using type = I;
};

template <typename List, template <typename I, typename X> class Op, typename I>
using Accumulate_t = typename Accumulate<List, Op, I>::type;

// AccumulateIS : Accumulate by integer sequence
template <typename List,
          template <typename I, typename List, size_t Num> class Op, typename I,
          size_t... Nums>
struct AccumulateIS;

template <typename List,
          template <typename I, typename List, size_t Num> class Op, typename I>
struct AccumulateIS<List, Op, I> {
  using type = I;
};

template <typename List,
          template <typename I, typename List, size_t Num> class Op, typename I,
          size_t NumHead, size_t... NumTail>
struct AccumulateIS<List, Op, I, NumHead, NumTail...>
    : AccumulateIS<List, Op, typename Op<I, List, NumHead>::type, NumTail...> {
};

template <typename List,
          template <typename I, typename List, size_t Num> class Op, typename I,
          size_t... Nums>
using AccumulateIS_t = typename AccumulateIS<List, Op, I, Nums...>::type;

// Filter
template <typename List, template <typename> class Op>
struct Filter {
 private:
  template <typename I, typename X>
  struct FilterOp {
    using type = std::conditional_t<Op<X>::value, PushFront_t<I, X>, I>;
  };

 public:
  using type = Accumulate_t<List, FilterOp, TypeList<>>;
};
template <typename List, template <typename> class Op>
using Filter_t = typename Filter<List, Op>::type;

// Reverse
template <typename List>
using Reverse = Accumulate<List, PushFront, TypeList<>>;

template <typename List>
using Reverse_t = typename Reverse<List>::type;

// PushBack
template <typename List, typename T>
using PushBack = Reverse<PushFront_t<Reverse_t<List>, T>>;
template <typename List, typename T>
using PushBack_t = typename PushBack<List, T>::type;

// Concat
template <typename List0, typename List1>
using Concat = Accumulate<Reverse_t<List0>, PushFront, List1>;

template <typename List0, typename List1>
using Concat_t = typename Concat<List0, List1>::type;

// ConcatR
template <typename List0, typename List1>
struct ConcatR;

template <typename List0>
struct ConcatR<List0, TypeList<>> {
  using type = List0;
};

template <typename List0, typename Head, typename... Tail>
struct ConcatR<List0, TypeList<Head, Tail...>>
    : ConcatR<PushFront_t<List0, Head>, TypeList<Tail...>> {};

template <typename List0, typename List1>
using ConcatR_t = typename ConcatR<List0, List1>::type;

// Transform
template <typename List, template <typename T> class Op>
struct Transform;

template <template <typename T> class Op, typename... Ts>
struct Transform<TypeList<Ts...>, Op> {
  using type = TypeList<typename Op<Ts>::type...>;
};

template <typename List, template <typename> class Op>
using Transform_t = typename Transform<List, Op>::type;

// Select
template <typename List, size_t... Indices>
struct Select {
  using type = TypeList<At_t<List, Indices>...>;
};

template <typename List, size_t... Indices>
using Select_t = typename Select<List, Indices...>::type;

// Contain
template <typename List, typename T, bool found = false,
          bool = IsEmpty<List>::value>
struct ContainRec;

template <typename List, typename T>
struct ContainRec<List, T, false, true> {
  static constexpr bool value = false;
};

template <typename List, typename T, bool isEmpty>
struct ContainRec<List, T, true, isEmpty> {
  static constexpr bool value = true;
};

template <typename List, typename T>
struct ContainRec<List, T, false, false>
    : ContainRec<PopFront_t<List>, T, std::is_same<Front_t<List>, T>::value> {};

template <typename List, typename T>
using Contain = ContainRec<List, T>;

template <typename List, typename T>
constexpr bool Contain_v = Contain<List, T>::value;

// ContainList
template <typename List0, typename List1>
struct ContainList;

template <typename List, typename... Ts>
struct ContainList<List, TypeList<Ts...>>
    : Conjunction<Bool<Contain_v<List, Ts>>...> {};

template <typename List, typename... Ts>
constexpr bool ContainList_v = ContainList<List, Ts...>::type::value;

// IsTypeList
template <typename List>
using IsTypeList = is_instance_of<List, TypeList>;
template <typename List>
constexpr bool IsTypeList_v = IsTypeList<List>::value;

// Instance
template <typename List, template <typename...> class T>
struct Instance;

template <template <typename...> class T, typename... Args>
struct Instance<TypeList<Args...>, T> {
  using type = T<Args...>;
};
template <typename List, template <typename...> class T>
using Instance_t = typename Instance<List, T>::type;

// is_instantiable
template <typename List, template <typename...> class T>
struct CanInstantiate;

template <template <typename...> class T, typename... Args>
struct CanInstantiate<TypeList<Args...>, T> : is_instantiable<T, Args...> {};
template <typename List, template <typename...> class T>
constexpr bool CanInstantiate_v = CanInstantiate<List, T>::value;

// is_same_template
template <template <typename...> class T, template <typename...> class U,
          typename List>
struct IsSameTemplate;

template <template <typename...> class T, template <typename...> class U,
          typename... Args>
struct IsSameTemplate<T, U, TypeList<Args...>>
    : is_same_template<T, U, Args...> {};
template <template <typename...> class T, template <typename...> class U,
          typename List>
constexpr bool IsSameTemplate_v = IsSameTemplate<T, U, List>::value;

// ExistInstance
template <typename List, template <typename...> class T, bool found = false,
          bool = IsEmpty<List>::value>
struct ExistInstanceRec;

template <typename List, template <typename...> class T>
struct ExistInstanceRec<List, T, false, true> : std::false_type {};

template <typename List, template <typename...> class T, bool isEmpty>
struct ExistInstanceRec<List, T, true, isEmpty> : std::true_type {};

template <typename List, template <typename...> class T>
struct ExistInstanceRec<List, T, false, false>
    : ExistInstanceRec<PopFront_t<List>, T,
                       is_instance_of_v<Front_t<List>, T>> {};

template <typename List, template <typename...> class T>
using ExistInstance = ExistInstanceRec<List, T>;

template <typename List, template <typename...> class T>
constexpr bool ExistInstance_v = ExistInstance<List, T>::value;

// get first template instantiable type
template <typename List, typename LastT, template <typename...> class T,
          bool found = false, bool = IsEmpty<List>::value>
struct SearchInstanceRec;

template <typename List, typename LastT, template <typename...> class T>
struct SearchInstanceRec<List, LastT, T, false, true> {};  // no 'type'

template <typename List, typename LastT, template <typename...> class T,
          bool isEmpty>
struct SearchInstanceRec<List, LastT, T, true, isEmpty> {
  using type = LastT;
};

template <typename List, typename LastT, template <typename...> class T>
struct SearchInstanceRec<List, LastT, T, false, false>
    : SearchInstanceRec<PopFront_t<List>, Front_t<List>, T,
                        is_instance_of_v<Front_t<List>, T>> {};

template <typename List, template <typename...> class T>
using SearchInstance = SearchInstanceRec<List, void, T>;

template <typename List, template <typename...> class T>
using SearchInstance_t = typename SearchInstance<List, T>::type;

namespace detail {
template <typename List, template <typename X, typename Y> typename Less>
struct QuickSort;

template <template <typename X, typename Y> typename Less>
struct QuickSort<TypeList<>, Less> {
  using type = TypeList<>;
};

template <template <typename X, typename Y> typename Less, typename T>
struct QuickSort<TypeList<T>, Less> {
  using type = TypeList<T>;
};

template <template <typename X, typename Y> typename Less, typename Head,
          typename... Tail>
struct QuickSort<TypeList<Head, Tail...>, Less> {
 private:
  template <typename X>
  struct LessThanHead {
    static constexpr bool value = Less<X, Head>::value;
  };

  template <typename X>
  struct GEThanHead {
    static constexpr bool value = !Less<X, Head>::value;
  };

  using LessList = Filter_t<TypeList<Tail...>, LessThanHead>;
  using GEList = Filter_t<TypeList<Tail...>, GEThanHead>;

 public:
  using type =
      Concat_t<typename QuickSort<LessList, Less>::type,
               PushFront_t<typename QuickSort<GEList, Less>::type, Head>>;
};
}  // namespace detail

template <typename List, template <typename X, typename Y> typename Less>
using QuickSort = detail::QuickSort<List, Less>;
template <typename List, template <typename X, typename Y> typename Less>
using QuickSort_t = typename QuickSort<List, Less>::type;
}  // namespace My

#endif  // TYPE_LIST_HXX
