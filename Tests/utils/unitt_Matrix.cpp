#include "Matrix.h"
#include <iostream>

int main()
{

    // Test 1: create an empty Matrix obj
    {
        Matrix<uint32_t, float> emptyMatrix1;
        std::cout << "Empty array created successfully." << std::endl;
    }

    // Test 2: create parametrized matrices with size 10x5
    {
        uint32_t rows = 10, cols = 5;
        Matrix<uint32_t, float> paramMatrix(rows, cols);
        std::cout << "Parametrized matrix created successfully." << std::endl;
    }

    // Test 3: verify copy constructor
    {
        uint32_t rows = 5, cols = 3;
        Matrix<uint32_t, float> paramMatrix(rows, cols);
        Matrix<uint32_t, float> copyMatrix(paramMatrix);
        std::cout << "Copy constructor works. Size of copy: " << copyMatrix.rows() << "x" << copyMatrix.cols() << std::endl;
    }

    // Test 4: verify getters
    {
        uint32_t rows = 6, cols = 4;
        float* aux = (float*)calloc(rows * cols, sizeof(float));
        Matrix<uint32_t, float> testMatrix(rows, cols);
        for (uint32_t i = 0; i < rows * cols; ++i)
        {
            testMatrix[i] = static_cast<float>(i) * 2.0f; // Fill with some values
        }
        if (testMatrix.rows() == rows && testMatrix.cols() == cols)
        {
            std::cout << "Getters work. Rows: " << testMatrix.rows() << ", Columns: " << testMatrix.cols() << std::endl;
        }
        else
        {
            std::cout << "Getters failed." << std::endl;
            exit(EXIT_FAILURE);
        }
        if(testMatrix.size() == rows * cols)
        {
            std::cout << "Size getter works. Size: " << testMatrix.size() << std::endl;
        }
        else
        {
            std::cout << "Size getter failed." << std::endl;
            exit(EXIT_FAILURE);
        }
        aux = testMatrix.data();
        for (uint32_t i = 0; i < rows * cols; ++i)
        {
            if (aux[i] != testMatrix[i])
            {
                std::cout << "Data getter failed at index " << i << ". Expected: " << aux[i] << ", got: " << testMatrix[i] << std::endl;
                exit(EXIT_FAILURE);
            }
        }
        std::cout << "Data getter works." << std::endl;
    }

    // Test 5: verify the size setter
    {
        uint32_t rows = 6, cols = 4;
        uint32_t size1 = rows * cols;
        Matrix<uint32_t, float> testMatrix; // Base version of setSize
        testMatrix.setSize(rows, cols);
        if (testMatrix.size() == size1)
        {
            std::cout << "Set size works. Size: " << testMatrix.size() << std::endl;
        }
        else
        {
            std::cout << "Set size failed." << std::endl;
            exit(EXIT_FAILURE);
        }
    }

    return 0;
}