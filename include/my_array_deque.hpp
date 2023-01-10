#ifndef ALGORITHMS_AND_DATA_STRUCTS_MY_ARRAY_DEQUE_HPP
#define ALGORITHMS_AND_DATA_STRUCTS_MY_ARRAY_DEQUE_HPP

#include <iostream>
#include <memory>
#include <exception>

template<class T>
class Deque {
public:

    Deque() : _ptr{nullptr}, _size{0}, _head{-1}, _tail{-1} {}

    void setSize(size_t n) noexcept {
        _ptr = std::make_unique<T[]>(n);
        _size = n;
    }

    bool empty() const noexcept {
        return _head == -1;
    }

    void pushBack(const T &val) {
        if ((_tail = (_tail + 1) % _size) == _head)
            throw std::runtime_error("overflow");
        if (empty())
            _head = 0;
        _ptr[_tail] = val;

    }

    void pushFront(const T &val) {
        if(empty())
            _head = 0;
        if((_head = (_head == 0 ? _size - 1 : _head - 1)) == _tail)
            throw std::runtime_error("error");
        if(_tail == -1)
            _tail = 0;
        _ptr[_head] = val;
    }

    T popBack() {
        if (empty())
            throw std::runtime_error("error");
        T pop_value = _tail;
        if (_tail == _head) {
            _tail = -1;
            _head = -1;
        } else {
            _tail = (_tail == 0 ? _size - 1 : _tail - 1);
        }
        return _ptr[pop_value];
    }

    T popFront() {
        if (empty())
            throw std::runtime_error("error");
        T pop_value = _head;
        if (_tail == _head) {
            _tail = -1;
            _head = -1;
        } else {
            _head = (_head + 1) % _size;
        }
        return _ptr[pop_value];
    }

    template<class U>
    friend std::ostream &operator<<(std::ostream &, Deque<U> &);

private:

    std::unique_ptr<T[]> _ptr;
    int _size;
    int _head;
    int _tail;

};

template<class T>
std::ostream &operator<<(std::ostream &out, Deque<T> &d) {
    if (d.empty())
        return out << "empty\n";
    for (int i = d._head; i != d._tail; i = (i + 1) % d._size)
        out << d._ptr[i] << " ";
    out << d._ptr[d._tail];
    return out;
}

#endif //ALGORITHMS_AND_DATA_STRUCTS_MY_ARRAY_DEQUE_HPP
