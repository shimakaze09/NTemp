//
// Created by Admin on 2/12/2024.
//

#ifndef SI_HXX
#define SI_HXX

/*
 * Single Inheritance (SI)
 * Single Inheritance - Template (SIT)
 *
 * [ Usage ]
 * - SI
 *   template<typename Base>
 *   struct Derived : Base {
 *   private:
 *     using VBCs = SIVBCs<typename Base::$VBC-name$, ...>;
 *   public:
 *     using Base::Base;
 *    ...
 *   };
 *   template<typename Base>
 *   class $class-name$ : SI<$base-class-name$, ...>::type<Base> {
 *   private:
 *	   using VBCs = SIVBCs<typename Base::$VBC-name$, ...>;
 *   public:
 *	   using Base::Base;
 *	   ...
 *   }
 */

namespace My {
struct SINil {};

template <typename... VBCs>  // virtual base classes
struct SIVBCs {};

template <template <typename> class... Classes>
struct SI;

template <template <typename> class Class>
struct SI<Class> {
  template <typename Base>
  using type = Class<Base>;
};

template <template <typename> class ClassHead,
          template <typename> class... ClassTail>
struct SI<ClassHead, ClassTail...> {
  template <typename Base>
  using type = ClassHead<typename SI<ClassTail...>::template type<Base>>;
};

template <template <typename, typename...> class... Interfaces>
struct SIT;

template <template <typename, typename...> class Interface>
struct SIT<Interface> {
  template <typename Base, typename... Ts>
  using type = Interface<Base, Ts...>;
};

template <template <typename, typename...> class IHead,
          template <typename, typename...> class... ITail>
struct SIT<IHead, ITail...> {
  template <typename Base, typename... Ts>
  using type = IHead<typename SIT<ITail...>::template type<Base, Ts...>, Ts...>;
};
}  // namespace My

#endif  //SI_HXX
