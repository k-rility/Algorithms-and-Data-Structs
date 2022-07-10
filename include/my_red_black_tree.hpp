
#ifndef ALGORITHS_AND_DATA_STRUCTS_MY_RED_BLACK_TREE_HPP
#define ALGORITHS_AND_DATA_STRUCTS_MY_RED_BLACK_TREE_HPP

template<class T>
class my_red_black_tree {
private:

    enum color {
        red,
        black
    };

    struct __node {
        __node *__left;
        __node *__right;
        __node *__parent;
        T __data;
        color __color;

    };
private:

    void __insert(const T &value, __node *&root, __node *&node) noexcept {
        if (root != nullptr && value > root->__data) {
            node->__parent = root;
            __insert(value, root->__right, node);
        } else if (root != nullptr && value < root->__data) {
            node->__parent = root;
            __insert(value, root->__left, node);
        } else if (root == nullptr) {
            root = node;
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
        if (node == __root || node->__parent == __root)
            return;
        __node *parent = node->__parent;
        __node *gparent = parent->__parent;
        if (parent == gparent->__left) {
            __node *uncle = gparent->__right;
            if (uncle && uncle->__color == red) {
                parent->__color = black;
                uncle->__color = black;
                gparent->__color = red;
                __insert_fix_up(gparent);
            } else if (parent->__color == red) {
                if (parent->__right == node) {
                    __left_rotate(parent);
                } else {
                    __right_rotate(gparent);
                    gparent->__color = red;
                    parent->__color = black;
                }
            }
        } else {
            __node *uncle = gparent->__left;
            if (uncle && uncle->__color == red) {
                parent->__color = black;
                uncle->__color = black;
                gparent->__color = red;
                __insert_fix_up(gparent);
            } else if (parent->__color == red) {
                if (parent->__right == node) {
                    __left_rotate(gparent);
                    gparent->__color = red;
                    parent->__color = black;
                } else {
                    __right_rotate(parent);
                }
            }
        }
        __root->__color = black;
    }

    void __right_rotate(__node *&node) noexcept {
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

    void __left_rotate(__node *&node) noexcept {
        __node *pivot = node->__right;
        node->__right = pivot->__left;
        if (pivot->__left != nullptr) {
            pivot->__left->__parent = node;
        }
        pivot->__parent = node->__parent;
        if (node->__parent == nullptr) {
            __root = pivot;
            //TODO тут можно сделать по другому без else if, аналогично и с правым вращением (но как я понял лучше,
            // покачто, оставить как есть)
        } else if (node == node->__parent->__left) {
            //node=pivot
            node->__parent->__left = pivot;
        } else if (node == node->__parent->__right) {
            //node=pivot
            node->__parent->__right = pivot;
        }
        pivot->__left = node;
        node->__parent = pivot;
    }

    void __remove_fix_up(__node *&node) noexcept {
        if (node->__color == red) {
            if (!(node->__right)) {
                if (!(node->__left->__left) && !(node->__left->__right)) {
                    node->__color = black;
                    node->__left->__color = red;
                } else if (node->__left->__left) {
                    __node *temp = node;
                    node->__color = black;
                    node->__left->__color = red;
                    node->__left->__left->__color = black;
                    __right_rotate(temp);
                } else {
                    __node *left = node->__left;
                    node->__left->__color = red;
                    node->__left->__right->__color = black;
                    __left_rotate(left);
                    __remove_fix_up(node);
                }
            } else {
                if (!(node->__right->__left) && !(node->__right->__right)) {
                    node->__color = black;
                    node->__right->__color = red;
                } else if (node->__right->__right) {
                    __node *temp = node;
                    node->__color = black;
                    node->__right->__color = red;
                    node->__right->__right->__color = black;
                    __left_rotate(temp);
                } else {
                    __node *right = node->__right;
                    node->__right->__color = red;
                    node->__right->__left->__color = black;
                    __right_rotate(right);
                    __remove_fix_up(node);
                }
            }
        } else {
            if (!(node->__right)) {
                if (node->__left->__color == red) {
                    if (node->__left->__right == __max(node->__left)) {
                        node->__left->__color = black;
                        node->__left->__right->__color = red;
                        __node *temp = node;
                        __right_rotate(temp);
                    } else if (node->__left->__right->__left) {
                        __node *left = node->__left;
                        left->__right->__left->__color = black;
                        __node *temp = node;
                        __left_rotate(left);
                        __right_rotate(temp);
                    } else {
                        __node *left_correct = node->__left->__right;
                        node->__left->__right->__right->__color = black;
                        __node *temp = node;
                        __left_rotate(left_correct);
                        __node *left = node->__left;
                        __left_rotate(left);
                        __right_rotate(temp);
                    }
                }
            }
        }
    }

    void __remove(const T &value, __node *&node) noexcept {
        if (!node)
            return;
        else if (value > node->__data)
            __remove(value, node->__right);
        else if (value < node->__data)
            __remove(value, node->__left);
        else {
            if (node->__color == red) {
                if (!(node->__left) && !(node->__right)) {
                    delete node;
                    node = nullptr;
                } else {
                    __node *temp = __max(node->__left);
                    node->__data = temp->__data;
                    __remove(temp->__data, node->__left);
                }
            } else {
                if (node->__left && node->__right) {
                    __node *temp = __max(node->__left);
                    node->__data = temp->__data;
                    __remove(temp->__data, node->__left);
                } else if (node->__left && node->__left->__color == red) {
                    __node *temp = node->__left;
                    temp->__color = black;
                    temp->__parent = node->__parent;
                    delete node;
                    node = temp;
                } else if (node->__right && node->__right->__color == red) {
                    __node *temp = node->__right;
                    temp->__color = black;
                    temp->__parent = node->__parent;
                    delete node;
                    node = temp;
                } else {
                    // TODO рассмотреть случай если удаляемая вершина является корнем
                    __node *parent = node->__parent;
                    delete node;
                    node = nullptr;
                    __remove_fix_up(parent);
                }
            }
        }
    }

    __node *__min(__node *node) const noexcept {
        while (node->__left)
            node = node->__left;
        return
                node;
    }

    __node *__max(__node *node)
    const noexcept {
        while (node->__right)
            node = node->__right;
        return
                node;
    }

public:

    my_red_black_tree()
    noexcept: __root(nullptr) {}

    ~my_red_black_tree()
    noexcept {
        __destructor(__root);
    }

    __node *find(const T &value) const noexcept {
        return __find(value, __root);
    }

    void insert(const T &value) noexcept {
        __node *node = new __node{nullptr, nullptr, nullptr, value, red};
        __insert(value, __root, node);
    }


    void remove(const T &value) noexcept {
        __remove(value, __root);
    }

    __node *min() const noexcept {
        return __min(__root);
    }

    __node *max() const noexcept {
        return __max(__root);
    }


    bool empty() const noexcept {
        if (__root == nullptr)
            return true;
        return false;
    }

private:
    __node *__root;
};

#endif //ALGORITHS_AND_DATA_STRUCTS_MY_RED_BLACK_TREE_HPP
