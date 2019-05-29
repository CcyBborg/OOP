#ifndef CONTAINER_H
#define CONTAINER_H

#include <cstddef>

namespace containers {
    class Container {
    public:
        explicit Container(size_t size = 0);

        virtual ~Container() = 0;

        bool isEmpty() const noexcept;
        size_t getSize() const noexcept;

    protected:
        size_t size_;
    };
}

#include "ContainerImplementation.hpp"

#endif
