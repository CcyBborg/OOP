#include <iostream>
#include <cassert>
#include "Iterator.h"
#include "MutableIterator.h"
#include "Matrix.h"

void testMatrix() {
    using namespace containers;
    {
        Matrix<int> mtr1({
                                 {1, 2, 3},
                                 {4, 5, 6},
                                 {7, 8, 9}
                         });

        Matrix<int> mtr2(mtr1);
        assert(mtr2 == mtr1);

        Matrix<int> mtr3({
                                 {1, 1, 3},
                                 {4, 5, 6},
                                 {7, 8, 9}
                         });
        assert(mtr1 != mtr3);

        mtr3 = mtr2;
        assert(mtr1 == mtr3);

        mtr3 = {
                {1, 2, 3},
                {4, 5, 6}
        };
        assert(mtr3.getSize() == 6);

        assert(mtr3.getRows() == 2);
        assert(mtr3.getColumns() == 3);

        assert(mtr3.at(0, 0) == 1);
        assert(mtr3.at(1, 0) == 4);
        assert(mtr3.at(1, 2) == 6);

        assert(mtr3(0, 0) == 1);
        assert(mtr3(1, 0) == 4);
        assert(mtr3(1, 2) == 6);

        Matrix<int> mtr3Negative = -mtr3;
        assert(mtr3Negative.getSize() == 6);
        assert(mtr3Negative.getRows() == 2);
        assert(mtr3Negative.getColumns() == 3);

        assert(mtr3Negative(0, 0) == -1);
        assert(mtr3Negative(1, 0) == -4);
        assert(mtr3Negative(1, 2) == -6);
    }

    {
        Matrix<int> mtrSum1({
            {1, 2, 3},
            {4, 5, 6}
        });
        Matrix<int> mtrSum2({
            {10, 9, 8},
            {7, 6, 5}
        });
        Matrix<int> sum = mtrSum1 + mtrSum2;
        assert(sum.getSize() == 6);
        assert(sum.getRows() == 2);
        assert(sum.getColumns() == 3);
        assert(sum(0, 0) == 11);
        assert(sum(1, 0) == 11);
        assert(sum(1, 2) == 11);
    }

    {
        Matrix<int> mtr({
            {1, 2, 3},
            {4, 5, 6}
        });
        Matrix<int> res = mtr * 2;
        assert(res.getSize() == 6);
        assert(res.getRows() == 2);
        assert(res.getColumns() == 3);
        assert(res(0, 0) == 2);
        assert(res(0, 1) == 4);
        assert(res(1, 2) == 12);
    }

    {
        Matrix<int> mtr({
            {1, 2, 3},
            {4, 5, 6}
        });
        Matrix<int> res = 2 * mtr;
        assert(res.getSize() == 6);
        assert(res.getRows() == 2);
        assert(res.getColumns() == 3);
        assert(res(0, 0) == 2);
        assert(res(0, 1) == 4);
        assert(res(1, 2) == 12);
    }

    {
        Matrix<int> mtr1({
            {-2, 1},
            {5, 4}
        });
        Matrix<int> mtr2({
            {3},
            {-1}
        });

        Matrix<int> res = mtr1 * mtr2;

        assert(res.getSize() == 2);
        assert(res.getRows() == 2);
        assert(res.getColumns() == 1);

        assert(res(0, 0) == -7);
        assert(res(1, 0) == 11);
    }

    {
        Matrix<int> mtr({
            {1, 2},
            {3, 4},
            {5, 6}
        });
        Matrix<int> mtr2({
            {10, 9},
            {8, 7},
            {6, 5}
        });

        mtr += mtr2;

        assert(mtr.getSize() == 6);
        assert(mtr.getRows() == 3);
        assert(mtr.getColumns() == 2);

        assert(mtr(0, 0) == 11);
        assert(mtr(0, 1) == 11);
        assert(mtr(2, 1) == 11);
    }

    {
        Matrix<int> mtr({
            {1, 2, 3},
            {4, 5, 6}
        });

        Matrix<int> expected({
            {1, 4},
            {2, 5},
            {3, 6}
        });

        mtr.transposition();

        assert(mtr == expected);
    }

    {
        Matrix<int> mtr({
            {1, 2, 3},
            {4, 5, 6}
        });

        assert(mtr[0][0] == 1);
        assert(mtr[1][0] == 4);
        assert(mtr[1][2] == 6);
    }

    {
        Matrix<int> mtr({
            {1, 2, 3},
            {4, 5, 6}
        });

        Iterator<int> it = mtr.begin();
        for (int i = 1; i <= 6; i++, it++) {
            assert(*it == i);
        }
    }

    // Test MatrixInvalidException on std::initializer_list constructor
    {
        bool exceptionThrown = false;
        try {
            Matrix<int> mtr2({{1, 2, 3}, {4, 5}});
        } catch (const containers::exceptions::MatrixInvalidSizeException& ex) {
            exceptionThrown = true;
        }

        assert(exceptionThrown);
    }

    // Test MatrixIndexOutOfBoundsException on at
    {
        bool exceptionThrown = false;
        Matrix<int> mtr({
            {1, 2, 3},
            {4, 5, 6}
        });
        try {
            mtr.at(4, 5);
        } catch (const containers::exceptions::MatrixIndexOutOfBoundsException& ex) {
            exceptionThrown = true;
        }

        assert(exceptionThrown);
    }

    // Test MatrixIndexOutOfBoundsException on operator()
    {
        bool exceptionThrown = false;
        Matrix<int> mtr({
                                {1, 2, 3},
                                {4, 5, 6}
                        });
        try {
            mtr(4, 5);
        } catch (const containers::exceptions::MatrixIndexOutOfBoundsException& ex) {
            exceptionThrown = true;
        }

        assert(exceptionThrown);
    }

    // Test MatrixIndexOutOfBoundsException on operator[][]
    {
        bool exceptionThrown = false;
        Matrix<int> mtr({
                                {1, 2, 3},
                                {4, 5, 6}
                        });
        try {
            mtr[0][5];
        } catch (const containers::exceptions::MatrixIndexOutOfBoundsException& ex) {
            exceptionThrown = true;
        }

        assert(exceptionThrown);
    }

    // Test division of matrix on num (matrix / num)
    {
        Matrix<int> mtr({
                                {2, 5, 6},
                                {8, 2, 5}
                        });
        mtr /= 2;

        assert(mtr.getSize() == 6);
        assert(mtr.getRows() == 2);
        assert(mtr.getColumns() == 3);
        assert(mtr[0][0] == 1);
        assert(mtr[1][0] == 4);
        assert(mtr[1][2] == 2);
    }

    // Test getGaussDeterminanat
//    {
//        Matrix<int> mtr({{11, -3}, {-15, -2}});
//
//        assert(mtr.getGaussDeterminant() == -67);
//    }

}

int main() {
    testMatrix();

    std::cout << "OK!" << std::endl;
    return 0;
}