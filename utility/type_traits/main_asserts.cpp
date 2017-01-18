#include SPECIFIC_HEADER
#include <utility>

template <class Type> struct always_true : true_type {};
template <class Type> struct always_false : false_type {};

template <class Type> constexpr Type test_enable_if(Type&& t, typename enable_if<always_true<Type>::value>::type* /*pt*/ = nullptr) { return std::forward<Type>(t); }
template <class Type> constexpr Type test_enable_if(Type&& /*t*/, typename enable_if<always_false<Type>::value>::type* /*pt*/ = nullptr) { return Type(); }

template <class Type> constexpr Type test_enable_if_t(Type&& t, enable_if_t<always_true<Type>::value>* /*pt*/ = nullptr) { return std::forward<Type>(t); }
template <class Type> constexpr Type test_enable_if_t(Type&& /*t*/, enable_if_t<always_false<Type>::value>* /*pt*/ = nullptr) { return Type(); }

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
  static_assert(is_void<void>::value, "");
  static_assert(is_void<const void>::value, "");
  static_assert(is_void<volatile void>::value, "");
  static_assert(is_void<const volatile void>::value, "");
  static_assert(! is_void<bool>::value, "");
  static_assert(! is_void<int>::value, "");
  static_assert(! is_void<A>::value, "");
  
  // is_null_pointer
  static_assert(is_null_pointer<decltype(nullptr)>::value, "");
  static_assert(is_null_pointer<std::nullptr_t>::value, "");
  static_assert(is_null_pointer<const std::nullptr_t>::value, "");
  static_assert(is_null_pointer<volatile std::nullptr_t>::value, "");
  static_assert(is_null_pointer<const volatile std::nullptr_t>::value, "");
  static_assert(! is_null_pointer<void*>::value, "");
  static_assert(! is_null_pointer<int*>::value, "");
  static_assert(! is_null_pointer<A*>::value, "");
  
  // is_pointer
  static_assert(is_pointer<void*>::value, "");
  static_assert(is_pointer<void const * const>::value, "");
  static_assert(is_pointer<void const volatile * const volatile>::value, "");
  static_assert(is_pointer<int*>::value, "");
  static_assert(is_pointer<A*>::value, "");
  static_assert(is_pointer<decltype(&build_A)>::value, "");
  static_assert(! is_pointer<A&>::value, "");
  static_assert(! is_pointer<A[]>::value, "");
  static_assert(! is_pointer<A[10]>::value, "");
  static_assert(! is_pointer<decltype(nullptr)>::value, "");
  static_assert(! is_pointer<decltype(&A::a)>::value, "");
  static_assert(! is_pointer<decltype(&A::getA)>::value, "");
  static_assert(! is_pointer<std::nullptr_t>::value, "");
  
  // is_array
  static_assert(is_array<int[]>::value, "");
  static_assert(is_array<int const * const * const []>::value, "");
  static_assert(is_array<int[5]>::value, "");
  static_assert(is_array<A[]>::value, "");
  static_assert(is_array<A[5]>::value, "");
  static_assert(! is_array<A>::value, "");
  static_assert(! is_array<int>::value, "");
  static_assert(! is_array<int*>::value, "");
  static_assert(! is_array<std::nullptr_t>::value, "");
  
  // is_reference
  static_assert(! is_reference<A>::value, "");
  static_assert(is_reference<A&>::value, "");
  static_assert(is_reference<A const&>::value, "");
  static_assert(is_reference<A&&>::value, "");
  static_assert(! is_reference<int>::value, "");
  static_assert(is_reference<int&>::value, "");
  static_assert(is_reference<int const&>::value, "");
  static_assert(is_reference<int&&>::value, "");
  return 0;
}

