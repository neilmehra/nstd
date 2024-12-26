#pragma once

#include "type_traits.hpp"
#include "nstd_common.hpp"

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

template <class T> class unique_ptr {
public:
  using value_type = T;

  explicit unique_ptr(T* arg) : _data(arg) {}

  unique_ptr() = default;

  unique_ptr(const unique_ptr&) = delete;

  unique_ptr(unique_ptr&& rhs) noexcept : _data(rhs._data) {
    rhs._data = nullptr;
  }

  unique_ptr operator=(const unique_ptr&) = delete;

  unique_ptr& operator=(unique_ptr&& rhs) noexcept {
    if (_data != rhs._data) {
      _data = rhs._data;
      rhs._data = nullptr;
    }
    return *this;
  }

  ~unique_ptr() noexcept {
    if constexpr (nstd::is_array<T>::value) {
      delete[] this->_data;
    } else {
      delete this->_data;
    }
  }

  nstd::enable_if<!nstd::is_array<T>::value, T&>::type
  operator*() const noexcept {
    return *_data;
  }

  nstd::enable_if<!nstd::is_array<T>::value, T*>::type
  operator->() const noexcept {
    return _data;
  }

  nstd::enable_if<!nstd::is_array<T>::value, typename nstd::remove_array<T>::type&>::type
  operator[](nstd::size_t i) const {
    return _data[i];
  }

  operator bool() const noexcept { return _data != nullptr; }

  T* get() const noexcept { return _data; }

  friend void swap(unique_ptr&, unique_ptr&);

private:
  T* _data;
};

template <class T> void swap(nstd::unique_ptr<T>& a, nstd::unique_ptr<T>& b) {
  nstd::swap(a._data, b._data);
}

template <typename T, typename... Args>
constexpr nstd::unique_ptr<T> make_unique(Args&&... args) {
  return unique_ptr<T>(new T(nstd::forward<Args>(args)...));
}

class A {
public:
  A(int a, int b) : x(a), c(b) {}

  void meow() {}

private:
  int x, c;
};

void test() {
  auto x = nstd::unique_ptr(new A{1, 2});
  auto y = nstd::make_unique<A>(1, 2);
  (*y).meow();
}
} // namespace nstd
