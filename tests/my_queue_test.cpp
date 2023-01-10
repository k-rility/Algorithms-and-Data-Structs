#include "gtest/gtest.h"
#include "my_queue.hpp"

TEST(Queue, Enqueue) {
    Queue<int> q;
    q.enqueue(10);
    q.dequeue();
}