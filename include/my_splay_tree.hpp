#ifndef ALGORITHS_AND_DATA_STRUCTS_SPLAY_TREE_HPP
#define ALGORITHS_AND_DATA_STRUCTS_SPLAY_TREE_HPP


#include <iostream>
#include <memory>
#include <queue>

template<typename T>
class SplayTree {
private:
    struct _Node {
        long long _Key;
        T _Value;
        _Node *_Left;
        _Node *_Right;
        _Node *_Parent;
    };

    void _Destructor(_Node *node) {
        if (node) {
            _Destructor(node->_Left);
            _Destructor(node->_Right);
            delete node;
        }
    }

    void _Zig(_Node *node) {
        if (node == _Root) return;
        _Node *pivot = node->_Parent;
        pivot->_Left = node->_Right;
        if (node->_Right)
            node->_Right->_Parent = pivot;
        node->_Parent = pivot->_Parent;
        if (!pivot->_Parent)
            _Root = node;
        else if (pivot == pivot->_Parent->_Left)
            pivot->_Parent->_Left = node;
        else if (pivot == pivot->_Parent->_Right)
            pivot->_Parent->_Right = node;
        node->_Right = pivot;
        pivot->_Parent = node;
    }

    void _Zag(_Node *node) {
        if (node == _Root) return;
        _Node *pivot = node->_Parent;
        pivot->_Right = node->_Left;
        if (node->_Left)
            node->_Left->_Parent = pivot;
        node->_Parent = pivot->_Parent;
        if (!pivot->_Parent)
            _Root = node;
        else if (pivot == pivot->_Parent->_Left)
            pivot->_Parent->_Left = node;
        else if (pivot == pivot->_Parent->_Right)
            pivot->_Parent->_Right = node;
        node->_Left = pivot;
        pivot->_Parent = node;
    }

    _Node *_Splay(_Node *node) {
        while (node != _Root) {
            if (node->_Parent == _Root && node == node->_Parent->_Left)
                _Zig(node);
            else if (node->_Parent == _Root && node == node->_Parent->_Right)
                _Zag(node);
            else if (node == node->_Parent->_Left && node->_Parent == node->_Parent->_Parent->_Left) {
                _Zig(node->_Parent);
                _Zig(node);
            } else if (node == node->_Parent->_Right && node->_Parent == node->_Parent->_Parent->_Right) {
                _Zag(node->_Parent);
                _Zag(node);
            } else if (node->_Parent == node->_Parent->_Parent->_Left && node == node->_Parent->_Right) {
                _Zag(node);
                _Zig(node);
            } else if (node->_Parent == node->_Parent->_Parent->_Right && node == node->_Parent->_Left) {
                _Zig(node);
                _Zag(node);
            }
        }
        return node;
    }

    _Node *_Max(_Node *node) {
        while (node->_Right)
            node = node->_Right;
        return node;
    }

    size_t _Depth(_Node *node) const noexcept {
        if (!node) return 0;
        size_t ldepth = 0;
        size_t rdepth = 0;
        ldepth = _Depth(node->_Left);
        rdepth = _Depth(node->_Right);
        if (rdepth > ldepth)
            return rdepth + 1;
        else
            return ldepth + 1;
    }

public:
    SplayTree() : _Root(nullptr) {}

    ~SplayTree() {
        _Destructor(_Root);
    }

    _Node *Search(long long key) {
        if (!_Root)
            return nullptr;
        _Node *tmp = _Root;
        _Node *p = nullptr;
        while (tmp) {
            p = tmp;
            if (tmp->_Key < key)
                tmp = tmp->_Right;
            else if (tmp->_Key > key)
                tmp = tmp->_Left;
            else {
                _Splay(tmp);
                return tmp;
            }
        }
        _Splay(p);
        return nullptr;
    }

    std::pair<long long, T> Max() {
        if (Empty())
            throw std::logic_error("Cannot find max element of an empty tree");
        _Node *tmp = _Root;
        while (tmp->_Right)
            tmp = tmp->_Right;
        _Splay(tmp);
        return std::make_pair(tmp->_Key, tmp->_Value);
    }

    std::pair<long long, T> Min() {
        if (Empty())
            throw std::logic_error("Cannot find min element of an empty tree");
        _Node *tmp = _Root;
        while (tmp->_Left)
            tmp = tmp->_Left;
        _Splay(tmp);
        return std::make_pair(tmp->_Key, tmp->_Value);
    }

