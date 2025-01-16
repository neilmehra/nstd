#pragma once

namespace nstd {
// this is GCC impl, see if clang has same intrinsic function for declval?
template <typename T> auto declval() noexcept -> decltype(__declval<T>(0)) {
  static_assert(false, "declval() must not be used!");
  return __declval<T>(0);
}
} // namespace nstd
