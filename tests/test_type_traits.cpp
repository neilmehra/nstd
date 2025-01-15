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

TEST(TypeTraits, RemoveCV) {
  EXPECT_TRUE((nstd::is_same_v<nstd::remove_cv_t<int>, int>));
  EXPECT_TRUE((nstd::is_same_v<nstd::remove_cv_t<const int>, int>));
  EXPECT_TRUE((nstd::is_same_v<nstd::remove_cv_t<volatile int>, int>));
  EXPECT_TRUE((nstd::is_same_v<nstd::remove_cv_t<const volatile int>, int>));

  EXPECT_TRUE((nstd::is_same_v<nstd::remove_const_t<int>, int>));
  EXPECT_TRUE((nstd::is_same_v<nstd::remove_const_t<const int>, int>));
  EXPECT_TRUE(
      (nstd::is_same_v<nstd::remove_const_t<volatile int>, volatile int>));
  EXPECT_TRUE((
      nstd::is_same_v<nstd::remove_const_t<const volatile int>, volatile int>));

  EXPECT_TRUE((nstd::is_same_v<nstd::remove_volatile_t<int>, int>));
  EXPECT_TRUE((nstd::is_same_v<nstd::remove_volatile_t<volatile int>, int>));
  EXPECT_TRUE((nstd::is_same_v<nstd::remove_volatile_t<const int>, const int>));
  EXPECT_TRUE((
      nstd::is_same_v<nstd::remove_volatile_t<volatile const int>, const int>));
}

TEST(TypeTraits, AddCV) {
  EXPECT_TRUE((nstd::is_same_v<nstd::add_cv_t<int>, const volatile int>));
  EXPECT_TRUE((nstd::is_same_v<nstd::add_cv_t<const int>, const volatile int>));
  EXPECT_TRUE(
      (nstd::is_same_v<nstd::add_cv_t<volatile int>, const volatile int>));
  EXPECT_TRUE((
      nstd::is_same_v<nstd::add_cv_t<const volatile int>, const volatile int>));

  EXPECT_TRUE((nstd::is_same_v<nstd::add_const_t<int>, const int>));
  EXPECT_TRUE((nstd::is_same_v<nstd::add_const_t<const int>, const int>));
  EXPECT_TRUE(
      (nstd::is_same_v<nstd::add_const_t<volatile int>, const volatile int>));
  EXPECT_TRUE((nstd::is_same_v<nstd::add_const_t<const volatile int>,
                               const volatile int>));

  EXPECT_TRUE((nstd::is_same_v<nstd::add_volatile_t<int>, volatile int>));
  EXPECT_TRUE(
      (nstd::is_same_v<nstd::add_volatile_t<volatile int>, volatile int>));
  EXPECT_TRUE(
      (nstd::is_same_v<nstd::add_volatile_t<const int>, const volatile int>));
  EXPECT_TRUE((nstd::is_same_v<nstd::add_volatile_t<volatile const int>,
                               const volatile int>));
}

TEST(TypeTraits, RemoveRef) {
  EXPECT_TRUE((nstd::is_same_v<nstd::remove_reference_t<int>, int>));
  EXPECT_TRUE((nstd::is_same_v<nstd::remove_reference_t<int&>, int>));
  EXPECT_TRUE((nstd::is_same_v<nstd::remove_reference_t<int&&>, int>));
}

TEST(TypeTraits, AddRef) {
  EXPECT_TRUE((nstd::is_same_v<nstd::add_lvalue_reference_t<int>, int&>));
  EXPECT_TRUE((nstd::is_same_v<nstd::add_lvalue_reference_t<int&>, int&>));
  EXPECT_TRUE((nstd::is_same_v<nstd::add_lvalue_reference_t<int&&>, int&>));

  EXPECT_TRUE((nstd::is_same_v<nstd::add_rvalue_reference_t<int>, int&&>));
  EXPECT_TRUE((nstd::is_same_v<nstd::add_rvalue_reference_t<int&>, int&>));
  EXPECT_TRUE((nstd::is_same_v<nstd::add_rvalue_reference_t<int&&>, int&&>));
}

