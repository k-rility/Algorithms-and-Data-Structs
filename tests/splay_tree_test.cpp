#include <gtest/gtest.h>
#include "my_splay_tree.hpp"

TEST(SplayTree, Add) {
    SplayTree<std::string> spt;
    spt.Add(100, "aaa");
    spt.Add(200, "bbb");
    spt.Add(300, "ccc");
    spt.Add(75, "ddd");
    spt.Add(50, "eee");
    spt.Add(400, "eee");
    spt.Add(60, "fff");
    spt.Add(250, "ggg");
}

TEST(SplayTree, MaxMin) {
    SplayTree<std::string> spt;
    spt.Add(100, "aaa");

    EXPECT_EQ(spt.Max().first, 100);
    EXPECT_EQ(spt.Max().second, "aaa");

    EXPECT_EQ(spt.Min().first, 100);
    EXPECT_EQ(spt.Min().second, "aaa");

    spt.Add(200, "bbb");
    spt.Add(300, "ccc");
    spt.Add(75, "ddd");
    spt.Add(50, "eee");
    spt.Add(400, "fff");
    spt.Add(60, "ggg");
    spt.Add(250, "hhh");

    EXPECT_EQ(spt.Max().first, 400);
    EXPECT_EQ(spt.Max().second, "fff");

    EXPECT_EQ(spt.Min().first, 50);
    EXPECT_EQ(spt.Min().second, "eee");
}

TEST(SplayTree, Set) {
    SplayTree<std::string> spt;
    spt.Add(100, "aaa");
    spt.Add(200, "bbb");
    spt.Add(300, "ccc");
    spt.Add(75, "ddd");
    spt.Add(50, "eee");
    spt.Add(400, "fff");
    spt.Add(60, "ggg");
    spt.Add(250, "hhh");

//    spt.Set(50, "хуй");
    spt.Set(1, "хуй");
}

TEST(SplayTree, Search) {
    SplayTree<std::string> spt;
    spt.Add(100, "aaa");

    EXPECT_EQ(spt.Search(100)->_Value, "aaa");

    spt.Add(200, "bbb");
    spt.Add(300, "ccc");
    spt.Add(75, "ddd");
    spt.Add(50, "eee");
    spt.Add(400, "fff");
    spt.Add(60, "ggg");
    spt.Add(250, "hhh");

    EXPECT_EQ(spt.Search(1), nullptr);
    EXPECT_EQ(spt.Search(400)->_Value, "fff");
    EXPECT_EQ(spt.Search(10000), nullptr);
    EXPECT_EQ(spt.Search(251), nullptr);
}

TEST(SplayTree, Delete) {
    SplayTree<std::string> spt;
    spt.Add(100, "aaa");
    spt.Add(200, "bbb");
//    spt.Add(300, "ccc");
//    spt.Add(75, "ddd");
//    spt.Add(50, "eee");
//    spt.Add(400, "fff");
//    spt.Add(60, "ggg");
//    spt.Add(250, "hhh");
//
//    spt.Delete(100);
    try {
        spt.Delete(1);
    } catch (const std::logic_error &err) {
        std::cout << err.what() << std::endl;
    }
//    spt.Delete(300);
    spt.Print();
//    spt.Delete(60);

    SplayTree<std::string> test;
//    test.Add(200, "fdsfs");
//    test.Add(400, "fdsfs");
//    test.Add(500, "fdsfs");
//    test.Add(175, "fdsfs");
//    test.Delete(500);
    test.Print();
}

