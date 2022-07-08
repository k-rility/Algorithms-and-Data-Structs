#include "gtest/gtest.h"
#include "my_red_black_tree.hpp"

TEST(Red_Black_Tree, Constructor) {
    my_red_black_tree<int> rbt;
    ASSERT_TRUE(rbt.empty());

    rbt.insert(10);

    ASSERT_FALSE(rbt.empty());
}

TEST(Red_Black_Tree, Destructor) {}

TEST(Red_Black_Tree, Find) {}

TEST(Red_Black_Tree, LeftRotate) {}

TEST(Red_Black_Tree, RightRotate) {}