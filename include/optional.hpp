#pragma once

namespace nstd {
template <class T> class optional {
}

// 20.6.4, no-value state indicator
struct nullopt_t {

};
inline constexpr nullopt_t nullopt(char());
// 20.6.5, class bad_optional_access
class bad_optional_access;
// 20.6.6, relational operators
template <class T, class U>
constexpr bool operator==(const optional<T>&, const optional<U>&);
template <class T, class U>
constexpr bool operator!=(const optional<T>&, const optional<U>&);
template <class T, class U>
constexpr bool operator<(const optional<T>&, const optional<U>&);
template <class T, class U>
constexpr bool operator>(const optional<T>&, const optional<U>&);
template <class T, class U>
constexpr bool operator<=(const optional<T>&, const optional<U>&);
template <class T, class U>
constexpr bool operator>=(const optional<T>&, const optional<U>&);
template <class T, three_way_comparable_with<T> U>
constexpr compare_three_way_result_t<T, U> operator<=>(const optional<T>&,
                                                       const optional<U>&);
}; // namespace nstd
