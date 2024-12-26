#pragma once

#include "../type_traits.hpp"

namespace nstd {

template <class T>
constexpr nstd::remove_reference<T>::type&& move(T&& arg) noexcept {
  return static_cast<nstd::remove_reference<T>::type&&>(arg);
}

template <class T>
constexpr T&& forward(typename nstd::identity<T>::type& arg) {
  return static_cast<nstd::identity<T>::type&&>(arg);
}

template <class T> void swap(T& a, T& b) {
  T tmp(nstd::move(a));
  a = nstd::move(b);
  b = nstd::move(tmp);
}

} // namespace nstd
