#pragma once

// #include "move.hpp"
//
//
// namespace nstd {
//
// template <class T> class unique_ptr {
// public:
//   using value_type = T;
//
//   explicit unique_ptr(T* arg = nullptr) : _data(arg) {}
//
//   unique_ptr(const unique_ptr&) = delete;
//   unique_ptr& operator=(const unique_ptr&) = delete;
//
//   unique_ptr(unique_ptr&& rhs) noexcept : _data(rhs._data) {
//     rhs._data = nullptr;
//   }
//
//   unique_ptr& operator=(unique_ptr&& rhs) noexcept {
//     if (_data != rhs._data) {
//       delete _data;
//       _data = rhs._data;
//       rhs._data = nullptr;
//     }
//     return *this;
//   }
//
//   ~unique_ptr() noexcept { delete _data; }
//
//   T& operator*() const noexcept { return *_data; }
//
//   T* operator->() const noexcept { return _data; }
//
//   explicit operator bool() const noexcept { return _data != nullptr; }
//
//   T* get() const noexcept { return _data; }
//
//   template <class U> friend void swap(unique_ptr<U>&, unique_ptr<U>&);
//
// private:
//   T* _data;
// };
//
// template <class T> class unique_ptr<T[]> {
// public:
//   using value_type = T;
//
//   explicit unique_ptr(T* arg = nullptr) : _data(arg) {}
//
//   unique_ptr(const unique_ptr&) = delete;
//   unique_ptr& operator=(const unique_ptr&) = delete;
//
//   unique_ptr(unique_ptr&& rhs) noexcept : _data(rhs._data) {
//     rhs._data = nullptr;
//   }
//
//   unique_ptr& operator=(unique_ptr&& rhs) noexcept {
//     if (_data != rhs._data) {
//       delete[] _data;
//       _data = rhs._data;
//       rhs._data = nullptr;
//     }
//     return *this;
//   }
//
//   ~unique_ptr() noexcept { delete[] _data; }
//
//   explicit operator bool() const noexcept { return _data != nullptr; }
//
//   T& operator[](nstd::size_t index) const { return _data[index]; }
//
//   T* get() const noexcept { return _data; }
//
//   template <class U> friend void swap(unique_ptr<U>&, unique_ptr<U>&);
//
// private:
//   T* _data;
// };
//
// template <class T> void swap(nstd::unique_ptr<T>& a, nstd::unique_ptr<T>& b) {
//   nstd::swap(a._data, b._data);
// }
//
// template <class T, typename... Args>
// constexpr nstd::unique_ptr<T> make_unique(Args&&... args) {
//   return unique_ptr<T>(new T(nstd::forward<Args>(args)...));
// }
//
// } // namespace nstd
//