TEST(SplayTree, Depth) {

    SplayTree<std::string> test;
    test.Add(10, "aaa");
    test.Add(20, "aaa");
    test.Add(30, "aaa");
    std::cout << test.Depth() << std::endl;
//    test.Add(10, "aaa");
    test.Print();

    SplayTree<std::string> spt;

    EXPECT_EQ(0, spt.Depth());

    spt.Add(100, "aaa");

    EXPECT_EQ(1, spt.Depth());

    spt.Add(200, "bbb");
    spt.Add(300, "ccc");
    spt.Add(75, "ddd");
    spt.Add(50, "eee");
    spt.Add(400, "fff");
    spt.Add(60, "ggg");
    spt.Add(250, "hhh");
//    std::cout << spt << std::endl;
    spt.Print();
    EXPECT_EQ(5, spt.Depth());

    SplayTree<std::string> spt2;
    spt2.Print();
}

TEST(SplayTree, UnlnownErr) {
    SplayTree<std::string> spt;
    spt.Add(200, "ffsfs");
    spt.Add(400, "ffsfs");
//    spt.Add(300, "ffsfs");
//    spt.Add(250, "ffsfs");
//    spt.Set(300, "shava");
    spt.Delete(200);
    spt.Delete(250);
    spt.Max();
    spt.Print();
}

TEST(SplayTree, What) {
    SplayTree<std::string> test;
    test.Add(200, "lol");
    test.Print();
    test.Add(900, "tomnov pidor");
    test.Print();
    test.Set(900, "kek");
    test.Print();
    test.Delete(900);
}

TEST(SplayTree, Print) {
    SplayTree<std::string> test;
    test.Add(200, "bbb");
    test.Add(300, "ccc");
    test.Add(75, "ddd");
    test.Add(50, "eee");
    test.Add(400, "fff");
    test.Add(60, "ggg");
    test.Add(250, "hhh");
    test.Print();
}

TEST(SplayTree, Test5) {
    SplayTree<std::string> test;
    test.Add(8, "10");
    test.Add(4, "14");
    test.Add(7, "15");
    test.Add(9, "11");
    test.Add(3, "13");
    test.Add(5, "16");
    test.Add(88, "1");
    test.Add(11, "2");
    test.Add(6, "18");
    test.Add(4, "14");
    test.Set(11, "121");
    test.Set(6, "36");
    test.Set(8, "64");
    test.Set(5, "25");
    test.Set(88, "100500");
    test.Print();
}

TEST(SplayTree, Test9) {
//    try {
    SplayTree<std::string> test;
    test.Add(8, "10");
    test.Add(4, "14");
    test.Add(7, "15");
    test.Set(8, "11");
    test.Add(3, "13");
    test.Add(5, "16");
    test.Add(45, "1");
    test.Add(46, "2");
    test.Delete(46);
    test.Add(10, "100");
    test.Delete(3);
    test.Print();
    test.Delete(5);
    test.Add(6, "36");
    test.Add(9, "81");
    test.Print();
    test.Delete(8);
    test.Print();
    test.Delete(45);
    try {
        test.Delete(100);
    } catch (...) {
        std::cout << "error\n";
    }
    test.Print();
    test.Delete(7);
    test.Delete(10);
    test.Print();
    test.Delete(9);
    test.Delete(4);
    test.Delete(6);
    test.Print();
    try {
        test.Delete(8);
    } catch (...) {
        std::cout << "error\n";
    }
    test.Print();
//    } catch (const std::logic_error &err) {
//        std::cout << "error\n";
//        std::cout << err.what() << std::endl;
//    }
}

TEST(SplayTree, NewPrint) {
    SplayTree<std::string> test;
    test.Add(200, "bbb");
    test.Add(300, "ccc");
    test.Add(75, "ddd");
    test.Add(50, "eee");
    test.Add(400, "fff");
    test.Add(60, "ggg");
    test.Add(250, "hhh");
    test.Add(900, "hhh");
    test.Add(1000, "hhh");
    test.Add(2000, "hhh");
//    test.Add(8, "10");
//    test.Add(4, "14");
//    test.Add(7, "15");
//    test.Add(9, "11");
//    test.Add(3, "13");
//    test.Add(5, "16");
//    test.Add(88, "1");
    test.Print();
}
