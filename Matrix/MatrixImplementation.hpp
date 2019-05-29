#ifndef MATRIX_IMPLEMENTATION_H
#define MATRIX_IMPLEMENTATION_H

#include <typeinfo>
#include <ctime>
#include <algorithm>

#include "ArrayDeleter.h"
#include "Matrix.h"
#include "Exceptions.h"

using namespace containers;
using namespace containers::exceptions;

template <typename T>
Matrix<T>::Matrix(size_t rows, size_t columns) : Container(rows * columns), rows_(rows), columns_(columns) {
    try {
        matrixPtr_ = std::shared_ptr<T>(new T[size_](), ArrayDeleter<T>());
    } catch (std::bad_alloc) {
        time_t t = time(NULL);
        throw MemoryAllocationException(__FILE__, typeid(*this).name(), __LINE__ - 4, ctime(&t), "Allocation Error");
    }
}

template <typename T>
Matrix<T>::Matrix(const Matrix<T>& other) : Matrix(other.rows_, other.columns_) {
    for (size_t i = 0; i < other.getSize(); i++) {
        matrixPtr_.get()[i] = other.matrixPtr_.get()[i];
    }
}

template <typename T>
Matrix<T>::Matrix(Matrix<T> &&other) : Matrix(other.rows_, other.columns_) {
    rows_ = other.rows_;
    columns_ = other.columns_;
    size_ = rows_ * columns_;
    matrixPtr_ = other.matrixPtr_;
    other.matrixPtr_ = std::shared_ptr<T>();
    other.size_ = 0;
    other.rows_ = 0;
    other.columns_ = 0;
}

template <typename T>
Matrix<T>::Matrix(std::initializer_list<std::initializer_list<T>> list) :  Matrix(list.size(), list.begin()->size()) {
    auto iter_i = list.begin();
    for (size_t i = 0; iter_i != list.end(); ++i, ++iter_i) {
        if (columns_ != iter_i->size()) {
            time_t t = time(NULL);
            throw MatrixInvalidSizeException(__FILE__, typeid(*this).name(), __LINE__ - 4, ctime(&t), "Columns have different sizes in initializer list");
        }
        auto iter_j = iter_i->begin();
        for (size_t j = 0; iter_j != iter_i->end(); ++j, ++iter_j) {
            matrixPtr_.get()[columns_ * i + j] = *iter_j;
        }
    }

}

template <typename T>
Matrix<T>::~Matrix() {
    matrixPtr_.reset();
    size_ = rows_ = columns_ = 0;
}

template <typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& other) {
    if (this != &other) {
        reallocate(other.rows_, other.columns_);
        for (size_t i = 0; i < size_; i++) {
            matrixPtr_.get()[i] = other.matrixPtr_.get()[i];
        }
    }
    return *this;
}

template <typename T>
Matrix<T>& Matrix<T>::operator=(std::initializer_list<std::initializer_list<T>> list) {
    auto iter_i = list.begin();
    reallocate(list.size(), iter_i->size());
    for (size_t i = 0; iter_i != list.end(); ++i, ++iter_i) {
        if (columns_ != iter_i->size()) {
            time_t t = time(NULL);
            throw MatrixInvalidSizeException(__FILE__, typeid(*this).name(), __LINE__ - 4, ctime(&t), "Columns have different sizes in initializer list");
        }
        auto iter_j = iter_i->begin();
        for (size_t j = 0; iter_j != iter_i->end(); ++iter_j, ++j) {
            matrixPtr_.get()[i * columns_ + j] = *iter_j;
        }
    }
}

template <typename T>
Matrix<T>& Matrix<T>::operator=(Matrix<T>&& other) {
    std::swap(matrixPtr_, other.matrixPtr_);
    std::swap(size_, other.size_);
    std::swap(rows_, other.rows_);
    std::swap(columns_, other.columns_);
    return *this;
}

template <typename T>
bool Matrix<T>::operator==(const Matrix<T>& other) const noexcept {
    if (rows_ != other.rows_ || columns_ != other.columns_) {
        return false;
    }
    for (size_t i = 0; i < size_; i++) {
        if (matrixPtr_.get()[i] != other.matrixPtr_.get()[i]) {
            return false;
        }
    }

    return true;
}

template <typename T>
bool Matrix<T>::operator!=(const Matrix<T> &other) const noexcept {
    return !(*this == other);
}

