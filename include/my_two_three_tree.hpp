#ifndef ALGORITHMS_AND_DATA_STRUCTS_MY_TWO_THREE_TREE_HPP
#define ALGORITHMS_AND_DATA_STRUCTS_MY_TWO_THREE_TREE_HPP

#include <memory>

template<typename T>
class my_two_three_tree {
private:

    struct Node {
        Node *Parent;
        Node *Left;
        Node *Middle;
        Node *Right;
        T leftValue;
        T rightValue;

        bool isLeaf() const noexcept {
            return Left == nullptr;
        }
    };

    Node *_Destructor(Node *node) noexcept {
        if (node) {
            _Destructor(node->Left);
            _Destructor(node->Middle);
            _Destructor(node->Right);
            delete node;
            node = nullptr;
        }
        return nullptr;
    }

    Node *_addToNode(Node *node, Node *newNode) noexcept {
        if (node->rightValue == 0) {
            if (newNode->leftValue < node->leftValue) {
                node->rightValue = node->leftValue;
                node->leftValue = newNode->leftValue;
                node->Right = node->Middle;
                if (newNode->Left) {
                    newNode->Middle->Parent = node;
                    newNode->Left->Parent = node;
                }
                node->Middle = newNode->Middle;
                node->Left = newNode->Left;
                delete newNode;
                return node;
            } else {
                node->rightValue = newNode->leftValue;
                if (newNode->Left) {
                    newNode->Middle->Parent = node;
                    newNode->Left->Parent = node;
                }
                node->Middle = newNode->Left;
                node->Right = newNode->Middle;
                delete newNode;
                return node;
            }
        } else {
            if (newNode->leftValue < node->leftValue) {
                Node *newMiddle = new Node{node, node->Middle, node->Right, nullptr, node->rightValue, 0};
                if (node->Right) {
                    node->Middle->Parent = newMiddle;
                    node->Right->Parent = newMiddle;
                }
                node->rightValue = 0;
                node->Middle = newMiddle;
                node->Right = nullptr;
                node->Left = newNode;
                if (node->Parent) {
                    if (node == node->Parent->Middle)
                        node->Parent->Middle = nullptr;
                    else if (node == node->Parent->Right)
                        node->Parent->Right = nullptr;
                    else
                        node->Parent->Left = nullptr;
                }
                return node;
            } else if (newNode->leftValue > node->rightValue) {
                Node *newLeft = new Node{node, node->Left, node->Middle, nullptr, node->leftValue, 0};
                if (node->Left) {
                    node->Left->Parent = newLeft;
                    node->Middle->Parent = newLeft;
                }
                node->Left = newLeft;
                node->Middle = newNode;
                node->leftValue = node->rightValue;
                node->rightValue = 0;
                node->Right = nullptr;
                if (node->Parent) {
                    if (node == node->Parent->Middle)
                        node->Parent->Middle = nullptr;
                    else if (node == node->Parent->Right)
                        node->Parent->Right = nullptr;
                    else
                        node->Parent->Left = nullptr;
                }
                return node;
            } else {
                Node *newMiddle = new Node{node, newNode->Middle, node->Right, nullptr, node->rightValue, 0};
                Node *newLeft = new Node{node, node->Left, newNode->Left, nullptr, node->leftValue, 0};
                node->leftValue = newNode->leftValue;
                node->rightValue = 0;
                if (newNode->Left) {
                    node->Left->Parent = newLeft;
                    node->Right->Parent = newMiddle;
                    newNode->Left->Parent = newLeft;
                    newNode->Middle->Parent = newMiddle;
                }
                node->Left = newLeft;
                node->Middle = newMiddle;
                node->Right = nullptr;
                delete newNode;
                if (node->Parent) {
                    if (node == node->Parent->Middle)
                        node->Parent->Middle = nullptr;
                    else if (node == node->Parent->Right)
                        node->Parent->Right = nullptr;
                    else
                        node->Parent->Left = nullptr;
                }
                return node;
            }
        }
    }

    Node *_insert(const T &value, Node *node) noexcept {
        if (!node)
            return new Node{nullptr, nullptr, nullptr, nullptr, value, 0};
        else if (node->isLeaf()) {
            return _addToNode(node, new Node{node, nullptr, nullptr, nullptr, value, 0});
        } else if (value < node->leftValue) {
            Node *returnValue = _insert(value, node->Left);
            if (returnValue == node->Left)
                return node;
            else
                return _addToNode(node, returnValue);
        } else if (node->rightValue == 0 || value < node->rightValue) {
            Node *returnValue = _insert(value, node->Middle);
            if (returnValue == node->Middle)
                return node;
            else
                return _addToNode(node, returnValue);
        } else {
            Node *returnValue = _insert(value, node->Right);
            if (returnValue == node->Right)
                return node;
            else
                return _addToNode(node, returnValue);
        }
    }


public:

    my_two_three_tree() noexcept: _Root(nullptr) {}

    ~my_two_three_tree() noexcept {
        _Root = _Destructor(_Root);
    }

    void insert(const T &value) noexcept {
        _Root = _insert(value, _Root);
    }

private:
    Node *_Root;
};

#endif //ALGORITHMS_AND_DATA_STRUCTS_MY_TWO_THREE_TREE_HPP
