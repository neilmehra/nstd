#pragma once

#include "def.hpp"

namespace nstd {

template <class T>
class Vector {
private:
  T*_data;
  T* _start;
  T* _end;
  nstd::size_t capacity;

public:
  using value_type = T;

  explicit Vector(nstd::size_t initial_capacity = 16)
      : _data(new T[initial_capacity]), capacity(initial_capacity) {}

  ~Vector() { delete[] _data; }

  T &operator[](nstd::size_t index) {
    return _data[index];
  }

  const T &operator[](nstd::size_t index) const {
    return _data[index];
  }

  nstd::size_t get_capacity() const { return capacity; }
};
}
