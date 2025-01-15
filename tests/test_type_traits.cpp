#include "../include/type_traits.hpp"
#include <gtest/gtest.h>

struct Foo {
  int b;
  const int c;
  volatile int d;
  const volatile int e;
  void foo();
  void foo_c() const;
  void foo_n() noexcept;
  void foo_cn() const noexcept;
  void foo_cn_lref() const& noexcept;
  void foo_cn_rref() const&& noexcept;

  static int z;
  static const int y;
  static volatile int x;
  static const volatile int w;

  static void s_foo();
  static void s_foo_n() noexcept;
};

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
  struct A {
    void bar();
    static void bar2();
  };
  EXPECT_TRUE(nstd::is_pointer_v<int*>);
  EXPECT_TRUE(nstd::is_pointer_v<void*>);
  EXPECT_TRUE(nstd::is_pointer_v<int* const>);
  EXPECT_TRUE(nstd::is_pointer_v<decltype(&foo)>);
  EXPECT_TRUE(nstd::is_pointer_v<decltype(&goo)>);
  EXPECT_FALSE(nstd::is_pointer_v<decltype(&A::bar)>);
  EXPECT_TRUE(nstd::is_pointer_v<decltype(&A::bar2)>);

  EXPECT_TRUE(nstd::is_pointer_v<volatile int*>);
  EXPECT_TRUE(nstd::is_pointer_v<volatile void*>);
  EXPECT_TRUE(nstd::is_pointer_v<volatile int* const>);
  EXPECT_TRUE(nstd::is_pointer_v<volatile decltype(&foo)>);
  EXPECT_TRUE(nstd::is_pointer_v<volatile decltype(&goo)>);
  EXPECT_FALSE(nstd::is_pointer_v<volatile decltype(&A::bar)>);
  EXPECT_TRUE(nstd::is_pointer_v<volatile decltype(&A::bar2)>);

  EXPECT_TRUE(nstd::is_pointer_v<const int*>);
  EXPECT_TRUE(nstd::is_pointer_v<const void*>);
  EXPECT_TRUE(nstd::is_pointer_v<const int* const>);
  EXPECT_TRUE(nstd::is_pointer_v<const decltype(&foo)>);
  EXPECT_TRUE(nstd::is_pointer_v<const decltype(&goo)>);
  EXPECT_FALSE(nstd::is_pointer_v<const decltype(&A::bar)>);
  EXPECT_TRUE(nstd::is_pointer_v<const decltype(&A::bar2)>);

  EXPECT_TRUE(nstd::is_pointer_v<const volatile int*>);
  EXPECT_TRUE(nstd::is_pointer_v<const volatile void*>);
  EXPECT_TRUE(nstd::is_pointer_v<const volatile int* const>);
  EXPECT_TRUE(nstd::is_pointer_v<const volatile decltype(&foo)>);
  EXPECT_TRUE(nstd::is_pointer_v<const volatile decltype(&goo)>);
  EXPECT_FALSE(nstd::is_pointer_v<const volatile decltype(&A::bar)>);
  EXPECT_TRUE(nstd::is_pointer_v<const volatile decltype(&A::bar2)>);
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

