#pragma once

#include "move.hpp"
#include "type_traits.hpp"
#include <cstddef>
#include <utility>

namespace nstd {

// forward declarations

template <class T>
constexpr conditional_t<!is_nothrow_move_constructible_v<T> &&
                            is_copy_constructible_v<T>,
                        const T&, T&&>
move_if_noexcept(T& x) noexcept;
// 20.2.5, as_const
template <class T> constexpr add_const_t<T>& as_const(T& t) noexcept;
template <class T> void as_const(const T&&) = delete;
// 20.2.6, declval
template <class T> add_rvalue_reference_t<T> declval() noexcept;
// as unevaluated operand
// 20.3, Compile-time integer sequences
template <class T, T...> struct integer_sequence;
template <size_t... I> using index_sequence = integer_sequence<size_t, I...>;
template <class T, T N> using make_integer_sequence = integer_sequence<T, N>;

template <size_t N>
using make_index_sequence = make_integer_sequence<size_t, N>;
template <class... T>
using index_sequence_for = make_index_sequence<sizeof...(T)>;
// 20.4, class template pair
template <class T1, class T2> struct pair;
// 20.4.3, pair specialized algorithms
template <class T1, class T2>
constexpr void swap(pair<T1, T2>& x,
                    pair<T1, T2>& y) noexcept(noexcept(x.swap(y)));
template <class T1, class T2> constexpr pair<T1, T2> make_pair(T1&&, T2&&);
// 20.4.4, tuple-like access to pair
template <class T> struct tuple_size;
template <size_t I, class T> struct tuple_element;
template <class T1, class T2> struct tuple_size<pair<T1, T2>>;
template <size_t I, class T1, class T2> struct tuple_element<I, pair<T1, T2>>;
template <size_t I, class T1, class T2>
constexpr tuple_element_t<I, pair<T1, T2>>& get(pair<T1, T2>&) noexcept;
template <size_t I, class T1, class T2>
constexpr tuple_element_t<I, pair<T1, T2>>&& get(pair<T1, T2>&&) noexcept;
template <size_t I, class T1, class T2>
constexpr const tuple_element_t<I, pair<T1, T2>>&
get(const pair<T1, T2>&) noexcept;
template <size_t I, class T1, class T2>
constexpr const tuple_element_t<I, pair<T1, T2>>&&
get(const pair<T1, T2>&&) noexcept;
template <class T1, class T2> constexpr T1& get(pair<T1, T2>& p) noexcept;
template <class T1, class T2>
constexpr const T1& get(const pair<T1, T2>& p) noexcept;
template <class T1, class T2> constexpr T1&& get(pair<T1, T2>&& p) noexcept;
template <class T1, class T2>
constexpr const T1&& get(const pair<T1, T2>&& p) noexcept;
template <class T2, class T1> constexpr T2& get(pair<T1, T2>& p) noexcept;
template <class T2, class T1>
constexpr const T2& get(const pair<T1, T2>& p) noexcept;
template <class T2, class T1> constexpr T2&& get(pair<T1, T2>&& p) noexcept;
template <class T2, class T1>
constexpr const T2&& get(const pair<T1, T2>&& p) noexcept;
// 20.4.5, pair piecewise construction
struct piecewise_construct_t {
  explicit piecewise_construct_t() = default;
};
inline constexpr piecewise_construct_t piecewise_construct{};
template <class... Types> class tuple;
// defined in <tuple> (20.5.2)
// in-place construction
struct in_place_t {
  explicit in_place_t() = default;
};
inline constexpr in_place_t in_place{};
template <class T> struct in_place_type_t {
  explicit in_place_type_t() = default;
};
template <class T> inline constexpr in_place_type_t<T> in_place_type{};
template <size_t I> struct in_place_index_t {
  explicit in_place_index_t() = default;
};
template <size_t I> inline constexpr in_place_index_t<I> in_place_index{};

} // namespace nstd
