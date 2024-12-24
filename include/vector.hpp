#pragma once

#include <cstddef>
#include <stdexcept>

template <typename T> class Vector {
private:
  T *data;
  std::size_t capacity;

public:
  explicit Vector(std::size_t initial_capacity = 10)
      : data(new T[initial_capacity]), capacity(initial_capacity) {}

  ~Vector() { delete[] data; }

  T &operator[](std::size_t index) {
    if (index >= capacity) {
      throw std::out_of_range("Index out of bounds");
    }
    return data[index];
  }

  const T &operator[](std::size_t index) const {
    if (index >= capacity) {
      throw std::out_of_range("Index out of bounds");
    }
    return data[index];
  }

  std::size_t get_capacity() const { return capacity; }
};
