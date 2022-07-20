#include "gtest/gtest.h"
#include "my_stack.hpp"

TEST(Stack, Constructors) {
    Stack<int> st;
    st.Push(10);
    st.Push(20);
    st.Push(30);
    st.Pop();
}