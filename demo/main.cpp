#include <iostream>
#include "my_red_black_tree.hpp"

int main() {
    my_red_black_tree<int> rbt;
    rbt.insert(30);
    rbt.insert(40);
    rbt.insert(25);
    rbt.insert(50);
    rbt.insert(35);
    rbt.insert(37);
    rbt.insert(32);
    rbt.remove(50);
//    std::cout << rbt.bh() << std::endl;
    return 0;
}
