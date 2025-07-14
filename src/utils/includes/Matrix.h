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
        // Setters:
            // Overload of setSize receiving rows and columns
            void setSize(ITYPE &nr, ITYPE &nc);
};

#endif //! MATRIX_H