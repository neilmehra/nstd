#pragma once

// #include "move.hpp"
//
//
// namespace nstd {
//
// template <class T> class shared_ptr {
// public:
//   using value_type = T;
//
//   explicit shared_ptr(T* arg = nullptr) : _data(arg), _num(new int(1)) {}
//
//   shared_ptr(const shared_ptr& rhs) : _data(rhs._data), _num(rhs._num) {
//     (*_num)++;
//   }
//
//   shared_ptr(shared_ptr&& rhs) noexcept : _data(rhs._data), _num(rhs._num) {
//     rhs._data = nullptr;
//     rhs._num = nullptr;
//   }
//
//   shared_ptr& operator=(const shared_ptr& rhs) {
//     if (_data != rhs._data) {
//       _data = rhs._data;
//       _num = rhs._num;
//       (*_num)++;
//     }
//     return *this;
//   }
//
//   shared_ptr& operator=(shared_ptr&& rhs) noexcept {
//     if (_data != rhs._data) {
//       _data = rhs._data;
//       rhs._data = nullptr;
//     }
//     return *this;
//   }
//
//   ~shared_ptr() noexcept {
//     if (_num) {
//       (*_num)--;
//       if (*_num == 0) {
//         delete _data;
//         delete _num;
//       }
//     }
//   }
//
//   T& operator*() const noexcept { return *_data; }
//
//   T* operator->() const noexcept { return _data; }
//
//   explicit operator bool() const noexcept { return _data != nullptr; }
//
//   T* get() const noexcept { return _data; }
//
//   int count() const noexcept { return *_num; }
//
//   template <class U> friend void swap(shared_ptr<U>&, shared_ptr<U>&);
//
// private:
//   T* _data;
//   int* _num;
// };
//
// template <class T> class shared_ptr<T[]> {
// public:
//   using value_type = T;
//
//   explicit shared_ptr(T* arg = nullptr) : _data(arg), _num(new int(1)) {}
//
//   shared_ptr(const shared_ptr& rhs) : _data(rhs._data), _num(rhs._num) {
//     (*_num)++;
//   }
//
//   shared_ptr(shared_ptr&& rhs) noexcept : _data(rhs._data), _num(rhs._num) {
//     delete[] rhs._data;
//     rhs._data = nullptr;
//     rhs._num = nullptr;
//   }
//
//   shared_ptr& operator=(const shared_ptr& rhs) {
//     if (_data != rhs._data) {
//       _data = rhs._data;
//       _num = rhs._num;
//       (*_num)++;
//     }
//     return *this;
//   }
//
//   shared_ptr& operator=(shared_ptr&& rhs) noexcept {
//     if (_data != rhs._data) {
//       _data = rhs._data;
//       delete[] rhs._data;
//       rhs._data = nullptr;
//     }
//     return *this;
//   }
//
//   ~shared_ptr() noexcept {
//     if (_num) {
//       (*_num)--;
//       if (*_num == 0) {
//         delete _data;
//         delete _num;
//       }
//     }
//   }
//
//   T& operator[](nstd::size_t index) const { return _data[index]; }
//
//   explicit operator bool() const noexcept { return _data != nullptr; }
//
//   T* get() const noexcept { return _data; }
//
//   int count() const noexcept { return *_num; }
//
//   template <class U> friend void swap(shared_ptr<U>&, shared_ptr<U>&);
//
// private:
//   T* _data;
//   int* _num;
// };
//
// template <class T> void swap(nstd::shared_ptr<T>& a, nstd::shared_ptr<T>& b) {
//   nstd::swap(a._data, b._data);
// }
//
// template <class T, typename... Args>
// constexpr nstd::shared_ptr<T> make_shared(Args&&... args) {
//   return shared_ptr<T>(new T(nstd::forward<Args>(args)...));
// }
//
// } // namespace nstd
