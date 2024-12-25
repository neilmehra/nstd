#pragma once

#include "type_traits.hpp"

namespace nstd {

template <class T> 
constexpr nstd::remove_reference<T>::type&& move(T& arg) {
  return static_cast<nstd::remove_reference<T>::type&&>(arg);
}
} // namespace nstd
