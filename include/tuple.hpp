#pragma once

#include <cstddef>
namespace nstd {

template <class... Types> class tuple;

// 20.5.3.4 tuple creation functions

// 20.5.3.5

template <class F, class Tuple>
constexpr decltype(auto) apply(F&& f, Tuple&& t);

template <class T, class Tuple> constexpr T make_from_tuple(Tuple&& t);

// 20.5.3.6

template <class T> struct tuple_size;
template <class T> struct tuple_size<const T>;
template <class T> struct tuple_size<volatile T>;
template <class T> struct tuple_size<const volatile T>;

template <std::size_t I, class T> struct tuple_element;
template <std::size_t I, class T> struct tuple_element<I, const T>;
template <std::size_t I, class T> struct tuple_element<I, volatile T>;
template <std::size_t I, class T> struct tuple_element<I, const volatile T>;

template <size_t I, class... Types> struct tuple_element<I, tuple<Types...>>;

template <std::size_t I, class T>
using tuple_element_t = typename tuple_element<I, T>::type;

} // namespace nstd
