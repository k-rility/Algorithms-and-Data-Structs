#ifndef AISD_MY_AVL_TREE_HPP
#define AISD_MY_AVL_TREE_HPP

template<class T>
class my_avl_tree {
private:
    struct __node {
        __node *__left;
        __node *__right;
        T __data;
        unsigned char __height = 0;
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

    void __destructor(__node *&node) noexcept {
        if (node) {
            __destructor(node->__left);
            __destructor(node->__right);
            delete node;
        }
        return;
    }

    void __fix_height(__node *node) noexcept {
        unsigned int height_left = height(node->__left);
        unsigned int height_right = height(node->__right);
        if (height_left > height_right)
            node->__height = height_left + 1;
        else
            node->__height = height_right + 1;
    }

    __node *__insert_fix_up(__node *node) noexcept {
        __fix_height(node);
        if (__balance(node) == 2) {
            if (__balance(node->__right) < 0)
                node->__right = __right_rotate(node->__right);
            return __left_rotate(node);
        } else if (__balance(node) == -2) {
            if (__balance(node->__left) > 0)
                node->__left = __left_rotate(node->__left);
            return __right_rotate(node);
        }
        return node;
    }

    unsigned char __balance(__node *node) const noexcept {
        return height(node->__right) - height(node->__left);
    }

    __node *__insert(const T &value, __node *node) noexcept {
        if (!node)
            node = new __node{nullptr, nullptr, value};
        else if (value > node->__data)
            node->__right = __insert(value, node->__right);
        else if (value < node->__data)
            node->__left = __insert(value, node->__left);
        return __insert_fix_up(node);
    }

    __node *__left_rotate(__node *node) noexcept {
        __node *left = node->__right;
        node->__right = left->__left;
        left->__left = node;
        __fix_height(node);
        __fix_height(left);
        return left;
    }

    __node *__right_rotate(__node *node) noexcept {
        __node *right = node->__left;
        node->__left = right->__right;
        right->__right = node;
        __fix_height(node);
        __fix_height(right);
        return right;
    }

public:

    my_avl_tree() noexcept: __root(nullptr) {}

    ~my_avl_tree() noexcept {
        __destructor(__root);
    }

    inline unsigned char height(__node *node) const noexcept {
        if (node)
            return node->__height;
        return 0;
    }

    __node *find(const T &value) const noexcept {
        return __find(value, __root);
    }

    void insert(const T &value) noexcept {
        __root = __insert(value, __root);
    }

private:

    __node *__root;
};

#endif //AISD_MY_AVL_TREE_HPP
