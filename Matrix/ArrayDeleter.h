#ifndef ARRAY_DELETER_H
#define ARRAY_DELETER_H

template <typename T>
struct ArrayDeleter {
    void operator()(T const *p) {
        delete [] p;
    }
};

#endif