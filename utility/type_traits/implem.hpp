#pragma once
#include <cstddef>

// Type trait constants

struct true_type { static const constexpr bool value = true; };
struct false_type { static const constexpr bool value = false; };

// Type transformations

template <bool b, class Type = void> struct enable_if {};
template <class Type> struct enable_if<true, Type> { using type = Type; };
template <bool b, class Type = void> using enable_if_t = typename enable_if<b,Type>::type;

// Type modifications

template <class Type> struct remove_const { using type = Type; };
template <class Type> struct remove_const<const Type> { using type = Type; };
template <class Type> using remove_const_t = typename remove_const<Type>::type;

template <class Type> struct remove_volatile { using type = Type; };
template <class Type> struct remove_volatile<volatile Type> { using type = Type; };
template <class Type> using remove_volatile_t = typename remove_volatile<Type>::type;

template <class Type> struct remove_cv { using type = remove_volatile_t<remove_const_t<Type>>; };
template <class Type> using remove_cv_t = typename remove_cv<Type>::type;

// Type categories

template <class Type> struct __is_void : false_type {};
template <> struct __is_void<void> : true_type {};
template <class Type> struct is_void : __is_void<remove_cv_t<Type>> {};

template <class Type> struct __is_null_pointer : false_type {};
template <> struct __is_null_pointer<std::nullptr_t> : true_type {};
template <class Type> struct is_null_pointer : __is_null_pointer<remove_cv_t<Type>> {};

template <class Type> struct __is_pointer : false_type {};
template <class Type> struct __is_pointer<Type*> : true_type {};
template <class Type> struct is_pointer : __is_pointer<remove_cv_t<Type>> {};

template <class Type> struct __is_array : false_type {};
template <class Type> struct __is_array<Type[]> : true_type {};
template <class Type, std::size_t NUM> struct __is_array<Type[NUM]> : true_type {};
template <class Type> struct is_array : __is_array<remove_cv_t<Type>> {};

template <class Type> struct __is_reference : false_type {};
template <class Type> struct __is_reference<Type&> : true_type {};
template <class Type> struct __is_reference<Type&&> : true_type {};
template <class Type> struct is_reference : __is_reference<remove_cv_t<Type>> {};

#if ! defined(NO_SUPPORT_CONSTEXPR_CXX14)
  template <class Type> constexpr bool is_void_v = is_void<Type>::value;
  template <class Type> constexpr bool is_null_pointer_v = is_null_pointer<Type>::value;
  template <class Type> constexpr bool is_pointer_v = is_pointer<Type>::value;
  template <class Type> constexpr bool is_array_v = is_array<Type>::value;
  template <class Type> constexpr bool is_reference_v = is_reference<Type>::value;
#endif

