#ifndef ALGORITHMS_AND_DATA_STRUCTS_MY_DEQUEUE_HPP
#define ALGORITHMS_AND_DATA_STRUCTS_MY_DEQUEUE_HPP


#include <cctype>
#include <istream>
#include <fstream>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <algorithm>

class overflowException : public std::out_of_range {
public:
    overflowException() : std::out_of_range("overflow") {}
};

class underflowException : public std::out_of_range {
public:
    underflowException() : std::out_of_range("underflow") {}
};

template<class T>
class Dequeue {
public:

    explicit Dequeue() : _ptr{nullptr}, _size{0}, _head{-1}, _tail{-1} {}


    inline bool empty() const noexcept {
        return _head == -1 && _tail == -1;
    }

    inline bool isSized() const noexcept {
        return _size != 0;
    }

    inline void setSize(size_t n) noexcept {
        _ptr = std::make_unique<T[]>(n);
        _size = n;
    }

    inline void pushBack(const T &val) {
        if ((_head == 0 && _tail == _size - 1) || (_head == _tail + 1))
            throw overflowException();
        if (empty())
            _head = _tail = 0;
        else if (_tail == _size - 1)
            _tail = 0;
        else
            _tail = _tail + 1;
        _ptr[_tail] = val;
    }

    inline void pushFront(const T &val) {
        if ((_head == 0 && _tail == _size - 1) || (_head == _tail + 1))
            throw overflowException();
        if (empty())
            _head = _tail = 0;
        else if (_head == 0)
            _head = _size - 1;
        else
            _head = _head - 1;
        _ptr[_head] = val;
    }

    inline T popFront() {
        if (empty())
            throw underflowException();
        T pop_value = _ptr[_head];
        if (_tail == _head) {
            _head = -1;
            _tail = -1;
        } else {
            _head = (_head + 1) % _size;
        }
        return pop_value;
    }

    inline T popBack() {
        if (empty())
            throw underflowException();
        T pop_value = _ptr[_tail];
        if (_tail == _head) {
            _head = -1;
            _tail = -1;
        } else {
            _tail = (_tail == 0 ? _size - 1 : --_tail);
        }
        return pop_value;
    }

    void Print() const noexcept {
        if (empty()) {
            std::cout << "empty\n";
            return;
        }
        for (int i = _head; i != _tail; i = (i + 1) % _size)
            std::cout << _ptr[i] << ' ';
        std::cout << _ptr[_tail] << std::endl;
    }

    template<class U>
    friend std::ostream &operator<<(std::ostream &, Dequeue<U> &);

private:
    std::unique_ptr<T[]> _ptr;
    int _size;
    int _head;
    int _tail;
};

//template <class T>
//std::ostream& operator<<(std::ostream& out, Dequeue<T>& dq){
//	if(dq.empty())
//		return out << "empty";
//	for(int i = dq._head; i != dq._tail; i = (i + 1) % dq._size)
//		out<< dq._ptr[i]<<" ";
//	out << dq._ptr[dq._tail];
//	return out;
//}


//
//int main(int argc, char ** argv){
//
//    Dequeue<std::string> dq;
//    std::string line;
////    std::ifstream in{argv[1]};
//    //std::ofstream out{argv[2]};
//    while(std::getline(std::cin, line) && !dq.isSized()){
//        if(line.empty())
//            continue;
//        auto it = std::find_if(line.begin(), line.end(), [](char c){ return std::isspace(c); });
//        if(std::string(line.begin(), it) != "set_size"){
//            std::cout << "error\n";
//            continue;
//        }
//        it = std::find_if_not(it, line.end(), [](char c){ return std::isspace(c);});
//        auto sizeVal = std::string(it, line.end());
//        try{
//            dq.setSize(std::stoull(sizeVal));
//        }catch(const std::invalid_argument&){
//            std::cout << "error\n";
//        }
//    }
//    if(!dq.isSized())
//        return 0;
//    /*while(std::getline(std::cin, line))*/do{
//        if(line.empty())
//            continue;
//        auto it = std::find_if(line.begin(), line.end(), [](char c){ return std::isspace(c);});
//        auto cmd = std::string(line.begin(), it);
//        if(cmd == "print"){
//            if(it == line.end())
//                dq.Print();
//            else
//                std::cout<< "error\n";
//        }else if(cmd == "pushb"){
//            auto end = std::find_if(it + 1, line.end(), [](char c){return std::isspace(c);});
//            if(end != line.end()){
//                std::cout<< "error\n";
//                continue;
//            }
//            try{
//                it = std::find_if_not(it, line.end(), [](char c){ return std::isspace(c);});
//                dq.pushBack(std::string(it, line.end()));
//            }catch(const overflowException& e){
//                std::cout << e.what()<<std::endl;
//            }
//        }else if(cmd == "pushf"){
//            auto end = std::find_if(it + 1, line.end(), [](char c){return std::isspace(c);});
//            if(end != line.end()){
//                std::cout<< "error\n";
//                continue;
//            }
//            try{
//                it = std::find_if_not(it, line.end(), [](char c){ return std::isspace(c);});
//                dq.pushFront(std::string(it, line.end()));
//            }catch(const overflowException& e){
//                std::cout << e.what()<<std::endl;
//            }
//        }else if(cmd == "popb"){
//            if(it == line.end()){
//                try{
//                    std::cout << dq.popBack() <<std::endl;
//                }catch(const underflowException& e){
//                    std::cout << e.what()<<std::endl;
//                }
//            }else{
//                std::cout<< "error\n";
//            }
//        }else if(cmd  == "popf"){
//            if(it == line.end()){
//                try{
//                    std::cout <<dq.popFront()<<std::endl;
//                }catch(const underflowException& e){
//                    std::cout << e.what()<<std::endl;
//                }
//            }else{
//                std::cout<< "error\n";
//            }
//        }else{
//            std::cout <<"error\n";
//        }
//    }while(std::getline(std::cin, line));
//    return 0;
//}



#endif //ALGORITHMS_AND_DATA_STRUCTS_MY_DEQUEUE_HPP
