#include "move.hpp"
#include "type_traits.hpp"
#include <compare>
#include <exception>
#include <limits>
#include <type_traits>
#include <variant>

namespace nstd {

namespace detail {
template <std::size_t, class...> struct var_index {};

template <std::size_t I, class T1, class... TN>
struct var_index<I, T1, TN...> : public var_index<I - 1, TN...> {};

template <class T1, class... TN> struct var_index<0, T1, TN...> {
  using type = T1;
};

template <std::size_t I, class... TN>
using var_index_t = typename var_index<I, TN...>::type;

template <class, class...>
struct var_find_type : integral_constant<int, std::numeric_limits<int>::min()> {
};

template <class T, class U, class... UN>
struct var_find_type<T, U, UN...>
    : public nstd::integral_constant<int, 1 + var_find_type<T, UN...>::value> {
};

template <class T, class... UN>
struct var_find_type<T, T, UN...> : public nstd::integral_constant<int, 0> {};

template <class T, class... UN>
constexpr int var_find_type_v = var_find_type<T, UN...>::value;

} // namespace detail

struct bad_variant_access : public std::exception {
  bad_variant_access() = default;
  bad_variant_access(const bad_variant_access&) = default;
  ~bad_variant_access() noexcept override = default;
  const char* what() const noexcept override { return "bad variant access"; }
};

template <class... T> class variant {
public:
  constexpr variant() : _index(0) {
    ::new (static_cast<void*>(&buf)) detail::var_index_t<0, T...>{};
  }
  constexpr variant(const variant& rhs) : engaged(rhs.engaged) {
    if (engaged) {
      _index = rhs._index;
      using alt_t = detail::var_index_t<_index, T...>;
      alt_t& rhs_obj = reinterpret_cast<alt_t&>(rhs.buf);
      ::new (static_cast<void*>(&buf)) alt_t(rhs_obj);
    }
  }
  constexpr variant(variant&& rhs) noexcept : engaged(rhs.engaged) {
    if (engaged) {
      _index = rhs._index;
      using alt_t = detail::var_index_t<_index, T...>;
      alt_t& rhs_obj = reinterpret_cast<alt_t&>(rhs.buf);
      ::new (static_cast<void*>(&buf)) alt_t(nstd::move(rhs_obj));
    }
  }

  constexpr variant& operator=(const variant& rhs) {
    if (this != &rhs) {
      using alt_t = detail::var_index_t<_index, T...>;
      if (!rhs.engaged) {
        reinterpret_cast<alt_t&>(rhs.buf).~alt_t();
      } else {
        _index = rhs._index;
        using alt_t = detail::var_index_t<_index, T...>;
        alt_t& rhs_obj = reinterpret_cast<alt_t&>(rhs.buf);
        ::new (static_cast<void*>(&buf)) alt_t(rhs_obj);
      }
    }
    return *this;
  }
  constexpr variant& operator=(variant&& rhs) {
    if (this != &rhs) {
      using alt_t = detail::var_index_t<_index, T...>;
      if (!rhs.engaged) {
        reinterpret_cast<alt_t&>(rhs.buf).~alt_t();
      } else {
        _index = rhs._index;
        using alt_t = detail::var_index_t<_index, T...>;
        alt_t& rhs_obj = reinterpret_cast<alt_t&>(rhs.buf);
        ::new (static_cast<void*>(&buf)) alt_t(nstd::move(rhs_obj));
      }
    }
    return *this;
  }

  constexpr std::size_t index() const noexcept { return _index; }

  constexpr bool valueless_by_exception() const noexcept { return !engaged; }

  ~variant() noexcept {}

private:
  int _index;
  bool engaged;
  std::aligned_union_t<0, T...> buf;
};
} // namespace nstd
