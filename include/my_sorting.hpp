#ifndef AISD_MY_SORTING_HPP
#define AISD_MY_SORTING_HPP

#include <iostream>
#include <vector>
#include <cmath>

// сортировка пузырьком - все элементы последовательно сравниваются со всеми

// сортировка пузырьком
// сложность в лучем случае О(n)
// сложность в худшем случае О(n^2)
// сложность в среднем О(n^2)
// память O(1)
// устойчивая
// адаптивная
// нельзя расспараллелить

template<typename It, typename Compare = std::less<>>
void bubbleSort(It first, It last, Compare cmp = Compare{}) {
    for (It i = first; i != last - 2; ++i) {
        for (It j = first; j != last - 1; ++j)
            if (cmp(*j, *(j + 1)))
                std::iter_swap(j, j + 1);
    }
}

// сортировка вставками - все элементы последовательно размещаются в подходящее место среди ранее упорядоченных элементов

// сортировка вставками
// сложность в лучем случае О(n)
// сложность в худшем случае О(n^2)
// сложность в среднем О(n^2)
// память O(1)
// устойчивая
// адаптивная
// нельзя расспараллелить

template<typename It, typename Compare = std::less<>>
void selectionSort(It first, It last, Compare cmp = Compare{}) {
    for (It i = first; i != last - 1; ++i) {
        It min_or_max = i;
        for (It j = i + 1; j != last; ++j) {
            if (cmp(*min_or_max, *j))
                min_or_max = j;
//            for (It k = first; k != last; ++k)
//                if (k == min_or_max)
//                    std::cout << "[" << *k << "] ";
//                else
//                    std::cout << *k << " ";
//            std::cout << std::endl;
        }
        std::iter_swap(min_or_max, i);
    }
}

// сортировка выбором - вабирается минимальный элемент из неотсортированной части и кладется на соответствующее ему место

// сортировка выбором
// сложность в лучем случае О(n^2)
// сложность в худшем случае О(n^2)
// сложность в среднем О(n^2)
// память O(1)
// не устойчивая
// не адаптивная
// нельзя расспараллелить

template<typename It, typename Compare = std::less<>>
void insertionSort(It first, It last, Compare cmp = Compare{}) {
    for (It i = first + 1; i != last; ++i) {
        It j = i - 1;
        while (j >= first && cmp(*j, *(j + 1))) {
            std::iter_swap(j, j + 1);
            --j;
//            for (It k = first; k != last; ++k)
//                if (k == j + 1)
//                    std::cout << "[" << *k << "] ";
//                else
//                    std::cout << *k << " ";
//            std::cout << std::endl;
        }
    }
}

// сортировка слиянием - это сортировка, затем они аналогично сортируются (т.е. применяется рекурсия), после чего эти
// два отсортированных массива объединяются

// сложность по времени во всех случаях O(nlogn)
// слияние массива требует дополнительный массив, а слияние списка происходит без затрат памяти (т.к. элементы можно
// свободно отцеплять от входных списков и включать в итоговый)

// затраты памяти:
//      - массив: O(n) для слияния нужен массив
//      - список: O(logn) осталась рекурсия
// устойчива
// распараллеливается
// не адаптивна

// merge - операция слияния, которая принимает на вход два отсортированных массива (или связных списка) и возвращает
// новый отсортированный, в который входят все элементы обоих исходных массивов

void merge(size_t first1, size_t first2, size_t last, std::vector<int> &vec) {
    const size_t n1 = first2 - first1 + 1;
    const size_t n2 = last - first2;
    std::vector<int> L;
    std::vector<int> R;
    for (size_t i = 0; i < n1; ++i)
        L.push_back(vec[first1 + i]);
    for (size_t i = 0; i < n2; ++i)
        R.push_back(vec[first2 + i + 1]);
    size_t i = 0;
    size_t j = 0;
    for (size_t k = first1; k < last + 1; ++k) {
        if (j == R.size() || (i != L.size() && L[i] <= R[j])) {
            vec[k] = L[i];
            ++i;
        } else {
            vec[k] = R[j];
            ++j;
        }
    }
}

void mergeSort(size_t first, size_t last, std::vector<int> &vec) {
    if (first < last) {
        size_t mid = std::floor((first + last) / 2);
        mergeSort(first, mid, vec);
        mergeSort(mid + 1, last, vec);
        merge(first, mid, last, vec);
    }
}

