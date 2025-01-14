#include "../include/type_traits.hpp"
#include <gtest/gtest.h>

using five_int = nstd::integral_constant<int, 5>;

TEST(TypeTraits, IsSame) {
  EXPECT_TRUE((nstd::is_same_v<int, int>));
  EXPECT_FALSE((nstd::is_same_v<int, long>));
}

TEST(TypeTraits, IntegralConstant) {
  EXPECT_TRUE((nstd::integral_constant<int, 10>::value == 10));
  EXPECT_TRUE((nstd::is_same_v<nstd::integral_constant<int, 10>::value_type,
                               nstd::integral_constant<int, 5>::value_type>));
  EXPECT_FALSE((nstd::is_same_v<nstd::integral_constant<int, 10>::value_type,
                                nstd::integral_constant<long, 5>::value_type>));
}

TEST(TypeTraits, BoolConstant) {
  EXPECT_TRUE(nstd::bool_constant<true>::value);
  EXPECT_FALSE(nstd::bool_constant<false>::value);
}

TEST(TypeTraits, ConstVolatileModification) {
  EXPECT_TRUE((nstd::is_same_v<nstd::remove_cv<int>::type, int>));
  EXPECT_TRUE((nstd::is_same_v<nstd::remove_cv<const int>::type, int>));
  EXPECT_TRUE((nstd::is_same_v<nstd::remove_cv<const volatile int>::type, int>));
  EXPECT_TRUE((nstd::is_same_v<nstd::remove_cv<volatile int>::type, int>));

  EXPECT_TRUE((nstd::is_same_v<nstd::remove_const<int>::type, int>));
  EXPECT_TRUE((nstd::is_same_v<nstd::remove_const<const int>::type, int>));
  EXPECT_TRUE((nstd::is_same_v<nstd::remove_const<const volatile int>::type, volatile int>));
  EXPECT_TRUE((nstd::is_same_v<nstd::remove_const<volatile int>::type, volatile int>));

  EXPECT_TRUE((nstd::is_same_v<nstd::remove_volatile<int>::type, int>));
  EXPECT_TRUE((nstd::is_same_v<nstd::remove_volatile<volatile int>::type, int>));
  EXPECT_TRUE((nstd::is_same_v<nstd::remove_volatile<volatile const int>::type, const int>));
  EXPECT_TRUE((nstd::is_same_v<nstd::remove_volatile<const int>::type, const int>));
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

TEST(TypeTraits, IsArray) {
  EXPECT_TRUE(nstd::is_array_v<int[]>);
  EXPECT_TRUE(nstd::is_array_v<int[10]>);
  EXPECT_TRUE(nstd::is_array_v<const int[]>);
  EXPECT_TRUE(nstd::is_array_v<const int[10]>);
  EXPECT_TRUE(nstd::is_array_v<volatile int[]>);
  EXPECT_TRUE(nstd::is_array_v<volatile int[10]>);
  EXPECT_TRUE(nstd::is_array_v<const volatile int[]>);
  EXPECT_TRUE(nstd::is_array_v<const volatile int[10]>);
}

TEST(TypeTraits, IsFunction) {
  struct Foo {
    static void s_foo_member() {};
    static void s_foo_member_c() {};
    static void s_foo_member_cn() {};
    void foo_member() {};
    void foo_member_c() const {};
    void foo_member_cn() const noexcept {};
  };
  Foo bar{};
  void foo();
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wvexing-parse"
  int moo();
#pragma clang diagnostic pop
  int goo(int, int);
  int loo(int...);
  EXPECT_TRUE(nstd::is_function_v<decltype(Foo::s_foo_member)>);
  EXPECT_TRUE(nstd::is_function_v<decltype(Foo::s_foo_member_c)>);
  EXPECT_TRUE(nstd::is_function_v<decltype(Foo::s_foo_member_cn)>);
  EXPECT_TRUE(nstd::is_function_v<decltype(bar.s_foo_member)>);
  EXPECT_TRUE(nstd::is_function_v<decltype(bar.s_foo_member_c)>);
  EXPECT_TRUE(nstd::is_function_v<decltype(bar.s_foo_member_cn)>);
  EXPECT_TRUE(nstd::is_function_v<decltype(foo)>);
  EXPECT_TRUE(nstd::is_function_v<decltype(moo)>);
  EXPECT_TRUE(nstd::is_function_v<decltype(goo)>);
  EXPECT_TRUE(nstd::is_function_v<decltype(loo)>);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
