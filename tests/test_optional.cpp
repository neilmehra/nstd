#include <gtest/gtest.h>
#include "../include/optional.hpp"  // Adjust include as needed for your project structure

#include <string>

// We place our tests in a test fixture or in separate TEST() blocks.
// For brevity, we'll use separate TEST blocks here.

// 1. Test default construction (empty optional)
TEST(OptionalTest, DefaultConstructor) {
    nstd::optional<int> opt;
    EXPECT_FALSE(opt.has_value());
    EXPECT_FALSE(static_cast<bool>(opt)); // same as !opt
}

// 2. Test construction from a value (copy)
TEST(OptionalTest, ConstructFromValueCopy) {
    nstd::optional<int> opt(42);
    EXPECT_TRUE(opt.has_value());
    EXPECT_EQ(opt.value(), 42);
}

// 3. Test construction from a value (move)
TEST(OptionalTest, ConstructFromValueMove) {
    std::string str = "Hello";
    nstd::optional<std::string> opt(nstd::move(str));
    EXPECT_TRUE(opt.has_value());
    EXPECT_EQ(opt.value(), "Hello");
    // str may be moved from, but let's just check it's not strictly required
}

// 4. Test copy constructor
TEST(OptionalTest, CopyConstructor) {
    nstd::optional<int> opt1(100);
    nstd::optional<int> opt2(opt1); // copy-construct

    EXPECT_TRUE(opt2.has_value());
    EXPECT_EQ(opt2.value(), 100);
}

// 5. Test move constructor
TEST(OptionalTest, MoveConstructor) {
    nstd::optional<int> opt1(200);
    nstd::optional<int> opt2(nstd::move(opt1));

    EXPECT_TRUE(opt2.has_value());
    EXPECT_EQ(opt2.value(), 200);

    // opt1 may now be empty or has_value could still be true depending on implementation,
    // but we expect your code to set engaged = false on the moved-from.
    EXPECT_FALSE(opt1.has_value()); 
}

// 6. Test copy assignment
TEST(OptionalTest, CopyAssignment) {
    nstd::optional<int> opt1(300);
    nstd::optional<int> opt2;
    opt2 = opt1; // copy-assign

    EXPECT_TRUE(opt2.has_value());
    EXPECT_EQ(opt2.value(), 300);

    // copy-assign an empty to a non-empty
    nstd::optional<int> opt3;
    opt2 = opt3; // opt3 is empty
    EXPECT_FALSE(opt2.has_value());
}

// 7. Test move assignment
TEST(OptionalTest, MoveAssignment) {
    nstd::optional<std::string> opt1(std::string("Test"));
    nstd::optional<std::string> opt2;
    opt2 = nstd::move(opt1); // move-assign

    EXPECT_TRUE(opt2.has_value());
    EXPECT_EQ(opt2.value(), "Test");
    EXPECT_FALSE(opt1.has_value()); // per your implementation's behavior
}

// 8. Test operator=(T const&) and operator=(T&&)
TEST(OptionalTest, AssignValueOperators) {
    nstd::optional<std::string> opt;
    EXPECT_FALSE(opt.has_value());

    opt = std::string("Hello");
    EXPECT_TRUE(opt.has_value());
    EXPECT_EQ(opt.value(), "Hello");

    opt = std::string("World");
    EXPECT_EQ(opt.value(), "World");

    // Move assignment
    std::string mover = "Movable";
    opt = nstd::move(mover);
    EXPECT_TRUE(opt.has_value());
    EXPECT_EQ(opt.value(), "Movable");
}

// 9. Test emplace
TEST(OptionalTest, Emplace) {
    nstd::optional<std::string> opt;
    EXPECT_FALSE(opt.has_value());

    auto& ref = opt.emplace("Data");
    EXPECT_TRUE(opt.has_value());
    EXPECT_EQ(opt.value(), "Data");
    EXPECT_EQ(&ref, &opt.value()); // emplace returns reference to the new value

    // Emplace again should destroy old value and create a new one
    opt.emplace(5, 'X'); // std::string(size_t n, char c)
    EXPECT_EQ(opt.value(), "XXXXX");
}

// 10. Test reset
TEST(OptionalTest, Reset) {
    nstd::optional<int> opt(123);
    EXPECT_TRUE(opt.has_value());
    EXPECT_EQ(opt.value(), 123);

    opt.reset();
    EXPECT_FALSE(opt.has_value());
    EXPECT_THROW(opt.value(), nstd::bad_optional_access);

    // Reset on an already-empty optional
    opt.reset();
    EXPECT_FALSE(opt.has_value());
}

// 11. Test throwing bad_optional_access if no value
TEST(OptionalTest, ThrowIfNoValue) {
    nstd::optional<int> opt; // empty
    EXPECT_FALSE(opt.has_value());
    EXPECT_THROW({
        (void) opt.value(); // force an exception
    }, nstd::bad_optional_access);
}

// 12. Test swap (we rely on your `swap(optional<T>& rhs)`)
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
