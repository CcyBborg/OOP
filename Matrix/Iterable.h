#ifndef ITERABLE_H
#define ITERABLE_H

#include "Iterator.h"
#include "MutableIterator.h"

using namespace containers::iterators;

namespace containers {
    template <typename T>
    class Iterable {
    public:
        virtual Iterator<T> begin() const = 0;
        virtual Iterator<T> end() const = 0;

    };
}

#endif