#include "../include/optional.hpp"
#include <gtest/gtest.h>

#include <string>

TEST(OptionalTest, DefaultConstructor) {
  nstd::optional<int> opt;
  EXPECT_FALSE(opt.has_value());
  EXPECT_FALSE(static_cast<bool>(opt));
}

TEST(OptionalTest, ConstructFromValueCopy) {
  nstd::optional<int> opt(42);
  EXPECT_TRUE(opt.has_value());
  EXPECT_EQ(opt.value(), 42);
}

TEST(OptionalTest, ConstructFromValueMove) {
  std::string str = "Hello";
  nstd::optional<std::string> opt(nstd::move(str));
  EXPECT_TRUE(opt.has_value());
  EXPECT_EQ(opt.value(), "Hello");
}

TEST(OptionalTest, CopyConstructor) {
  nstd::optional<int> opt1(100);
  nstd::optional<int> opt2(opt1);

  EXPECT_TRUE(opt2.has_value());
  EXPECT_EQ(opt2.value(), 100);
}

TEST(OptionalTest, MoveConstructor) {
  nstd::optional<int> opt1(200);
  nstd::optional<int> opt2(nstd::move(opt1));

  EXPECT_TRUE(opt2.has_value());
  EXPECT_EQ(opt2.value(), 200);

  EXPECT_FALSE(opt1.has_value());
}

TEST(OptionalTest, CopyAssignment) {
  nstd::optional<int> opt1(300);
  nstd::optional<int> opt2;
  opt2 = opt1;

  EXPECT_TRUE(opt2.has_value());
  EXPECT_EQ(opt2.value(), 300);

  nstd::optional<int> opt3;
  opt2 = opt3;
  EXPECT_FALSE(opt2.has_value());
}

TEST(OptionalTest, MoveAssignment) {
  nstd::optional<std::string> opt1(std::string("Test"));
  nstd::optional<std::string> opt2;
  opt2 = nstd::move(opt1);

  EXPECT_TRUE(opt2.has_value());
  EXPECT_EQ(opt2.value(), "Test");
  EXPECT_FALSE(opt1.has_value());
}

TEST(OptionalTest, AssignValueOperators) {
  nstd::optional<std::string> opt;
  EXPECT_FALSE(opt.has_value());

  opt = std::string("Hello");
  EXPECT_TRUE(opt.has_value());
  EXPECT_EQ(opt.value(), "Hello");

  opt = std::string("World");
  EXPECT_EQ(opt.value(), "World");

  std::string mover = "Movable";
  opt = nstd::move(mover);
  EXPECT_TRUE(opt.has_value());
  EXPECT_EQ(opt.value(), "Movable");
}

TEST(OptionalTest, Emplace) {
  nstd::optional<std::string> opt;
  EXPECT_FALSE(opt.has_value());

  auto& ref = opt.emplace("Data");
  EXPECT_TRUE(opt.has_value());
  EXPECT_EQ(opt.value(), "Data");
  EXPECT_EQ(&ref, &opt.value());

  opt.emplace(5, 'X');
  EXPECT_EQ(opt.value(), "XXXXX");
}

TEST(OptionalTest, Reset) {
  nstd::optional<int> opt(123);
  EXPECT_TRUE(opt.has_value());
  EXPECT_EQ(opt.value(), 123);

  opt.reset();
  EXPECT_FALSE(opt.has_value());
  EXPECT_THROW(opt.value(), nstd::bad_optional_access);

  opt.reset();
  EXPECT_FALSE(opt.has_value());
}

TEST(OptionalTest, ThrowIfNoValue) {
  nstd::optional<int> opt;
  EXPECT_FALSE(opt.has_value());
  EXPECT_THROW({ (void)opt.value(); }, nstd::bad_optional_access);
}

TEST(OptionalTest, Swap) {
  nstd::optional<int> opt1(10);
  nstd::optional<int> opt2(20);

  opt1.swap(opt2);
  EXPECT_EQ(opt1.value(), 20);
  EXPECT_EQ(opt2.value(), 10);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
