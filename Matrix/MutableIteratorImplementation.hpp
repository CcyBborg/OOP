#ifndef MUTABLE_ITERATOR_IMPLEMENTATION_H
#define MUTABLE_ITERATOR_IMPLEMENTATION_H

#include "MutableIterator.h"
#include "Iterator.h"

using namespace containers::iterators;

template <typename T>
MutableIterator<T>::MutableIterator(const MutableIterator<T>& other) : Iterator<T>(other) {}

template <typename T>
MutableIterator<T>::MutableIterator(std::shared_ptr<T> sharedPtr, size_t index) : Iterator<T>(sharedPtr, index) {}

template <typename T>
T& MutableIterator<T>::operator*() {
    return this->sharedPtr_[this->index_];
}

template <typename T>
T* MutableIterator<T>::operator->() {
    return this->sharedPtr_.get() + this->index_;
}

#endif