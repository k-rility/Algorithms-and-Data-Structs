#include "my_bloom_filter.hpp"
#include "gtest/gtest.h"

TEST(Test, ff) {
    MyBloomFilter b(2, 0.250);
    b.Add(7);
    b.Print();
    b.Add(5);
    b.Print();
    b.Add(14);
    b.Print();
    std::cout<< b.Search(7)<< std::endl;
    std::cout<< b.Search(10)<< std::endl;
    std::cout<< b.Search(15)<< std::endl;
    std::cout<< b.Search(14)<< std::endl;
    std::cout<< b.Search(5)<< std::endl;
    std::cout<< b.Search(13)<< std::endl;
}