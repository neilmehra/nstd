#pragma once

namespace nstd {

template <class T, T u> struct integral_constant {
  using type = T;
  constexpr static T value = u;

  constexpr operator T() const { return value; }

  constexpr T operator()() const noexcept { return value; }
};

template <bool b> using bool_constant = integral_constant<bool, b>;

using true_type = bool_constant<true>;
using false_type = bool_constant<false>;

template <class T> struct is_reference : public false_type {};

template <class T> struct is_reference<T&> : public true_type {};

template <class T> struct is_reference<T&&> : public true_type {};

template <class T> struct is_lvalue_reference : public false_type {};

template <class T> struct is_lvalue_reference<T&> : public true_type {};

template <class T> struct is_rvalue_reference : public false_type {};

template <class T> struct is_rvalue_reference<T&&> : public true_type {};

template <class T, class U> struct is_same : public false_type {};

template <class T> struct is_same<T, T> : public true_type {};

template <class T> using is_void = is_same<T, void>;

template <class T> struct is_const : public false_type {};

template <class T> struct is_const<const T> : public true_type {};

template <class T> struct is_volatile : public false_type {};

template <class T> struct is_volatile<volatile T> : public true_type {};

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

} // namespace nstd
