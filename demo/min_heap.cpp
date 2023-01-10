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

    struct node {
        key_type key;
        value_type value;
    };

public:


    node Min() const {
        if (isEmpty())
            throw std::exception();
        return m_array_[0];
    }

    node &At(size_t idx) {
        if (idx > m_array_.size() - 1)
            throw std::exception();
        return m_array_[idx];
    }

    node Max() const {
        if (isEmpty())
            throw std::exception();
        size_t max_index = m_array_.size() - 1;
        size_t parent = _Parent(max_index);
        for (size_t i = max_index; i > parent; --i)
            if (m_array_[max_index].key < m_array_[i].key)
                max_index = i;
        return m_array_[max_index];
    }

    void Add(const key_type &key, const value_type &value) {
        if (m_map_.count(key) != 0)
            throw std::exception();
        size_t i = m_array_.size();
        m_array_.push_back({});
        while (i > 0 && m_array_[_Parent(i)].key > key) {
            m_array_[i] = std::move(m_array_[_Parent(i)]);
            m_map_[m_array_[i].key] = i;
            i = _Parent(i);
        }
        m_array_[i] = node{key, value};
        m_map_[m_array_[i].key] = i;
    }

    void Set(const key_type &key, const value_type &value) {
        if (isEmpty())
            throw std::exception();
        m_array_[m_map_.at(key)].value = value;
    }

    node ExtractMin() {
        if (isEmpty())
            throw std::exception();
        node extracted = std::move(m_array_[0]);
        m_map_.erase(extracted.key);
        std::swap(m_array_.front(), m_array_.back());
        if (!m_map_.empty())
            m_map_[m_array_[0].key] = 0;
        m_array_.pop_back();
        _Heapify(0);
        return extracted;
    }

    inline bool isSearched(const key_type &key) const {
        return m_map_.count(key) == 1;
    }

    size_t Search(const key_type &key) {
        return m_map_.find(key)->second;
    }

    void Delete(const key_type &key) {
        if (isEmpty())
            throw std::exception();
        _HeapifyUp(m_map_.at(key));
        ExtractMin();
    }

    template<typename K, typename V>

    friend std::ostream &operator<<(std::ostream &, const MinHeap<K, V> &) noexcept;

private:
    std::vector<node> m_array_;
    std::unordered_map<key_type, size_t> m_map_;

    inline bool isEmpty() const { return m_array_.empty(); }

    inline size_t _Parent(size_t n) const { return (n - 1) >> 1u; }

    inline size_t _Left(size_t n) const { return (n << 1u) + 1; }

    inline size_t _Right(size_t n) const { return (n << 1u) + 2; }

    void _Heapify(size_t n) {
        size_t left = _Left(n);
        size_t right = _Right(n);
        size_t smallest = n;
        if (left < m_array_.size() && m_array_[smallest].key > m_array_[left].key)
            smallest = left;
        if (right < m_array_.size() && m_array_[smallest].key > m_array_[right].key)
            smallest = right;
        if (smallest != n) {
            std::swap(m_map_[m_array_[smallest].key], m_map_[m_array_[n].key]);
            std::swap(m_array_[n], m_array_[smallest]);
            _Heapify(smallest);
        }
    }

    void _HeapifyUp(size_t n) {
        if (n > 0 && m_array_[n].key > m_array_[_Parent(n)].key) {
            std::swap(m_map_[m_array_[n].key], m_map_[m_array_[_Parent(n)].key]);
            std::swap(m_array_[n], m_array_[_Parent(n)]);
            _HeapifyUp(_Parent(n));
        }
    }

};

template<typename K, typename V>

std::ostream &operator<<(std::ostream &out, const MinHeap<K, V> &mh) noexcept {
    if (mh.isEmpty()) {
        out << '_';
        return out;
    }

    out << '[' << mh.m_array_.front().key << ' ' << mh.m_array_.front().value << ']';
    size_t i = 1;
    size_t lvlSize = 2;
    while (lvlSize <= mh.m_array_.size()) {
        out << std::endl;
        for (size_t j = 0; j < lvlSize; ++j, ++i) {
            if (i < mh.m_array_.size())
                out << '[' << mh.m_array_[i].key << ' ' << mh.m_array_[i].value << ' '
                    << mh.m_array_[mh._Parent(i)].key << "] ";
            else
                out << "_ ";
        }
        lvlSize <<= 1u;
        // 1 - 1
        // 1 << 1u -- 2 = 10
        // 2 << 1u -- 4 = 100
        // 4 << 1u -- 8 = 1000
        // ...
    }
    return out;
}

int main([[maybe_unused]]int argc, [[maybe_unused]]char **argv) {
    MinHeap<int64_t, std::string> mh;
    int64_t key;
    std::string value;
    std::string cmd;
    while (std::cin >> cmd) {
        try {
            if (cmd == "add") {
                std::cin >> key >> value;
                mh.Add(key, value);
            } else if (cmd == "set") {
                std::cin >> key >> value;
                mh.Set(key, value);
            } else if (cmd == "min") {
                auto node = mh.Min();
                std::cout << node.key << ' ' << 0 << ' ' << node.value << std::endl;
            } else if (cmd == "max") {
                auto node = mh.Max();
                std::cout << node.key << ' ' << mh.Search(node.key) << ' ' << node.value << std::endl;
            } else if (cmd == "search") {
                std::cin >> key;
                if (!mh.isSearched(key))
                    std::cout << false << std::endl;
                else {
                    auto index = mh.Search(key);
                    std::cout << true << ' ' << index << ' ' << mh.At(index).value << std::endl;
                }
            } else if (cmd == "delete") {
                std::cin >> key;
                mh.Delete(key);
            } else if (cmd == "print") {
                std::cout << mh << std::endl;
            } else if (cmd == "extract") {
                auto node = mh.ExtractMin();
                std::cout << node.key << ' ' << node.value << std::endl;
            }
        } catch (const std::exception &) {
            std::cout << "error" << std::endl;
        }


    }
    return 0;
}