TEST(TypeTraits, IsVoid) {
  EXPECT_TRUE((nstd::is_void_v<void>));
  EXPECT_FALSE((nstd::is_void_v<int>));
  EXPECT_FALSE((nstd::is_void_v<void*>));
  EXPECT_TRUE((nstd::is_void_v<const void>));
  EXPECT_TRUE((nstd::is_void_v<volatile void>));
  EXPECT_TRUE((nstd::is_void_v<const volatile void>));
}

TEST(TypeTraits, IsIntegral) {
  EXPECT_TRUE((nstd::is_integral_v<bool>));
  EXPECT_TRUE((nstd::is_integral_v<char>));
  EXPECT_TRUE((nstd::is_integral_v<char8_t>));
  EXPECT_TRUE((nstd::is_integral_v<char16_t>));
  EXPECT_TRUE((nstd::is_integral_v<char32_t>));
  EXPECT_TRUE((nstd::is_integral_v<wchar_t>));
  EXPECT_TRUE((nstd::is_integral_v<short>));
  EXPECT_TRUE((nstd::is_integral_v<int>));
  EXPECT_TRUE((nstd::is_integral_v<long>));
  EXPECT_TRUE((nstd::is_integral_v<long long>));
  EXPECT_TRUE((nstd::is_integral_v<unsigned short>));
  EXPECT_TRUE((nstd::is_integral_v<unsigned int>));
  EXPECT_TRUE((nstd::is_integral_v<unsigned long>));
  EXPECT_TRUE((nstd::is_integral_v<unsigned long long>));

  EXPECT_TRUE((nstd::is_integral_v<const bool>));
  EXPECT_TRUE((nstd::is_integral_v<const char>));
  EXPECT_TRUE((nstd::is_integral_v<const char8_t>));
  EXPECT_TRUE((nstd::is_integral_v<const char16_t>));
  EXPECT_TRUE((nstd::is_integral_v<const char32_t>));
  EXPECT_TRUE((nstd::is_integral_v<const wchar_t>));
  EXPECT_TRUE((nstd::is_integral_v<const short>));
  EXPECT_TRUE((nstd::is_integral_v<const int>));
  EXPECT_TRUE((nstd::is_integral_v<const long>));
  EXPECT_TRUE((nstd::is_integral_v<const long long>));
  EXPECT_TRUE((nstd::is_integral_v<const unsigned short>));
  EXPECT_TRUE((nstd::is_integral_v<const unsigned int>));
  EXPECT_TRUE((nstd::is_integral_v<const unsigned long>));
  EXPECT_TRUE((nstd::is_integral_v<const unsigned long long>));

  EXPECT_TRUE((nstd::is_integral_v<volatile bool>));
  EXPECT_TRUE((nstd::is_integral_v<volatile char>));
  EXPECT_TRUE((nstd::is_integral_v<volatile char8_t>));
  EXPECT_TRUE((nstd::is_integral_v<volatile char16_t>));
  EXPECT_TRUE((nstd::is_integral_v<volatile char32_t>));
  EXPECT_TRUE((nstd::is_integral_v<volatile wchar_t>));
  EXPECT_TRUE((nstd::is_integral_v<volatile short>));
  EXPECT_TRUE((nstd::is_integral_v<volatile int>));
  EXPECT_TRUE((nstd::is_integral_v<volatile long>));
  EXPECT_TRUE((nstd::is_integral_v<volatile long long>));
  EXPECT_TRUE((nstd::is_integral_v<volatile unsigned short>));
  EXPECT_TRUE((nstd::is_integral_v<volatile unsigned int>));
  EXPECT_TRUE((nstd::is_integral_v<volatile unsigned long>));
  EXPECT_TRUE((nstd::is_integral_v<volatile unsigned long long>));

  EXPECT_TRUE((nstd::is_integral_v<const volatile bool>));
  EXPECT_TRUE((nstd::is_integral_v<const volatile char>));
  EXPECT_TRUE((nstd::is_integral_v<const volatile char8_t>));
  EXPECT_TRUE((nstd::is_integral_v<const volatile char16_t>));
  EXPECT_TRUE((nstd::is_integral_v<const volatile char32_t>));
  EXPECT_TRUE((nstd::is_integral_v<const volatile wchar_t>));
  EXPECT_TRUE((nstd::is_integral_v<const volatile short>));
  EXPECT_TRUE((nstd::is_integral_v<const volatile int>));
  EXPECT_TRUE((nstd::is_integral_v<const volatile long>));
  EXPECT_TRUE((nstd::is_integral_v<const volatile long long>));
  EXPECT_TRUE((nstd::is_integral_v<const volatile unsigned short>));
  EXPECT_TRUE((nstd::is_integral_v<const volatile unsigned int>));
  EXPECT_TRUE((nstd::is_integral_v<const volatile unsigned long>));
  EXPECT_TRUE((nstd::is_integral_v<const volatile unsigned long long>));
}

