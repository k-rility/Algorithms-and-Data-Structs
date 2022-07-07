
#ifndef ALGORITHS_AND_DATA_STRUCTS_STACK_HPP
#define ALGORITHS_AND_DATA_STRUCTS_STACK_HPP

#include <iostream>

template<class T>

class my_stack {
private:
    struct node {
        node *__next;
        T __data;
    };
public:

    my_stack() noexcept: __top(nullptr) {}

    inline void push(const T &value) noexcept {
        node *new_top = new node{__top, value};
        __top = new_top;
    }

    inline void pop() noexcept {
        if (__top == nullptr) return;
        node *temp = __top;
        __top = __top->__next;
        delete temp;
    }

    ~my_stack() noexcept {
        while (__top != nullptr) {
            node *next = __top->__next;
            delete __top;
            __top = next;
        }
        __top = nullptr;
    }

private:
    node *__top;
};

#endif //ALGORITHS_AND_DATA_STRUCTS_STACK_HPP
