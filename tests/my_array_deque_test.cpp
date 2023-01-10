#include "gtest/gtest.h"
#include "my_array_deque.hpp"

TEST(Deque, test) {

    Deque<int> d;
    d.setSize(5);
    d.pushFront(10);
    d.pushFront(20);
    d.pushFront(30);
    std::cout << d << std::endl;
}