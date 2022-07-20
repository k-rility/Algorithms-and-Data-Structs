#include <gtest/gtest.h>
#include "my_two_three_tree.hpp"

TEST(Two_Three_Tree, Constructor) {
//    my_two_three_tree<int> ttt;
//    ttt.insert(100);
//    ttt.insert(200);
//    ttt.insert(150);
//    ttt.insert(75);
//    ttt.insert(50);
//    ttt.insert(40);
//    ttt.insert(30);



//    ttt.insert(90);
//    ttt.insert(80);
//    ttt.insert(60);
//    ttt.insert(200);
//    ttt.insert(50);
//    ttt.insert(40);
//    ttt.insert(30);
//    ttt.insert(20);
//    ttt.insert(10);
//    ttt.insert(5);
//    ttt.insert(1);
}

TEST(TwoThreeTreeTests, LeftInsert) {
    my_two_three_tree<int> ttt;
    ttt.insert(200);
    ttt.insert(175);
    ttt.insert(150);
    ttt.insert(125);
    ttt.insert(100);
    ttt.insert(75);
    ttt.insert(50);
    ttt.insert(40);
    ttt.insert(30);
    ttt.insert(20);
    ttt.insert(10);
    ttt.insert(5);
}

TEST(TwoThreeTreeTests, RightInsert) {
    my_two_three_tree<int> ttt;
//    ttt.insert(100);
//    ttt.insert(200);
//    ttt.insert(300);
//    ttt.insert(400);
//    ttt.insert(500);
//    ttt.insert(600);
    ttt.insert(200);
    ttt.insert(150);
    ttt.insert(100);
    ttt.insert(300);
    ttt.insert(400);
    ttt.insert(500);
    ttt.insert(600);
}

TEST(TwoThreeTests, MiddleInsert) {
    my_two_three_tree<int> ttt;
    ttt.insert(100);
    ttt.insert(600);
    ttt.insert(150);
    ttt.insert(500);
    ttt.insert(525);
    ttt.insert(505);
    ttt.insert(510);
    ttt.insert(650);
    ttt.insert(675);
    ttt.insert(610);
    ttt.insert(620);
    ttt.insert(520);
    ttt.insert(515);
    ttt.insert(514);
    ttt.insert(512);
}