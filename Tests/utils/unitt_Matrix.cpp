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

    // Test 6: verify the data setter, used from Array class
    {
        uint32_t rows = 3, cols = 3;
        uint32_t size1 = rows * cols;
        Matrix<uint32_t, float> testMatrix(rows, cols);
        float* data = (float*)calloc(size1, sizeof(float));
        for (uint32_t i = 0; i < size1; ++i)
        {
            data[i] = static_cast<float>(i) * 3.0f; // Fill with some values
        }
        testMatrix.setData(size1, data);
        testMatrix.print();
        for (uint32_t i = 0; i < size1; ++i)
        {
            if (testMatrix[i] != data[i])
            {
                std::cout << "Data setter failed at index " << i << ". Expected: " << data[i] << ", got: " << testMatrix[i] << std::endl;
                exit(EXIT_FAILURE);
            }
        }
        std::cout << "Data setter works." << std::endl;
        free(data);
    }

    // Test 7: verify the addRow method
    {
        uint32_t rows = 3, cols = 3;
        Matrix<uint32_t, float> testMatrix(rows, cols);
        for (uint32_t i = 0; i < rows * cols; ++i)
        {
            testMatrix[i] = static_cast<float>(i) * 2.0f; // Fill with some values
        }
        testMatrix.print();
        printf("Adding a new row at the end...\n");
        uint32_t iRow = rows-1;
        float* newRowData = (float*)calloc(cols, sizeof(float));
        for (uint32_t j = 0; j < cols; ++j)
        {
            newRowData[j] = static_cast<float>(j) + 10.0f; // Fill with some values
        }
        testMatrix.addRow(iRow, newRowData);
        testMatrix.print();
        iRow = 1;
        printf("Adding a new row at index %d...\n", iRow);
        testMatrix.addRow(iRow, newRowData);
        testMatrix.print();
        if (testMatrix[5] != 12.0f || testMatrix[10] != 14.0f || testMatrix.rows() != 5)
        {
            std::cout << "Add row failed." << std::endl;
            std::cout << "Expected: 12.0f at index 5, 14.0f at index 10, rows = 5." << std::endl;
            std::cout << "Got: " << testMatrix[5] << " at index 5, " << testMatrix[10] << " at index 10, rows = " << testMatrix.rows() << std::endl;
            exit(EXIT_FAILURE);
        }
        std::cout << "Add row works." << std::endl;
        newRowData = nullptr;
    }

    // Test 8: verify the addCol method
    {
        uint32_t rows = 3, cols = 5;
        Matrix<uint32_t, float> testMatrix(rows, cols);
        for (uint32_t i = 0; i < rows * cols; ++i)
        {
            testMatrix[i] = static_cast<float>(i) * 2.0f; // Fill with some values
        }
        testMatrix.print();
        printf("Adding a new column at the end...\n");
        float *newColData = (float *)calloc(rows, sizeof(float));
        for (uint32_t j = 0; j < rows; ++j)
        {
            newColData[j] = static_cast<float>(j) + 100.0f; // Fill with some values
        }
        // Add column at the end
        uint32_t iCol = cols - 1;
        testMatrix.addColumn(iCol, newColData);
        testMatrix.print();
        // Add column at index 2
        iCol = 2;
        testMatrix.addColumn(iCol, newColData);
        testMatrix.print();
        if (testMatrix[2] != 100.0f || testMatrix[12] != 101.0f || testMatrix.cols() != 7)
        {
            std::cout << "Add column failed." << std::endl;
            std::cout << "Expected: 100.0f at index 2, 101.0f at index 12, cols = 7." << std::endl;
            std::cout << "Got: " << testMatrix[2] << " at index 2, " << testMatrix[12] << " at index 12, cols = " << testMatrix.cols() << std::endl;
            exit(EXIT_FAILURE);
        }
        std::cout << "Add column works." << std::endl;
        newColData = nullptr;
    }

    // Test 9: verify the getRow method
    {
        uint32_t rows = 4, cols = 3;
        Matrix<uint32_t, float> testMatrix(rows, cols);
        for (uint32_t i = 0; i < rows * cols; ++i)
        {
            testMatrix[i] = static_cast<float>(i) + 1.0f; // Fill with some values
        }
        testMatrix.print();
        uint32_t rowIndex = 2;
        Array<uint32_t, float> rowArray = testMatrix.getRow(rowIndex);
        rowArray.print();
        for (uint32_t j = 0; j < cols; ++j)
        {
            if (rowArray[j] != testMatrix(rowIndex, j))
            {
                std::cout << "Get row failed at index " << j << ". Expected: " << testMatrix(rowIndex, j) << ", got: " << rowArray[j] << std::endl;
                exit(EXIT_FAILURE);
            }
        }
        std::cout << "Get row works." << std::endl;
    }

    // Test 10: verify the getCol method
    {
        uint32_t rows = 4, cols = 3;
        Matrix<uint32_t, float> testMatrix(rows, cols);
        for (uint32_t i = 0; i < rows * cols; ++i)
        {
            testMatrix[i] = static_cast<float>(i) + 1.0f; // Fill with some values
        }
        testMatrix.print();
        uint32_t colIndex = 1;
        Array<uint32_t, float> colArray = testMatrix.getCol(colIndex);
        colArray.print();
        for (uint32_t j = 0; j < rows; ++j)
        {
            if (colArray[j] != testMatrix(j, colIndex))
            {
                std::cout << "Get column failed at index " << j << ". Expected: " << testMatrix(j, colIndex) << ", got: " << colArray[j] << std::endl;
                exit(EXIT_FAILURE);
            }
        }
        std::cout << "Get column works." << std::endl;
    }

    // Test n: verify the access operator
    {
        uint32_t rows = 3, cols = 3;
        Matrix<uint32_t, float> testMatrix(rows, cols);
        for (uint32_t i = 0; i < rows * cols; ++i)
        {
            testMatrix[i] = static_cast<float>(i) + 1.0f; // Fill with some values
        }
        testMatrix.print();
        for (uint32_t i = 0; i < rows; ++i)
        {
            for (uint32_t j = 0; j < cols; ++j)
            {
                if (testMatrix(i, j) != static_cast<float>(i * cols + j) + 1.0f)
                {
                    std::cout << "Access operator failed at (" << i << ", " << j << "). Expected: " << static_cast<float>(i * cols + j) + 1.0f << ", got: " << testMatrix(i, j) << std::endl;
                    exit(EXIT_FAILURE);
                }
            }
        }
        std::cout << "Access operator works." << std::endl;
    }

    // Test ?: verify the pointwise sum operator
    {
        uint32_t rows = 3, cols = 3;
        Matrix<uint32_t, float> testMatrix1(rows, cols);
        Matrix<uint32_t, float> testMatrix2(rows, cols);
        for (uint32_t i = 0; i < rows * cols; ++i)
        {
            testMatrix1[i] = static_cast<float>(i) + 1.0f; // Fill with some values
            testMatrix2[i] = static_cast<float>(i) + 2.0f; // Fill with some values
        }
        Matrix<uint32_t, float> sumMatrix = testMatrix1 + testMatrix2;
        sumMatrix.print();
        for (uint32_t i = 0; i < rows * cols; ++i)
        {
            if (sumMatrix[i] != (testMatrix1[i] + testMatrix2[i]))
            {
                std::cout << "Pointwise sum operator failed at index " << i << ". Expected: " << (testMatrix1[i] + testMatrix2[i]) << ", got: " << sumMatrix[i] << std::endl;
                exit(EXIT_FAILURE);
            }
        }
        std::cout << "Pointwise sum operator works." << std::endl;
    }

    // Test ?: verify the += operator
    {
        uint32_t rows = 3, cols = 3;
        Matrix<uint32_t, float> testMatrix1(rows, cols);
        Matrix<uint32_t, float> testMatrix2(rows, cols);
        for (uint32_t i = 0; i < rows * cols; ++i)
        {
            testMatrix1[i] = static_cast<float>(i) + 1.0f; // Fill with some values
            testMatrix2[i] = static_cast<float>(i) + 2.0f; // Fill with some values
        }
        testMatrix1 += testMatrix2;
        testMatrix1.print();
        for (uint32_t i = 0; i < rows * cols; ++i)
        {
            if (testMatrix1[i] != (static_cast<float>(i) + 1.0f + static_cast<float>(i) + 2.0f))
            {
                std::cout << "Pointwise accumulation operator failed at index " << i << ". Expected: " << (static_cast<float>(i) + 1.0f + static_cast<float>(i) + 2.0f) << ", got: " << testMatrix1[i] << std::endl;
                exit(EXIT_FAILURE);
            }
        }
        std::cout << "Pointwise accumulation operator works." << std::endl;
    }

    return 0;
}