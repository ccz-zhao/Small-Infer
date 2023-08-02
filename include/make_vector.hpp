#pragma once
#include <vector>


namespace sinfer {

template<typename T>
void push_vector(std::vector<T>& v, const T& t) {
    v.push_back(t);
}

template<typename T, typename ...Args>
void push_vector(std::vector<T>& v, const T& t, Args... args) {
    v.push_back(t);
    push_vector(v, args...);
}

template<typename T, typename ...Args>
std::vector<T> make_vector(Args... args) {
    std::vector<T> v;
    push_vector(v, args...);
    return v;
}

}   // namespace sinfer