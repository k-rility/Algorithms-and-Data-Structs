#ifndef ALGORITHS_AND_DATA_STRUCTS_MY_BINARY_SEARCH_TREE_HPP
#define ALGORITHS_AND_DATA_STRUCTS_MY_BINARY_SEARCH_TREE_HPP

#include <iostream>

template<class T>
class my_binary_search_tree {
private:
    struct __node {
        __node *__left;
        __node *__right;
        T __data;
    };
private:

    void __add(const T &value, __node *&node) noexcept {
        if (node == nullptr) {
            node = new __node{nullptr, nullptr, value};
        } else if (value > node->__data) {
            __add(value, node->__right);
        } else if (value < node->__data) {
            __add(value, node->__left);
        }
    }

    __node *__destructor(__node *&node) noexcept {
        if (node != nullptr) {
            __destructor(node->__left);
            __destructor(node->__right);
            delete node;
        }
        return nullptr;
    }

    __node *__find(const T &value, __node *node) const noexcept {
        if (node == nullptr) {
            return nullptr;
        } else if (value > node->__data) {
            return __find(value, node->__right);
        } else if (value < node->__data) {
            return __find(value, node->__left);
        }
        return node;
    }

    void __remove(const T &value, __node *&node) noexcept {
        if (node == nullptr) {
            return;
        } else if (value > node->__data) {
            __remove(value, node->__right);
        } else if (value < node->__data) {
            __remove(value, node->__left);
        } else {
            if (node->__left == nullptr && node->__right == nullptr) {
                delete node;
            } else if (node->__right == nullptr) {
                __node *new_left = node->__left;
                delete node;
                node = new_left;
            } else if (node->__left == nullptr) {
                __node *new_right = node->__right;
                delete node;
                node = new_right;
            } else {
                __node *temp = __min(node->__right);
                node->__data = temp->__data;
                __remove(temp->__data, node->__right);
            }
        }
        return;
    }

    __node *__min(__node *node) const noexcept {
        while (node->__left != nullptr) {
            node = node->__left;
        }
        return node;
    }

    __node *__max(__node *node) const noexcept {
        while (node->__right != nullptr) {
            node = node->__right;
        }
        return node;
    }

    size_t __depth(__node *node) const noexcept {
        size_t depth_right = 0;
        size_t depth_left = 0;
        if (node == nullptr) {
            return 0;
        } else {
            depth_left = __depth(node->__left);
            depth_right = __depth(node->__right);
            if (depth_right > depth_left) {
                return depth_right + 1;
            } else {
                return depth_left + 1;
            }
        }
    }

public:
    my_binary_search_tree() noexcept: __root(nullptr) {}

    ~my_binary_search_tree() noexcept {
        __destructor(__root);
    }

    size_t depth() const noexcept {
        return __depth(__root) - 1;
    }

    void add(const T &value) noexcept {
        __add(value, __root);
    }

    void remove(const T &value) noexcept {
        __remove(value, __root);
    }

    __node *find(const T &value) const noexcept {
        return __find(value, __root);
    }

    __node *min() const noexcept {
        return __min(__root);
    }

    __node *max() const noexcept {
        return __max(__root);
    }

private:
    __node *__root;
};

#endif //ALGORITHS_AND_DATA_STRUCTS_MY_BINARY_SEARCH_TREE_HPP
