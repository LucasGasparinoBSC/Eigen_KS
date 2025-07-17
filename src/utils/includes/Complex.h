// DEfines a Complex number in a class

#ifndef COMPLEX_H
#define COMPLEX_H

#pragma once

#include <iostream>
#include <cmath>
#include <cstdint>

template <typename ITYPE, typename RTYPE>
class Complex
{
    private:
        // Cartesian data
        RTYPE real_part;
        RTYPE imag_part;
    public:
        // Constructors:
            // Default constructor
            Complex();
            // Parametrized constructor
            Complex(RTYPE& real, RTYPE& imag);
            // Copy constructor
            Complex(const Complex<ITYPE, RTYPE> &other);

        // Destructor
        ~Complex();

        // Getters:
            // get the real part
            RTYPE real() const { return real_part; }
            // get the imaginary part
            RTYPE imag() const { return imag_part; }

        // Setter
        void setReal(RTYPE& real) { real_part = real; }
        void setImag(RTYPE& imag) { imag_part = imag; }
        void setComplex(RTYPE& real, RTYPE& imag) { real_part = real; imag_part = imag; }

        // Methods:
            // Module
            RTYPE module();
            // Argument
            RTYPE argument();
            // Conjugate
            void conjugate();
            // Invert
            Complex<ITYPE, RTYPE> invert();
            // Power
            Complex<ITYPE, RTYPE> power(uint32_t& exponent);

        // Operators
            // Assignment operator
            Complex<ITYPE, RTYPE> &operator=(const Complex<ITYPE, RTYPE> &other);
            // Addition operator
            Complex<ITYPE, RTYPE> operator+(const Complex<ITYPE, RTYPE> &other);
            // Subtraction operator
            Complex<ITYPE, RTYPE> operator-(const Complex<ITYPE, RTYPE> &other);
            // Multiplication operator
            Complex<ITYPE, RTYPE> operator*(const Complex<ITYPE, RTYPE> &other);
            // Division operator
            Complex<ITYPE, RTYPE> operator/(Complex<ITYPE, RTYPE> &other);
};

#endif //! COMPLEX_H