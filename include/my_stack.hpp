
#ifndef ALGORITHS_AND_DATA_STRUCTS_STACK_HPP
#define ALGORITHS_AND_DATA_STRUCTS_STACK_HPP

#include <iostream>
#include <memory>

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

/////////////////////////////////////////////////////////////////////////////////

template<typename T>
class Stack {
private:
    struct _Node {
        T _Data;
        std::unique_ptr<_Node> _Next;

        _Node(T val) : _Data{val}, _Next{nullptr} {}


        ~_Node() {
            std::cout << "Destructor" << std::endl;
        }
    };

public:
    Stack() noexcept: _Top(nullptr) {}

    ~Stack() noexcept {}

    void Push(const T &value) noexcept {
        std::unique_ptr<_Node> new_node = std::make_unique<_Node>(value);
        new_node->_Next = std::move(_Top);
        _Top = std::move(new_node);
    }

    void Pop() noexcept {
        _Top = std::move(_Top->_Next);
    }

private:
    std::unique_ptr<_Node> _Top;
};

#endif //ALGORITHS_AND_DATA_STRUCTS_STACK_HPP
