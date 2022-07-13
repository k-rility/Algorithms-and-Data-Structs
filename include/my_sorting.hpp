#ifndef AISD_MY_SORTING_HPP
#define AISD_MY_SORTING_HPP

template<class T>

bool less(const T &val1, const T &val2) noexcept {
    if (val1 < val2)
        return true;
    return false;
}

//template<class It, class Out, class Compare=>
#endif //AISD_MY_SORTING_HPP
