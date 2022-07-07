#ifndef ALGORITHS_AND_DATA_STRUCTS_MY_LINKED_LIST_HPP
#define ALGORITHS_AND_DATA_STRUCTS_MY_LINKED_LIST_HPP

#include <iostream>

template<class T>

class my_linked_list {
private:
    struct __node {
        __node *__next;
        T __data;
    };

public:

    my_linked_list() noexcept: __head(nullptr) {}

    ~my_linked_list() noexcept {
        while (__head != nullptr) {
            __node *next = __head->__next;
            delete __head;
            __head = next;
        }
        delete __head;
    }

    inline void push_front(const T &value) noexcept {
        __node *new_node = new __node{__head, value};
        __head = new_node;
    }

    inline void remove_after(__node *node) noexcept {
        __node *temp = node->__next;
        node->__next = node->__next->__next;
        delete temp;
    }

    inline void pop_front() noexcept {
        if (__head == nullptr) return;
        __node *temp = __head;
        __head = __head->__next;
        delete temp;
    }

    __node *search(const T &value) const noexcept {
        __node *temp = __head;
        while (value != temp->__data) {
            temp = temp->__next;
        }
        return temp;
    }

    inline void insert_after(__node *node, const T &value) noexcept {
        __node *new_node = new __node{node->__next, value};
        node->__next = new_node;
    }

    void reverse() noexcept {
        __node *next = nullptr;
        __node *prev = nullptr;
        while (__head != nullptr) {
            next = __head->__next;
            __head->__next = prev;
            prev = __head;
            __head = next;
        }
        __head = prev;
    }


private:
    __node *__head;
};

#endif //ALGORITHS_AND_DATA_STRUCTS_MY_LINKED_LIST_HPP
