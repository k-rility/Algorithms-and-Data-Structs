#include <gtest/gtest.h>
#include "my_min_heap.hpp"

TEST(MinHeap, Add) {
    MinHeap<int64_t, std::string> mh;
    mh.Add(10, "hui");
    mh.Add(20, "lol");
    mh.Add(30, "lol");
    mh.Add(40, "lol");
    mh.Add(50, "lol");
    mh.Add(2000, "lol");
    mh.Add(1000000, "lol");
}

TEST(MinHeap, Min) {
    MinHeap<int64_t, std::string> mh;
    mh.Add(10, "hui");
    mh.Add(20, "lol");
    mh.Add(30, "lol");
    mh.Add(40, "lol");
    mh.Add(50, "lol");
    mh.Add(2000, "lol");
    mh.Add(1000000, "lol");
    EXPECT_EQ(10, mh.Min().first.first);
    std::cout << mh.Min().first.first << std::endl;
}

TEST(MinHeap, Max) {
    MinHeap<int64_t, std::string> mh;
    mh.Add(10, "hui");
    mh.Add(20, "lol");
    mh.Add(30, "lol");
    mh.Add(40, "lol");
    mh.Add(50, "lol");
    mh.Add(2000, "lol");
    mh.Add(100'000'0, "lol");
    EXPECT_EQ(100'000'0, mh.Max().first.first);
    std::cout << mh.Max().first.first << std::endl;
}

TEST(MinHeap, ExtractMin) {
    MinHeap<int64_t, std::string> mh;
    mh.Add(10, "hui");
    mh.Add(20, "lol");
    mh.Add(30, "lol");
    mh.Add(40, "lol");
    mh.Add(50, "lol");
    mh.Add(2000, "lol");
    mh.Add(100'000'0, "lol");
    EXPECT_EQ(10, mh.ExtractMin().first);
}

TEST(MinHeap, Test3) {
    MinHeap<int64_t, std::string> mh;
    mh.Add(8, "10");
    mh.Add(4, "14");
    mh.Add(7, "15");
    mh.Set(8, "11");
    mh.Add(3, "13");
    mh.Add(5, "10");
    mh.Add(10, "10");
    if (!mh.isSearched(88))
        std::cout << false << std::endl;
    else
        std::cout << mh.Search(88).first.first << std::endl;
    if (!mh.isSearched(7))
        std::cout << false << std::endl;
    else
        std::cout << mh.Search(7).first.first << std::endl;
    mh.Delete(4);
    mh.ExtractMin();
    mh.Print();
}

TEST(MinHeap, Test14) {
    MinHeap<int64_t, std::string> mh;
//    try {
//        mh.Max();
//    } catch (const std::exception &) {
//        std::cout << "error" << std::endl;
//    }
//    mh.Search(-4819157362427870784);
//    mh.Delete(8481518896991861250);
    mh.Add(-230860151376351956, "peizlr/ocwtqms");
//    mh.Delete(2083918878028242006);
    mh.Delete(-230860151376351956);
    mh.Add(7858774124746514669, "hx[d]._g");
    if (mh.isSearched(-230860151376351956)) {
        auto node = mh.Search(-230860151376351956);
        std::cout << node.first.first << ' ' << node.first.second << std::endl;
    } else
        std::cout << false << std::endl;
}