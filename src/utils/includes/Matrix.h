// Extends the aray class for matrices

#ifndef MATRIX_H
#define MATRIX_H

#pragma once

#include <cstdint>
#include <cstdlib>
#include <cstdio>
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