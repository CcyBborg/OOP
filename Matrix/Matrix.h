#ifndef MATRIX_H
#define MATRIX_H

#include <initializer_list>
#include <memory>
#include "Container.h"
#include "MutableIterable.h"

namespace containers {
    template<typename T>
    class Matrix final : public Container, public MutableIterable<T> {
    public:
        Matrix(size_t rows, size_t columns);
        explicit Matrix(const Matrix<T>& other);
        Matrix(Matrix<T>&& other);
        Matrix(std::initializer_list<std::initializer_list<T>> list);

        ~Matrix();

        Matrix<T>& operator=(const Matrix<T>& other);
        Matrix<T>& operator=(Matrix<T>&& other);
        Matrix<T>& operator=(std::initializer_list<std::initializer_list<T>> list);

        bool operator==(const Matrix<T>& other) const noexcept;
        bool operator!=(const Matrix<T>& other) const noexcept;

        size_t getRows() const noexcept;
        size_t getColumns() const noexcept;

        bool isSquare() const noexcept;

        const T& at(size_t rowI, size_t columnI) const;
        T& at(size_t rowI, size_t columnI);

        T& operator()(size_t rowI, size_t columnI);
        const T& operator()(size_t rowI, size_t columnI) const;

        const Matrix<T>& operator+() const;
        Matrix<T> operator-() const;

        Matrix<T> operator+(const Matrix<T>& other) const;
        Matrix<T> operator-(const Matrix<T>& other) const;
        Matrix<T> operator*(const Matrix<T>& other) const;
        Matrix<T> operator*(const T& num) const;
        Matrix<T> operator/(const T& num) const;

        Matrix<T>& operator+=(const Matrix<T>& other);
        Matrix<T>& operator-=(const Matrix<T>& other);
        Matrix<T>& operator*=(const Matrix<T>& other);
        Matrix<T>& operator*=(const T& num);
        Matrix<T>& operator/=(const T& num);

        Matrix<T>& inverse();
        Matrix<T>& transposition();
        T getGaussDeterminant() const;

        void setValue(size_t rowI, size_t colI, const T& value);

        class Row {
        public:
            Row(Matrix<T>& matrix, size_t row) : matrix_(matrix), row_(row) {}

            T& operator[](size_t colI) {
                return matrix_(row_, colI);
            }

            const T& operator[](size_t colI) const {
                return matrix_(row_, colI);
            }
        private:
            Matrix<T>& matrix_;
            size_t row_;
        };

        Row operator[](size_t rowI){
            return Row(*this, rowI);
        }

        const Row operator[](size_t rowI) const {
            return Row(*this, rowI);
        }

        MutableIterator<T> begin() override;
        MutableIterator<T> end() override;
        Iterator<T> begin() const override;
        Iterator<T> end() const override;

    private:
        bool isValidIndexes(size_t rowI, size_t columnI) const;
        void reallocate(size_t rows, size_t cols);
        bool equalSize(const Matrix<T>& other) const;
        void swapRows(size_t rowI, size_t rowJ);
        size_t rows_;
        size_t columns_;
        std::shared_ptr<T> matrixPtr_;
    };

}


#include "MatrixImplementation.hpp"

#endif