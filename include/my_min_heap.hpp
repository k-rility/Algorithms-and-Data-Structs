#ifndef ALGORITHMS_AND_DATA_STRUCTS_MY_MIN_HEAP_HPP
#define ALGORITHMS_AND_DATA_STRUCTS_MY_MIN_HEAP_HPP

#include <iostream>

#include <cstdint>
#include <exception>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

template<typename Key, typename Value>
class MinHeap {

    using value_type = Value;
    using key_type = Key;
    using node = std::pair<Key, Value>;

public:

    std::pair<node, size_t> Min() const {
        if (isEmpty())
            throw std::exception();
        return std::make_pair(m_array_[0], 0);
    }

    std::pair<node, size_t> Max() const {
        if (isEmpty())
            throw std::exception();
        size_t max_index = m_array_.size() - 1;
        size_t parent = _Parent(max_index);
        for (size_t i = max_index; i > parent; --i)
            if (m_array_[max_index] < m_array_[i])
                max_index = i;
        return std::make_pair(m_array_[max_index], max_index);
    }

    void Add(const key_type &key, const value_type &value) {
        if (m_map_.count(key) != 0)
            throw std::exception();
        size_t i = m_array_.size();
        m_array_.push_back({});
        while (i > 0 && m_array_[_Parent(i)].first > key) {
            m_array_[i] = std::move(m_array_[_Parent(i)]);
            m_map_[m_array_[i].first] = i;
            i = _Parent(i);
        }
        m_array_[i] = std::make_pair(key, value);
        m_map_[m_array_[i].first] = i;
    }

    void Set(const key_type &key, const value_type &value) {
        if (isEmpty())
            throw std::exception();
        m_array_[m_map_.at(key)].second = value;
    }

    node ExtractMin() {
        if (isEmpty())
            throw std::exception();
        node extracted = std::move(m_array_[0]);
        m_map_.erase(extracted.first);
        std::swap(m_array_.front(), m_array_.back());
        if (!m_map_.empty())
            m_map_[m_array_[0].first] = 0;
        m_array_.pop_back();
        _Heapify(0);
        return extracted;
    }

    inline bool isSearched(const key_type &key) const {
        return m_map_.count(key) == 1;
    }

    std::pair<node, size_t> Search(const key_type &key) {
        size_t i = m_map_.at(key);
        return std::make_pair(m_array_[i], i);
    }

    void Delete(const key_type &key) {
        if (isEmpty())
            throw std::exception();
        _HeapifyUp(m_map_.at(key));
        ExtractMin();
    }

    void Print() {
        if (isEmpty()) {
            std::cout << '_' << std::endl;
            return;
        }

        std::cout << '[' << m_array_.front().first << ' ' << m_array_.front().second << ']';
        size_t i = 1;
        size_t lvlSize = 2;
        while (lvlSize <= m_array_.size()) {
            std::cout << std::endl;
            for (size_t j = 0; j < lvlSize; ++j, ++i) {
                if (i < m_array_.size())
                    std::cout << '[' << m_array_[i].first << ' ' << m_array_[i].second << ' '
                              << m_array_[_Parent(i)].first << "] ";
                else
                    std::cout << "_ ";
            }
            lvlSize <<= 1u;
            // 1 - 1
            // 1 << 1u -- 2 = 10
            // 2 << 1u -- 4 = 100
            // 4 << 1u -- 8 = 1000
            // ...
        }
    }

private:
    std::vector<node> m_array_;
    std::unordered_map<key_type, size_t> m_map_;

    inline bool isEmpty() const { return m_array_.empty(); }

    size_t _Parent(size_t n) const { return (n - 1) >> 1u; }

    size_t _Left(size_t n) const { return (n << 1u) + 1; }

    size_t _Right(size_t n) const { return (n << 1u) + 2; }

    void _Heapify(size_t n) {
        size_t left = _Left(n);
        size_t right = _Right(n);
        size_t smallest = n;
        if (left < m_array_.size() && m_array_[smallest].first > m_array_[left].first)
            smallest = left;
        if (right < m_array_.size() && m_array_[smallest].first > m_array_[right].first)
            smallest = right;
        if (smallest != n) {
            std::swap(m_map_[m_array_[smallest].first], m_map_[m_array_[n].first]);
            std::swap(m_array_[n], m_array_[smallest]);
            _Heapify(smallest);
        }
    }

    void _HeapifyUp(size_t n) {
        if (n > 0 && m_array_[n].first > m_array_[_Parent(n)].first) {
            std::swap(m_map_[m_array_[n].first], m_map_[m_array_[_Parent(n)].first]);
            std::swap(m_array_[n], m_array_[_Parent(n)]);
            _HeapifyUp(_Parent(n));
        }
    }

};

#endif //ALGORITHMS_AND_DATA_STRUCTS_MY_MIN_HEAP_HPP
