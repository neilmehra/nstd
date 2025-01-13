#include <gtest/gtest.h>

// TEST(Utility, Move) 
//   int x = 5;
//   const int& y = 5;
//   EXPECT_TRUE((nstd::is_same<decltype(nstd::move(x)), int&&>::value));
//   EXPECT_TRUE((nstd::is_same<decltype(nstd::move(y)), const int&&>::value));
//   EXPECT_TRUE((nstd::is_same<decltype(nstd::move(5)), int&&>::value));
// }
//
// // simple wrapper to tests perfect forwarding
// template <class T> constexpr T&& wrapper(T&& arg) {
//   return nstd::forward<T>(arg);
// }
//
// TEST(Utility, Forward) {
//   int x = 5;
//   const int& y = x;
//   EXPECT_TRUE((nstd::is_same<decltype(wrapper(x)), int&>::value));
//   EXPECT_TRUE((nstd::is_same<decltype(wrapper(y)), const int&>::value));
//   EXPECT_TRUE((nstd::is_same<decltype(wrapper(5)), int&&>::value));
// }
//
// // A simple test struct to track construction/destruction
// struct TestType {
//   static int count;
//   int x{0};
//
//   TestType() { ++count; }
//   explicit TestType(int val) : x(val) { ++count; }
//   ~TestType() { --count; }
//
//   void setVal(int v) { x = v; }
//   int getVal() const { return x; }
// };
//
// int TestType::count = 0;
//
// TEST(UniquePtr, DefaultConstructor) {
//   nstd::unique_ptr<int> ptr;
//   EXPECT_FALSE(ptr);
//   EXPECT_EQ(ptr.get(), nullptr);
// }
//
// TEST(UniquePtr, RawPointerConstructor) {
//   nstd::unique_ptr<int> ptr(new int(10));
//   EXPECT_TRUE(ptr);
//   EXPECT_NE(ptr.get(), nullptr);
//   EXPECT_EQ(*ptr, 10);
// }
//
// TEST(UniquePtr, MoveConstructor) {
//   nstd::unique_ptr<int> ptr1(new int(42));
//   EXPECT_TRUE(ptr1);
//
//   nstd::unique_ptr<int> ptr2(std::move(ptr1));
//   EXPECT_FALSE(ptr1);
//   EXPECT_TRUE(ptr2);
//   EXPECT_NE(ptr2.get(), nullptr);
//   EXPECT_EQ(*ptr2, 42);
// }
//
// TEST(UniquePtr, MoveAssignment) {
//   nstd::unique_ptr<int> ptr1(new int(100));
//   nstd::unique_ptr<int> ptr2(new int(200));
//   EXPECT_EQ(*ptr1, 100);
//   EXPECT_EQ(*ptr2, 200);
//
//   ptr2 = std::move(ptr1);
//   EXPECT_FALSE(ptr1);
//   EXPECT_TRUE(ptr2);
//   EXPECT_EQ(*ptr2, 100);
// }
//
// TEST(UniquePtr, OperatorBool) {
//   nstd::unique_ptr<int> ptr;
//   EXPECT_FALSE(ptr);
//
//   ptr = nstd::unique_ptr<int>(new int(5));
//   EXPECT_TRUE(ptr);
// }
//
// TEST(UniquePtr, DereferenceOperator) {
//   nstd::unique_ptr<int> ptr(new int(5));
//   EXPECT_EQ(*ptr, 5);
//   *ptr = 10;
//   EXPECT_EQ(*ptr, 10);
// }
//
// TEST(UniquePtr, ArrowOperator) {
//   nstd::unique_ptr<TestType> ptr(new TestType(123));
//   ASSERT_NE(ptr.get(), nullptr);
//   EXPECT_EQ(ptr->getVal(), 123);
//
//   ptr->setVal(456);
//   EXPECT_EQ(ptr->getVal(), 456);
// }
//
// TEST(UniquePtr, SwapFunction) {
//   nstd::unique_ptr<int> ptr1(new int(1));
//   nstd::unique_ptr<int> ptr2(new int(2));
//   EXPECT_EQ(*ptr1, 1);
//   EXPECT_EQ(*ptr2, 2);
//
//   swap(ptr1, ptr2);
//   EXPECT_EQ(*ptr1, 2);
//   EXPECT_EQ(*ptr2, 1);
// }
//
// TEST(UniquePtr, ArraySupport) {
//   nstd::unique_ptr<int[]> arrPtr(new int[3]{10, 20, 30});
//   EXPECT_EQ(arrPtr[0], 10);
//   EXPECT_EQ(arrPtr[1], 20);
//   EXPECT_EQ(arrPtr[2], 30);
//
//   arrPtr[1] = 999;
//   EXPECT_EQ(arrPtr[1], 999);
// }
//
// TEST(UniquePtr, MakeUnique) {
//   auto intPtr = nstd::make_unique<int>(77);
//   ASSERT_TRUE(intPtr);
//   EXPECT_EQ(*intPtr, 77);
//
//   auto objPtr = nstd::make_unique<TestType>(999);
//   ASSERT_TRUE(objPtr);
//   EXPECT_EQ(objPtr->getVal(), 999);
// }
//
// TEST(UniquePtr, DestructionTest) {
//   {
//     EXPECT_EQ(TestType::count, 0);
//     auto ptr = nstd::make_unique<TestType>(42);
//     EXPECT_EQ(TestType::count, 1);
//     EXPECT_EQ(ptr->getVal(), 42);
//   }
//   EXPECT_EQ(TestType::count, 0);
// }
//
// TEST(SharedPtr, DefaultConstructor) {
//   nstd::shared_ptr<int> ptr;
//   EXPECT_FALSE(ptr);
//   EXPECT_EQ(ptr.get(), nullptr);
// }
//
// TEST(SharedPtr, RawPointerConstructor) {
//   nstd::shared_ptr<int> ptr(new int(10));
//   EXPECT_TRUE(ptr);
//   EXPECT_NE(ptr.get(), nullptr);
//   EXPECT_EQ(*ptr, 10);
// }
//
// TEST(SharedPtr, MoveConstructor) {
//   nstd::shared_ptr<int> ptr1(new int(42));
//   EXPECT_TRUE(ptr1);
//   EXPECT_EQ(ptr1.count(), 1);
//
//   nstd::shared_ptr<int> ptr2(std::move(ptr1));
//   EXPECT_FALSE(ptr1);
//   EXPECT_TRUE(ptr2);
//   EXPECT_NE(ptr2.get(), nullptr);
//   EXPECT_EQ(*ptr2, 42);
// }
//
// TEST(SharedPtr, MoveAssignment) {
//   nstd::shared_ptr<int> ptr1(new int(100));
//   nstd::shared_ptr<int> ptr2(new int(200));
//   EXPECT_EQ(*ptr1, 100);
//   EXPECT_EQ(*ptr2, 200);
//
//   ptr2 = std::move(ptr1);
//   EXPECT_FALSE(ptr1);
//   EXPECT_TRUE(ptr2);
//   EXPECT_EQ(*ptr2, 100);
// }
//
// TEST(SharedPtr, OperatorBool) {
//   nstd::shared_ptr<int> ptr;
//   EXPECT_FALSE(ptr);
//
//   ptr = nstd::shared_ptr<int>(new int(5));
//   EXPECT_TRUE(ptr);
// }
//
// TEST(SharedPtr, DereferenceOperator) {
//   nstd::shared_ptr<int> ptr(new int(5));
//   EXPECT_EQ(*ptr, 5);
//   *ptr = 10;
//   EXPECT_EQ(*ptr, 10);
// }
//
// TEST(SharedPtr, ArrowOperator) {
//   nstd::shared_ptr<TestType> ptr(new TestType(123));
//   ASSERT_NE(ptr.get(), nullptr);
//   EXPECT_EQ(ptr->getVal(), 123);
//
//   ptr->setVal(456);
//   EXPECT_EQ(ptr->getVal(), 456);
// }
//
// TEST(SharedPtr, SwapFunction) {
//   nstd::shared_ptr<int> ptr1(new int(1));
//   nstd::shared_ptr<int> ptr2(new int(2));
//   EXPECT_EQ(*ptr1, 1);
//   EXPECT_EQ(*ptr2, 2);
//
//   swap(ptr1, ptr2);
//   EXPECT_EQ(*ptr1, 2);
//   EXPECT_EQ(*ptr2, 1);
// }
//
// TEST(SharedPtr, ArraySupport) {
//   nstd::shared_ptr<int[]> arrPtr(new int[3]{10, 20, 30});
//   EXPECT_EQ(arrPtr[0], 10);
//   EXPECT_EQ(arrPtr[1], 20);
//   EXPECT_EQ(arrPtr[2], 30);
//
//   arrPtr[1] = 999;
//   EXPECT_EQ(arrPtr[1], 999);
// }
//
// TEST(SharedPtr, MakeShared) {
//   auto intPtr = nstd::make_shared<int>(77);
//   ASSERT_TRUE(intPtr);
//   EXPECT_EQ(*intPtr, 77);
//
//   auto objPtr = nstd::make_shared<TestType>(999);
//   ASSERT_TRUE(objPtr);
//   EXPECT_EQ(objPtr->getVal(), 999);
// }
//
// TEST(SharedPtr, SharingTest) {
//   auto ptr1 = nstd::make_shared<int>(42);
//   EXPECT_EQ(ptr1.count(), 1);
//   {
//     auto ptr2 = ptr1;
//     EXPECT_EQ(ptr1.count(), 2);
//     EXPECT_EQ(ptr2.count(), 2);
//   }
//   EXPECT_EQ(ptr1.count(), 1);
// }

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
