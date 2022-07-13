#include <gtest/gtest.h>
#include "my_avl_tree.hpp"

TEST(AVL_Tree, Constructor) {
    my_avl_tree<int> avlt;
    avlt.insert(100);
    avlt.insert(200);
//    avlt.insert(50);
    avlt.insert(300);
}

TEST(AVL_Tree, Destructor) {

}
