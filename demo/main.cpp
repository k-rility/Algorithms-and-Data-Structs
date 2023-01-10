#include <cctype>
#include <exception>
#include <fstream>
#include <iterator>
#include <queue>
#include <iostream>
#include <memory>
#include <ostream>
#include <stdexcept>
#include <string>
#include <algorithm>

template<typename T, typename K>
class SplayTree {
private:
    struct _Node {
        K _Key;
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

//    std::pair<long long, T> Max() {
//        if (Empty())
//            throw std::logic_error("Cannot find max element of an empty tree");
//        _Node *tmp = _Root;
//        while (tmp->_Right)
//            tmp = tmp->_Right;
//        _Splay(tmp);
//        return std::make_pair(tmp->_Key, tmp->_Value);
//    }
    T &At(const K &key) {
        if (Empty())
            throw std::logic_error("Cannot find element of an empty tree");
        auto tmp = Search(key);
        if (tmp)
            return tmp->_Value;
        throw std::logic_error("Unable to access element by key");
    }

    long long Max() {
        if (Empty())
            throw std::logic_error("Cannot find max element of an empty tree");
        _Node *tmp = _Root;
        while (tmp->_Right)
            tmp = tmp->_Right;
        _Splay(tmp);
        return tmp->_Key;
    }


//    std::pair<long long, T> Min() {
//        if (Empty())
//            throw std::logic_error("Cannot find min element of an empty tree");
//        _Node *tmp = _Root;
//        while (tmp->_Left)
//            tmp = tmp->_Left;
//        _Splay(tmp);
//        return std::make_pair(tmp->_Key, tmp->_Value);
//    }

    long long Min() {
        if (Empty())
            throw std::logic_error("Cannot find min element of an empty tree");
        _Node *tmp = _Root;
        while (tmp->_Left)
            tmp = tmp->_Left;
        _Splay(tmp);
        return tmp->_Key;
    }

    void Set(long long key, const T &newValue) {
        if (!_Root) throw std::logic_error("Attempt to change the value of node in an empty tree");
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
        if (!tmp) {
            _Splay(p);
            throw std::logic_error("Element not found for this key");
        }
    }

    void Add(const K &key, const T &value) {
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

    void Delete(const K &key) {
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
            _Splay(p);
            throw std::logic_error("No element to remove");
        }
    }

    bool Empty() const noexcept {
        return _Root == nullptr;
    }

    size_t Depth() const noexcept {
        return _Depth(_Root);
    }

    template<typename U, typename L>

    friend std::ostream &operator<<(std::ostream &, const SplayTree<U, L> &) noexcept;

private:
    _Node *_Root;

    std::string __nulls_repeat(size_t n) const noexcept {
        std::string result{};
        if (n) {
            result.reserve(n << 1);
            while (n) {
                result.append(" _", 2);
                --n;
            }
        }
        return result;
    }
};


template<typename T, typename K>
std::ostream &operator<<(std::ostream &out, const SplayTree<T, K> &st) noexcept {
    if (st.Empty())
        return out << "_";
    using node_ptr = typename SplayTree<T, K>::_Node *;
    struct _node {
        node_ptr node;
        size_t null_count;

        _node(node_ptr node_) noexcept: node{node_}, null_count{(node) ? false : true} {}
    };

    std::vector<_node> curr_lvl;
    std::vector<_node> next_lvl;
    curr_lvl.emplace_back(st._Root);
    do {
        for (auto it = curr_lvl.begin(); it != curr_lvl.end(); ++it) {
            if (it != curr_lvl.begin())
                out << ' ';
            if (node_ptr node = it->node; node) {
                out << '[' << node->_Key << ' ' << node->_Value;
                if (node_ptr parent = node->_Parent; parent)
                    out << ' ' << parent->_Key;
                out << ']';

                if (node->_Left)
                    next_lvl.emplace_back(node->_Left);
                else if (next_lvl.empty() || next_lvl.back().node)
                    next_lvl.emplace_back(nullptr);
                else
                    ++next_lvl.back().null_count;

                if (node->_Right)
                    next_lvl.emplace_back(node->_Right);
                else if (next_lvl.empty() || next_lvl.back().node)
                    next_lvl.emplace_back(nullptr);
                else
                    ++next_lvl.back().null_count;
            } else {
                out << '_' << st.__nulls_repeat(it->null_count - 1);
                if (next_lvl.empty() || next_lvl.back().node) {
                    next_lvl.emplace_back(nullptr);
                    next_lvl.back().null_count = it->null_count << 1;
                } else
                    next_lvl.back().null_count += it->null_count << 1;
            }
        }
        if (next_lvl.size() > 1)
            out << '\n';
        std::swap(next_lvl, curr_lvl);
        next_lvl.clear();
    } while (curr_lvl.size() > 1);
    return out;
}

int main([[maybe_unused]] int argc, [[maybe_unused]]char **argv) {
    SplayTree<std::string, long long> spt;
    std::string line;
    while (std::getline(std::cin, line)) {
        if (line.empty())
            continue;
        auto it = std::find_if(line.begin(), line.end(), [](char c) { return std::isspace(c); });
        auto cmd = std::string(line.begin(), it);
        try {
            if (cmd == "add") {
                auto key = std::find_if_not(it + 1, line.end(), [](char c) { return std::isspace(c); });
                auto value = std::find_if(key + 1, line.end(), [](char c) { return std::isspace(c); });
                spt.Add(std::stoll(std::string(key, value)), std::string(value + 1, line.end()));
            } else if (cmd == "set") {
                auto key = std::find_if_not(it + 1, line.end(), [](char c) { return std::isspace(c); });
                auto value = std::find_if(key + 1, line.end(), [](char c) { return std::isspace(c); });
                spt.Set(std::stoll(std::string(key, value)), std::string(value + 1, line.end()));
            } else if (cmd == "search") {
                auto key = std::find_if_not(it + 1, line.end(), [](char c) { return std::isspace(c); });
                auto tmp = std::stoll(std::string(key, line.end()));
                auto node = spt.Search(tmp);
                if (node && node->_Key == tmp)
                    std::cout << true << ' ' << node->_Value << std::endl;
                else
                    std::cout << false << std::endl;
            } else if (cmd == "delete") {
                auto key = std::find_if_not(it + 1, line.end(), [](char c) { return std::isspace(c); });
                spt.Delete(std::stoll(std::string(key, line.end())));
            } else if (cmd == "max") {
                auto key_max = spt.Max();
                std::cout << key_max << ' ' << spt.At(key_max) << std::endl;
            } else if (cmd == "min") {
                auto key_min = spt.Min();
                std::cout << key_min << ' ' << spt.At(key_min) << std::endl;
            } else if (cmd == "print") {
                std::cout << spt << std::endl;
            }

        } catch (std::exception &) {
            std::cout << "error" << std::endl;
        }
    }
    return 0;
}
