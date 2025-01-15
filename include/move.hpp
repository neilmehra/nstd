#pragma once

#include "type_traits.hpp"
#include <cstddef>

// 20.2.2, swap
// 20.2.3, exchange
// 20.2.4, forward/move
namespace nstd {

// 20.2.4, forward/move
// this has to use remove_reference_t<T> because && here is a universal
// forwarding ref. this causes problems when we pass an lvalue, since when we
// static_cast it to an rvalue, reference collapsing will cause it to return as
// an lvalue
template <class T>
constexpr nstd::remove_reference_t<T>&& move(T&& t) noexcept {
  return static_cast<nstd::remove_reference_t<T>&&>(t);
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
  for(std::size_t i = 0; i < N; i++) {
    nstd::swap(a[i], b[i]);
  }
}

// 20.2.4, forward/move
template <class T> constexpr T&& forward(remove_reference_t<T>& t) noexcept {

}

template <class T> constexpr T&& forward(remove_reference_t<T>&& t) noexcept {

}
// 20.2.3, exchange
template <class T, class U = T> constexpr T exchange(T& obj, U&& new_val) {
  T old_val = nstd::move(obj);
  obj = nstd::forward<U>(new_val);
  return old_val;
};

} // namespace nstd
