#ifndef MUTABLE_ITERABLE_H
#define MUTABLE_ITERABLE_H

#include "Iterable.h"

using namespace containers::iterators;

namespace containers {
    template <typename T>
    class MutableIterable : public Iterable<T> {
    public:
        virtual MutableIterator<T> begin() = 0;
        virtual MutableIterator<T> end() = 0;
    };
}

#endif