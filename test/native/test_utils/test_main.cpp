#include <gtest/gtest.h>
#include "RotatingIndex.hpp"

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    if (RUN_ALL_TESTS())
        ;
    return 0;
}

TEST(RotatingIndex, Construction) {
    RotatingIndex<int> sut(4);
    ASSERT_TRUE(true);
}

TEST(RotatingIndex, InitialState) {
    RotatingIndex<int> sut(4);
    ASSERT_EQ(sut.GetIndex(), 0);
}

TEST(RotatingIndex, TestOverflowWithGetIndexMethod) {
    RotatingIndex<int> sut(4);

    ASSERT_EQ(sut.GetIndexAndIncrement(), 0);
    ASSERT_EQ(sut.GetIndexAndIncrement(), 1);
    ASSERT_EQ(sut.GetIndexAndIncrement(), 2);
    ASSERT_EQ(sut.GetIndexAndIncrement(), 3);
    ASSERT_EQ(sut.GetIndexAndIncrement(), 0);
    ASSERT_EQ(sut.GetIndexAndIncrement(), 1);
}

TEST(RotatingIndex, TestOverflowWithCheckIfRevolvesMethod) {
    RotatingIndex<int> sut(4);

    ASSERT_FALSE(sut.IncrementAndCheckIfRevolves());
    ASSERT_FALSE(sut.IncrementAndCheckIfRevolves());
    ASSERT_FALSE(sut.IncrementAndCheckIfRevolves());
    ASSERT_TRUE(sut.IncrementAndCheckIfRevolves());
    ASSERT_FALSE(sut.IncrementAndCheckIfRevolves());
    ASSERT_FALSE(sut.IncrementAndCheckIfRevolves());
}

TEST(RotatingIndex, GetIndexReturnsCorrectValue) {
    RotatingIndex<int> sut(4);

    ASSERT_EQ(sut.GetIndexAndIncrement(), 0);
    ASSERT_EQ(sut.GetIndex(), 1);
    ASSERT_EQ(sut.GetIndexAndIncrement(), 1);
    ASSERT_EQ(sut.GetIndex(), 2);
}

TEST(RotatingIndex, TestReset) {
    RotatingIndex<int> sut(4);

    sut.GetIndexAndIncrement();
    sut.ResetIndex();
    ASSERT_EQ(sut.GetIndex(), 0);
}

TEST(RotatingIndex, TestDifferentTypeAndMaximum) {
    RotatingIndex<short> sut(6);

    ASSERT_FALSE(sut.IncrementAndCheckIfRevolves());
    ASSERT_FALSE(sut.IncrementAndCheckIfRevolves());
    ASSERT_FALSE(sut.IncrementAndCheckIfRevolves());
    ASSERT_FALSE(sut.IncrementAndCheckIfRevolves());
    ASSERT_FALSE(sut.IncrementAndCheckIfRevolves());
    ASSERT_TRUE(sut.IncrementAndCheckIfRevolves());
    ASSERT_FALSE(sut.IncrementAndCheckIfRevolves());
    ASSERT_FALSE(sut.IncrementAndCheckIfRevolves());
}