    void Set(long long key, const T &newValue) {
        if (!_Root) return;
        _Node *tmp = _Root;
        _Node *p = nullptr;
        while (tmp) {
            p = tmp;
            if (tmp->_Key < key)
                tmp = tmp->_Right;
            else if (tmp->_Key > key)
                tmp = tmp->_Left;
            else {
                tmp->_Value = newValue;
                _Splay(tmp);
                return;
            }
        }
        if (!tmp)
            _Splay(p);
    }

    void Add(long long key, const T &value) {
        if (!_Root) {
            _Root = new _Node{key, value, nullptr, nullptr, nullptr};
        } else {
            _Node *tmp = _Root;
            _Node *prv = _Root;
            while (tmp) {
                prv = tmp;
                if (key > tmp->_Key)
                    tmp = tmp->_Right;
                else if (key < tmp->_Key)
                    tmp = tmp->_Left;
                else {
                    _Splay(tmp);
                    throw std::logic_error("The element is already present in the tree");
                }
            }
            if (key > prv->_Key) {
                prv->_Right = new _Node{key, value, nullptr, nullptr, prv};
                _Splay(prv->_Right);
            } else if (key < prv->_Key) {
                prv->_Left = new _Node{key, value, nullptr, nullptr, prv};
                _Splay(prv->_Left);
            }
        }
    }

    void Delete(long long key) {
        _Node *tmp = _Root;
        //TODO сделать без лишнего выделения память
        _Node *parent = nullptr;
        while (tmp) {
            parent = tmp;
            if (tmp->_Key < key)
                tmp = tmp->_Right;
            else if (tmp->_Key > key)
                tmp = tmp->_Left;
            else if (tmp->_Key == key) {
                _Splay(tmp);
                if (tmp->_Left && tmp->_Right) {
                    _Root = tmp->_Left;
                    tmp->_Left->_Parent = nullptr;
                    _Splay(_Max(_Root));
                    _Root->_Right = tmp->_Right;
                    if (tmp->_Right)
                        tmp->_Right->_Parent = _Root;
                } else if (tmp->_Left && !tmp->_Right) {
                    _Root = tmp->_Left;
                } else {
                    _Root = tmp->_Right;
                }
                delete tmp;
                tmp = nullptr;
                if (_Root)
                    _Root->_Parent = nullptr;
                return;
            }
        }
        if (!tmp) {
            _Splay(parent);
            throw std::logic_error("No element to remove");
        }
    }

    size_t Depth() const noexcept {
        return _Depth(_Root);
    }

    bool Empty() const noexcept {
        return _Root == nullptr;
    }

    template<typename U>
    friend std::ostream &operator<<(std::ostream &, const SplayTree<T> &);

//    void _Print(/*_Node *node, size_t lvl*/) {
//        std::queue<_Node *> q1;
//        std::queue<_Node *> q2;
//        q1.push(_Root);
//        bool flag = true;
//        while (!q1.empty() || !q2.empty()) {
//            while (!q1.empty()) {
//                _Node *tmp = q1.front();
//                q1.pop();
//                if (!tmp) {
//                    q2.push(nullptr);
//                    q2.push(nullptr);
//                    std::cout << "NULL ";
//                } else if (tmp == _Root) {
//                    if (tmp->_Left || tmp->_Right)
//                        flag = false;
//                    std::cout << tmp->_Key << ' ' << tmp->_Value;
//                    q2.push(tmp->_Left);
//                    q2.push(tmp->_Right);
//                } else {
//                    if (tmp->_Left || tmp->_Right)
//                        flag = false;
//                    std::cout << tmp->_Key << ' ';
//                    q2.push(tmp->_Left);
//                    q2.push(tmp->_Right);
//                }
//            }
//            if (flag)
//                break;
//            flag = true;
//            std::cout << std::endl;
//            while (!q2.empty()) {
//                _Node *tmp = q2.front();
//                q2.pop();
//                if (!tmp) {
//                    q1.push(nullptr);
//                    q1.push(nullptr);
//                    std::cout << "NULL ";
//                } else if (tmp == _Root) {
//                    if (tmp->_Left || tmp->_Right)
//                        flag = false;
//                    std::cout << tmp->_Key << ' ' << tmp->_Value;
//                    q2.push(tmp->_Left);
//                    q2.push(tmp->_Right);
//                } else {
//                    if (tmp->_Left || tmp->_Right)
//                        flag = false;
//                    std::cout << tmp->_Key << ' ';
//                    q1.push(tmp->_Left);
//                    q1.push(tmp->_Right);
//                }
//            }
//            if (flag)
//                break;
//            std::cout << std::endl;
////            q.pop();
////            _Node *tmp = q.front();
////            if (!tmp) {
////                q.push(nullptr);
////                q.push(nullptr);
////                continue;
////            }
////            if (tmp->_Right) {
////                q.push(tmp->_Right);
////            } else {
////                q.push(nullptr);
////            }
////            if (tmp->_Left) {
////                q.push(tmp->_Left);
////            } else {
////                q.push(nullptr);
////            }
//        }
////        if (!node) {
////            if (lvl > 1) {
////                _Print(nullptr, lvl - 1);
////                _Print(nullptr, lvl - 1);
////            } else {
////                std::cout << "_ "/* << ' '*/;
////            }
////            return;
////        }
////        if (lvl == 1) {
////            if (node == _Root)
////                std::cout << '[' << node->_Key << ' ' << node->_Value << ']';
////            else
////                std::cout << '[' << node->_Key << ' ' << node->_Value << ' ' << node->_Parent->_Key << "] ";
////        } else if (lvl > 1) {
////            _Print(node->_Left, lvl - 1);
////            _Print(node->_Right, lvl - 1);
////        }
//    }

