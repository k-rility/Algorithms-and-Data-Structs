#ifndef ALGORITHMS_AND_DATA_STRUCTS_MY_HASH_TABLE_LINEAR_PROBE_HPP
#define ALGORITHMS_AND_DATA_STRUCTS_MY_HASH_TABLE_LINEAR_PROBE_HPP

#include <iostream>

// Хэш-таблица с открытой адресацией (метод линейной пробы)

class HashTableLinearProbe {
public:

    HashTableLinearProbe(size_t capacity = 11, double fillCoefficient = 0.75) : _Size{0}, _Capacity{capacity},
                                                                                _FillCoefficient{fillCoefficient},
                                                                                _Arr{new _Node *[_Capacity]} {
        for (size_t i = 0; i < _Capacity; ++i)
            _Arr[i] = nullptr;
    }

    ~HashTableLinearProbe() noexcept {
        for (size_t i = 0; i < _Capacity; ++i)
            if (_Arr[i]) delete _Arr[i];
        delete[] _Arr;
    }

    void Resize() noexcept {
        _Size = 0;
        _Capacity *= 2;
        _Node **newArr = new _Node *[_Capacity];
        for (size_t i = 0; i < _Capacity; ++i)
            newArr[i] = nullptr;
        std::swap(_Arr, newArr);
        for (size_t i = 0; i < _Capacity / 2; ++i)
            if (newArr[i] != nullptr && newArr[i]->_isDeleted != true)
                Insert(newArr[i]->_value);
        for (size_t i = 0; i < _Capacity / 2; ++i)
            if (newArr[i]) delete newArr[i];
        delete[] newArr;
    }

    void Rehash() noexcept {
        _Size = 0;
        _Node **newArr = new _Node *[_Capacity];
        for (size_t i = 0; i < _Capacity; ++i)
            newArr[i] = nullptr;
        _Node **tmp = newArr;
        newArr = _Arr;
        _Arr = tmp;
//        std::swap(newArr, _Arr);
        for (size_t i = 0; i < _Capacity; ++i)
            if (newArr[i] != nullptr && newArr[i]->_isDeleted != true)
                Insert(newArr[i]->_value);
        for (size_t i = 0; i < _Capacity; ++i)
            if (newArr[i]) delete newArr[i];
        delete[] newArr;
    }

    void Remove(const std::string &value) noexcept {
        uint64_t h = _HashIndex(_HashFunc(value));
        uint64_t i = 0;
        while (_Arr[h] != nullptr) {
            if (_Arr[h]->_value == value && _Arr[h]->_isDeleted == false) {
                _Arr[h]->_isDeleted = true;
                --_Size;
                return;
            }
            ++i;
            h = (h + i) % _Capacity;
        }
    }

    double GetFillCoefficient() const noexcept {
        return double(_Size) / _Capacity;
    }

    long long Find(const std::string &value) const noexcept {
        long long h = _HashIndex(_HashFunc(value));
        uint64_t i = 0;
        while (_Arr[h] != nullptr) {
            if (_Arr[h]->_value == value && _Arr[h]->_isDeleted == false)
                return h;
            ++i;
            h = (h + i) % _Capacity;
        }
        return -1;
    }

    void Insert(const std::string &value) noexcept {
        if (GetFillCoefficient() >=
            _FillCoefficient) // если коеффициент заполнения, больше заданного коеффициента, то происходит перехэширование
            Resize();
        uint64_t h = _HashIndex(_HashFunc(value));
        bool flag_is_deleted = false;
        uint64_t i = 0;
        while (_Arr[h] != nullptr || flag_is_deleted != false) {
            if (_Arr[h]->_value == value && _Arr[h]->_isDeleted == false)
                return;
            if (_Arr[h]->_isDeleted == true) {
                flag_is_deleted = true;
                break;
            }
            ++i;
            h = (h + i) % _Capacity;
        }
        if (flag_is_deleted == false)
            _Arr[h] = new _Node(value);
        else {
            _Arr[h]->_value = value;
            _Arr[h]->_isDeleted = true;
        }
        ++_Size;
    }

    friend std::ostream &operator<<(std::ostream &, HashTableLinearProbe &) noexcept;

private:

    struct _Node {
        std::string _value;
        bool _isDeleted;

        _Node(const std::string &value) : _value(value), _isDeleted(false) {}
    }; // содержить элементы, где _value - значение по индексу, а _isDeleted - пометка удален ли элемент

    size_t _Size; // количество элементов в ХТ (не удаленных)
    size_t _Capacity; // емкость массива
    double _FillCoefficient; // коэффициент заполнения
    _Node **_Arr; // массив с данными

    uint64_t _HashIndex(uint64_t key) const noexcept { // получение индекса по значению ХФ
        return key % _Capacity;
    }

    uint64_t _HashFunc(const std::string &value) const noexcept { // ХФ вычисляется как сумма кодов символов
        size_t k = 0;
        for (size_t i = 0; i < value.size(); ++i)
            k += value[i];
        return k;
    }
};

std::ostream &operator<<(std::ostream &out, HashTableLinearProbe &ht) noexcept { // красивенький вывод
    for (size_t i = 0; i < ht._Capacity; ++i) {
        if (ht._Arr[i] == nullptr)
            out << '[' << i << "] -> None" << std::endl;
        else if (ht._Arr[i]->_isDeleted == true)
            out << '[' << i << "] -> deleted" << std::endl;
        else
            out << '[' << i << "] -> " << ht._Arr[i]->_value << std::endl;
    }
    return out;
}

#endif //ALGORITHMS_AND_DATA_STRUCTS_MY_HASH_TABLE_LINEAR_PROBE_HPP
