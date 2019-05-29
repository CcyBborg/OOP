#ifndef ITERATOR_H
#define ITERATOR_H

#include <memory>

namespace containers::iterators {
    template<typename T>
    class Iterator {
    public:
        Iterator(std::shared_ptr<T> sharedPtr, size_t index);
        Iterator(const Iterator<T>& other);

        virtual ~Iterator();

        bool operator==(const Iterator<T>& other) const;
        bool operator!=(const Iterator<T>& other) const;

        virtual Iterator<T>& operator++();
        virtual Iterator<T> operator++(int);
        virtual Iterator<T>& operator--();
        virtual Iterator<T> operator--(int);

        const T& operator*() const;
        const T* operator->() const;

    protected:
        std::shared_ptr<T> sharedPtr_;
        size_t index_;
    };
}

#include "IteratorImplementation.hpp"

#endif