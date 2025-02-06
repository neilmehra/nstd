#pragma once

#include <algorithm>
#include <bit>
#include <bitset>
#include <cstddef>
#include <iosfwd>
#include <limits>
#include <stdexcept>
#include <string>

namespace nstd {

template <std::size_t N> class bitset;

template <std::size_t N>
bitset<N> operator&(const bitset<N>&, const bitset<N>&) noexcept;

template <std::size_t N>
bitset<N> operator|(const bitset<N>&, const bitset<N>&) noexcept;

template <std::size_t N>
bitset<N> operator^(const bitset<N>&, const bitset<N>&) noexcept;

template <class charT, class traits, std::size_t N>
std::basic_istream<charT, traits>&
operator>>(std::basic_istream<charT, traits>& is, bitset<N>& x);

template <class charT, class traits, std::size_t N>
std::basic_ostream<charT, traits>&
operator<<(std::basic_ostream<charT, traits>& is, const bitset<N>& x);

template <std::size_t N> class bitset {
public:
  class reference {
  public:
    friend class bitset;
    reference() noexcept;

    reference(const reference&) = default;
    ~reference();

    reference& operator=(bool x) noexcept;
    reference& operator=(const reference&) noexcept;
    bool operator~() const noexcept;
    operator bool() const noexcept;
    reference& flip() noexcept;
  };

  constexpr bitset() noexcept {}

  constexpr bitset(unsigned long long val) noexcept {
    std::size_t M = std::min(N, block_t_bitsize);
    data[0] |= val;
  }

  // 20.9.2.2, bitset operations
  bitset<N>& operator&=(const bitset<N>& rhs) noexcept {
    for (std::size_t i = 0; i < num_blocks; i++) {
      data[i] &= rhs.data[i];
    }
  };

  bitset<N>& operator|=(const bitset<N>& rhs) noexcept {
    for (std::size_t i = 0; i < num_blocks; i++) {
      data[i] |= rhs.data[i];
    }
  };

  bitset<N>& operator^=(const bitset<N>& rhs) noexcept {
    for (std::size_t i = 0; i < num_blocks; i++) {
      data[i] ^= rhs.data[i];
    }
  };

  bitset<N>& operator<<=(std::size_t pos) noexcept {
    for (std::size_t i = N - 1; i >= pos; i--) {
      set_impl(i, (*this)[i - pos]);
    }
    for (std::size_t i = 0; i < pos; i++) {
      if (i + block_t_bitsize < pos) {
        data[i] = 0;
        i += block_t_bitsize - 1;
      } else {
        reset_impl(i);
      }
    }
    return *this;
  }

  bitset<N>& operator>>=(std::size_t pos) noexcept {
    for (std::size_t i = 0; i + pos < N; i++) {
      set_impl(i, (*this)[i + pos]);
    }
    for (std::size_t i = N - pos; i < N; i++) {
      if (i < pos + block_t_bitsize) {
        data[i] = 0;
        i += block_t_bitsize - 1;
      } else {
        reset_impl(i);
      }
    }
    return *this;
  };

  bitset<N>& set() noexcept { return set_impl(); };

  bitset<N>& set(std::size_t pos, bool val = true) {
    if (pos > N)
      throw std::out_of_range{"Attempted to set bit out of range"};
    return set_impl(pos, val);
  }

  bitset<N>& reset() noexcept { return reset_impl(); }

  bitset<N>& reset(std::size_t pos) { return reset_impl(pos); }

  bitset<N> operator~() const noexcept { return this->flip(); }

  bitset<N>& flip() noexcept {
    for (std::size_t i = 0; i < num_blocks; i++) {
      data[i] = ~data[i];
    }
    return *this;
  }

  bitset<N>& flip(std::size_t pos) {
    std::size_t block_idx = pos / block_t_bitsize;
    std::size_t bit = pos - (block_t_bitsize * block_idx);
    data[block_idx] ^= static_cast<block_t>(1) << bit;
    return *this;
  }

  // element access
  constexpr bool operator[](size_t pos) const {
    std::size_t block_idx = pos / block_t_bitsize;
    std::size_t bit = pos - (block_t_bitsize * block_idx);
    return (data[block_idx] & (static_cast<block_t>(1) << bit)) != 0;
  }

  // for b[i];
  reference operator[](size_t pos);

  // for b[i];
  unsigned long to_ulong() const;
  unsigned long long to_ullong() const;

  // TODO: stop being lazy
  std::string to_string(char zero = '0', char one = '1') const;

  size_t count() const noexcept {
    std::size_t sum = 0;
    for (std::size_t i = 0; i < num_blocks; i++) {
      sum += std::popcount(data[i]);
    }
    return sum;
  }

  constexpr size_t size() const noexcept { return N; }

  bool operator==(const bitset<N>& rhs) const noexcept {
    for (std::size_t i = 0; i < num_blocks; i++) {
      if (data[i] != rhs.data[i])
        return false;
    }
    return true;
  }

  bool test(size_t pos) const {
    if (pos >= N)
      throw std::out_of_range{"Attempted to test bit out of range"};
    return (*this)[pos];
  }

  bool all() const noexcept {
    block_t mask = std::numeric_limits<block_t>::max();
    for (std::size_t i = 0; i < num_blocks; i++) {
      if (mask != (mask & data[i]))
        return false;
    }
    return true;
  }

  bool any() const noexcept {
    block_t mask = 0;
    for (std::size_t i = 0; i < num_blocks; i++) {
      mask |= data[i];
      if (mask)
        return true;
    }
    return false;
  }

  bool none() const noexcept { return !any(); }

  bitset<N> operator<<(size_t pos) const noexcept {
    auto ret = *this;
    ret <<= pos;
    return ret;
  }

  bitset<N> operator>>(size_t pos) const noexcept {
    auto ret = *this;
    ret >>= pos;
    return ret;
  }

private:
  using block_t = std::size_t;
  constexpr static std::size_t block_t_bitsize = 8 * sizeof(block_t);
  constexpr static std::size_t num_blocks =
      (N + block_t_bitsize - 1) / block_t_bitsize;

  block_t data[num_blocks]{};

  // need a non-noexcept impl to reuse in bitshift operators
  bitset<N>& set_impl() {
    block_t mask = std::numeric_limits<block_t>::max();
    for (std::size_t i = 0; i < num_blocks; i++) {
      data[i] |= mask;
    }
  }

  bitset<N>& set_impl(std::size_t pos, bool val = true) {
    if (!val)
      return reset(pos);
    std::size_t block_idx = pos / block_t_bitsize;
    std::size_t bit = pos - (block_t_bitsize * block_idx);
    data[block_idx] |= (static_cast<block_t>(1) << bit);
    return *this;
  }

  bitset<N>& reset_impl() noexcept {
    for (std::size_t i = 0; i < num_blocks; i++) {
      data[i] &= 0;
    }
    return *this;
  }

  bitset<N>& reset_impl(std::size_t pos) {
    std::size_t block_idx = pos / block_t_bitsize;
    std::size_t bit = pos - (block_t_bitsize * block_idx);
    block_t mask = std::numeric_limits<block_t>::max();
    data[block_idx] &= mask ^ (static_cast<block_t>(1) << bit);
    return *this;
  }
};

template <class T> struct hash;
template <std::size_t N> struct hash<bitset<N>>;

} // namespace nstd
