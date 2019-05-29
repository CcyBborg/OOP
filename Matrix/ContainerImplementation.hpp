#ifndef CONTAINER_IMPLEMENTATION_H
#define CONTAINER_IMPLEMENTATION_H

#include "Container.h"

using namespace containers;

Container::Container(size_t size) : size_(size) {}

Container::~Container() {
    size_ = 0;
}

bool Container::isEmpty() const noexcept {
    return size_ == 0;
}
size_t Container::getSize() const noexcept {
    return size_;
}

#endif