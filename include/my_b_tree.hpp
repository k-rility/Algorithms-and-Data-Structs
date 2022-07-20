#ifndef ALGORITHMS_AND_DATA_STRUCTS_B_TREE_HPP
#define ALGORITHMS_AND_DATA_STRUCTS_B_TREE_HPP

#include <iostream>
/*
template<typename _Tp, std::size_t _Size = 2>
struct __node {
    __node *_Parent;
    size_t _Max_Keys_Size = 2 * _Size - 1;
    size_t _Max_Sons_Size = 2 * _Size;
    _Tp *_Keys[1];
    __node *_Sons[1];
    size_t _Keys_Size = 0;
    size_t _Sons_Size = 0;

    __node(const _Tp &value) noexcept: _Parent(nullptr), _Keys_Size(1) {
        _Keys[0] = value;
    }

    void push_back_keys(const _Tp &value) noexcept {
        if (_Keys_Size < _Max_Keys_Size) {
            _Tp *NewKeysStore = new _Tp[_Keys_Size + 1]();
            for (size_t i = 0; i < _Keys_Size - 1; ++i)
                NewKeysStore[i] = _Keys[i];
            delete _Keys;
            _Keys = NewKeysStore;
            _Keys[_Keys_Size] = value;
            ++_Keys_Size;
        } else {

        }
    }
};*/

/*template<typename _Tp, std::size_t _Size = 2>
class my_b_tree {
public:
    using _Node = __node<_Tp, _Size>;
    using value_type = _Tp;
private:

    void __insert(const value_type &value, _Node *&node) noexcept {

    }

public:

    my_b_tree() noexcept: _M_root(nullptr) {}

    void insert(const value_type &value) noexcept {

    }

private:
    _Node *_M_root;
};*/

#endif //ALGORITHMS_AND_DATA_STRUCTS_B_TREE_HPP
