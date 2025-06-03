#pragma once

#include "type_traits.hpp"
#include <ostream>
#include <tuple>

namespace nstd {

template <class T> class default_delete {
  using pointer = T*;

  constexpr default_delete() {}

  void operator()(T* p) {
    if (is_array_v<T>) {
      delete[] p;
    } else {
      delete p;
    }
  }
};

namespace detail {

template <class AlwaysVoid, template <class...> class T, class... Args>
struct detector : public false_type {};

template <template <class...> class T, class... Args>
struct detector<void_t<typename T<Args...>::pointer>, T, Args...>
    : public true_type {};

template <template <class...> class T, class... Args>
struct has_pointer_type : public detector<void, T, Args...> {};

template <template <class...> class T, class... Args>
constexpr bool has_pointer_type_v = has_pointer_type<T, Args...>::value;

} // namespace detail

template <class T, class Deleter = default_delete<T>> class unique_ptr {
public:
  using pointer =
      conditional_t<detail::has_pointer_type_v<remove_reference_t, Deleter>,
                    typename remove_reference_t<Deleter>::pointer, T*>;
  using element_type = T;
  using deleter_type = Deleter;

  constexpr unique_ptr(pointer p) noexcept;
  constexpr unique_ptr() noexcept;
  unique_ptr(unique_ptr&) = delete;

  constexpr unique_ptr(unique_ptr&&) noexcept
    requires is_move_constructible_v<T>;

  constexpr ~unique_ptr() noexcept;

  constexpr unique_ptr& operator=(unique_ptr&) = delete;
  constexpr unique_ptr& operator=(unique_ptr&&) noexcept
    requires is_move_assignable_v<T>;

  constexpr void release() noexcept;
  constexpr void reset(pointer p) noexcept;
  constexpr void swap(const unique_ptr&) noexcept;

  [[gnu::always_inline]] [[nodiscard]] constexpr pointer get() const noexcept;

  [[gnu::always_inline]] [[nodiscard]] constexpr Deleter&
  get_deleter() noexcept;
  [[gnu::always_inline]] [[nodiscard]] constexpr Deleter&
  get_deleter() const noexcept;

  [[gnu::always_inline]] [[nodiscard]] explicit operator bool() const noexcept;

  [[gnu::always_inline]] [[nodiscard]] add_lvalue_reference_t<T>
  operator*() const noexcept(noexcept(*declval<pointer>()));
  [[gnu::always_inline]] [[nodiscard]] pointer operator->() const noexcept;

private:
  std::tuple<T, Deleter> obj_;
};

template <class T, class D>
constexpr unique_ptr<T, D>::unique_ptr(pointer p) noexcept : obj_{p, D{}} {}

template <class T, class D>
constexpr unique_ptr<T, D>::unique_ptr() noexcept : obj_{nullptr, D{}} {}

template <class T, class D>
constexpr unique_ptr<T, D>::unique_ptr(unique_ptr&& o) noexcept
  requires is_move_constructible_v<T>
{}

template <class T, class D> constexpr unique_ptr<T, D>::~unique_ptr() noexcept {
  release();
}

template <class T, class D>
constexpr unique_ptr<T, D>&
unique_ptr<T, D>::operator=(unique_ptr<T, D>&& o) noexcept
  requires is_move_assignable_v<T>
{
  if (this != &o) {
    release();
    obj_ = move(o.obj_);
    o.get() = nullptr;
  }
  return *this;
}

template <class T, class D>
constexpr void unique_ptr<T, D>::release() noexcept {
  if (get()) {
    get_deleter()(get());
  }
}

template <class T, class D>
constexpr void unique_ptr<T, D>::reset(pointer p) noexcept {
  release();
  get() = p;
}

template <class T, class D>
constexpr void unique_ptr<T, D>::swap(const unique_ptr<T, D>& o) noexcept {
  swap(obj_, o.obj_);
}

template <class T, class D>
[[gnu::always_inline]] [[nodiscard]] constexpr auto
unique_ptr<T, D>::get() const noexcept -> pointer {
  return std::get<0>(obj_);
}

template <class T, class D>
[[gnu::always_inline]] [[nodiscard]] constexpr D&
unique_ptr<T, D>::get_deleter() noexcept {
  return std::get<1>(obj_);
}

template <class T, class D>
[[gnu::always_inline]] [[nodiscard]] constexpr D&
unique_ptr<T, D>::get_deleter() const noexcept {
  return std::get<1>(obj_);
}

template <class T, class D>
[[nodiscard]] unique_ptr<T, D>::operator bool() const noexcept {
  return get() != nullptr;
}

template <class T, class D>
add_lvalue_reference_t<T> unique_ptr<T, D>::operator*() const
    noexcept(noexcept(*declval<pointer>())) {
  return *get();
}

template <class T, class D>
auto unique_ptr<T, D>::operator->() const noexcept -> pointer {
  return *get();
}

template <class T, class D, class... Args>
unique_ptr<T, D> make_unique(Args&&... args) {
  return unique_ptr<T, D>(new T(forward<Args>(args)...));
}

template <class T1, class D1, class T2, class D2>
bool operator<(const unique_ptr<T1, D1>& x, const unique_ptr<T2, D2>& y) {
  return std::less<common_type_t<typename unique_ptr<T1, D1>::pointer,
                                 typename unique_ptr<T2, D2>::pointer>>()(
      x.get(), y.get());
}

template <class T1, class D1, class T2, class D2>
bool operator==(const unique_ptr<T1, D1>& x, const unique_ptr<T2, D2>& y) {
  return x.get() == y.get();
}

template <class T1, class D1, class T2, class D2>
bool operator<=(const unique_ptr<T1, D1>& x, const unique_ptr<T2, D2>& y) {
  return !(y < x);
}

template <class T1, class D1, class T2, class D2>
bool operator>(const unique_ptr<T1, D1>& x, const unique_ptr<T2, D2>& y) {
  return y < x;
}

template <class T1, class D1, class T2, class D2>
bool operator>=(const unique_ptr<T1, D1>& x, const unique_ptr<T2, D2>& y) {
  return !(x < y);
}

template <class T, class D>
  requires requires(std::ostream& out, unique_ptr<T, D>& p) { out << p.get(); }
std::ostream& operator<<(std::ostream& out, const unique_ptr<T, D>& x) {
  return out << x.get();
}

template <class T, class D>
void swap(unique_ptr<T, D>& lhs, unique_ptr<T, D>& rhs) {
  lhs.swap(rhs);
}

template <class T, class Deleter> class unique_ptr<T[], Deleter> {
public:
  using pointer =
      conditional_t<detail::has_pointer_type_v<remove_reference_t, Deleter>,
                    typename remove_reference_t<Deleter>::pointer, T*>;
  using element_type = T;
  using deleter_type = Deleter;

  constexpr unique_ptr(pointer p) noexcept;
  constexpr unique_ptr() noexcept;
  unique_ptr(unique_ptr&) = delete;

  constexpr unique_ptr(unique_ptr&&) noexcept
    requires is_move_constructible_v<T>;

  constexpr ~unique_ptr() noexcept;

  constexpr unique_ptr& operator=(unique_ptr&) = delete;
  constexpr unique_ptr& operator=(unique_ptr&&) noexcept
    requires is_move_assignable_v<T>;

  constexpr void release() noexcept;
  constexpr void reset(pointer p) noexcept;
  constexpr void swap(const unique_ptr&) noexcept;

  [[gnu::always_inline]] [[nodiscard]] constexpr pointer get() const noexcept;

  [[gnu::always_inline]] [[nodiscard]] constexpr Deleter&
  get_deleter() noexcept;
  [[gnu::always_inline]] [[nodiscard]] constexpr Deleter&
  get_deleter() const noexcept;

  [[gnu::always_inline]] [[nodiscard]] explicit operator bool() const noexcept;
  [[gnu::always_inline]] [[nodiscard]] T& operator[](std::size_t idx) const;

  [[gnu::always_inline]] [[nodiscard]] add_lvalue_reference_t<T>
  operator*() const noexcept(noexcept(*declval<pointer>()));
  [[gnu::always_inline]] [[nodiscard]] pointer operator->() const noexcept;

private:
  std::tuple<T, Deleter> obj_;
};

template <class T, class D>
constexpr unique_ptr<T[], D>::unique_ptr(pointer p) noexcept : obj_{p, D{}} {}

template <class T, class D>
constexpr unique_ptr<T[], D>::unique_ptr() noexcept : obj_{nullptr, D{}} {}

template <class T, class D>
constexpr unique_ptr<T[], D>::unique_ptr(unique_ptr&& o) noexcept
  requires is_move_constructible_v<T>
{}

template <class T, class D>
constexpr unique_ptr<T[], D>::~unique_ptr() noexcept {
  release();
}

template <class T, class D>
constexpr unique_ptr<T[], D>&
unique_ptr<T[], D>::operator=(unique_ptr<T[], D>&& o) noexcept
  requires is_move_assignable_v<T>
{
  if (this != &o) {
    release();
    obj_ = move(o.obj_);
    o.get() = nullptr;
  }
  return *this;
}

template <class T, class D>
constexpr void unique_ptr<T[], D>::release() noexcept {
  if (get()) {
    get_deleter()(get());
  }
}

template <class T, class D>
constexpr void unique_ptr<T[], D>::reset(pointer p) noexcept {
  release();
  get() = p;
}

template <class T, class D>
constexpr void unique_ptr<T[], D>::swap(const unique_ptr<T[], D>& o) noexcept {
  swap(obj_, o.obj_);
}

template <class T, class D>
[[gnu::always_inline]] [[nodiscard]] constexpr auto
unique_ptr<T[], D>::get() const noexcept -> pointer {
  return std::get<0>(obj_);
}

template <class T, class D>
[[gnu::always_inline]] [[nodiscard]] constexpr D&
unique_ptr<T[], D>::get_deleter() noexcept {
  return std::get<1>(obj_);
}

template <class T, class D>
[[gnu::always_inline]] [[nodiscard]] constexpr D&
unique_ptr<T[], D>::get_deleter() const noexcept {
  return std::get<1>(obj_);
}

template <class T, class D>
[[nodiscard]] unique_ptr<T[], D>::operator bool() const noexcept {
  return get() != nullptr;
}

template <class T, class D>
add_lvalue_reference_t<T> unique_ptr<T[], D>::operator*() const
    noexcept(noexcept(*declval<pointer>())) {
  return *get();
}

template <class T, class D>
auto unique_ptr<T[], D>::operator->() const noexcept -> pointer {
  return *get();
}

template <class T, class D, class... Args>
unique_ptr<T[], D> make_unique(Args&&... args) {
  return unique_ptr<T, D>(new T(forward<Args>(args)...));
}

template <class T1, class D1, class T2, class D2>
bool operator<(const unique_ptr<T1[], D1>& x, const unique_ptr<T2[], D2>& y) {
  return std::less<common_type_t<typename unique_ptr<T1[], D1>::pointer,
                                 typename unique_ptr<T2[], D2>::pointer>>()(
      x.get(), y.get());
}

template <class T1, class D1, class T2, class D2>
bool operator==(const unique_ptr<T1[], D1>& x, const unique_ptr<T2[], D2>& y) {
  return x.get() == y.get();
}

template <class T1, class D1, class T2, class D2>
bool operator<=(const unique_ptr<T1[], D1>& x, const unique_ptr<T2[], D2>& y) {
  return !(y < x);
}

template <class T1, class D1, class T2, class D2>
bool operator>(const unique_ptr<T1[], D1>& x, const unique_ptr<T2[], D2>& y) {
  return y < x;
}

template <class T1, class D1, class T2, class D2>
bool operator>=(const unique_ptr<T1[], D1>& x, const unique_ptr<T2[], D2>& y) {
  return !(x < y);
}

template <class T, class D>
  requires requires(std::ostream& out, unique_ptr<T[], D>& p) {
    out << p.get();
  }
std::ostream& operator<<(std::ostream& out, const unique_ptr<T, D>& x) {
  return out << x.get();
}

template <class T, class D>
void swap(unique_ptr<T[], D>& lhs, unique_ptr<T[], D>& rhs) {
  lhs.swap(rhs);
}

} // namespace nstd
