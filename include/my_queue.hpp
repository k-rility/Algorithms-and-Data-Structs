#ifndef ALGORITHS_AND_DATA_STRUCTS_MY_QUEUE_HPP
#define ALGORITHS_AND_DATA_STRUCTS_MY_QUEUE_HPP

#include <iostream>
#include <memory>

template<class T>
class my_queue {
public:

    my_queue() : __head(nullptr), __tail(nullptr) {}

    ~my_queue() {
        while (__head != nullptr) {
            node *next = __head->__next;
            delete __head;
            __head = next;
        }
        delete __head;
    }

    void enqueue(const T &value) {
        node *new_node = new node{nullptr, value};
        if (__head == nullptr) {
            __head = new_node;
            __tail = __head;
            return;
        }
        __tail->__next = new_node;
        __tail = new_node;
    }

    T dequeue() {
        if (empty()) return -1;
        node *temp = __head;
        T res = temp->__data;
        if (__head == __tail) {
            __head = nullptr;
            __tail = __head;
        } else {
            __head = __head->__next;
        }
        delete temp;
        --__size;
        return res;
    }

    size_t size() const {
        return __size;
    }

    bool empty() const {
        if (__size == 0) return true;
        return false;
    }

private:

    struct node {
        node *__next;
        T __data;
    };
    node *__head;
    node *__tail;
    size_t __size = 0;
};

template<class T>
class Queue {
public:

    Queue() : _head{nullptr}, _tail{nullptr} {}

    void enqueue(const T &val) {
        std::shared_ptr<node> new_node = std::make_shared<node>(node{nullptr, val});
        if (!_head) {
            _head = new_node;
            _tail = _head;
            return;
        }
        _tail->_next = new_node;
        _tail = new_node;
    }

    T dequeue() {
        if (!_head)
            throw std::runtime_error("error");
        T temp = _head->_data;
        _head = _head->_next;
        return temp;
    }

private:
    struct node {
        std::shared_ptr<node> _next;
        T _data;
    };
    std::shared_ptr<node> _head;
    std::shared_ptr<node> _tail;
};

#endif //ALGORITHS_AND_DATA_STRUCTS_MY_QUEUE_HPP
