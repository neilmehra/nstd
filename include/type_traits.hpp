#pragma once

#include "declval.hpp"
#include <cstddef>
#include <type_traits>

namespace nstd {

// 20.15.3, Helper Types

template <class T, T v> struct integral_constant {
  constexpr static T value = v;
  using value_type = T;
  using type = integral_constant<T, v>;

  constexpr operator value_type() const noexcept { return value; }
  constexpr value_type operator()() const noexcept { return value; }
};

template <bool B> using bool_constant = integral_constant<bool, B>;
using true_type = bool_constant<true>;
using false_type = bool_constant<false>;

// helper functions for evaluating bool variadic templates with
// checks if T is in Args...
template <bool T, bool... Args> struct _contains;

template <bool T> struct _contains<T> : public false_type {};

template <bool T, bool... Args>
struct _contains<T, T, Args...> : public true_type {};

template <bool T, bool U, bool... Args>
struct _contains<T, U, Args...> : public _contains<T, Args...> {};

template <bool T, bool... Args>
constexpr bool _contains_v = _contains<T, Args...>::value;

// checks if true_type is in Args
template <bool... Args> struct _or : public _contains<true, Args...> {};

template <bool... Args> constexpr bool _or_v = _or<Args...>::value;

// checks if T = all of Args...
template <bool T, bool... Args> struct _all;

template <bool T> struct _all<T> : public true_type {};

template <bool T, bool... Args>
struct _all<T, T, Args...> : public _all<T, Args...> {};

template <bool T, bool U, bool... Args>
struct _all<T, U, Args...> : public false_type {};

template <bool T, bool... Args> constexpr bool _all_v = _all<T, Args...>::value;

// checks if all of Args is true_type
template <bool... Args> struct _and : public _all<true, Args...> {};

template <bool... Args> constexpr bool _and_v = _and<Args...>::value;

// 20.15.4.1, primary type categories
template <class T> struct is_void;
template <class T> struct is_null_pointer;
template <class T> struct is_integral;
template <class T> struct is_floating_point;
template <class T> struct is_array;
template <class T> struct is_pointer;
template <class T> struct is_lvalue_reference;
template <class T> struct is_rvalue_reference;
template <class T> struct is_member_object_pointer;
template <class T> struct is_member_function_pointer;
template <class T> struct is_enum;
template <class T> struct is_union;
template <class T> struct is_class;
template <class T> struct is_function;
// 20.15.4.2, composite type categories
template <class T> struct is_reference;
template <class T> struct is_arithmetic;
template <class T> struct is_fundamental;
template <class T> struct is_object;
template <class T> struct is_scalar;
template <class T> struct is_compound;
template <class T> struct is_member_pointer;
// 20.15.4.3, type properties
template <class T> struct is_const;
template <class T> struct is_volatile;
template <class T> struct is_trivial;
template <class T> struct is_trivially_copyable;
template <class T> struct is_standard_layout;
template <class T> struct is_empty;
template <class T> struct is_polymorphic;
template <class T> struct is_abstract;
template <class T> struct is_final;
template <class T> struct is_aggregate;
template <class T> struct is_signed;
template <class T> struct is_unsigned;
template <class T> struct is_bounded_array;
template <class T> struct is_unbounded_array;
template <class T, class... Args> struct is_constructible;
template <class T> struct is_default_constructible;
template <class T> struct is_copy_constructible;
template <class T> struct is_move_constructible;
template <class T, class U> struct is_assignable;
template <class T> struct is_copy_assignable;
template <class T> struct is_move_assignable;
template <class T, class U> struct is_swappable_with;
template <class T> struct is_swappable;
template <class T> struct is_destructible;
template <class T, class... Args> struct is_trivially_constructible;
template <class T> struct is_trivially_default_constructible;
template <class T> struct is_trivially_copy_constructible;
template <class T> struct is_trivially_move_constructible;
template <class T, class U> struct is_trivially_assignable;
template <class T> struct is_trivially_copy_assignable;
template <class T> struct is_trivially_move_assignable;
template <class T> struct is_trivially_destructible;
template <class T, class... Args> struct is_nothrow_constructible;
template <class T> struct is_nothrow_default_constructible;
template <class T> struct is_nothrow_copy_constructible;
template <class T> struct is_nothrow_move_constructible;
template <class T, class U> struct is_nothrow_assignable;
template <class T> struct is_nothrow_copy_assignable;
template <class T> struct is_nothrow_move_assignable;
template <class T, class U> struct is_nothrow_swappable_with;
template <class T> struct is_nothrow_swappable;
template <class T> struct is_nothrow_destructible;
template <class T> struct has_virtual_destructor;
template <class T> struct has_unique_object_representations;
// 20.15.5, type property queries
template <class T> struct alignment_of;
template <class T> struct rank;
template <class T, unsigned I = 0> struct extent;
// 20.15.6, type relations
template <class T, class U> struct is_same;
template <class Base, class Derived> struct is_base_of;
template <class From, class To> struct is_convertible;
template <class From, class To> struct is_nothrow_convertible;
template <class T, class U> struct is_layout_compatible;
template <class Base, class Derived> struct is_pointer_interconvertible_base_of;
template <class Fn, class... ArgTypes> struct is_invocable;
template <class R, class Fn, class... ArgTypes> struct is_invocable_r;
template <class Fn, class... ArgTypes> struct is_nothrow_invocable;
template <class R, class Fn, class... ArgTypes> struct is_nothrow_invocable_r;
// 20.15.7.1, const-volatile modifications
template <class T> struct remove_const;
template <class T> struct remove_volatile;
template <class T> struct remove_cv;
template <class T> struct add_const;
template <class T> struct add_volatile;
template <class T> struct add_cv;
template <class T> using remove_const_t = typename remove_const<T>::type;
template <class T> using remove_volatile_t = typename remove_volatile<T>::type;
template <class T> using remove_cv_t = typename remove_cv<T>::type;
template <class T> using add_const_t = typename add_const<T>::type;
template <class T> using add_volatile_t = typename add_volatile<T>::type;
template <class T> using add_cv_t = typename add_cv<T>::type;
// 20.15.7.2, reference modifications
template <class T> struct remove_reference;
template <class T> struct add_lvalue_reference;
template <class T> struct add_rvalue_reference;
template <class T>
using remove_reference_t = typename remove_reference<T>::type;
template <class T>
using add_lvalue_reference_t = typename add_lvalue_reference<T>::type;
template <class T>
using add_rvalue_reference_t = typename add_rvalue_reference<T>::type;
// 20.15.7.3, sign modifications
template <class T> struct make_signed;
template <class T> struct make_unsigned;
template <class T> using make_signed_t = typename make_signed<T>::type;
template <class T> using make_unsigned_t = typename make_unsigned<T>::type;
// 20.15.7.4, array modifications
template <class T> struct remove_extent;
template <class T> struct remove_all_extents;
template <class T> using remove_extent_t = typename remove_extent<T>::type;
template <class T>
using remove_all_extents_t = typename remove_all_extents<T>::type;
// 20.15.7.5, pointer modifications
template <class T> struct remove_pointer;
template <class T> struct add_pointer;
template <class T> using remove_pointer_t = typename remove_pointer<T>::type;
template <class T> using add_pointer_t = typename add_pointer<T>::type;
// 20.15.7.6, other transformations
template <class T> struct type_identity;
// TODO
// template <size_t Len, size_t Align = default - alignment> // see 20.15.7.6
// struct aligned_storage;
template <size_t Len, class... Types> struct aligned_union;
template <class T> struct remove_cvref;
template <class T> struct decay;
template <bool, class T = void> struct enable_if;
template <bool, class T, class F> struct conditional;
template <class... T> struct common_type;
template <class T, class U, template <class> class TQual,
          template <class> class UQual>
struct basic_common_reference {};
template <class... T> struct common_reference;
template <class T> struct underlying_type;
template <class Fn, class... ArgTypes> struct invoke_result;
template <class T> struct unwrap_reference;
template <class T> struct unwrap_ref_decay;
template <class T> using type_identity_t = typename type_identity<T>::type;
// TODO
// template <size_t Len, size_t Align = default - alignment> // see 20.15.7.6
// using aligned_storage_t = typename aligned_storage<Len, Align>::type;
template <size_t Len, class... Types>
using aligned_union_t = typename aligned_union<Len, Types...>::type;
template <class T> using remove_cvref_t = typename remove_cvref<T>::type;
template <class T> using decay_t = typename decay<T>::type;
template <bool b, class T = void>
using enable_if_t = typename enable_if<b, T>::type;
template <bool b, class T, class F>
using conditional_t = typename conditional<b, T, F>::type;
template <class... T> using common_type_t = typename common_type<T...>::type;
template <class... T>
using common_reference_t = typename common_reference<T...>::type;
template <class T> using underlying_type_t = typename underlying_type<T>::type;
template <class Fn, class... ArgTypes>
using invoke_result_t = typename invoke_result<Fn, ArgTypes...>::type;
template <class T>
using unwrap_reference_t = typename unwrap_reference<T>::type;
template <class T>
using unwrap_ref_decay_t = typename unwrap_ref_decay<T>::type;
template <class...> using void_t = void;
// 20.15.8, logical operator traits
template <class... B> struct conjunction;
template <class... B> struct disjunction;
template <class B> struct negation;
// 20.15.4.1, primary type categories
template <class T> inline constexpr bool is_void_v = is_void<T>::value;
template <class T>
inline constexpr bool is_null_pointer_v = is_null_pointer<T>::value;
template <class T> inline constexpr bool is_integral_v = is_integral<T>::value;
template <class T>
inline constexpr bool is_floating_point_v = is_floating_point<T>::value;
template <class T> inline constexpr bool is_array_v = is_array<T>::value;
template <class T> inline constexpr bool is_pointer_v = is_pointer<T>::value;
template <class T>
inline constexpr bool is_lvalue_reference_v = is_lvalue_reference<T>::value;
template <class T>
inline constexpr bool is_rvalue_reference_v = is_rvalue_reference<T>::value;
template <class T>
inline constexpr bool is_member_object_pointer_v =
    is_member_object_pointer<T>::value;
template <class T>
inline constexpr bool is_member_function_pointer_v =
    is_member_function_pointer<T>::value;
template <class T> inline constexpr bool is_enum_v = is_enum<T>::value;
template <class T> inline constexpr bool is_union_v = is_union<T>::value;
template <class T> inline constexpr bool is_class_v = is_class<T>::value;
template <class T> inline constexpr bool is_function_v = is_function<T>::value;
// 20.15.4.2, composite type categories
template <class T>
inline constexpr bool is_reference_v = is_reference<T>::value;
template <class T>
inline constexpr bool is_arithmetic_v = is_arithmetic<T>::value;
template <class T>
inline constexpr bool is_fundamental_v = is_fundamental<T>::value;
template <class T> inline constexpr bool is_object_v = is_object<T>::value;
template <class T> inline constexpr bool is_scalar_v = is_scalar<T>::value;
template <class T> inline constexpr bool is_compound_v = is_compound<T>::value;
template <class T>
inline constexpr bool is_member_pointer_v = is_member_pointer<T>::value;
// 20.15.4.3, type properties
template <class T> inline constexpr bool is_const_v = is_const<T>::value;
template <class T> inline constexpr bool is_volatile_v = is_volatile<T>::value;
template <class T> inline constexpr bool is_trivial_v = is_trivial<T>::value;
template <class T>
inline constexpr bool is_trivially_copyable_v = is_trivially_copyable<T>::value;
template <class T>
inline constexpr bool is_standard_layout_v = is_standard_layout<T>::value;
template <class T> inline constexpr bool is_empty_v = is_empty<T>::value;
template <class T>
inline constexpr bool is_polymorphic_v = is_polymorphic<T>::value;
template <class T> inline constexpr bool is_abstract_v = is_abstract<T>::value;
template <class T> inline constexpr bool is_final_v = is_final<T>::value;
template <class T>
inline constexpr bool is_aggregate_v = is_aggregate<T>::value;
template <class T> inline constexpr bool is_signed_v = is_signed<T>::value;
template <class T> inline constexpr bool is_unsigned_v = is_unsigned<T>::value;
template <class T>
inline constexpr bool is_bounded_array_v = is_bounded_array<T>::value;
template <class T>
inline constexpr bool is_unbounded_array_v = is_unbounded_array<T>::value;
template <class T, class... Args>
inline constexpr bool is_constructible_v = is_constructible<T, Args...>::value;
template <class T>
inline constexpr bool is_default_constructible_v =
    is_default_constructible<T>::value;
template <class T>
inline constexpr bool is_copy_constructible_v = is_copy_constructible<T>::value;
template <class T>
inline constexpr bool is_move_constructible_v = is_move_constructible<T>::value;
template <class T, class U>
inline constexpr bool is_assignable_v = is_assignable<T, U>::value;
template <class T>
inline constexpr bool is_copy_assignable_v = is_copy_assignable<T>::value;
template <class T>
inline constexpr bool is_move_assignable_v = is_move_assignable<T>::value;
template <class T, class U>
inline constexpr bool is_swappable_with_v = is_swappable_with<T, U>::value;
template <class T>
inline constexpr bool is_swappable_v = is_swappable<T>::value;
template <class T>
inline constexpr bool is_destructible_v = is_destructible<T>::value;
template <class T, class... Args>
inline constexpr bool is_trivially_constructible_v =
    is_trivially_constructible<T, Args...>::value;
template <class T>
inline constexpr bool is_trivially_default_constructible_v =
    is_trivially_default_constructible<T>::value;
template <class T>
inline constexpr bool is_trivially_copy_constructible_v =
    is_trivially_copy_constructible<T>::value;
template <class T>
inline constexpr bool is_trivially_move_constructible_v =
    is_trivially_move_constructible<T>::value;
template <class T, class U>
inline constexpr bool is_trivially_assignable_v =
    is_trivially_assignable<T, U>::value;
template <class T>
inline constexpr bool is_trivially_copy_assignable_v =
    is_trivially_copy_assignable<T>::value;
template <class T>
inline constexpr bool is_trivially_move_assignable_v =
    is_trivially_move_assignable<T>::value;
template <class T>
inline constexpr bool is_trivially_destructible_v =
    is_trivially_destructible<T>::value;
template <class T, class... Args>
inline constexpr bool is_nothrow_constructible_v =
    is_nothrow_constructible<T, Args...>::value;
template <class T>
inline constexpr bool is_nothrow_default_constructible_v =
    is_nothrow_default_constructible<T>::value;
template <class T>
inline constexpr bool is_nothrow_copy_constructible_v =
    is_nothrow_copy_constructible<T>::value;
template <class T>
inline constexpr bool is_nothrow_move_constructible_v =
    is_nothrow_move_constructible<T>::value;
template <class T, class U>
inline constexpr bool is_nothrow_assignable_v =
    is_nothrow_assignable<T, U>::value;
template <class T>
inline constexpr bool is_nothrow_copy_assignable_v =
    is_nothrow_copy_assignable<T>::value;
template <class T>
inline constexpr bool is_nothrow_move_assignable_v =
    is_nothrow_move_assignable<T>::value;
template <class T, class U>
inline constexpr bool is_nothrow_swappable_with_v =
    is_nothrow_swappable_with<T, U>::value;
template <class T>
inline constexpr bool is_nothrow_swappable_v = is_nothrow_swappable<T>::value;
template <class T>
inline constexpr bool is_nothrow_destructible_v =
    is_nothrow_destructible<T>::value;
template <class T>
inline constexpr bool has_virtual_destructor_v =
    has_virtual_destructor<T>::value;
template <class T>
inline constexpr bool has_unique_object_representations_v =
    has_unique_object_representations<T>::value;
// 20.15.5, type property queries
template <class T>
inline constexpr size_t alignment_of_v = alignment_of<T>::value;
template <class T> inline constexpr size_t rank_v = rank<T>::value;
template <class T, unsigned I = 0>
inline constexpr size_t extent_v = extent<T, I>::value;
// 20.15.6, type relations
template <class T, class U>
inline constexpr bool is_same_v = is_same<T, U>::value;
template <class Base, class Derived>
inline constexpr bool is_base_of_v = is_base_of<Base, Derived>::value;
template <class From, class To>
inline constexpr bool is_convertible_v = is_convertible<From, To>::value;
template <class From, class To>
inline constexpr bool is_nothrow_convertible_v =
    is_nothrow_convertible<From, To>::value;
template <class T, class U>
inline constexpr bool is_layout_compatible_v =
    is_layout_compatible<T, U>::value;
template <class Base, class Derived>
inline constexpr bool is_pointer_interconvertible_base_of_v =
    is_pointer_interconvertible_base_of<Base, Derived>::value;
template <class Fn, class... ArgTypes>
inline constexpr bool is_invocable_v = is_invocable<Fn, ArgTypes...>::value;
template <class R, class Fn, class... ArgTypes>
inline constexpr bool is_invocable_r_v =
    is_invocable_r<R, Fn, ArgTypes...>::value;
template <class Fn, class... ArgTypes>
inline constexpr bool is_nothrow_invocable_v =
    is_nothrow_invocable<Fn, ArgTypes...>::value;
template <class R, class Fn, class... ArgTypes>
inline constexpr bool is_nothrow_invocable_r_v =
    is_nothrow_invocable_r<R, Fn, ArgTypes...>::value;

// 20.15.8, logical operator traits
template <class... B>
inline constexpr bool conjunction_v = conjunction<B...>::value;
template <class... B>
inline constexpr bool disjunction_v = disjunction<B...>::value;
template <class B> inline constexpr bool negation_v = negation<B>::value;
// 20.15.9, member relationships
template <class S, class M>
constexpr bool is_pointer_interconvertible_with_class(M S::* m) noexcept;
template <class S1, class S2, class M1, class M2>
constexpr bool is_corresponding_member(M1 S1::* m1, M2 S2::* m2) noexcept;
// 20.15.10, constant evaluation context
constexpr bool is_constant_evaluated() noexcept;

//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
// forward declarations
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
// definitions start here
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//

// 20.15.4.1, primary type categories
// is_void
template <class T> struct is_void_base : public false_type {};
template <> struct is_void_base<void> : public true_type {};
template <class T> struct is_void : public is_void_base<remove_cv_t<T>> {};

// is_null_pointer
template <class T> struct is_null_pointer_base : public false_type {};
template <> struct is_null_pointer_base<std::nullptr_t> : public true_type {};
template <class T>
struct is_null_pointer : public is_null_pointer_base<remove_cv_t<T>> {};

// is_integral
template <class T> struct is_integral_base : public false_type {};
template <> struct is_integral_base<bool> : public true_type {};
template <> struct is_integral_base<char> : public true_type {};
template <> struct is_integral_base<char8_t> : public true_type {};
template <> struct is_integral_base<char16_t> : public true_type {};
template <> struct is_integral_base<char32_t> : public true_type {};
template <> struct is_integral_base<wchar_t> : public true_type {};
template <> struct is_integral_base<short> : public true_type {};
template <> struct is_integral_base<int> : public true_type {};
template <> struct is_integral_base<long> : public true_type {};
template <> struct is_integral_base<long long> : public true_type {};
template <> struct is_integral_base<signed char> : public true_type {};
template <> struct is_integral_base<unsigned char> : public true_type {};
template <> struct is_integral_base<unsigned short> : public true_type {};
template <> struct is_integral_base<unsigned int> : public true_type {};
template <> struct is_integral_base<unsigned long> : public true_type {};
template <> struct is_integral_base<unsigned long long> : public true_type {};
template <class T>
struct is_integral : public is_integral_base<remove_cv_t<T>> {};

// is_floating_point
template <class T> struct is_floating_point_base : public false_type {};
template <> struct is_floating_point_base<float> : public true_type {};
template <> struct is_floating_point_base<double> : public true_type {};
template <> struct is_floating_point_base<long double> : public true_type {};
template <class T>
struct is_floating_point : public is_floating_point_base<remove_cv_t<T>> {};

// is_array
template <class T> struct is_array_base : public false_type {};
template <class T> struct is_array_base<T[]> : public true_type {};
template <class T, std::size_t N>
struct is_array_base<T[N]> : public true_type {};
template <class T> struct is_array : public is_array_base<remove_cv_t<T>> {};

// is_pointer
template <class T> struct is_pointer_base : public false_type {};
template <class T> struct is_pointer_base<T*> : public true_type {};
template <class T> struct is_pointer_base<T* const> : public true_type {};
template <class T> struct is_pointer_base<const T*> : public true_type {};
template <class T> struct is_pointer_base<const T* const> : public true_type {};
template <class T>
struct is_pointer : public is_pointer_base<remove_cv_t<T>> {};

// is_lvalue_reference
template <class T> struct is_lvalue_reference : public false_type {};
template <class T> struct is_lvalue_reference<T&> : public true_type {};

// is_rvalue_reference
template <class T> struct is_rvalue_reference : public false_type {};
template <class T> struct is_rvalue_reference<T&&> : public true_type {};

// is_member_object_pointer
template <class T> struct is_member_object_pointer_base : public false_type {};
template <class C, class Ret>
struct is_member_object_pointer_base<Ret C::*>
    : public bool_constant<!is_member_function_pointer_v<Ret C::*>> {};
template <class T>
struct is_member_object_pointer : public is_member_object_pointer_base<T> {};

// is_member_function_pointer

template <class T> struct _remove_fp_qual {
  using type = T;
};

template <class C, class Ret, class... Args>
struct _remove_fp_qual<Ret (C::*)(Args...)> {
  using type = Ret (C::*)(Args...);
};

template <class C, class Ret, class... Args>
struct _remove_fp_qual<Ret (C::*)(Args...) const> {
  using type = Ret (C::*)(Args...);
};

template <class C, class Ret, class... Args>
struct _remove_fp_qual<Ret (C::*)(Args...) const noexcept> {
  using type = Ret (C::*)(Args...);
};

template <class C, class Ret, class... Args>
struct _remove_fp_qual<Ret (C::*)(Args...) const&> {
  using type = Ret (C::*)(Args...);
};

template <class C, class Ret, class... Args>
struct _remove_fp_qual<Ret (C::*)(Args...) const&&> {
  using type = Ret (C::*)(Args...);
};

template <class C, class Ret, class... Args>
struct _remove_fp_qual<Ret (C::*)(Args...) const & noexcept> {
  using type = Ret (C::*)(Args...);
};

template <class C, class Ret, class... Args>
struct _remove_fp_qual<Ret (C::*)(Args...) const && noexcept> {
  using type = Ret (C::*)(Args...);
};

template <class C, class Ret, class... Args>
struct _remove_fp_qual<Ret (C::*)(Args...)&> {
  using type = Ret (C::*)(Args...);
};

template <class C, class Ret, class... Args>
struct _remove_fp_qual<Ret (C::*)(Args...) & noexcept> {
  using type = Ret (C::*)(Args...);
};

template <class C, class Ret, class... Args>
struct _remove_fp_qual<Ret (C::*)(Args...) &&> {
  using type = Ret (C::*)(Args...);
};

template <class C, class Ret, class... Args>
struct _remove_fp_qual<Ret (C::*)(Args...) && noexcept> {
  using type = Ret (C::*)(Args...);
};

template <class C, class Ret, class... Args>
struct _remove_fp_qual<Ret (C::*)(Args...) noexcept> {
  using type = Ret (C::*)(Args...);
};

template <class T> using _remove_fp_qual_t = _remove_fp_qual<T>::type;

template <class T>
struct is_member_function_pointer_base : public false_type {};
template <class C, class Ret, class... Args>
struct is_member_function_pointer_base<Ret (C::*)(Args...)> : public true_type {
};
template <class T>
struct is_member_function_pointer
    : public is_member_function_pointer_base<_remove_fp_qual_t<T>> {};

// is_enum
template <class T> struct is_enum : public bool_constant<__is_enum(T)> {};

// is_union
template <class T> struct is_union : public bool_constant<__is_union(T)> {};

// is_class
template <class T> struct is_class : public bool_constant<__is_class(T)> {};

// is_function
// ignores lambdas, `std::function`, function ptrs

template <class T> struct _remove_f_qual {
  using type = T;
};

template <class Ret, class... Args> struct _remove_f_qual<Ret(Args...)> {
  using type = Ret(Args...);
};

template <class Ret, class... Args> struct _remove_f_qual<Ret(Args...) const> {
  using type = Ret(Args...);
};

template <class Ret, class... Args>
struct _remove_f_qual<Ret(Args...) const noexcept> {
  using type = Ret(Args...);
};

template <class Ret, class... Args> struct _remove_f_qual<Ret(Args...) const&> {
  using type = Ret(Args...);
};

template <class Ret, class... Args>
struct _remove_f_qual<Ret(Args...) const&&> {
  using type = Ret(Args...);
};

template <class Ret, class... Args>
struct _remove_f_qual<Ret(Args...) const & noexcept> {
  using type = Ret(Args...);
};

template <class Ret, class... Args>
struct _remove_f_qual<Ret(Args...) const && noexcept> {
  using type = Ret(Args...);
};

template <class Ret, class... Args> struct _remove_f_qual<Ret(Args...)&> {
  using type = Ret(Args...);
};

template <class Ret, class... Args>
struct _remove_f_qual<Ret(Args...) & noexcept> {
  using type = Ret(Args...);
};

template <class Ret, class... Args> struct _remove_f_qual<Ret(Args...) &&> {
  using type = Ret(Args...);
};

template <class Ret, class... Args>
struct _remove_f_qual<Ret(Args...) && noexcept> {
  using type = Ret(Args...);
};

template <class Ret, class... Args>
struct _remove_f_qual<Ret(Args...) noexcept> {
  using type = Ret(Args...);
};

template <class T> using _remove_f_qual_t = _remove_f_qual<T>::type;

template <class T> struct is_function_base : public false_type {};

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wambiguous-ellipsis"

template <class Ret, class... Args>
struct is_function_base<Ret(Args......)> : public true_type {};

#pragma clang diagnostic pop

template <class Ret, class... Args>
struct is_function_base<Ret(Args...)> : public true_type {};

template <class T>
struct is_function
    : public is_function_base<remove_reference_t<_remove_f_qual_t<T>>> {};

// 20.15.4.2, composite type categories
template <class T>
struct is_reference
    : public _or<is_lvalue_reference_v<T>, is_rvalue_reference_v<T>> {};

template <class T>
struct is_arithmetic : public _or<is_integral_v<T>, is_floating_point_v<T>> {};

template <class T>
struct is_fundamental
    : public _or<is_void_v<T>, is_arithmetic_v<T>, is_null_pointer_v<T>> {};

template <class T>
struct is_object
    : public _or<is_scalar_v<T>, is_array_v<T>, is_union_v<T>, is_class_v<T>> {
};
template <class T>
struct is_scalar
    : public _or<is_arithmetic_v<T>, is_null_pointer_v<T>,
                 is_member_pointer_v<T>, is_pointer_v<T>, is_enum_v<T>> {};

template <class T>
struct is_compound
    : public _or<is_member_pointer_v<T>, is_pointer_v<T>, is_enum_v<T>,
                 is_array_v<T>, is_union_v<T>, is_class_v<T>, is_reference_v<T>,
                 is_function_v<T>> {};

template <class T>
struct is_member_pointer : public _or<is_member_object_pointer_v<T>,
                                      is_member_function_pointer_v<T>> {};

// 20.15.4.3, type properties
// is_const
template <class T> struct is_const : public false_type {};
template <class T> struct is_const<const T> : public true_type {};
template <class T> struct is_const<const volatile T> : public true_type {};

// is_volatile
template <class T> struct is_volatile : public false_type {};
template <class T> struct is_volatile<volatile T> : public true_type {};
template <class T> struct is_volatile<const volatile T> : public true_type {};

// type properties w/ compiler extensions
template <class T> struct is_trivial : public bool_constant<__is_trivial(T)> {};
template <class T>
struct is_trivially_copyable
    : public bool_constant<__is_trivially_copyable(T)> {};
template <class T>
struct is_standard_layout : public bool_constant<__is_standard_layout(T)> {};
template <class T> struct is_empty : public bool_constant<__is_empty(T)> {};
template <class T>
struct is_polymorphic : public bool_constant<__is_polymorphic(T)> {};
template <class T>
struct is_abstract : public bool_constant<__is_abstract(T)> {};
template <class T> struct is_final : public bool_constant<__is_final(T)> {};
template <class T>
struct is_aggregate : public bool_constant<__is_aggregate(T)> {};

// is_(un)signed
template <class T>
struct is_signed : public _and<is_arithmetic_v<T>, (T(-1) < T(0))> {};

template <class T>
struct is_unsigned : public _and<is_arithmetic_v<T>, (T(-1) > T(0))> {};

// (un)bounded array
template <class T> struct is_bounded_array : public false_type {};

template <class T, std::size_t N>
struct is_bounded_array<T[N]> : public true_type {};
template <class T> struct is_unbounded_array : public false_type {};
template <class T> struct is_unbounded_array<T[]> : public true_type {};

// Operations

// constructible
template <class, class, class...>
struct is_constructible_base : public false_type {};
template <class T, class... Args>
struct is_constructible_base<void_t<decltype(T(std::declval<Args>()...))>, T,
                             Args...> : public true_type {};

template <class T, class... Args>
struct is_constructible : public is_constructible_base<void, T, Args...> {};
template <class T>
struct is_default_constructible : public is_constructible<T> {};
template <class T>
struct is_copy_constructible
    : public bool_constant<is_constructible_v<T, const T&>> {};
template <class T>
struct is_move_constructible
    : public bool_constant<is_constructible_v<T, T&&>> {};

template <class, class, class = void>
struct is_assignable_base : public false_type {};

template <class T, class U>
struct is_assignable_base<
    T, U, void_t<decltype(std::declval<T>() = std::declval<U>())>>
    : public true_type {};

template <class T, class U>
struct is_assignable : public is_assignable_base<T, U> {};

template <class T>
struct is_copy_assignable : public bool_constant<is_assignable_v<T, const T&>> {
};
template <class T>
struct is_move_assignable : public bool_constant<is_assignable_v<T, T&&>> {};

template <typename, typename, typename = void>
struct is_swappable_base : false_type {};

template <typename T, typename U>
struct is_swappable_base<
    T, U,
    void_t<decltype(std::declval<T&>().swap(std::declval<U&>()),
                    std::declval<U&>().swap(std::declval<T&>()))>> : true_type {
};

template <class T, class U>
struct is_swappable_with : public is_swappable_base<T, U> {};

template <class T> struct is_swappable : public is_swappable_with<T&, T&> {};

// destructor

template <class, class = void>
struct is_destructible_base : public false_type {};

// todo: why std::declval<T&> instead of std::declval<T>?
template <class T>
struct is_destructible_base<T, void_t<decltype(std::declval<T&>().~T())>>
    : public true_type {};

template <class T>
struct is_destructible
    : public _or<nstd::is_reference_v<T>,
                 is_destructible_base<std::remove_all_extents_t<T>>::value> {};

// trivial
template <class T, class... Args>
struct is_trivially_constructible
    : public bool_constant<__is_trivially_constructible(T)> {};
template <class T>
struct is_trivially_default_constructible
    : public bool_constant<is_trivially_constructible_v<T>> {};
template <class T>
struct is_trivially_copy_constructible
    : bool_constant<is_trivially_constructible_v<T, const T&>> {};
template <class T>
struct is_trivially_move_constructible
    : public bool_constant<is_trivially_constructible_v<T, T&&>> {};
template <class T, class U>
struct is_trivially_assignable : public bool_constant<is_assignable_v<T, U>> {};
template <class T>
struct is_trivially_copy_assignable
    : public bool_constant<is_trivially_assignable_v<T&, const T&>> {};
template <class T>
struct is_trivially_move_assignable
    : public bool_constant<is_trivially_assignable_v<T&, T&&>> {};
template <class T>
struct is_trivially_destructible
    : public bool_constant<__is_trivially_destructible(T)> {};

// nothrow
//

template <typename T, typename... Args>
concept nothrow_constructible = requires {
  { T(std::declval<Args>()...) } noexcept;
};

template <class, class, class...>
struct is_nothrow_constructible_base : public false_type {};

template <class T, class... Args>
struct is_nothrow_constructible_base<
    void_t<nstd::enable_if_t<noexcept(T(nstd::declval<Args>()...))>>, T,
    Args...> : public true_type {};

template <class T, class... Args>
struct is_nothrow_constructible
    : public is_nothrow_constructible_base<void, T, Args...> {};

template <class T, class... Args>
constexpr bool isn = is_nothrow_constructible<T, Args...>{};

template <class T>
struct is_nothrow_default_constructible
    : public bool_constant<is_nothrow_constructible_v<T>> {};
template <class T>
struct is_nothrow_copy_constructible
    : public bool_constant<is_nothrow_constructible_v<T, const T&>> {};
template <class T>
struct is_nothrow_move_constructible
    : public bool_constant<is_nothrow_constructible_v<T, T&&>> {};

template <class, class, class = void>
struct is_nothrow_assignable_base : public false_type {};

template <class T, class U>
struct is_nothrow_assignable_base<
    T, U,
    void_t<std::enable_if_t<noexcept(std::declval<T>() = std::declval<U>())>>>
    : public true_type {};

template <class T, class U>
struct is_nothrow_assignable : public is_nothrow_assignable_base<T, U> {};

template <class T>
struct is_nothrow_copy_assignable : public is_nothrow_assignable<T, const T&> {
};
template <class T>
struct is_nothrow_move_assignable : public is_nothrow_assignable<T, T&&> {};

template <typename, typename, typename = void>
struct is_nothrow_swappable_base : false_type {};

template <typename T, typename U>
struct is_nothrow_swappable_base<
    T, U,
    void_t<std::enable_if_t<noexcept(
        std::declval<T&>().swap(std::declval<U&>()),
        std::declval<U&>().swap(std::declval<T&>()))>>> : true_type {};

template <class T, class U>
struct is_nothrow_swappable_with : public is_nothrow_swappable_base<T, U> {};

template <class T>
struct is_nothrow_swappable : public is_nothrow_swappable_with<T&, T&> {};

template <class, class = void>
struct is_nothrow_destructible_base : public false_type {};

template <class T>
struct is_nothrow_destructible_base<
    T, void_t<std::enable_if_t<noexcept(std::declval<T&>().~T())>>>
    : public true_type {};

template <class T>
struct is_nothrow_destructible
    : public _or<
          nstd::is_reference_v<T>,
          is_nothrow_destructible_base<std::remove_all_extents_t<T>>::value> {};

//
template <class T>
struct has_virtual_destructor
    : public bool_constant<__has_virtual_destructor(T)> {};
template <class T>
struct has_unique_object_representations
    : public bool_constant<__has_unique_object_representations(
          std::remove_all_extents_t<T>)> {};

// 20.15.5, type property queries

template <class T>
struct alignment_of : public integral_constant<std::size_t, alignof(T)> {};

template <class T> struct rank : public integral_constant<std::size_t, 0> {};
template <class T>
struct rank<T[]> : public integral_constant<std::size_t, 1 + rank<T>::value> {};
template <class T, std::size_t N>
struct rank<T[N]> : public integral_constant<std::size_t, 1 + rank<T>::value> {
};

template <class T, unsigned I>
struct extent : public integral_constant<std::size_t, 0> {};
template <class T, std::size_t N>
struct extent<T[N], 0> : public integral_constant<std::size_t, N> {};
template <class T, unsigned I, std::size_t N>
struct extent<T[N], I> : extent<T, I - 1> {};
template <class T>
struct extent<T[], 0> : public integral_constant<std::size_t, 0> {};
template <class T, unsigned I>
struct extent<T[], I> : public extent<T, I - 1> {};

// 20.15.6

template <class T, class U> struct is_same : public false_type {};
template <class T> struct is_same<T, T> : public true_type {};

template <class Base> void _base_of_tester(Base* b) {}

template <class, class, class = void>
struct is_base_of_base : public false_type {};
template <class Base, class Derived>
struct is_base_of_base<
    Base, Derived,
    void_t<decltype(_base_of_tester<Base>(static_cast<Derived*>(nullptr)))>>
    : public true_type {};

template <class Base, class Derived>
struct is_base_of : public is_base_of_base<Base, Derived> {};

template <class, class, class = void>
struct is_convertible_base : public false_type {};
template <class From, class To>
struct is_convertible_base<
    From, To,
    void_t<decltype(void(std::declval<void (&)(To)>()(std::declval<From>())))>>
    : public true_type {};

template <class From, class To>
struct is_convertible : public is_convertible_base<From, To> {};

template <class, class, class = void>
struct is_nothrow_convertible_base : public false_type {};
template <class From, class To>
struct is_nothrow_convertible_base<
    From, To,
    void_t<std::enable_if_t<noexcept(
        void(std::declval<void (&)(To) noexcept>()(std::declval<From>())))>>>
    : public true_type {};

template <class From, class To>
struct is_nothrow_convertible : public is_nothrow_convertible_base<From, To> {};

template <class T, class U>
struct is_layout_compatible
    : public bool_constant<__is_layout_compatible(T, U)> {};
template <class Base, class Derived>
struct is_pointer_interconvertible_base_of
    : public bool_constant<__is_pointer_interconvertible_base_of(Base,

                                                                 Derived)> {};

template <class, class, class...>
struct is_invocable_base : public false_type {};
template <class Fn, class... ArgTypes>
struct is_invocable_base<
    void_t<decltype(std::declval<Fn>()(std::declval<ArgTypes>()...))>, Fn,
    ArgTypes...> : true_type {};

template <class Fn, class... ArgTypes>
struct is_invocable : public is_invocable_base<void, Fn, ArgTypes...> {};

// can we invoke Fn(ArgTypes...) and implicitly convert -> R?
template <class, class, class, class...>
struct is_invocable_r_base : public false_type {};
template <class R, class Fn, class... ArgTypes>
struct is_invocable_r_base<
    void_t<std::enable_if_t<_and_v<
        is_invocable_v<Fn, ArgTypes...>,
        is_convertible_v<
            decltype(std::declval<Fn>()(std::declval<ArgTypes>()...)), R>>>>,
    R, Fn, ArgTypes...> : public true_type {};

template <class R, class Fn, class... ArgTypes>
struct is_invocable_r : public is_invocable_r_base<void, R, Fn, ArgTypes...> {};

// can we invoke Fn(ArgTypes...) (noexcept) and implicitly convert -> R?
template <class, class, class, class...>
struct is_nothrow_invocable_r_base : public false_type {};
template <class R, class Fn, class... ArgTypes>
struct is_nothrow_invocable_r_base<
    void_t<std::enable_if_t<
        _and_v<is_nothrow_invocable_v<Fn, ArgTypes...>,
               is_convertible_v<std::enable_if_t<noexcept(std::declval<Fn>()(
                                    std::declval<ArgTypes>()...))>,
                                R>>>>,
    R, Fn, ArgTypes...> : public true_type {};

template <class R, class Fn, class... ArgTypes>
struct is_nothrow_invocable_r
    : public is_nothrow_invocable_r_base<void, R, Fn, ArgTypes...> {};

// 20.15.7.1 cv modification
template <class T> struct remove_const {
  using type = T;
};

template <class T> struct remove_const<const T> {
  using type = T;
};

template <class T> struct remove_volatile {
  using type = T;
};

template <class T> struct remove_volatile<volatile T> {
  using type = T;
};

template <class T> struct remove_cv {
  using type = T;
};

template <class T> struct remove_cv<const T> {
  using type = T;
};

template <class T> struct remove_cv<volatile T> {
  using type = T;
};

template <class T> struct remove_cv<const volatile T> {
  using type = T;
};

template <class T> struct add_const {
  using type = T const;
};

template <class T> struct add_volatile {
  using type = T volatile;
};

template <class T> struct add_cv {
  using type = T const volatile;
};

// 20.15.7.2 reference modification
template <class T> struct remove_reference {
  using type = T;
};

template <class T> struct remove_reference<T&> {
  using type = T;
};

template <class T> struct remove_reference<T&&> {
  using type = T;
};

template <class T> struct add_lvalue_reference {
  using type = T&;
};

template <class T> struct add_rvalue_reference {
  using type = T&&;
};

template <class T> struct make_signed {
  using type = T;
};

// 20.15.7.3 sign modification
template <> struct make_signed<unsigned char> {
  using type = char;
};

template <> struct make_signed<unsigned short> {
  using type = short;
};

template <> struct make_signed<unsigned int> {
  using type = int;
};

template <> struct make_signed<unsigned long> {
  using type = long;
};

template <> struct make_signed<unsigned long long> {
  using type = long long;
};

template <class T> struct make_unsigned {
  using type = T;
};

template <> struct make_unsigned<char> {
  using type = unsigned char;
};

template <> struct make_unsigned<short> {
  using type = unsigned short;
};

template <> struct make_unsigned<int> {
  using type = unsigned int;
};

template <> struct make_unsigned<long> {
  using type = unsigned long;
};

template <> struct make_unsigned<long long> {
  using type = unsigned long long;
};

// 20.15.7.4, array modifications
template <class T> struct remove_extent {
  using type = T;
};

template <class T> struct remove_extent<T[]> {
  using type = T;
};

template <class T, std::size_t N> struct remove_extent<T[N]> {
  using type = T;
};

template <class T> struct remove_all_extents {
  using type = T;
};

template <class T>
struct remove_all_extents<T[]> : public remove_all_extents<T> {};

template <class T, std::size_t N>
struct remove_all_extents<T[N]> : public remove_all_extents<T[]> {};

// 20.15.7.5, pointer modifications
template <class T> struct remove_pointer {
  using type = T;
};

template <class T> struct remove_pointer<T*> {
  using type = T;
};

template <class T> struct add_pointer {
  using type = T*;
};

// 20.15.7.6, other transformations
template <class T> struct type_identity {
  using type = T;
};

// TODO
// template <size_t Len, size_t Align = default - alignment> // see 20.15.7.6
// struct aligned_storage;
// template <size_t Len, class... Types> struct aligned_union;

template <class T> struct remove_cvref {
  using type = remove_cv_t<remove_reference_t<T>>;
};

template <class U> struct decay_base {
  using type = conditional<
      is_array_v<U>, remove_extent_t<U>*,
      conditional<is_function_v<U>, add_pointer_t<U>, remove_cv_t<U>>>;
};

template <class T> struct decay {
  using type = remove_reference_t<T>;
};

template <bool, class T> struct enable_if {};
template <class T> struct enable_if<true, T> {
  using type = T;
};

template <bool, class T, class F> struct conditional {
  using type = F;
};

template <class T, class F> struct conditional<true, T, F> {
  using type = T;
};

template <class...> struct common_type {};
template <class T> struct common_type<T> {
  using type = T;
};

namespace detail {

template <class T1, class T2>
using _common_type_test =
    decltype(false ? std::declval<T1>() : std::declval<T2>());

template <class T1, class T2, class = void> struct _common_type_test_struct {};

template <class T1, class T2>
struct _common_type_test_struct<T1, T2, void_t<_common_type_test<T1, T2>>>
    : public decay<_common_type_test<T1, T2>> {};

template <class T1, class T2, class = void>
struct _common_type_base
    : public _common_type_test_struct<const remove_reference_t<T1>&,
                                      const remove_reference_t<T2>&> {};

template <class T1, class T2>
struct _common_type_base<T1, T2, void_t<_common_type_test<T1, T2>>>
    : public _common_type_test_struct<T1, T2> {};

} // namespace detail

template <class T1, class T2>
struct common_type<T1, T2>
    : public conditional_t<
          _and_v<is_same_v<T1, decay_t<T1>>, is_same_v<T2, decay_t<T2>>>,
          detail::_common_type_base<T1, T2>,
          detail::_common_type_base<decay_t<T1>, decay_t<T2>>> {};

namespace detail {

template <class, class, class, class...> struct _common_type_multi {};
template <class T1, class T2, class... R>
struct _common_type_multi<void_t<typename common_type<T1, T2>::type>, T1, T2,
                          R...> : public common_type<T2, R...> {};

} // namespace detail

template <class T1, class T2, class... R>
struct common_type<T1, T2, R...>
    : public detail::_common_type_multi<void, T1, T2, R...> {};

using a = common_type_t<int, int, int>;

// template <class T, class U, template <class> class TQual,
//           template <class> class UQual>
// struct basic_common_reference {};
// template <class... T> struct common_reference;

template <class T> struct underlying_type {
  using type = __underlying_type(T);
};

template <class Fn, class... ArgTypes>
using invoke_result_tester =
    decltype(std::declval<Fn>()(std::declval<ArgTypes>()...));

template <class, class, class...> struct invoke_result_base {};

template <class Fn, class... ArgTypes>
struct invoke_result_base<void_t<invoke_result_tester<Fn, ArgTypes...>>, Fn,
                          ArgTypes...> {
  using type = invoke_result_tester<Fn, ArgTypes...>;
};

template <class Fn, class... ArgTypes>
struct invoke_result : public invoke_result_base<void, Fn, ArgTypes...> {};

template <class T> struct unwrap_reference {
  using type = T;
};

template <class T> struct unwrap_reference<std::reference_wrapper<T>> {
  using type = T&;
};

template <class T>
struct unwrap_ref_decay : public unwrap_reference_t<decay_t<T>> {};

template <class...> using void_t = void;

// 0 case
template <class... B> struct conjunction : public true_type {};
// 1 case
template <class B1> struct conjunction<B1> : public B1 {};
// 1+n case
template <class B1, class... BN>
struct conjunction<B1, BN...>
    : public conditional_t<bool(B1::value), conjunction<BN...>, B1> {};

// 0 case
template <class... B> struct disjunction : public false_type {};
// 1 case
template <class B1> struct disjunction<B1> : public B1 {};
// 1+n case
template <class B1, class... BN>
struct disjunction<B1, BN...>
    : public conditional_t<bool(B1::value), B1, disjunction<BN...>> {};

template <class B> struct negation : public bool_constant<!bool(B::value)> {};

} // namespace nstd
