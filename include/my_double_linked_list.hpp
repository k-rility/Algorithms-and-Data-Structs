#ifndef ALGORITHS_AND_DATA_STRUCTS_MY_DOUBLE_LINKED_LIST_HPP
#define ALGORITHS_AND_DATA_STRUCTS_MY_DOUBLE_LINKED_LIST_HPP

#include <iostream>

template<class T>
class my_double_linked_list {
private:
    struct __node {
        __node *__prev;
        __node *__next;
        T __data;
    };
public:

    my_double_linked_list() : __head(nullptr) {}

    inline void push_front(const T &value) noexcept {
        __node *new_node = new __node{nullptr, __head, value};
        if (__head != nullptr)
            __head->__prev = new_node;
        __head = new_node;
    }

    __node *search(const T &value) const noexcept {
        __node *temp = __head;
        while (value != temp->__data)
            temp = temp->__next;
        return temp;
    }

    inline void insert_after(__node *node, const T &value) noexcept {
        __node *new_node = new __node{node, node->__next, value};
        node->__next = new_node;
        if (new_node->__next != nullptr)
            node->__next->__prev = new_node;
    }

    inline void remove(__node *node) noexcept {
        if (node->__prev != nullptr)
            node->__prev->__next = node->__next;
        else
            __head = node->__next;
        if (node->__next != nullptr)
            node->__next->__prev = node->__prev;
        delete node;
    }

private:
    __node *__head;
};

#endif //ALGORITHS_AND_DATA_STRUCTS_MY_DOUBLE_LINKED_LIST_HPP