//template<typename It, typename Compare = std::less<>>
//void merge(It first1, It first2, It last, Compare cmp = Compare{}) {
//    const size_t n1 = first2 - first1 + 1;
//    const size_t n2 = last - first2;
//    std::vector<typename It::value_type> L;
//    std::vector<typename It::value_type> R;
////    int L[n1];
////    int R[n2];
////    for (size_t i = 0; i < n1 - 1; ++i)
////        L[i] = *(first1 + i);
////    for (size_t i = n2; i < n2 - 1; ++i)
////        L[i] = *(first2 + i - 1);
//    for (size_t i = 0; i < n1 - 1; ++i)
//        L.push_back(*(first1 + i));
//    for (size_t i = n2; i < n2 - 1; ++i)
//        R.push_back(*(first2 + i - 1));
//    size_t i = 0;
//    size_t j = 0;
//    for (It k = first1; k != last; ++k) {
//        if (cmp(L[i], R[j])) {
//            *k = L[i];
//            ++i;
//        } else {
//            *k = R[j];
//            ++j;
//        }
//    }
//}

//template<typename It, typename Compare = std::less<>>
//void mergeSort(It first, It last, Compare cmp = Compare{}) {
//    auto size = (last - first);
//    if (first < last - 1) {
//        It mid = last - std::ceil((size / 2));
//        mergeSort(first, mid, cmp);
//        mergeSort(mid + 1, last);
//        merge(first, mid, last, cmp);
//    }
//}

// сортировка подсчетом - сортировка числовых элементов, при которой производится подсчет вхождений каждого числа,
// и на основании этого осуществляется заполнение итогового массива

// сложность О(n + k)
// память O(n + k) выход и массив подсчетов
// устойчива в некоторых реализациях
// распараллеливания нет (можно в некоторых реализациях)
// не адаптивна

// где in - массив, который требуется отсортировать
// out - отсортированный массив
// k
// Применение сортировки подсчётом целесообразно лишь тогда, когда сортируемые числа имеют (или их можно отобразить в)
// диапазон возможных значений, который достаточно мал по сравнению с сортируемым множеством, например,
// миллион натуральных чисел меньших 1000.

void countSort(const std::vector<int> &in, std::vector<int> &out, size_t k) {
    std::vector<int> P;
    for (size_t i = 0; i < k; ++i)
        P.push_back(0);
    for (const auto &x: in)
        P[x] += 1;
    for (size_t i = 1; i < P.size(); ++i)
        P[i] += P[i - 1];
    for (size_t i = in.size(); i > 0; --i)
        out[--P[in[i - 1]]] = in[i - 1];
}

// TODO

// поразрядная сортировка (radix sort) - сортировка производящаяся поразрядно (для числа), побуквенно (для строки) и т.п.

// LSD (least significant digit) - реализация, при которой сортировка начинается с наименее значимого разряда и
// далее воспроизводится для более и более значимых разрядов

// MSD (most significant digit) - реализация, при которой сортировка начинается с наиболее значимого разряда и
// далее воспроизводится для менее и менее значимых разрядов

// для каждого разряда обязательно нужно выполнять устойчивую сортировку (например, сортировку подсчетом)

// обе реализации не адаптивны
// сложность O(lambda * d), где lambda - сложность используемой на символах сортировки
// d - наибольшее число разрядов в объекте
// О((n + k) * d) с сортировкой подсчетом

////============================================================================

// быстрая сортировка - сортировка, при которой в массиве выбирается элемент, после этого массив упорядочивается так,
// что все значения меньше выбранного оказались слева, больше - справа, далее происходит сортировка левого и правого подмассивов

int three_median(int a, int b, int c) {
    if (b > a) {
        if (b < c)
            return b;
        return (c < a) ? a : c;
    }
    if (a < c)
        return a;
    return (c < b) ? b : c;
}


std::pair<int, int> partition(std::vector<int> &vec, size_t left, size_t right, int pivot) {
    size_t m = left;
    while (m != right) {
        if (vec[m + 1] == pivot)
            ++m;
        else if (vec[m + 1] > pivot) {
            std::swap(vec[m + 1], vec[right]);
            --right;
        } else {
            std::swap(vec[m + 1], vec[left]);
            ++left;
            ++m;
        }
    }
    return {left, right};
}

void quickSort(std::vector<int> &vec, size_t left, size_t right) {
    if (left != right) {
        int pivot = three_median(vec[left], vec[right], vec[left + (((right - left) + 1) / 2)]);
        auto lr = partition(vec, left, right, pivot);
        quickSort(vec, left, lr.first);
        quickSort(vec, lr.second, right);
    }
}


#endif //AISD_MY_SORTING_HPP
