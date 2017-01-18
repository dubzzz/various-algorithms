#include SPECIFIC_HEADER
#include <utility>

template <class Type> struct always_true : true_type {};
template <class Type> struct always_false : false_type {};

template <class Type> constexpr Type test_enable_if(Type&& t, typename enable_if<always_true<Type>::value>::type* /*pt*/ = nullptr) { return std::forward<Type>(t); }
template <class Type> constexpr Type test_enable_if(Type&& t, typename enable_if<always_false<Type>::value>::type* /*pt*/ = nullptr) { return Type(); }

template <class Type> constexpr Type test_enable_if_t(Type&& t, enable_if_t<always_true<Type>::value>* /*pt*/ = nullptr) { return std::forward<Type>(t); }
template <class Type> constexpr Type test_enable_if_t(Type&& t, enable_if_t<always_false<Type>::value>* /*pt*/ = nullptr) { return Type(); }

struct A { int a; int getA() { return a; } };
struct B : A {};
struct C : A {};
struct D : B, C {};
struct E {};

A build_A() { return A(); }

int main()
{
  // true_type/false_type
  static_assert(true_type::value, "Value of true_type is true");
  static_assert(! false_type::value, "Value of false_type is false");
  
  // enable_if
  static_assert(test_enable_if(true), "Only the method with enable_if<true>::type should be enabled");
  static_assert(test_enable_if_t(true), "Only the method with enable_if_t<true> should be enabled");
  
  // is_void
  static_assert(is_void_v<void>, "");
  static_assert(is_void_v<const void>, "");
  static_assert(is_void_v<volatile void>, "");
  static_assert(is_void_v<const volatile void>, "");
  static_assert(! is_void_v<bool>, "");
  static_assert(! is_void_v<int>, "");
  static_assert(! is_void_v<A>, "");
  
  // is_null_pointer
  static_assert(is_null_pointer_v<decltype(nullptr)>, "");
  static_assert(is_null_pointer_v<std::nullptr_t>, "");
  static_assert(is_null_pointer_v<const std::nullptr_t>, "");
  static_assert(is_null_pointer_v<volatile std::nullptr_t>, "");
  static_assert(is_null_pointer_v<const volatile std::nullptr_t>, "");
  static_assert(! is_null_pointer_v<void*>, "");
  static_assert(! is_null_pointer_v<int*>, "");
  static_assert(! is_null_pointer_v<A*>, "");
  
  // is_pointer
  static_assert(is_pointer_v<void*>, "");
  static_assert(is_pointer_v<void const * const>, "");
  static_assert(is_pointer_v<void const volatile * const volatile>, "");
  static_assert(is_pointer_v<int*>, "");
  static_assert(is_pointer_v<A*>, "");
  static_assert(is_pointer_v<decltype(&build_A)>, "");
  static_assert(! is_pointer_v<A&>, "");
  static_assert(! is_pointer_v<A[]>, "");
  static_assert(! is_pointer_v<A[10]>, "");
  static_assert(! is_pointer_v<decltype(nullptr)>, "");
  static_assert(! is_pointer_v<decltype(&A::a)>, "");
  static_assert(! is_pointer_v<decltype(&A::getA)>, "");
  static_assert(! is_pointer_v<std::nullptr_t>, "");
  
  // is_array
  static_assert(is_array_v<int[]>, "");
  static_assert(is_array_v<int const * const * const []>, "");
  static_assert(is_array_v<int[5]>, "");
  static_assert(is_array_v<A[]>, "");
  static_assert(is_array_v<A[5]>, "");
  static_assert(! is_array_v<A>, "");
  static_assert(! is_array_v<int>, "");
  static_assert(! is_array_v<int*>, "");
  static_assert(! is_array_v<std::nullptr_t>, "");
  
  // is_reference
  static_assert(! is_reference_v<A>, "");
  static_assert(is_reference_v<A&>, "");
  static_assert(is_reference_v<A const&>, "");
  static_assert(is_reference_v<A&&>, "");
  static_assert(! is_reference_v<int>, "");
  static_assert(is_reference_v<int&>, "");
  static_assert(is_reference_v<int const&>, "");
  static_assert(is_reference_v<int&&>, "");
  return 0;
}

