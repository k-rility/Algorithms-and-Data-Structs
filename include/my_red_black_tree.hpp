
#ifndef ALGORITHS_AND_DATA_STRUCTS_MY_RED_BLACK_TREE_HPP
#define ALGORITHS_AND_DATA_STRUCTS_MY_RED_BLACK_TREE_HPP

template<class T>
class my_red_black_tree {
private:
    struct __node {
        __node *__left;
        __node *__right;
        __node *__parent;
        T __data;
        char __color;

    };
private:

    inline __node *&set_black_color(__node *&node) noexcept {
        node->__color = 'b';
        return node;
    }

    inline __node *&set_red_color(__node *&node) noexcept {
        node->__color = 'r';
        return node;
    }

//    void __insert(const T &value, __node *&root, __node *&node) noexcept {
//        if (root == nullptr && root == __root) {
//            root = set_black_colour(node);
//        } else if (root == nullptr && node->__parent->__colour == 'r') {
//            root = set_black_colour(node);
//        } else if (root == nullptr && node->__parent->__colour == 'b') {
//            root = set_red_colour(node);
//        } else if (value > root->__data) {
//            node->__parent = root;
//            __insert(value, root->__right, node);
//        } else if (value < root->__data) {
//            node->__parent = root;
//            __insert(value, root->__left, node);
//        }
//    }

    void __insert(const T &value, __node *&root, __node *&node) noexcept {
        if (root == nullptr && root == __root) {
            root = set_black_color(node);
        } else if (root != nullptr && value > root->__data) {
            node->__parent = root;
            __insert(value, root->__right, node);
        } else if (root != nullptr && value < root->__data) {
            node->__parent = root;
            __insert(value, root->__left, node);
        } else if (root == nullptr) {
            root = set_red_color(node);
        }
        __insert_fix_up(node);
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

    void __insert_fix_up(__node *&node) noexcept {
        __node *parent = node->__parent;
        if (parent == nullptr || parent->__parent == nullptr)
            return;
        __node *gparent = parent->__parent;
        if (gparent->__right == nullptr ||
            gparent->__right->__left == nullptr && gparent->__right->__right == nullptr) {
            __node *uncle = gparent->__right;
            if (uncle != nullptr && uncle->__color == 'r') {
                parent->__color = 'b';
                uncle->__color = 'b';
                gparent->__color = 'r';
                __insert_fix_up(gparent);
            } else if ((uncle == nullptr || uncle->__color == 'b') && parent->__color == 'r') {
                if (parent->__right == node) {
                    left_rotate(parent);
                } else {
                    right_rotate(gparent);
                    gparent->__color = 'r';
                    parent->__color = 'b';
                }
            }
        } else if (gparent->__left == nullptr ||
                   gparent->__left->__left == nullptr && gparent->__left->__right == nullptr) {
            __node *uncle = gparent->__left;
            if (uncle != nullptr && uncle->__color == 'r') {
                parent->__color = 'b';
                uncle->__color = 'b';
                gparent->__color = 'r';
                __insert_fix_up(gparent);
            } else if ((uncle == nullptr || uncle->__color == 'b') && parent->__color == 'r') {
                if (parent->__right == node) {
                    left_rotate(gparent);
                    gparent->__color = 'r';
                    parent->__color = 'b';
                } else {
                    right_rotate(parent);
                }
            }
        }
        __root->__color = 'b';
    }

public:

    my_red_black_tree() noexcept: __root(nullptr) {}

    ~my_red_black_tree() noexcept {
        __destructor(__root);
    }

    __node *find(const T &value) const noexcept {
        return __find(value, __root);
    }

    void insert(const T &value) noexcept {
        __node *node = new __node{nullptr, nullptr, nullptr, value};
        __insert(value, __root, node);
    }

    void left_rotate(__node *&node) noexcept {
        __node *pivot = node->__right;
        node->__right = pivot->__left;
        if (pivot->__left != nullptr) {
            pivot->__left->__parent = node;
        }
        pivot->__parent = node->__parent;
        if (node->__parent == nullptr) {
            __root = pivot;
        } else if (node == node->__parent->__left) {
            node->__parent->__left = pivot;
        } else if (node == node->__parent->__right) {
            node->__parent->__right = pivot;
        }
        pivot->__left = node;
        node->__parent = pivot;
    }

    void right_rotate(__node *&node) noexcept {
        __node *pivot = node->__left;
        node->__left = pivot->__right;
        if (pivot->__right != nullptr) {
            pivot->__right->__parent = node;
        }
        pivot->__parent = node->__parent;
        if (node->__parent == nullptr) {
            __root = pivot;
        } else if (node == node->__parent->__left) {
            node->__parent->__left = pivot;
        } else if (node == node->__parent->__right) {
            node->__parent->__right = pivot;
        }
        pivot->__right = node;
        node->__parent = pivot;
    }


private:
    __node *__root;
};

#endif //ALGORITHS_AND_DATA_STRUCTS_MY_RED_BLACK_TREE_HPP