TEST(TypeTraits, IsMemberObjectPtr) {
  EXPECT_FALSE(nstd::is_member_object_pointer_v<decltype(&Foo::foo)>);
  EXPECT_FALSE(nstd::is_member_object_pointer_v<decltype(&Foo::foo_c)>);
  EXPECT_FALSE(nstd::is_member_object_pointer_v<decltype(&Foo::foo_n)>);
  EXPECT_FALSE(nstd::is_member_object_pointer_v<decltype(&Foo::foo_cn)>);
  EXPECT_FALSE(nstd::is_member_object_pointer_v<decltype(&Foo::foo_cn_lref)>);
  EXPECT_FALSE(nstd::is_member_object_pointer_v<decltype(&Foo::foo_cn_rref)>);
  EXPECT_FALSE(nstd::is_member_object_pointer_v<decltype(&Foo::s_foo)>);
  EXPECT_FALSE(nstd::is_member_object_pointer_v<decltype(&Foo::s_foo_n)>);

  EXPECT_TRUE(nstd::is_member_object_pointer_v<decltype(&Foo::b)>);
  EXPECT_TRUE(nstd::is_member_object_pointer_v<decltype(&Foo::c)>);
  EXPECT_TRUE(nstd::is_member_object_pointer_v<decltype(&Foo::d)>);
  EXPECT_TRUE(nstd::is_member_object_pointer_v<decltype(&Foo::e)>);

  EXPECT_FALSE(nstd::is_member_object_pointer_v<decltype(&Foo::z)>);
  EXPECT_FALSE(nstd::is_member_object_pointer_v<decltype(&Foo::y)>);
  EXPECT_FALSE(nstd::is_member_object_pointer_v<decltype(&Foo::x)>);
  EXPECT_FALSE(nstd::is_member_object_pointer_v<decltype(&Foo::w)>);
}

TEST(TypeTraits, IsMemberFunctionPtr) {
  EXPECT_TRUE(nstd::is_member_function_pointer_v<decltype(&Foo::foo)>);
  EXPECT_TRUE(nstd::is_member_function_pointer_v<decltype(&Foo::foo_c)>);
  EXPECT_TRUE(nstd::is_member_function_pointer_v<decltype(&Foo::foo_n)>);
  EXPECT_TRUE(nstd::is_member_function_pointer_v<decltype(&Foo::foo_cn)>);
  EXPECT_TRUE(nstd::is_member_function_pointer_v<decltype(&Foo::foo_cn_lref)>);
  EXPECT_TRUE(nstd::is_member_function_pointer_v<decltype(&Foo::foo_cn_rref)>);
  EXPECT_FALSE(nstd::is_member_function_pointer_v<decltype(&Foo::s_foo)>);
  EXPECT_FALSE(nstd::is_member_function_pointer_v<decltype(&Foo::s_foo_n)>);

  EXPECT_FALSE(nstd::is_member_function_pointer_v<decltype(&Foo::b)>);
  EXPECT_FALSE(nstd::is_member_function_pointer_v<decltype(&Foo::c)>);
  EXPECT_FALSE(nstd::is_member_function_pointer_v<decltype(&Foo::d)>);
  EXPECT_FALSE(nstd::is_member_function_pointer_v<decltype(&Foo::e)>);

  EXPECT_FALSE(nstd::is_member_function_pointer_v<decltype(&Foo::z)>);
  EXPECT_FALSE(nstd::is_member_function_pointer_v<decltype(&Foo::y)>);
  EXPECT_FALSE(nstd::is_member_function_pointer_v<decltype(&Foo::x)>);
  EXPECT_FALSE(nstd::is_member_function_pointer_v<decltype(&Foo::w)>);
}

TEST(TypeTraits, IsFunction) {
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

  EXPECT_TRUE(nstd::is_function_v<decltype(Foo::s_foo)>);
  EXPECT_TRUE(nstd::is_function_v<decltype(Foo::s_foo_n)>);
  EXPECT_TRUE(nstd::is_function_v<decltype(foo)>);
  EXPECT_TRUE(std::is_function_v<decltype(foo)>);
  EXPECT_TRUE(nstd::is_function_v<decltype(moo)>);
  EXPECT_TRUE(nstd::is_function_v<decltype(goo)>);
  EXPECT_TRUE(nstd::is_function_v<decltype(loo)>);
  EXPECT_TRUE(nstd::is_function_v<decltype(loo)>);
  EXPECT_TRUE(nstd::is_function_v<decltype(aoo)>);
}

TEST(TypeTraits, IsReference) {}

TEST(TypeTraits, IsArithmetic) {}

TEST(TypeTraits, IsFundamental) {}

TEST(TypeTraits, IsObject) {}

TEST(TypeTraits, IsScalar) {}

TEST(TypeTraits, IsCompound) {}

TEST(TypeTraits, IsMemberPtr) {}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
