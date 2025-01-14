#pragma once

#include <cstddef>
#include <type_traits>

namespace nstd {

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

// 20.15.7.1, const-volatile modifications
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
template <class T> struct add_const {
  using type = const T;
};
template <class T> struct add_volatile {
  using type = volatile T;
};
template <class T> struct add_cv {
  using type = const volatile T;
};

template <class T> using remove_const_t = typename remove_const<T>::type;
template <class T> using remove_volatile_t = typename remove_volatile<T>::type;
template <class T> using remove_cv_t = typename remove_cv<T>::type;
template <class T> using add_const_t = typename add_const<T>::type;
template <class T> using add_volatile_t = typename add_volatile<T>::type;
template <class T> using add_cv_t = typename add_cv<T>::type;

// 20.15.7.2, reference modifications
template <class T> struct remove_reference {
  using type = T;
};
template <class T> struct remove_reference<T&> {
  using type = T;
};
template <class T> struct remove_reference<T&&> {
  using type = T;
};
// note that this is a bit weird. if T is a ref-type, then we follow through with reference collapsing rules rather than it actually being an rvalue ref
// e.g add_rvalue_reference<T&>::type is T&
template <class T> struct add_lvalue_reference {
  using type = T&;
};
template <class T> struct add_rvalue_reference {
  using type = T&&;
};

template <class T>
using remove_reference_t = typename remove_reference<T>::type;
template <class T>
using add_lvalue_reference_t = typename add_lvalue_reference<T>::type;
template <class T>
using add_rvalue_reference_t = typename add_rvalue_reference<T>::type;

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
template <class T, std::size_t N> struct is_array_base<T[N]> : public true_type {};
template <class T> struct is_array : public is_array_base<remove_cv_t<T>> {};

// is_pointer
template <class T> struct is_pointer_base : public false_type {};
template <class T> struct is_pointer_base<T[]> : public true_type {};
template <class T> struct is_pointer : public is_pointer<remove_cv_t<T>> {};
template <class T, std::size_t N> struct is_pointer<T[N]> : true_type {};

template <class T> struct is_lvalue_reference : public false_type {};
template <class T> struct is_lvalue_reference<T&> : public true_type {};

template <class T> struct is_rvalue_reference : public false_type {};
template <class T> struct is_rvalue_reference<T&&> : public true_type {};

template <class T> struct is_member_object_pointer;
template <class T> struct is_member_function_pointer;

template <class T> struct is_enum : public bool_constant<__is_enum(T)> {};
template <class T> struct is_union : public bool_constant<__is_union(T)> {};
template <class T> struct is_class : public bool_constant<__is_class(T)> {};

// is_function

template <class T> struct _remove_f_noexcept {
  using type = T;
};

template <class Ret, class... Args>
struct _remove_f_noexcept<Ret(Args...) noexcept> {
  using type = Ret (*)(Args...);
};

template <class T> struct _remove_f_const {
  using type = T;
};

template <class Ret, class... Args> struct _remove_f_const<Ret(Args...) const> {
  using type = Ret (*)(Args...);
};

template <class T> struct _remove_f_const_noexcept {
  using type = T;
};

template <class Ret, class... Args>
struct _remove_f_const_noexcept<Ret(Args...) const noexcept> {
  using type = Ret (*)(Args...);
};

template <class T> struct is_function_base : public false_type {};

template <class Ret, class... Args>
struct is_function_base<Ret(Args......)> : public true_type {};

template <class Ret, class... Args>
struct is_function_base<Ret(Args...)> : public true_type {};

template <class T>
struct is_function
    : public is_function_base<typename remove_reference<typename remove_cv<
          typename _remove_f_const_noexcept<T>::type>::type>::type> {};

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
template <class T, class U> struct is_same : public false_type {};
template <class T> struct is_same<T, T> : public true_type {};
template <class Base, class Derived> struct is_base_of;
template <class From, class To> struct is_convertible;
template <class From, class To> struct is_nothrow_convertible;
template <class T, class U> struct is_layout_compatible;
template <class Base, class Derived> struct is_pointer_interconvertible_base_of;
template <class Fn, class... ArgTypes> struct is_invocable;
template <class R, class Fn, class... ArgTypes> struct is_invocable_r;
template <class Fn, class... ArgTypes> struct is_nothrow_invocable;
template <class R, class Fn, class... ArgTypes> struct is_nothrow_invocable_r;
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
// template <size_t Len, size_t Align = default - alignment> // see 20.15.7.6
struct aligned_storage;
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
template <class T>
inline constexpr bool is_function_v = is_function_base<T>::value;
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
constexpr bool is_pointer_interconvertible_with_class(M S::*m) noexcept;
template <class S1, class S2, class M1, class M2>
constexpr bool is_corresponding_member(M1 S1::*m1, M2 S2::*m2) noexcept;
// 20.15.10, constant evaluation context
constexpr bool is_constant_evaluated() noexcept;

} // namespace nstd
