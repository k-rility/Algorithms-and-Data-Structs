#include <iostream>
#include "my_red_black_tree.hpp"

int main() {
    my_red_black_tree<int> rbt;
    rbt.insert(20);
    rbt.insert(15);
    rbt.insert(35);
    rbt.insert(40);
    rbt.insert(30);
    rbt.insert(45);
    rbt.insert(50);
    rbt.insert(60);
    return 0;
}
