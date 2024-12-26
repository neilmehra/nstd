#pragma once

#include "nstd_common.hpp"
#include "type_traits.hpp"
#include <cassert>

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

  explicit unique_ptr(T* arg = nullptr) : _data(arg) {}

  unique_ptr(const unique_ptr&) = delete;
  unique_ptr& operator=(const unique_ptr&) = delete;

  unique_ptr(unique_ptr&& rhs) noexcept : _data(rhs._data) {
    rhs._data = nullptr;
  }

  unique_ptr& operator=(unique_ptr&& rhs) noexcept {
    if (_data != rhs._data) {
      _data = rhs._data;
      rhs._data = nullptr;
    }
    return *this;
  }

  ~unique_ptr() noexcept { delete _data; }

  T& operator*() const noexcept { return *_data; }

  T* operator->() const noexcept { return _data; }

  explicit operator bool() const noexcept { return _data != nullptr; }

  T* get() const noexcept { return _data; }

  template <class U> friend void swap(unique_ptr<U>&, unique_ptr<U>&);

private:
  T* _data;
};

template <class T> class unique_ptr<T[]> {
public:
  using value_type = T;

  explicit unique_ptr(T* arg = nullptr) : _data(arg) {}

  unique_ptr(const unique_ptr&) = delete;
  unique_ptr& operator=(const unique_ptr&) = delete;

  unique_ptr(unique_ptr&& rhs) noexcept : _data(rhs._data) {
    rhs._data = nullptr;
  }

  unique_ptr& operator=(unique_ptr&& rhs) noexcept {
    if (_data != rhs._data) {
      delete[] _data;
      _data = rhs._data;
      rhs._data = nullptr;
    }
    return *this;
  }

  ~unique_ptr() noexcept { delete[] _data; }

  explicit operator bool() const noexcept { return _data != nullptr; }

  T& operator[](nstd::size_t index) const { return _data[index]; }

  T* get() const noexcept { return _data; }

  template <class U> friend void swap(unique_ptr<U>&, unique_ptr<U>&);

private:
  T* _data;
};

template <class T> void swap(nstd::unique_ptr<T>& a, nstd::unique_ptr<T>& b) {
  nstd::swap(a._data, b._data);
}

template <class T, typename... Args>
constexpr nstd::unique_ptr<T> make_unique(Args&&... args) {
  return unique_ptr<T>(new T(nstd::forward<Args>(args)...));
}

template <class T> class shared_ptr {
public:
  using value_type = T;

  explicit shared_ptr(T* arg = nullptr) : _data(arg), _num(new int(1)) {}

  shared_ptr(const shared_ptr& rhs) : _data(rhs._data), _num(rhs._num) {
    (*_num)++;
  }

  shared_ptr(shared_ptr&& rhs) noexcept : _data(rhs._data), _num(rhs._num) {
    rhs._data = nullptr;
    rhs._num = nullptr;
  }

  shared_ptr& operator=(const shared_ptr& rhs) {
    if (_data != rhs._data) {
      _data = rhs._data;
      _num = rhs._num;
      (*_num)++;
    }
    return *this;
  }

  shared_ptr& operator=(shared_ptr&& rhs) noexcept {
    if (_data != rhs._data) {
      _data = rhs._data;
      rhs._data = nullptr;
    }
    return *this;
  }

  ~shared_ptr() noexcept {
    if (_num) {
      (*_num)--;
      if (*_num == 0) {
        delete _data;
        delete _num;
      }
    }
  }

  T& operator*() const noexcept { return *_data; }

  T* operator->() const noexcept { return _data; }

  explicit operator bool() const noexcept { return _data != nullptr; }

  T* get() const noexcept { return _data; }

  int count() const noexcept { return *_num; }

  template <class U> friend void swap(shared_ptr<U>&, shared_ptr<U>&);

private:
  T* _data;
  int* _num;
};

template <class T> class shared_ptr<T[]> {
public:
  using value_type = T;

  explicit shared_ptr(T* arg = nullptr) : _data(arg), _num(new int(1)) {}

  shared_ptr(const shared_ptr& rhs) : _data(rhs._data), _num(rhs._num) {
    (*_num)++;
  }

  shared_ptr(shared_ptr&& rhs) noexcept : _data(rhs._data), _num(rhs._num) {
    delete[] rhs._data;
    rhs._data = nullptr;
    rhs._num = nullptr;
  }

  shared_ptr& operator=(const shared_ptr& rhs) {
    if (_data != rhs._data) {
      _data = rhs._data;
      _num = rhs._num;
      (*_num)++;
    }
    return *this;
  }

  shared_ptr& operator=(shared_ptr&& rhs) noexcept {
    if (_data != rhs._data) {
      _data = rhs._data;
      delete[] rhs._data;
      rhs._data = nullptr;
    }
    return *this;
  }

  ~shared_ptr() noexcept {
    if (_num) {
      (*_num)--;
      if (*_num == 0) {
        delete _data;
        delete _num;
      }
    }
  }

  T& operator[](nstd::size_t index) const { return _data[index]; }

  explicit operator bool() const noexcept { return _data != nullptr; }

  T* get() const noexcept { return _data; }

  int count() const noexcept { return *_num; }

  template <class U> friend void swap(shared_ptr<U>&, shared_ptr<U>&);

private:
  T* _data;
  int* _num;
};

template <class T> void swap(nstd::shared_ptr<T>& a, nstd::shared_ptr<T>& b) {
  nstd::swap(a._data, b._data);
}

template <class T, typename... Args>
constexpr nstd::shared_ptr<T> make_shared(Args&&... args) {
  return shared_ptr<T>(new T(nstd::forward<Args>(args)...));
}

} // namespace nstd
