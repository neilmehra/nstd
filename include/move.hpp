#pragma once

#include "type_traits.hpp"
#include <cstddef>

// 20.2.2, swap
// 20.2.3, exchange
// 20.2.4, forward/move
namespace nstd {

// 20.2.4, forward/move
// this has to use remove_reference_t<T>, since assume `t` is of type U&. then (U = T&)&& = T& by ref collapsing rules
// using remove_reference_t<T> ensures we will return a type that is an rvalue ref
template <class T>
constexpr nstd::remove_reference_t<T>&& move(T&& t) noexcept {
  return static_cast<nstd::remove_reference_t<T>&&>(t);
}

template <class T>
constexpr conditional_t<!is_nothrow_move_constructible_v<T> &&
                            is_copy_constructible_v<T>,
                        const T&, T&&>
move_if_noexcept(T& x) noexcept {
  return nstd::move(x);
}

// 20.2.2, swap
template <class T>
constexpr void swap(T& a,
                    T& b) noexcept(std::is_nothrow_move_assignable_v<T> &&
                                   std::is_nothrow_move_constructible_v<T>) {
  T tmp = nstd::move(a);
  a = nstd::move(b);
  b = nstd::move(tmp);
}
template <class T, std::size_t N>
constexpr void swap(T (&a)[N], T (&b)[N]) noexcept(is_nothrow_swappable_v<T>) {
  for (std::size_t i = 0; i < N; i++) {
    nstd::swap(a[i], b[i]);
  }
}

// 20.2.4, forward/move
// https://stackoverflow.com/questions/38344332/why-does-stdforward-have-two-overloads
template <class T> constexpr T&& forward(remove_reference_t<T>& t) noexcept {
  return static_cast<T&&>(t);
}

template <class T> constexpr T&& forward(remove_reference_t<T>&& t) noexcept {
  return static_cast<T&&>(t);
}
// 20.2.3, exchange
template <class T, class U = T> constexpr T exchange(T& obj, U&& new_val) {
  T old_val = nstd::move(obj);
  obj = nstd::forward<U>(new_val);
  return old_val;
};

} // namespace nstd
