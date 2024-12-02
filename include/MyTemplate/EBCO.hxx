//
// Created by Admin on 2/12/2024.
//

#ifndef EBCO_HXX
#define EBCO_HXX

namespace My {
struct EBCONil {};

template <template <typename> class... Classes>
struct EBCO;

template <template <typename> class Class>
struct EBCO<Class> {
  template <typename Base>
  using type = Class<Base>;
};

template <template <typename> class ClassHead,
          template <typename> class... ClassTail>
struct EBCO<ClassHead, ClassTail...> {
  template <typename Base>
  using type = ClassHead<typename EBCO<ClassTail...>::template type<Base>>;
};

template <template <typename, typename...> class... Interfaces>
struct EBCOI;

template <template <typename, typename...> class Interface>
struct EBCOI<Interface> {
  template <typename Base, typename... Args>
  using type = Interface<Base, Args...>;
};

template <template <typename, typename...> class InterfaceHead,
          template <typename, typename...> class... InterfaceTail>
struct EBCOI<InterfaceHead, InterfaceTail...> {
  template <typename Base, typename... Args>
  using type = InterfaceHead<
      typename EBCOI<InterfaceTail...>::template type<Base, Args...>, Args...>;
};
}  // namespace My

#endif  // EBCO_HXX
