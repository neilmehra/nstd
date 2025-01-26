#pragma once

#include "move.hpp"
#include "utility.hpp"
#include <exception>
#include <type_traits>

namespace nstd {

// 20.6.4, no-value state indicator
struct nullopt_t {
  constexpr explicit nullopt_t(int) noexcept {}
};
inline constexpr nullopt_t nullopt(0);

// 20.6.5, class bad_optional_access
struct bad_optional_access : public std::exception {
  bad_optional_access() noexcept = default;
  bad_optional_access(const bad_optional_access& other) noexcept = default;
  virtual ~bad_optional_access() noexcept override = default;
  const char* what() const noexcept override { return "bad optional access"; }
};

template <class T> class optional {
public:
  using value_type = T;

  constexpr optional() noexcept : engaged(false) {}

  constexpr optional(nullopt_t) noexcept : engaged(false) {}

  constexpr optional(const T& rhs) noexcept : engaged(true) {
    ::new (static_cast<void*>(&buf)) T(rhs);
  }

  constexpr optional(T&& rhs) noexcept : engaged(true) {
    ::new (static_cast<void*>(&buf)) T(nstd::move(rhs));
  }

  constexpr optional(const optional<T>& rhs) : engaged(rhs.engaged) {
    if (engaged) {
      ::new (static_cast<void*>(&buf)) T(rhs.value());
    }
  }

  constexpr optional(optional<T>&& rhs) : engaged(rhs.engaged) {
    if (engaged) {
      ::new (static_cast<void*>(&buf)) T(nstd::move(rhs.value()));
      rhs.engaged = false;
    }
  }

  ~optional() noexcept {
    if (engaged) {
      reinterpret_cast<T*>(&buf)->~T();
    }
  }

  optional& operator=(const optional<T>& rhs) noexcept {
    if (this != &rhs) {
      if (engaged && rhs.engaged) {
        // shouldn't we reset here? TODO
        **this = *rhs;
      } else if (engaged && !rhs.engaged) {
        reset();
      } else if (!engaged && rhs.engaged) {
        engaged = true;
        ::new (static_cast<void*>(&buf)) T(rhs.value());
      }
    }
    return *this;
  }

  optional& operator=(optional<T>&& rhs) noexcept {
    if (this != &rhs) {
      if (engaged && rhs.engaged) {
        **this = nstd::move(*rhs);
      } else if (engaged && !rhs.engaged) {
        reset();
      } else if (!engaged && rhs.engaged) {
        engaged = true;
        ::new (static_cast<void*>(&buf)) T(nstd::move(rhs.value()));
      }
    }
    rhs.reset();
    return *this;
  }

  optional& operator=(const T& rhs) noexcept {
    if (engaged) {
      **this = rhs;
    } else {
      ::new (static_cast<void*>(&buf)) T(rhs);
      engaged = true;
    }
    return *this;
  }

  optional& operator=(T&& rhs) noexcept {
    if (engaged) {
      **this = nstd::move(rhs);
    } else {
      ::new (static_cast<void*>(&buf)) T(nstd::move(rhs));
      engaged = true;
    }
    return *this;
  }

  template <class... Args> T& emplace(Args... args) {
    reset();
    ::new (static_cast<void*>(&buf)) T(nstd::forward<Args>(args)...);
    engaged = true;
    return value();
  }

  void swap(optional<T>& rhs) { nstd::swap(value(), rhs.value()); }

  constexpr explicit operator bool() const noexcept { return engaged; }

  constexpr bool has_value() const noexcept { return engaged; }

  T& value() {
    if (!engaged) {
      throw bad_optional_access();
    }
    return *reinterpret_cast<T*>(&buf);
  }

  const T& value() const {
    if (!engaged) {
      throw bad_optional_access();
    }
    return *reinterpret_cast<const T*>(&buf);
  }

  T& operator*() { return value(); }

  const T& operator*() const { return value(); }

  T& operator->() { return value(); }

  const T& operator->() const { return value(); }

  void reset() {
    if (engaged) {
      reinterpret_cast<T*>(&buf)->~T();
      engaged = false;
    }
  }

private:
  bool engaged;
  std::aligned_storage_t<sizeof(T), alignof(T)> buf;
};

} // namespace nstd
