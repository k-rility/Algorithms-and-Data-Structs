#include <iostream>
#include "my_red_black_tree.hpp"
#include <string>

void func(int *&tt) {
    std::cout << &tt << std::endl;
    int b = 20;
    int *other = &b;
    tt = other;
    std::cout << &tt << std::endl;
//    std::cout << *tt << std::endl;
}

int main() {
    int a = 10;
    int *ptr = &a;
    std::cout << &ptr << std::endl;
    func(ptr);
    std::cout << *ptr << std::endl;

//    my_red_black_tree<int> rbt;

//    rbt.insert(100);
//    rbt.insert(50);
//    rbt.insert(120);
//    rbt.remove(100);

//    rbt.insert(80);
//    rbt.insert(60);
//    rbt.insert(40);
//    rbt.insert(20);
//    rbt.insert(90);
//    rbt.insert(70);
//    rbt.insert(50);
//    rbt.insert(30);
//    rbt.insert(10);
//    rbt.insert(95);
//    rbt.insert(85);
//    rbt.insert(75);
//    rbt.insert(65);
//    rbt.insert(55);
//    rbt.insert(45);
//    rbt.insert(35);
//    rbt.insert(25);
//    rbt.insert(15);
//    rbt.insert(5);

//    rbt.remove(85);
//    rbt.remove(100);
//
//    rbt.insert(101);
//    rbt.insert(1);
//    rbt.insert(102);
//    rbt.insert(2);
//    rbt.insert(103);
//    rbt.insert(3);
//
//
//    rbt.insert(120);
//    rbt.insert(140);
//    rbt.insert(160);
//    rbt.insert(180);
//
//    rbt.remove(180);
//    rbt.remove(140);
//    rbt.remove(160);
//    rbt.remove(103);
//    rbt.remove(101);
//    rbt.remove(90);
//
//    rbt.remove(120);
//
//    rbt.insert(100);
//    rbt.insert(80);
//    rbt.insert(120);
//    rbt.insert(140);
//    rbt.insert(60);
//    rbt.insert(40);
//    rbt.insert(20);
//    rbt.insert(50);
//    rbt.insert(10);
//    rbt.insert(5);
//    rbt.insert(15);
//
//    rbt.remove(15);
//
//    rbt.insert(25);
//
//    rbt.remove(50);

//    rbt.remove(25);
//    rbt.remove(50);


//    rbt.remove(32);
//    rbt.remove(50);
//    std::cout << rbt.bh() << std::endl;
    return 0;
}
