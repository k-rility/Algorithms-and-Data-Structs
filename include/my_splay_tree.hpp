#ifndef ALGORITHMS_AND_DATA_STRUCTS_SPLAY_TREE_HPP
#define ALGORITHMS_AND_DATA_STRUCTS_SPLAY_TREE_HPP

template<class T>
class my_splay_tree {
private:
    struct __node {
        __node *__parent;
        __node *__left;
        __node *__right;
        T __data;
    };

private:

    __node *__find(const T &value, __node *node) const noexcept {
        if (!node) return nullptr;
        else if (value > node->__data)
            return __find(value, node->__right);
        else if (value < node->__data)
            return __find(value, node->__left);
        return node;
    }

    void __zig(__node *node) noexcept {
        __node *pivot = node->__left;
        node->__left = pivot->__right;
        if (pivot->__right)
            pivot->__right->__parent = pivot->__parent;
        pivot->__parent = node->__parent;
        if (!node->__parent)
            __root = pivot;
        else if (node == node->__parent->__left)
            node->__parent->__left = pivot;
        else
            node->__parent->__right = pivot;
        pivot->__right = node;
        node->__parent = pivot;
    }

    void __zag(__node *node) noexcept {
        __node *pivot = node->__right;
        node->__right = pivot->__left;
        if (pivot->__left)
            pivot->__left->__parent = pivot->__parent;
        pivot->__parent = node->__parent;
        if (!node->__parent)
            __root = pivot;
        else if (node == node->__parent->__left)
            node->__parent->__left = pivot;
        else
            node->__parent->__right = pivot;
        pivot->__left = node;
        node->__parent = pivot;
    }

    void __insert(const T &value, __node *&parent, __node *&node) noexcept {
        if (!parent)
            parent = node;
        else if (value > parent->__data) {
            node->__parent = parent;
            __insert(value, parent->__right, node);
        } else {
            node->__parent = parent;
            __insert(value, parent->__left, node);
        }
        __splay(node);
    }

    void __destructor(__node *&node) noexcept {
        if (node) {
            __destructor(node->__left);
            __destructor(node->__right);
            delete node;
        }
    }

    void __splay(__node *&node) noexcept {
        while (node != __root) {
            if (node->__parent == __root && node == node->__parent->__left)
                __zig(node->__parent);
            else if (node->__parent == __root && node == node->__parent->__right)
                __zag(node->__parent);
            else if()
        }
    }

public:

    my_splay_tree() noexcept: __root(nullptr) {}

    ~my_splay_tree() noexcept {
        __destructor(__root);
    }

    __node *find(const T &value) const noexcept {
        return __find(value, __root);
    }

    void insert(const T &value) noexcept {
        __node *node = new __node{nullptr, nullptr, nullptr, value};
        __insert(value, __root, node);
    }

private:
    __node *__root;
};

#endif //ALGORITHMS_AND_DATA_STRUCTS_SPLAY_TREE_HPP
