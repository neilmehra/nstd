#include "../include/type_traits.hpp"
#include <gtest/gtest.h>

using five_int = nstd::integral_constant<int, 5>;

TEST(TypeTraits, SameAs) {
  EXPECT_TRUE((nstd::is_same<int, int>::value));
  EXPECT_TRUE((nstd::is_same<five_int, five_int>::value));
  EXPECT_FALSE((nstd::is_same<int&, int>::value));
}

TEST(TypeTraits, IntegralConstant) {
  EXPECT_EQ(five_int()(), 5);
  EXPECT_EQ(five_int::value, 5);
  EXPECT_EQ(static_cast<int>(five_int()), 5);
  EXPECT_TRUE((nstd::is_same<five_int::type, int>::value));
}

TEST(TypeTraits, BoolConstant) {
  EXPECT_TRUE(nstd::bool_constant<true>::value);
  EXPECT_FALSE(nstd::bool_constant<false>::value);
}

TEST(TypeTraits, IsReference) {
  EXPECT_FALSE(nstd::is_reference<int>::value);
  EXPECT_TRUE(nstd::is_reference<int&>::value);
  EXPECT_TRUE(nstd::is_reference<int&&>::value);

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

TEST(TypeTraits, IsConst) {
  EXPECT_TRUE((nstd::is_const<const int>::value));
  EXPECT_FALSE((nstd::is_const<int>::value));
  EXPECT_TRUE((nstd::is_const<const volatile int>::value));
  EXPECT_FALSE((nstd::is_const<volatile int>::value));
}

TEST(TypeTraits, IsVolatile) {
  EXPECT_TRUE((nstd::is_volatile<volatile int>::value));
  EXPECT_FALSE((nstd::is_volatile<int>::value));
  EXPECT_TRUE((nstd::is_volatile<const volatile int>::value));
  EXPECT_FALSE((nstd::is_volatile<const int>::value));
}


TEST(TypeTraits, IsArray) {
  EXPECT_TRUE((nstd::is_array<int[]>::value));
  EXPECT_FALSE((nstd::is_array<int>::value));
}

TEST(TypeTraits, RemoveReference) {
  EXPECT_TRUE((nstd::is_same<nstd::remove_reference<int>::type, int>::value));
  EXPECT_TRUE((nstd::is_same<nstd::remove_reference<int&>::type, int>::value));
  EXPECT_TRUE((nstd::is_same<nstd::remove_reference<int&&>::type, int>::value));
}

TEST(TypeTraits, RemoveConst) {
  EXPECT_TRUE((nstd::is_same<nstd::remove_const<int>::type, int>::value));
  EXPECT_TRUE((nstd::is_same<nstd::remove_const<const int>::type, int>::value));
  EXPECT_TRUE((nstd::is_same<nstd::remove_const<const volatile int>::type,
                             volatile int>::value));
}

TEST(TypeTraits, RemoveVolatile) {
  EXPECT_TRUE((nstd::is_same<nstd::remove_volatile<int>::type, int>::value));
  EXPECT_TRUE(
      (nstd::is_same<nstd::remove_volatile<volatile int>::type, int>::value));
  EXPECT_TRUE((nstd::is_same<nstd::remove_volatile<const volatile int>::type,
                             const int>::value));
}

TEST(TypeTraits, RemoveCV) {
  EXPECT_TRUE((nstd::is_same<nstd::remove_cv<int>::type, int>::value));
  EXPECT_TRUE((nstd::is_same<nstd::remove_cv<const int>::type, int>::value));
  EXPECT_TRUE((nstd::is_same<nstd::remove_cv<volatile int>::type, int>::value));
  EXPECT_TRUE(
      (nstd::is_same<nstd::remove_cv<const volatile int>::type, int>::value));
}

TEST(TypeTraits, RemoveArray) {
  EXPECT_TRUE((nstd::is_same<nstd::remove_array<int[]>::type, int>::value));
  EXPECT_TRUE((nstd::is_same<nstd::remove_array<int>::type, int>::value));
  EXPECT_TRUE((nstd::is_same<nstd::remove_array<int>::type, int>::value));
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