TEST(TypeTraits, IsFloatingPoint) {
  EXPECT_TRUE((nstd::is_floating_point_v<float>));
  EXPECT_TRUE((nstd::is_floating_point_v<double>));
  EXPECT_TRUE((nstd::is_floating_point_v<long double>));

  EXPECT_TRUE((nstd::is_floating_point_v<const float>));
  EXPECT_TRUE((nstd::is_floating_point_v<const double>));
  EXPECT_TRUE((nstd::is_floating_point_v<const long double>));

  EXPECT_TRUE((nstd::is_floating_point_v<volatile float>));
  EXPECT_TRUE((nstd::is_floating_point_v<volatile double>));
  EXPECT_TRUE((nstd::is_floating_point_v<volatile long double>));

  EXPECT_TRUE((nstd::is_floating_point_v<const volatile float>));
  EXPECT_TRUE((nstd::is_floating_point_v<const volatile double>));
  EXPECT_TRUE((nstd::is_floating_point_v<const volatile long double>));
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

TEST(TypeTraits, IsPointer) {
  void foo();
  void goo() noexcept;
  EXPECT_TRUE(nstd::is_pointer_v<int*>);
  EXPECT_TRUE(nstd::is_pointer_v<void*>);
  EXPECT_TRUE(nstd::is_pointer_v<const int*>);
  EXPECT_TRUE(nstd::is_pointer_v<int* const>);
  EXPECT_TRUE(nstd::is_pointer_v<const int* const>);
  EXPECT_TRUE(nstd::is_pointer_v<const int* const>);
  EXPECT_TRUE(nstd::is_pointer_v<decltype(&foo)>);
  EXPECT_TRUE(nstd::is_pointer_v<decltype(&goo)>);

  EXPECT_TRUE(nstd::is_pointer_v<volatile int*>);
  EXPECT_TRUE(nstd::is_pointer_v<volatile void*>);
  EXPECT_TRUE(nstd::is_pointer_v<volatile const int*>);
  EXPECT_TRUE(nstd::is_pointer_v<volatile int* const>);
  EXPECT_TRUE(nstd::is_pointer_v<volatile const int* const>);
  EXPECT_TRUE(nstd::is_pointer_v<volatile const int* const>);
  EXPECT_TRUE(nstd::is_pointer_v<volatile decltype(&foo)>);
  EXPECT_TRUE(nstd::is_pointer_v<volatile decltype(&goo)>);
}

TEST(TypeTraits, IsLvalueRef) {
  EXPECT_FALSE(nstd::is_lvalue_reference_v<int>);
  EXPECT_TRUE(nstd::is_lvalue_reference_v<int&>);
  EXPECT_FALSE(nstd::is_lvalue_reference_v<int&&>);

  EXPECT_FALSE(nstd::is_lvalue_reference_v<const int>);
  EXPECT_TRUE(nstd::is_lvalue_reference_v<const int&>);
  EXPECT_FALSE(nstd::is_lvalue_reference_v<const int&&>);

  EXPECT_FALSE(nstd::is_lvalue_reference_v<volatile int>);
  EXPECT_TRUE(nstd::is_lvalue_reference_v<volatile int&>);
  EXPECT_FALSE(nstd::is_lvalue_reference_v<volatile int&&>);

  EXPECT_FALSE(nstd::is_lvalue_reference_v<const volatile int>);
  EXPECT_TRUE(nstd::is_lvalue_reference_v<const volatile int&>);
  EXPECT_FALSE(nstd::is_lvalue_reference_v<const volatile int&&>);
}

TEST(TypeTraits, IsRvalueRef) {
  EXPECT_FALSE(nstd::is_rvalue_reference_v<int>);
  EXPECT_FALSE(nstd::is_rvalue_reference_v<int&>);
  EXPECT_TRUE(nstd::is_rvalue_reference_v<int&&>);

  EXPECT_FALSE(nstd::is_rvalue_reference_v<const int>);
  EXPECT_FALSE(nstd::is_rvalue_reference_v<const int&>);
  EXPECT_TRUE(nstd::is_rvalue_reference_v<const int&&>);

  EXPECT_FALSE(nstd::is_rvalue_reference_v<volatile int>);
  EXPECT_FALSE(nstd::is_rvalue_reference_v<volatile int&>);
  EXPECT_TRUE(nstd::is_rvalue_reference_v<volatile int&&>);

  EXPECT_FALSE(nstd::is_rvalue_reference_v<const volatile int>);
  EXPECT_FALSE(nstd::is_rvalue_reference_v<const volatile int&>);
  EXPECT_TRUE(nstd::is_rvalue_reference_v<const volatile int&&>);
}

TEST(TypeTraits, IsFunction) {
  struct Foo {
    static void s_foo_member() {};
    static void s_foo_member_c() {};
    static void s_foo_member_cn() noexcept {};
  };

  Foo bar{};
  void foo();
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wvexing-parse"
  int moo();
#pragma clang diagnostic pop
  int goo(int, int);
  int loo(int...);
  int aoo(int, int...);
  int lmao(int) noexcept;
  int lmao2(int);

  EXPECT_TRUE(nstd::is_function_v<decltype(Foo::s_foo_member)>);
  EXPECT_TRUE(nstd::is_function_v<decltype(Foo::s_foo_member_c)>);
  EXPECT_TRUE(nstd::is_function_v<decltype(Foo::s_foo_member_cn)>);
  EXPECT_TRUE(nstd::is_function_v<decltype(foo)>);
  EXPECT_TRUE(nstd::is_function_v<decltype(moo)>);
  EXPECT_TRUE(nstd::is_function_v<decltype(goo)>);
  EXPECT_TRUE(nstd::is_function_v<decltype(loo)>);
  EXPECT_TRUE(nstd::is_function_v<decltype(loo)>);
  EXPECT_TRUE(nstd::is_function_v<decltype(aoo)>);
}

TEST(TypeTraits, IsReference) {
  EXPECT_FALSE(nstd::is_lvalue_reference<int>::value);
  EXPECT_TRUE(nstd::is_lvalue_reference<int&>::value);
  EXPECT_FALSE(nstd::is_lvalue_reference<int&&>::value);

  EXPECT_FALSE(nstd::is_rvalue_reference<int>::value);
  EXPECT_FALSE(nstd::is_rvalue_reference<int&>::value);
  EXPECT_TRUE(nstd::is_rvalue_reference<int&&>::value);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
