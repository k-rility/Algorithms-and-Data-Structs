#ifndef ALGORITHMS_AND_DATA_STRUCTS_MY_HASH_TABLE_HPP
#define ALGORITHMS_AND_DATA_STRUCTS_MY_HASH_TABLE_HPP

#include <iostream>
#include <list>
#include <vector>
#include <algorithm>

template<typename Tv>
class LinkedList {
    using value_type = Tv;
private:
    struct _Node {
        value_type value;
        _Node *_next;
    };
public:

    LinkedList() noexcept: _Head(nullptr) {}

    ~LinkedList() noexcept {
        while (_Head != nullptr) {
            _Node *next = _Head->_next;
            delete _Head;
            _Head = next;
        }
        delete _Head;
    }

    inline void PushFront(const value_type &value) noexcept {
        _Head = new _Node{value, _Head};
    }

    bool isEmpty() const noexcept {
        return _Head == nullptr;
    }

    inline void PopFront() noexcept {
        if (isEmpty()) return;
        _Node *tmp = _Head;
        _Head = _Head->_next;
        delete tmp;
    }

private:
    _Node *_Head;
};

// Хэш-таблица с открытой адресацией

class HashTable {

public:

    HashTable() {}

    void Insert(const std::string &value) noexcept {
        _Array[_HashIndex(_HashFunc(value))].PushFront(value);
    }

//    void Remove(const std::string &value) noexcept {
//
//    }


private:

    struct _Node {
        std::string _value;
        bool _isDeleted;

        _Node(const std::string &value) : _value(value), _isDeleted(false) {}
    };

    size_t _Size = 11; // размер ХТ
    size_t _elementCount = 0;
    LinkedList<_Node> _Array[11]; // массив указателей на списки

    inline uint64_t _HashIndex(uint64_t key) const noexcept {
        return key % _Size;
    }

    inline uint64_t _HashFunc(const std::string &string) const noexcept {
        int64_t i = 0;
        for (const auto &x: string)
            i += x;
        return i;
    }
};



//TODO

////template<typename _Tvalue>
//class HashTable {
//public:
////    using value_type = _Tvalue;
//
//    HashTable(size_t capacity) : m_list_vec{new std::list<std::string> *[capacity]}, m_capacity{capacity} {}
//
////    void Insert(size_t key, const std::string &value) {
////
////    }
//
//private:
//    std::list<std::string> **m_list_vec;
//    size_t m_capacity;
//
//    int HashFunc(int key) const { return key % m_capacity; }
//};


//TODO

//template<typename _Tkey, typename _Tvalue>
//class my_hash_table {
//
//public:
//
//    using key_type = _Tkey;
//    using value_type = _Tvalue;
//
////    my_hash_table(): {}
//private:
//
////    my_hash_table(): {}
//
//    int HashFunc(int key, size_t tableSize) {
//        return key % tableSize;
//    }
//
//    int HashFunc(const std::string &key, size_t tableSize) {
//        int hashValue = 0;
//        for (char ch: key)
//            hashValue += ch;
//        return hashValue % tableSize;
//    }
//
//};

#endif //ALGORITHMS_AND_DATA_STRUCTS_MY_HASH_TABLE_HPP
