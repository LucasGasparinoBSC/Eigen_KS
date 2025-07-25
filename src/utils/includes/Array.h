#ifndef ARRAY_H
#define ARRAY_H

#pragma once

#include <cstdint>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <ctime>
#include <iostream>

template <typename ITYPE, typename RTYPE>
class Array
{
    private:
    protected:
        int errorCode = 0; // Default error code == no error
        ITYPE arrSize;
        RTYPE* arrData;

        // Error handling method
        void handleError(int errorCode);
    public:
    // Constructors:
        // Empty constructor
        Array();
        // Parametrized constructor
        Array(ITYPE &n);
        // Copy constructor
        Array(const Array<ITYPE, RTYPE> &other);

    // Destructor
    ~Array();

    // Getters:
        // Get size
        ITYPE size() const { return arrSize; }
        // Get data pointer
        RTYPE* data() { return arrData; }

    // Setters:
        // Set size
        void setSize(ITYPE &n);
        // Set data pointer
        void setData(ITYPE &n, RTYPE *data);

    // Methods:
        // Resize
        void resize(ITYPE newSize);
        // Append
        void append(RTYPE value);
        // Insert
        void insert(ITYPE index, RTYPE value);
        // Remove
        void remove(ITYPE index);
        // print
        void print() const;

    // Compute methods:
        // Dot product
        RTYPE dotProduct(const Array<ITYPE, RTYPE> &other);

    // Norms:
        // maxNorm
        RTYPE maxNorm();
        // sumNorm
        RTYPE sumNorm();
        // Eucledean norm
        RTYPE euclideanNorm();

    // Operators:
        // Access operator
        RTYPE &operator[](ITYPE index);
        // Const access operator
        const RTYPE &operator[](ITYPE index) const;
        // Range operator
        Array<ITYPE, RTYPE> operator()(ITYPE start, ITYPE end);
        // Assignment operator
        Array<ITYPE, RTYPE> &operator=(const Array<ITYPE, RTYPE> &other);
        // Pointwise addition operator
        Array<ITYPE, RTYPE> operator+(const Array<ITYPE, RTYPE> &other);
        // Pointwise subtraction operator
        Array<ITYPE, RTYPE> operator-(const Array<ITYPE, RTYPE> &other);
        // Pointwise multiplication operator
        Array<ITYPE, RTYPE> operator*(const Array<ITYPE, RTYPE> &other);
        // Pointwise accumulation operator
        Array<ITYPE, RTYPE> &operator+=(const Array<ITYPE, RTYPE> &other);
        // Pointwise reduction operator
        Array<ITYPE, RTYPE> &operator-=(const Array<ITYPE, RTYPE> &other);
        // Pointwise self-product operator
        Array<ITYPE, RTYPE> &operator*=(const Array<ITYPE, RTYPE> &other);
};

#endif