    void Print() {
//        if(!_Root){
//            _Print(_Root, 0);
//            return;
//        }
        if (Empty()) {
            std::cout << "_" << std::endl;
            return;
        }
        _Print();
/*        for (size_t i = 1; i <= Depth(); ++i) {
            _Print(_Root, i);
            std::cout << std::endl;
        }*/
    }

    void _Print() {
        if (Empty()) {
            std::cout << "_" << std::endl;
            return;
        }
        std::queue<_Node *> q1;
        std::queue<_Node *> q2;
        q1.emplace(_Root);
        bool flag = true;
        while (true) {
            while (!q1.empty()) {
                _Node *tmp = q1.front();
                q1.pop();
                if (!tmp) {
                    flag = true;
                    q2.emplace(nullptr);
                    q2.emplace(nullptr);
                    std::cout << "NULL ";
                } else {
                    flag = false;
                    std::cout << tmp->_Value << ' ';
                    q2.emplace(tmp->_Left);
                    q2.emplace(tmp->_Right);
                }
            }
            if (flag)
                break;
            std::cout << std::endl;
            while (!q2.empty()) {
                _Node *tmp = q2.front();
                q2.pop();
                if (!tmp) {
                    flag = true;
                    q1.emplace(nullptr);
                    q1.emplace(nullptr);
                    std::cout << "NULL ";
                } else {
                    flag = false;
                    std::cout << tmp->_Value << ' ';
                    q1.emplace(tmp->_Left);
                    q1.emplace(tmp->_Right);
                }
            }
            if (flag)
                break;
            std::cout << std::endl;
        }
    }

private:
    _Node *_Root;
};
//
//template<typename T>
//std::ostream &operator<<(std::ostream &out, const SplayTree<T> &spt) {
//    if (spt.Empty())
//        return out << "_";
//    std::queue<typename SplayTree<T>::_Node> q;
//    q.push(spt._Root);
//    while (!q.empty()) {
//        const typename SplayTree<T>::_Node *const tmp = q.front();
//        q.pop();
//        if (tmp->_Left) {
//            q.push(tmp->_left);
//            out << "[" << tmp->_Key << " " << tmp->_Value << " " << tmp->_Parent->_Key << "]";
//        } else {
//            out << "_ _ _" << std::endl;
//        }
//
//        if (tmp->_Right) {
//            q.push(tmp->_Right);
//            out << "[" << tmp->_Key << " " << tmp->_Value << " " << tmp->_Parent->_Key << "]";
//        } else {
//            out << "_ _ _" << std::endl;
//        }
//
//    }
//    return out;
//}



//int main() {
//    SplayTree<std::string> spt;
//    while()
//    return 0;
//}

#endif // ALGORITHS_AND_DATA_STRUCTS_SPLAY_TREE_HPP

