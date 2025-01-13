#include <gtest/gtest.h>
#include "../include/type_traits.hpp"

using five_int = nstd::integral_constant<int, 5>;

TEST(TypeTraits, BoolConstant) {
  EXPECT_TRUE(nstd::bool_constant<true>::value);
  EXPECT_FALSE(nstd::bool_constant<false>::value);
}

TEST(TypeTraits, IsReference) {
  EXPECT_FALSE(nstd::is_lvalue_reference<int>::value);
  EXPECT_TRUE(nstd::is_lvalue_reference<int&>::value);
  EXPECT_FALSE(nstd::is_lvalue_reference<int&&>::value);

  EXPECT_FALSE(nstd::is_rvalue_reference<int>::value);
  EXPECT_FALSE(nstd::is_rvalue_reference<int&>::value);
  EXPECT_TRUE(nstd::is_rvalue_reference<int&&>::value);
}

TEST(TypeTraits, IsVoid) {
  EXPECT_TRUE((nstd::is_void<void>::value));
  EXPECT_FALSE((nstd::is_void<int>::value));
  EXPECT_FALSE((nstd::is_void<void*>::value));
}

void func_foo() {

}

void func_bar(int x, int y) {

}

TEST(TypeTraits, IsFunction) {
  EXPECT_TRUE((nstd::is_function<decltype(func_foo)>::value));
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
