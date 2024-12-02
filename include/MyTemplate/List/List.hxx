//
// Created by Admin on 1/12/2024.
//

#ifndef LIST_HXX
#define LIST_HXX

#include <type_traits>

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

// [ Require ]
template <typename List>
struct FrontT;
template <typename List>
using Front = typename FrontT<List>::type;

template <typename List>
struct PopFrontT;
template <typename List>
using PopFront = typename PopFrontT<List>::type;

/*
* PushFrontT<List, T>
* // PushFront is already declared
* // but it needs definition of PushFrontT<List, T> for impl List
*/

template <typename List>
struct IsEmpty {
  static constexpr bool value = false;
};
template <typename List>
struct Length;

// [ Algorithms ]

// PushFront
template <typename List, typename... Ts>
struct PushFrontT;

template <typename List, typename... Ts>
using PushFront = typename PushFrontT<List, Ts...>::type;

template <typename List, typename T>
using PushAFrontT = PushFrontT<List, T>;  // push a type at front of list

template <typename List>
struct PushFrontT<List> {
  using type = List;
};

template <typename List, typename THead, typename... TTail>
struct PushFrontT<List, THead, TTail...>
    : PushFrontT<PushFront<List, THead>, TTail...> {};

// Clear
template <typename List, bool = IsEmpty<List>::value>
struct ClearT;

template <typename List>
using Clear = typename ClearT<List>::type;

template <typename List>
struct ClearT<List, false> : ClearT<PopFront<List>> {};

template <typename List>
struct ClearT<List, true> {
  using type = List;
};

// At
template <typename List, size_t N>
struct AtT : AtT<PopFront<List>, N - 1> {};

template <typename List, size_t N>
using At = typename AtT<List, N>::type;

template <typename List>
struct AtT<List, 0> {
  using type = Front<List>;
};

// Accumulate : list
template <typename List, template <typename I, typename X> class Op, typename I,
          bool = IsEmpty<List>::value>
struct AccumulateT;

template <typename List, template <typename I, typename X> class Op, typename I>
using Accumulate = typename AccumulateT<List, Op, I>::type;

template <typename List, template <typename I, typename X> class Op, typename I>
struct AccumulateT<List, Op, I, false>
    : AccumulateT<PopFront<List>, Op, typename Op<I, Front<List>>::type> {};

template <typename List, template <typename X, typename Y> class Op, typename I>
struct AccumulateT<List, Op, I, true> {
  using type = I;
};

// Accumulate : integer sequence
template <typename List,
          template <typename I, typename List, size_t Num> class Op, typename I,
          size_t... Nums>
struct AccumulateIST;

template <typename List,
          template <typename I, typename List, size_t Num> class Op, typename I,
          size_t... Nums>
using AccumulateIS = typename AccumulateIST<List, Op, I, Nums...>::type;

template <typename List,
          template <typename I, typename List, size_t Num> class Op, typename I>
struct AccumulateIST<List, Op, I> {
  using type = I;
};

template <typename List,
          template <typename I, typename List, size_t Num> class Op, typename I,
          size_t NumHead, size_t... NumTail>
struct AccumulateIST<List, Op, I, NumHead, NumTail...>
    : AccumulateIST<List, Op, typename Op<I, List, NumHead>::type, NumTail...> {
};

// Reverse
template <typename List>
using ReverseT = AccumulateT<List, PushAFrontT, Clear<List>>;
template <typename List>
using Reverse = typename ReverseT<List>::type;

// PushBack
template <typename List, typename T>
using PushBackT = ReverseT<PushFront<Reverse<List>, T>>;
template <typename List, typename T>
using PushBack = typename PushBackT<List, T>::type;

// Transform
template <typename List, template <typename T> class Op>
struct TransformT {
 private:
  template <typename I, typename T>
  using ToIT = PushFrontT<I, typename Op<T>::type>;

 public:
  using type = Reverse<Accumulate<List, ToIT, Clear<List>>>;
};

template <typename List, template <typename> class Op>
using Transform = typename TransformT<List, Op>::type;

// Select
template <typename List, size_t... Indices>
struct SelectT {
 private:
  template <typename I, typename List, size_t Index>
  using ToIT = PushFrontT<I, At<List, Index>>;

 public:
  using type = Reverse<AccumulateIS<List, ToIT, Clear<List>, Indices...>>;
};

template <typename List, size_t... Indices>
using Select = typename SelectT<List, Indices...>::type;

// Contains
template <typename List, typename T, bool found = false,
          bool = IsEmpty<List>::value>
struct ContainsRec;

template <typename List, typename T>
struct ContainsRec<List, T, false, true> {
  static constexpr bool value = false;
};

template <typename List, typename T, bool isEmpty>
struct ContainsRec<List, T, true, isEmpty> {
  static constexpr bool value = true;
};

template <typename List, typename T>
struct ContainsRec<List, T, false, false>
    : ContainsRec<PopFront<List>, T, std::is_same<Front<List>, T>::value> {};

template <typename List, typename T>
using Contains = ContainsRec<List, T>;
}  // namespace My

#endif  // LIST_HXX
