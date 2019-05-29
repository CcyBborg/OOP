#ifndef MUTABLE_ITERATOR_H
#define MUTABLE_ITERATOR_H

#include "Iterator.h"

namespace containers::iterators {
    template<typename T>
    class MutableIterator : public Iterator<T> {
    public:
        MutableIterator(const MutableIterator<T>& other);
        MutableIterator(std::shared_ptr<T> sharedPtr, size_t index);

        T& operator*();
        T* operator->();
    };
}

#include "MutableIteratorImplementation.hpp"

#endif