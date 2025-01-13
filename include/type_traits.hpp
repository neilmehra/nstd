#pragma once

#include <cstddef>

namespace nstd {

template <class T> struct identity {
  typedef T type;
};

template <class T, T v> struct integral_constant {
  constexpr static T value = v;
  using value_type = T;
  using type = integral_constant<T, v>;

  constexpr operator value_type() const noexcept { return value; }
  constexpr value_type operator()() const noexcept { return value; }
};

template <bool b> using bool_constant = integral_constant<bool, b>;

using true_type = bool_constant<true>;
using false_type = bool_constant<false>;

template <class T, class U> struct is_same : public false_type {};

template <class T> struct is_same<T, T> : public true_type {};

template <class T> struct is_reference : public false_type {};

template <class T> struct is_reference<T&> : public true_type {};

template <class T> struct is_reference<T&&> : public true_type {};

template <class T> struct is_lvalue_reference : public false_type {};

template <class T> struct is_lvalue_reference<T&> : public true_type {};

template <class T> struct is_rvalue_reference : public false_type {};

template <class T> struct is_rvalue_reference<T&&> : public true_type {};

template <class T> struct is_const : public false_type {};

template <class T> struct is_const<const T> : public true_type {};

template <class T> struct is_volatile : public false_type {};

template <class T> struct is_volatile<volatile T> : public true_type {};

template <class T> struct is_array : public false_type {};

template <class T> struct is_array<T[]> : public true_type {};

template <class T, std::size_t N> struct is_array<T[N]> : public true_type {};

template <class T> struct remove_reference {
  using type = T;
};

template <class T> struct remove_reference<T&> {
  using type = T;
};

template <class T> struct remove_reference<T&&> {
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

template <class T> using remove_cv_t = remove_cv<T>::type;

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

template <class T> struct remove_array {
  using type = T;
};

template <class T> struct remove_array<T[]> {
  using type = T;
};

template <bool b, class T> struct enable_if {};

template <class T> struct enable_if<true, T> {
  using type = T;
};

template <bool B, class T, class F> struct conditional {
  using type = T;
};
template <class T, class F> struct conditional<false, T, F> {
  using type = F;
};

template <class T> struct __is_void_base : public false_type {};
template <> struct __is_void_base<void> : public true_type {};
template <class T> struct is_void : __is_void_base<remove_cv_t<T>> {};

template <class T>
struct is_null_pointer : public is_same<T, std::nullptr_t> {};

template <class T> struct is_integral_base : public false_type {};
template <> struct is_integral_base<bool> : public true_type {};
template <> struct is_integral_base<char> : public true_type {};
template <> struct is_integral_base<char8_t> : public true_type {};
template <> struct is_integral_base<char16_t> : public true_type {};
template <> struct is_integral_base<char32_t> : public true_type {};
template <> struct is_integral_base<wchar_t> : public true_type {};
template <> struct is_integral_base<short> : public true_type {};
template <> struct is_integral_base<unsigned short> : public true_type {};
template <> struct is_integral_base<int> : public true_type {};
template <> struct is_integral_base<long> : public true_type {};
template <> struct is_integral_base<long long> : public true_type {};
template <> struct is_integral_base<unsigned int> : public true_type {};
template <> struct is_integral_base<unsigned long> : public true_type {};
template <> struct is_integral_base<unsigned long long> : public true_type {};
template <class T>
struct is_integral : public is_integral_base<remove_cv_t<T>> {};

template<class T> struct is_floating_point_base : public false_type{};
template<class T> struct is_floating_point_base<float

} // namespace nstd
