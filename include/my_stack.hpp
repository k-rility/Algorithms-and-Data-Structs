
#ifndef ALGORITHS_AND_DATA_STRUCTS_STACK_HPP
#define ALGORITHS_AND_DATA_STRUCTS_STACK_HPP

#include <iostream>
#include <iterator>

template<class T>

class my_stack {
private:
    struct __node {
        __node *__next;
        T __data;
    };
public:

    my_stack() noexcept: __top(nullptr) {}

    inline void push(const T &value) noexcept {
        __node *new_top = new __node{__top, value};
        __top = new_top;
        ++__size;
    }

    inline void pop() noexcept {
        if (__top == nullptr) return;
        __node *temp = __top;
        __top = __top->__next;
        delete temp;
        --__size;
    }

    ~my_stack() noexcept {
        while (__top != nullptr) {
            __node *next = __top->__next;
            delete __top;
            __top = next;
        }
        delete __top;
    }

    my_stack(const my_stack &rhs) noexcept: __top(rhs->__top) {}

//    bool operator==(const my_stack &rhs) const noexcept {
//
//    }

    size_t size() const noexcept {
        return __size;
    }

    bool empty() const noexcept {
        if (size() == 0)
            return true;
        return false;
    }

//    my_stack &operator=(const my_stack &rhs) noexcept {
//
//    }

private:
    __node *__top;
    size_t __size = 0;
};

#endif //ALGORITHS_AND_DATA_STRUCTS_STACK_HPP
