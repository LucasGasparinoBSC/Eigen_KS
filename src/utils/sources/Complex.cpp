#include "Complex.h"

// Default constructor
template <typename ITYPE, typename RTYPE>
Complex<ITYPE, RTYPE>::Complex() : real_part(0), imag_part(0) {}

// Parametrized constructor
template <typename ITYPE, typename RTYPE>
Complex<ITYPE, RTYPE>::Complex(RTYPE& real, RTYPE& imag) : real_part(real), imag_part(imag) {}

// Copy constructor
template <typename ITYPE, typename RTYPE>
Complex<ITYPE, RTYPE>::Complex(const Complex<ITYPE, RTYPE> &other)
    : real_part(other.real_part), imag_part(other.imag_part) {}

// Destructor
template <typename ITYPE, typename RTYPE>
Complex<ITYPE, RTYPE>::~Complex() {}

// Methods:

// Module
template <typename ITYPE, typename RTYPE>
RTYPE Complex<ITYPE, RTYPE>::module()
{
    return std::sqrt(real_part*real_part + imag_part*imag_part);
}

// Argument (in radians)
template <typename ITYPE, typename RTYPE>
RTYPE Complex<ITYPE, RTYPE>::argument()
{
    // alpha = arctangent(imag_part / real_part)
    return std::atan2(imag_part, real_part);
}

// Conjugate
template <typename ITYPE, typename RTYPE>
void Complex<ITYPE, RTYPE>::conjugate()
{
    imag_part = -imag_part;
}

// Invert
template <typename ITYPE, typename RTYPE>
Complex<ITYPE, RTYPE> Complex<ITYPE, RTYPE>::invert()
{
    RTYPE denom = module();
    denom = denom * denom;

    RTYPE real = real_part / denom;
    RTYPE imag = -imag_part / denom;
    return Complex<ITYPE, RTYPE>(real, imag);
}

// Power
template <typename ITYPE, typename RTYPE>
Complex<ITYPE, RTYPE> Complex<ITYPE, RTYPE>::power(uint32_t& exponent)
{
    if (exponent == 1)
    {
        return *this; // Return the same complex number
    }
    if (exponent == 0)
    {
        RTYPE real = static_cast<RTYPE>(1);
        RTYPE imag = static_cast<RTYPE>(0);
        return Complex<ITYPE, RTYPE>(real, imag);
    }
    Complex<ITYPE, RTYPE> result = *this;
    for (ITYPE i = 1; i < exponent; i++)
    {
        result = result * (*this);
    }
    return result;
}

// operators:

// Assignment operator
template <typename ITYPE, typename RTYPE>
Complex<ITYPE, RTYPE> &Complex<ITYPE, RTYPE>::operator=(const Complex<ITYPE, RTYPE> &other)
{
    if (this != &other) // Check for self-assignment
    {
        real_part = other.real_part;
        imag_part = other.imag_part;
    }
    return *this;
}

// Addition operator
template <typename ITYPE, typename RTYPE>
Complex<ITYPE, RTYPE> Complex<ITYPE, RTYPE>::operator+(const Complex<ITYPE, RTYPE> &other)
{
    RTYPE real = real_part + other.real_part;
    RTYPE imag = imag_part + other.imag_part;
    return Complex<ITYPE, RTYPE>(real, imag);
}

// Subtraction operator
template <typename ITYPE, typename RTYPE>
Complex<ITYPE, RTYPE> Complex<ITYPE, RTYPE>::operator-(const Complex<ITYPE, RTYPE> &other)
{
    RTYPE real = real_part - other.real_part;
    RTYPE imag = imag_part - other.imag_part;
    return Complex<ITYPE, RTYPE>(real, imag);
}

// Multiplication operator
// NOTE: this is a "by-parts" multiplication: (a+bi)*(c+di) = (ac-bd) + (ad+bc)i
template <typename ITYPE, typename RTYPE>
Complex<ITYPE, RTYPE> Complex<ITYPE, RTYPE>::operator*(const Complex<ITYPE, RTYPE> &other)
{
    RTYPE real = (real_part * other.real_part) - (imag_part * other.imag_part);
    RTYPE imag = (real_part * other.imag_part) + (imag_part * other.real_part);
    return Complex<ITYPE, RTYPE>(real, imag);
}

// Division operator
// NOTE: z1 / z2 = (z1 * conj(z2)) / (|z2|^2)
template <typename ITYPE, typename RTYPE>
Complex<ITYPE, RTYPE> Complex<ITYPE, RTYPE>::operator/(Complex<ITYPE, RTYPE> &other)
{
    Complex<ITYPE, RTYPE> conjOther = other.invert();
    return (*this * conjOther);
}

// Define specific implementations
template class Complex<uint32_t, float>;
template class Complex<uint64_t, float>;
template class Complex<uint32_t, double>;
template class Complex<uint64_t, double>;