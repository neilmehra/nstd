#pragma once

#include "type_traits.hpp"
#include <cstddef>
#include <type_traits>

namespace nstd {

template <class T>
constexpr nstd::remove_reference<T>::type&& move(T&& arg) noexcept {
  return static_cast<nstd::remove_reference<T>::type&&>(arg);
}

template <class T>
constexpr T&& forward(typename nstd::remove_reference<T>::type& arg) {
  return static_cast<nstd::identity<T>::type&&>(arg);
}

// see https://stackoverflow.com/questions/38344332/why-does-stdforward-have-two-overloads
template <class T>
constexpr T&& forward(typename nstd::remove_reference<T>::type&& arg) {
  return static_cast<nstd::identity<T>::type&&>(arg);
}

// todo, check noexcept operator on type
template <class T>
constexpr void swap(T& a,
                    T& b) noexcept(std::is_nothrow_move_constructible_v<T> &&
                                   std::is_nothrow_move_assignable_v<T>) {
  T tmp(nstd::move(a));
  a = nstd::move(b);
  b = nstd::move(tmp);
}

template <class T, std::size_t N>
constexpr void
swap(T (&a)[N], T (&b)[N]) noexcept(std::is_nothrow_move_constructible_v<T> &&
                                    std::is_nothrow_move_assignable_v<T>) {
  for (std::size_t i = 0; i < N; i++) {
    nstd::swap(a[i], b[i]);
  }
}

template <class T, class U = T>
constexpr T
exchange(T& obj,
         U&& new_val) noexcept(std::is_nothrow_move_constructible_v<T> &&
                               std::is_nothrow_assignable_v<T&, U>) {
  T old_val = nstd::move(obj);
  obj = nstd::forward<U>(new_val);
  return old_val;
}

} // namespace nstd
