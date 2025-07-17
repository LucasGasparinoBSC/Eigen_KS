#include "Complex.h"

int main()
{
    // Test creating an empty complex number
    {
        Complex<uint32_t, float> c1;
    }

    // Test creating a parametrized complex number
    {
        float real = 3.0f;
        float imag = 4.0f;
        Complex<uint32_t, float> c2(real, imag);
    }

    // Test the copy constructor
    {
        float real = 5.0f;
        float imag = 6.0f;
        Complex<uint32_t, float> c3(real, imag);
        Complex<uint32_t, float> c4(c3);
    }

    // test the getters
    {
        float real = 7.0f;
        float imag = 8.0f;
        Complex<uint32_t, float> c5(real, imag);
        if (c5.real() != real || c5.imag() != imag)
        {
            std::cerr << "Error in getters" << std::endl;
            exit(EXIT_FAILURE);
        }
    }

    // Test the setters
    {
        float real = 9.0f;
        float imag = 10.0f;
        Complex<uint32_t, float> c6;
        c6.setReal(real);
        c6.setImag(imag);
        if (c6.real() != real || c6.imag() != imag)
        {
            std::cerr << "Error in setters" << std::endl;
            exit(EXIT_FAILURE);
        }

        Complex<uint32_t, float> c7;
        c7.setComplex(real, imag);
        if (c7.real() != real || c7.imag() != imag)
        {
            std::cerr << "Error in setComplex" << std::endl;
            exit(EXIT_FAILURE);
        }
    }

    // Test the methods
    {
        float real = 11.0f;
        float imag = 12.0f;
        Complex<uint32_t, float> c8(real, imag);
        if (c8.module() != std::sqrt(real * real + imag * imag))
        {
            std::cerr << "Error in module calculation" << std::endl;
            exit(EXIT_FAILURE);
        }

        if (c8.argument() != std::atan2(imag, real))
        {
            std::cerr << "Error in argument calculation" << std::endl;
            exit(EXIT_FAILURE);
        }

        c8.conjugate();
        if (c8.imag() != -imag)
        {
            std::cerr << "Error in conjugate calculation" << std::endl;
            exit(EXIT_FAILURE);
        }
        c8.conjugate(); // revert conjugate

        float tmpR = c8.real();
        float tmpI = c8.imag();
        float mod = c8.module();
        float expectedR = tmpR / (mod * mod);
        float expectedI = -tmpI / (mod * mod);
        Complex<uint32_t, float> c9 = c8.invert();
        if (c9.real() != expectedR || c9.imag() != expectedI)
        {
            std::cerr << "Error in invert calculation" << std::endl;
            exit(EXIT_FAILURE);
        }

        uint32_t exponent = 2;
        Complex<uint32_t, float> c10 = c8.power(exponent);
        float expectedPowerR = std::pow(tmpR, exponent) - std::pow(tmpI, exponent);
        float expectedPowerI = 2 * tmpR * tmpI;
        if (c10.real() != expectedPowerR || c10.imag() != expectedPowerI)
        {
            std::cerr << "Error in power calculation" << std::endl;
            exit(EXIT_FAILURE);
        }
    }

    // Test the operators
    {
        float real = 13.0f;
        float imag = 14.0f;
        Complex<uint32_t, float> c11(real, imag);
        Complex<uint32_t, float> c12 = c11;
        if (c12.real() != real || c12.imag() != imag)
        {
            std::cerr << "Error in assignment operator" << std::endl;
            exit(EXIT_FAILURE);
        }

        Complex<uint32_t, float> c13 = c11 + c12;
        if (c13.real() != 2 * real || c13.imag() != 2 * imag)
        {
            std::cerr << "Error in addition operator" << std::endl;
            exit(EXIT_FAILURE);
        }

        Complex<uint32_t, float> c14 = c11/ c12;
    }
}