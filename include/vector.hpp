#pragma once

#include <cstddef>
namespace nstd {

template <class T> class Vector {
private:
  T* _data;
  T* _start;
  T* _end;
  std::size_t capacity;

public:
  using value_type = T;
  using ref_type = T&;

  explicit Vector(std::size_t initial_capacity = 16)
      : _data(new T[initial_capacity]), capacity(initial_capacity) {}

  ~Vector() { delete[] _data; }

  T& operator[](std::size_t index) { return _data[index]; }

  const T& operator[](std::size_t index) const { return _data[index]; }

  std::size_t get_capacity() const { return capacity; }
};
} // namespace nstd
