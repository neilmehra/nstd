#include "../include/type_traits.hpp"
#include "../include/utility.hpp"
#include <gtest/gtest.h>

TEST(Utility, Move) {
  int x = 5;
  const int& y = 5;
  EXPECT_TRUE((nstd::is_same<decltype(nstd::move(x)), int&&>::value));
  EXPECT_TRUE((nstd::is_same<decltype(nstd::move(y)), const int&&>::value));
  EXPECT_TRUE((nstd::is_same<decltype(nstd::move(5)), int&&>::value));
}

template <class T> constexpr T&& wrapper(T&& arg) {
  return nstd::forward<T>(arg);
}

TEST(Utility, Forward) {
  int x = 5;
  const int& y = x;
  EXPECT_TRUE((nstd::is_same<decltype(wrapper(x)), int&>::value));
  EXPECT_TRUE((nstd::is_same<decltype(wrapper(y)), const int&>::value));
  EXPECT_TRUE((nstd::is_same<decltype(wrapper(5)), int&&>::value));
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
