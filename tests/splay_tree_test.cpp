#include <gtest/gtest.h>
#include "my_splay_tree.hpp"

TEST(Splay_Tree, Constructor) {
    my_splay_tree<int> spt;
    spt.insert(41);
    spt.insert(38);
    spt.insert(31);
    spt.insert(12);
    spt.insert(19);
    spt.insert(8);
}