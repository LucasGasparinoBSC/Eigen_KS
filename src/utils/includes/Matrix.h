// Extends the aray class for matrices

#ifndef MATRIX_H
#define MATRIX_H

#pragma once

#include <cstdint>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <ctime>
#include <iostream>
#include "Array.h"

template <typename ITYPE, typename RTYPE>
class Matrix : public Array<ITYPE, RTYPE>
{
    private:
    protected:
        ITYPE nRows;
        ITYPE nCols;
    public:
        // Constructors:
            // Empty constructor
            Matrix();
            // Parametrized constructor
            Matrix(ITYPE &nr, ITYPE &nc);
            // Copy constructor
            Matrix(const Matrix<ITYPE, RTYPE> &other);
        // Destructor
        ~Matrix();
        // Getters:
            // Get number of rows
            ITYPE rows() const { return nRows; }
            // Get number of columns
            ITYPE cols() const { return nCols; }
            // Retrieve a row as an Array object
            Array<ITYPE, RTYPE> getRow(ITYPE &rowIndex);
            // Retrieve a column as an Array object
            Array<ITYPE, RTYPE> getCol(ITYPE &colIndex);
            // Setters:
            // Overload of setSize receiving rows and columns
            void setSize(ITYPE &nr, ITYPE &nc);
        // Methods:
            // Redefine the printing method
            void print() const;
            //Add a new row
            void addRow(ITYPE &iRow, RTYPE *data);
            // Add a new column
            void addColumn(ITYPE &iCol, RTYPE *data);
            // Remove a row
            void removeRow(ITYPE &iRow);
            // Remove a column
            void removeColumn(ITYPE &iCol);
            // Transpose the matrix
            Matrix<ITYPE, RTYPE> transpose();
        // Compute methods:
            // Trace: returns the sum of the diagonal elements
            RTYPE trace();
            // Double inner product: given two matrices, returns a scalar
            RTYPE doubleInnerProduct(const Matrix<ITYPE, RTYPE> &other);
            // Outer product: given two Arrays, returns a new Matrix object
            Matrix<ITYPE, RTYPE> outerProduct(const Array<ITYPE, RTYPE> &vec1, const Array<ITYPE, RTYPE> &vec2);
            // Matrix-vector multiplication, returns a new Array object
            Array<ITYPE, RTYPE> MatrixVectorProduct(const Array<ITYPE, RTYPE> &vec);
            // Matrix-matrix multiplication, returns a new Matrix object
            Matrix<ITYPE, RTYPE> MatrixMatrixProduct(const Matrix<ITYPE, RTYPE> &other);
        // Norms
            // row-sum norm (pInf)
            RTYPE rowSumNorm();
            // column-sum norm (p1)
            RTYPE colSumNorm();
            // Spectral norm (p2)
            RTYPE spectralNorm();
            // Frobenius norm (pF)
            RTYPE frobeniusNorm();
            // max-norm (pMax)
            RTYPE maxNorm();
        // Operators:
            // Row,Col operator: allows accesing elements by row and column
            RTYPE &operator()(ITYPE row, ITYPE col) { return this->arrData[row * nCols + col]; }
            // Const Row,Col operator: allows accesing elements by row and column
            const RTYPE &operator()(ITYPE row, ITYPE col) const { return this->arrData[row * nCols + col]; }
            // Assignment operator
            Matrix<ITYPE, RTYPE> &operator=(const Matrix<ITYPE, RTYPE> &other);
            // Pointwise sum operator
            Matrix<ITYPE, RTYPE> operator+(const Matrix<ITYPE, RTYPE> &other);
            // Pointwise subtraction operator
            Matrix<ITYPE, RTYPE> operator-(const Matrix<ITYPE, RTYPE> &other);
            // Pointwise multiplication operator. NOTE: Matrix-Matrix operation defined as a method!
            Matrix<ITYPE, RTYPE> operator*(const Matrix<ITYPE, RTYPE> &other);
            // Pointwise accumulation operator
            Matrix<ITYPE, RTYPE> &operator+=(const Matrix<ITYPE, RTYPE> &other);
            // Pointwise reduction operator
            Matrix<ITYPE, RTYPE> &operator-=(const Matrix<ITYPE, RTYPE> &other);
            // Pointwise self-product operator
            Matrix<ITYPE, RTYPE> &operator*=(const Matrix<ITYPE, RTYPE> &other);
};

#endif //! MATRIX_H