#include <gtest/gtest.h>
#include "my_splay_tree.hpp"

TEST(Splay_Tree, Constructor) {
    my_splay_tree<int> spt;
    spt.insert(100);
    spt.insert(50);
}