#pragma once

#include "type_traits.hpp"

namespace nstd {
// https://stackoverflow.com/questions/64060929/why-does-the-implementation-of-declval-in-libstdc-v3-look-so-complicated
template <class T>
typename nstd::add_rvalue_reference<T>::type declval() noexcept {
  static_assert(false);
}
} // namespace nstd
