#pragma once

#include "types.h"
#include "make_vector.hpp"

#include "gmock/gmock.h"
#include <algorithm>
#include <vector>
#include <memory>

namespace sinfer {

template<typename T>
class Tensor {
public:
    Tensor();
    Tensor(const std::vector<int>& dims);
    template<typename...Args>
    Tensor(Args...args);
    Tensor(const Tensor& other);
    Tensor(const Tensor&& other);
    Tensor& operator=(const Tensor& other);
    ~Tensor();

    T& operator[](const std::vector<int>& indices);
    const T& operator[](const std::vector<int>& indices) const;

    auto get_dimensions() const -> std::vector<int> {return dims_;}
    T* get_data() {return data_;}
    int use_count() {return *refcount_;}
    void show();

private:
    T* data_;
    int* refcount_;
    std::vector<int> dims_;
};

template<typename T>
Tensor<T>::Tensor()
    : data_(nullptr)
    , refcount_(new int(1))
{
}

template<typename T>
Tensor<T>::Tensor(const std::vector<int>& dims)
    : data_(nullptr)
    , refcount_(new int(1))
    , dims_(dims)
{
    int size = 1;
    for (int d : dims_) {
        size *= d;
    }
    data_ = new T[size];
}

template<typename T>
Tensor<T>::Tensor(const Tensor& other)
    : data_(nullptr)
    , refcount_(new int(1))
    , dims_(other.dims)
{
    int size = 1;
    for (int d : dims_) {
        size *= d;
    }
    data_ = new T[size];
    std::copy(other.data_, other.data_+size, data_);
}

template<typename T>
Tensor<T>::Tensor(const Tensor&& other)
    : data_(other.data_)
    , refcount_(other.refcount_)
    , dims_(std::move(other.dims))
{
    other.data_ = nullptr;
    other.refcount_ = nullptr;
}

template<typename T>
Tensor<T>& Tensor<T>::operator=(const Tensor<T>& other)
{
    if (this == &other) {
        return *this;
    }
    delete[] data_;
    dims_ = other.dims_;
    int size = 1;
    for (int d : dims_) {
        size *= d;
    }
    data_ = new T[size];
    std::copy(other.data_, other.data_+size, data_);
    refcount_ = other.refcount_;
    ++(*refcount_);
}

template<typename T>
Tensor<T>::~Tensor()
{
    if (refcount_ && --(*refcount_) == 0) {
        if (data_) {
            delete[] data_;  
        }
        delete refcount_;
    }
}

template<typename T>
T& Tensor<T>::operator[](const std::vector<int>& indices) {
    int index = 0;
    int stride = 1;
    for (size_t i = dims_.size()-1; i >= 0; --i) {
        index += stride * indices[i];
        stride *= dims_[i];
    }
    return data_[index];
}

template<typename T>
const T& Tensor<T>::operator[](const std::vector<int>& indices) const {
    int index = 0;
    int stride = 1;
    for (size_t i = dims_.size()-1; i >= 0; --i) {
        index += stride * indices[i];
        stride *= dims_[i];
    }
    return data_[index];
}

template<typename T> 
template<typename ...Args>
Tensor<T>::Tensor(Args...args) 
    :Tensor(make_vector<int>(args...))
{

}


}   // namespace sinfer