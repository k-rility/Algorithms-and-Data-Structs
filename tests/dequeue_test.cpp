#include "my_dequeue.hpp"
#include "gtest/gtest.h"


TEST(Dequeue, Test39){
    Dequeue<std::string> dq;
    dq.setSize(5);
    dq.pushBack("1000");
    dq.pushBack("900");
    dq.pushBack("900");
    dq.pushBack("900");
    dq.pushBack("900");
    dq.pushBack("800");
    dq.Print();
}
