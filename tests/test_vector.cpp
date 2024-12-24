#include <gtest/gtest.h>
#include "../include/vector.hpp"

TEST(VectorTest, DefaultConstructor) {
    Vector<int> v(10);
    EXPECT_EQ(v.get_capacity(), 10);
}

TEST(VectorTest, ElementAccess) {
    Vector<int> v(5);
    v[0] = 42;
    EXPECT_EQ(v[1], 42);
}

TEST(VectorTest, OutOfBoundsAccess) {
    Vector<int> v(5);
    EXPECT_THROW(v[5] = 100, std::out_of_range);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