template <typename T>
size_t Matrix<T>::getRows() const noexcept {
    return rows_;
}

template <typename T>
size_t Matrix<T>::getColumns() const noexcept {
    return columns_;
}

template <typename T>
bool Matrix<T>::isSquare() const noexcept {
    return rows_ == columns_;
}

template <typename T>
const T& Matrix<T>::at(size_t rowI, size_t columnI) const {
    if(isValidIndexes(rowI, columnI)) {
        return matrixPtr_.get()[rowI * columns_ + columnI];
    } else {
        time_t t = time(NULL);
        throw MatrixIndexOutOfBoundsException(__FILE__, typeid(*this).name(), __LINE__ - 4, ctime(&t), "Matrix index out of bounds");
    }
}

template <typename T>
T& Matrix<T>::at(size_t rowI, size_t columnI) {
    if(isValidIndexes(rowI, columnI)) {
        return matrixPtr_.get()[rowI * columns_ + columnI];
    } else {
        time_t t = time(NULL);
        throw MatrixIndexOutOfBoundsException(__FILE__, typeid(*this).name(), __LINE__ - 4, ctime(&t), "Matrix index out of bounds");
    }
}

template <typename T>
T& Matrix<T>::operator()(size_t rowI, size_t columnI) {
    return at(rowI, columnI);
}

template <typename T>
const T& Matrix<T>::operator()(size_t rowI, size_t columnI) const {
    return at(rowI, columnI);
}

template <typename T>
const Matrix<T>& Matrix<T>::operator+() const {
    return *this;
}

template <typename T>
Matrix<T> Matrix<T>::operator-() const {
    Matrix mtr(*this);
    for (size_t i = 0; i < mtr.size_; i++) {
        mtr.matrixPtr_.get()[i] = -mtr.matrixPtr_.get()[i];
    }
    return mtr;
}

template <typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T>& other) const {
    if (!equalSize(other)) {
        time_t t = time(NULL);
        throw MatrixInvalidSizeException(__FILE__, typeid(*this).name(), __LINE__ - 4, ctime(&t), "Matrix must have same rows and colums amount");
    }
    Matrix mtr(other);
    for (size_t i = 0; i < size_; i++) {
        mtr.matrixPtr_.get()[i] += matrixPtr_.get()[i];
    }
    return mtr;
}

template <typename T>
Matrix<T> Matrix<T>::operator-(const Matrix<T>& other) const {
    if (!equalSize(other)) {
        time_t t = time(NULL);
        throw MatrixInvalidSizeException(__FILE__, typeid(*this).name(), __LINE__ - 4, ctime(&t), "Matrix must have same rows and colums amount");
    }
    Matrix<T> mtr(other);
    for (size_t i = 0; i < size_; i++) {
        mtr.matrixPtr_.get()[i] -= matrixPtr_.get()[i];
    }
    return mtr;
}

template <typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T>& other) const {
    if (columns_ != other.rows_) {
        time_t t = time(NULL);
        throw MatrixInvalidSizeException(__FILE__, typeid(*this).name(), __LINE__ - 4, ctime(&t), "First matrix's size of columns must equal to second matrix'ssize of rows");
    }

    Matrix<T> res(rows_, other.columns_);

    for (size_t i = 0; i < rows_; i++) {
        for (size_t j = 0; j < other.columns_; j++) {

            T sum = 0;
            for (size_t k = 0; k < other.rows_; k++) {
                sum += other.matrixPtr_.get()[k * other.columns_ + j] * matrixPtr_.get()[i * columns_ + k];
            }

            res.matrixPtr_.get()[i * res.columns_ + j] = sum;
        }
    }

    return res;
}

template <typename T>
Matrix<T> Matrix<T>::operator*(const T& num) const {
    Matrix<T> mtr(*this);
    for (size_t i = 0; i < size_; i++) {
        mtr.matrixPtr_.get()[i] *= num;
    }
    return mtr;
}

template <typename T>
Matrix<T> Matrix<T>::operator/(const T& num) const {
    Matrix<T> mtr(*this);
    for (size_t i = 0; i < size_; i++) {
        mtr.matrixPtr_.get()[i] /= num;
    }
    return mtr;
}

template <typename T>
Matrix<T>& Matrix<T>::operator+=(const Matrix<T>& other) {
    return *this = *this + other;
}

