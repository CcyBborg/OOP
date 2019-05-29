#ifndef ITERATOR_IMPLEMENTATION_H
#define ITERATOR_IMPLEMENTATION_H

#include "Iterator.h"

using namespace containers::iterators;

template <typename T>
Iterator<T>::Iterator(std::shared_ptr<T> sharedPtr, size_t index) : sharedPtr_(sharedPtr), index_(index) {}

template <typename T>
Iterator<T>::Iterator(const Iterator<T>& other) : sharedPtr_(other.sharedPtr_), index_(other.index_) {}

template <typename T>
Iterator<T>::~Iterator() {
    sharedPtr_.reset();
}

template <typename T>
bool Iterator<T>::operator==(const Iterator<T>& other) const {
    return index_ == other.index_ && sharedPtr_ == other.sharedPtr_;
}

template <typename T>
bool Iterator<T>::operator!=(const Iterator<T>& other) const {
    return !(*this == other);
}

template <typename T>
Iterator<T>& Iterator<T>::operator++() {
    ++index_;
    return *this;
}

template <typename T>
Iterator<T> Iterator<T>::operator++(int) {
    Iterator<T> tmp(*this);
    ++(*this);
    return tmp;
}

template <typename T>
Iterator<T>& Iterator<T>::operator--() {
    --index_;
    return *this;
}

template <typename T>
Iterator<T> Iterator<T>::operator--(int) {
    Iterator<T> tmp(*this);
    --(*this);
    return tmp;
}

template <typename T>
const T& Iterator<T>::operator*() const {
    return sharedPtr_.get()[index_];
}

template <typename T>
const T* Iterator<T>::operator->() const {
    return sharedPtr_.get() + index_;
}

#endif
