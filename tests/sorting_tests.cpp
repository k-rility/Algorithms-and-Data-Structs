#include <gtest/gtest.h>
#include "my_sorting.hpp"

#include <vector>

TEST(Sort, BubbleSort) {
    std::vector<int> vec = {1, 4, 5, 6, 1, 8, 3, 0, 3, 19, 3, 5};
    bubbleSort(vec.begin(), vec.end(), std::less<>{});
    for (const auto &x: vec)
        std::cout << x << " ";
}

TEST(Sort, SelectionSort) {
    std::vector<int> vec = {3, 4, 5, 6, 1, 8, 3, 0, 3, 19, 3, 5};
    selectionSort(vec.begin(), vec.end(), std::less<>{});
    for (const auto &x: vec)
        std::cout << x << " ";
}

TEST(Sort, InsertionSort) {
    std::vector<int> vec = {3, 4, 5, 6, 1, 8, 3, 0, 3, 19, 3, 5};
    insertionSort(vec.begin(), vec.end(), std::less<>{});
    for (const auto &x: vec)
        std::cout << x << " ";
}

TEST(Sort, MergeSort) {
    std::vector<int> vec = {3, 4, 5, 6, 1, 8, 3, 0, 3, 19, 3, 5, 100};
    mergeSort(0, vec.size() - 1, vec);
    for (const auto &x: vec)
        std::cout << x << " ";
}

TEST(Sort, CountSort) {
    std::vector<int> in = {2, 1, 1, 0, 3, 3, 1};
    std::vector<int> out(in.size());
    countSort(in, out, 4);
    for (const auto &x: out)
        std::cout << x << " ";
}

TEST(Sort, QuickSort) {
//    std::vector<int> vec = {1, 8, 4, 3, 2, 7};
    std::vector<int> vec = {3, 4, 5, 6, 1, 8, 3, 0, 3, 19, 3, 5, 100};
    quickSort(vec, 0, vec.size() - 1);
    for (const auto &x: vec)
        std::cout << x << " ";
}
