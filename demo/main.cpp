#include <iostream>
#include "my_red_black_tree.hpp"

int main() {
    my_red_black_tree<int> rbt;
    rbt.insert(100);
    rbt.insert(80);
    rbt.insert(120);
    rbt.insert(140);
    rbt.insert(60);
    rbt.insert(40);
    rbt.insert(20);
    rbt.insert(50);
    rbt.insert(10);
    rbt.insert(5);
    rbt.insert(25);

    rbt.remove(25);
    rbt.remove(50);


//    rbt.remove(32);
//    rbt.remove(50);
//    std::cout << rbt.bh() << std::endl;
    return 0;
}
