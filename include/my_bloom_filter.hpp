#ifndef ALGORITHMS_AND_DATA_STRUCTS_MY_BLOOM_FILTER_HPP
#define ALGORITHMS_AND_DATA_STRUCTS_MY_BLOOM_FILTER_HPP

#include <iostream>
#include <cmath>
#include <vector>
#include <memory>
#include <algorithm>
#include "bitset"
#include <fstream>

class MyBloomFilter {
public:

    MyBloomFilter() = default;

    void Set(uint64_t N, double P) {
        n_ = N;
        P_ = P;
        m_ = std::round((-(n_ * std::log2(P_))) / std::log(2));
        hash_num_ = std::round(-std::log2(P_));
        SetPrimeNumber(hash_num_);
//        bits_ = std::make_unique<bool[]>(m_);
    }

    void Add(uint64_t K) {
        for (size_t i = 0; i < hash_num_; ++i)
            bits_[Hash(i, K)] = true;
    }

    bool Search(uint64_t K) const {
        for (size_t i = 0; i < hash_num_; ++i)
            if (bits_[Hash(i, K)] != true)
                return false;
        return true;
    }

    friend std::ostream &operator<<(std::ostream &, MyBloomFilter &);

    uint64_t GetHashNum() const noexcept {
        return hash_num_;
    }

    size_t GetStructSize() const noexcept {
        return m_;
    }

private:

    static constexpr size_t bloomFilterSize = 65536;

//    void SetPrimeNumber(uint64_t hashNum) {
//        while (arr_primes_.size() < hashNum) {
//            auto prime = arr_primes_[arr_primes_.size() - 1] + 1;
//            for (size_t i = 0; i < arr_primes_.size() - 1;) {
//                if (prime % arr_primes_[i] == 0) {
//                    ++prime;
//                    i = 0;
//                } else {
//                    ++i;
//                }
//            }
//            arr_primes_.push_back(prime);
//        }
//    }
    void SetPrimeNumber(uint64_t hashNum) {
        arr_primes_ = std::make_unique<uint64_t[]>(hashNum);
        arr_primes_[0] = 2;
        size_t size = 1;
        uint64_t counter = 3;
        while (size != hashNum) {
            bool flag = true;
            for (size_t i = 0; i < size && size != hashNum; ++i) {
                if (counter % arr_primes_[i] == 0) {
                    ++counter;
                    flag = false;
                    break;
                }
            }
            if(flag){
                arr_primes_[size] = counter;
                ++size;
            }
        }
    }

    long long Hash(uint64_t i, uint64_t K) const {
        return (((i + 1) * K + arr_primes_[i]) % M_) % m_;
    }

    uint64_t n_;
    double P_;
    size_t m_;
    uint64_t hash_num_;
//    std::vector<uint64_t> arr_primes_ = {2};
    std::unique_ptr<uint64_t[]> arr_primes_;
    std::bitset<bloomFilterSize> bits_;
    long long M_ = std::pow(2, 31) - 1; // Mersenne
};

std::ostream &operator<<(std::ostream &out, MyBloomFilter &bf) {
    for (size_t i = 0; i < bf.m_; ++i)
        out << bf.bits_[i];
    return out;
}

int main([[maybe_unused]]int argc, char **argv) {
//    MyBloomFilter bf;
//    bool isSet = false;
//
//    std::ifstream in{argv[1]};
//
//    std::string line;
//    while (!isSet && std::getline(in, line)) {
//        if (line.empty())
//            continue;
//        auto it = std::find_if(line.begin(), line.end(), [](char c) { return std::isspace(c); });
//        if (std::string(line.begin(), it) != "set") {
//            std::cout << "error\n";
//            continue;
//        }
//        auto it_n = std::find_if_not(it, line.end(), [](char c) { return std::isspace(c); });
//        auto it_P = std::find_if(it_n, line.end(), [](char c) { return std::isspace(c); });
//        auto n = std::string(it_n, it_P);
//        auto P = std::string(it_P, line.end());
//        try {
//            bf.Set(std::stoull(n), std::stod(P));
//        } catch (std::invalid_argument &) {
//            std::cout << "error\n";
//            continue;
//        }
//        std::cout << bf.GetStructSize() << " " << bf.GetHashNum() << std::endl;
//        isSet = true;
//    }
//
//    while (std::getline(in, line)) {
//        if (line.empty())
//            continue;
//        auto it = std::find_if(line.begin(), line.end(), [](char c) { return std::isspace(c); });
//        std::string cmd = std::string(line.begin(), it);
//        if (cmd == "add") {
//            auto it_K = std::find_if_not(it, line.end(), [](char c) { return std::isspace(c); });
//            std::string K = std::string(it_K, line.end());
//            try {
//                bf.Add(std::stoull(K));
//            } catch (std::invalid_argument &) {
//                std::cout << "error\n";
//            }
//        } else if (cmd == "search") {
//            auto it_K = std::find_if_not(it, line.end(), [](char c) { return std::isspace(c); });
//            std::string K = std::string(it_K, line.end());
//            try {
//                if (bf.Search(std::stoul(K)))
//                    std::cout << true << std::endl;
//                else
//                    std::cout << false << std::endl;
//            } catch (std::invalid_argument &) {
//                std::cout << "error\n";
//            }
//        } else if (cmd == "print") {
//            std::cout << bf << std::endl;
//        } else {
//            std::cout << "error\n";
//        }
//    }
//    return 0;
//}

#endif //ALGORITHMS_AND_DATA_STRUCTS_MY_BLOOM_FILTER_HPP