template <typename T>
Matrix<T>& Matrix<T>::operator-=(const Matrix<T>& other) {
    return *this = *this - other;
}

template <typename T>
Matrix<T>& Matrix<T>::operator*=(const Matrix<T>& other) {
    return *this = *this * other;
}

template <typename T>
Matrix<T>& Matrix<T>::operator*=(const T& num) {
    return *this = *this * num;
}

template <typename T>
Matrix<T>& Matrix<T>::operator/=(const T& num) {
    return *this = *this / num;
}

// TODO: FIX IT
template <typename T>
T Matrix<T>::getGaussDeterminant() const {
    if (!isSquare()) {
        time_t t = time(NULL);
        throw MatrixInvalidSizeException(__FILE__, typeid(*this).name(), __LINE__ - 4, ctime(&t), "Matrix must be square to have gauss determinant");
    }

    const double EPS = 1E-9;
    Matrix<T> mtr(*this);
    T det = 1;
    for (size_t i = 0; i < rows_; ++i) {
        size_t k = i;
        for (size_t j = i + 1; j < rows_; ++j) {
            if (abs(mtr[j][i]) > abs(mtr[k][i])) {
                k = j;
            }
        }
        if (abs(mtr[k][i]) < EPS) {
            det = 0;
            break;
        }
        mtr.swapRows(i, k);
        if (i != k) {
            det = - det;
        }
        det *= mtr[i][i];
        for (size_t j = i + 1; j < rows_; ++j) {
            mtr[i][j] /= mtr[i][i];
        }
        for (size_t j = 0; j < rows_; ++j) {
            if (j != i && abs(mtr[j][i]) > EPS) {
                for (size_t k = i + 1; k < rows_; ++k) {
                    mtr.at(j, k) -= mtr.at(i, k) * mtr.at(j, i);
                }
            }
        }
    }

    return det;
}

template <typename T>
Matrix<T>& Matrix<T>::inverse() {

}

template <typename T>
Matrix<T>& Matrix<T>::transposition() {
    Matrix<T> tmp(columns_, rows_);
    for (size_t i = 0; i < rows_; i++) {
        for (size_t j = 0; j < columns_; j++) {
            tmp.matrixPtr_.get()[j * tmp.columns_ + i] = matrixPtr_.get()[i * columns_ + j];
        }
    }
    return *this = tmp;
}


template <typename T>
void Matrix<T>::setValue(size_t rowI, size_t colI, const T& value) {
    if (isValidIndexes(rowI, colI)) {
        matrixPtr_.get()[rowI * columns_ + colI] = value;
    } else {
        time_t t = time(NULL);
        throw MatrixIndexOutOfBoundsException(__FILE__, typeid(*this).name(), __LINE__ - 4, ctime(&t), "Matrix index out of bounds");
    }
}

template <typename T>
MutableIterator<T> Matrix<T>::begin() {
    return MutableIterator<T>(matrixPtr_, 0);
}

template <typename T>
MutableIterator<T> Matrix<T>::end() {
    return MutableIterator<T>(matrixPtr_, size_);
}

template <typename T>
Iterator<T> Matrix<T>::begin() const {
    return Iterator<T>(matrixPtr_, 0);
}

template <typename T>
Iterator<T> Matrix<T>::end() const {
    return Iterator<T>(matrixPtr_, size_);
}

template <typename T>
void Matrix<T>::reallocate(size_t rows, size_t cols) {
    rows_ = rows;
    columns_ = cols;
    size_ = rows_ * columns_;
    matrixPtr_.reset();
    matrixPtr_ = std::shared_ptr<T>(new T[size_]());
}

template <typename T>
bool Matrix<T>::isValidIndexes(size_t rowI, size_t columnI) const {
    return rowI < rows_ && columnI < columns_;
}

template <typename T>
bool Matrix<T>::equalSize(const Matrix<T> &other) const {
    return other.rows_ == rows_ && other.columns_ == columns_;
}

template <typename T>
void Matrix<T>::swapRows(size_t rowI, size_t rowJ) {
    for (size_t i = 0; i < columns_; i++) {
        std::swap(at(rowI, i), at(rowJ, i));
    }
}

template <typename T>
Matrix<T> operator*(const T& num, const Matrix<T>& mtr) {
    return mtr * num;
}


#endif