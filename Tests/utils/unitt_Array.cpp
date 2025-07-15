#include "Array.h"
#include <iostream>

int main()
{

    // Test 1: create an empty Array obj
    {
        Array<uint32_t, float> emptyArray1;
    }
    std::cout << "Empty array created successfully." << std::endl;

    // Test 2: create parametrized arrays with size 10
    {
        uint32_t size1 = 10;
        Array<uint32_t, float> paramArray(size1);
    }
    std::cout << "Parametrized array created successfully." << std::endl;

    // Test 3: veryfy copy constructor
    {
        uint32_t size2 = 5;
        Array<uint32_t, float> paramArray(size2);
        Array<uint32_t, float> copyArray(paramArray);
        std::cout << "Copy constructor works. Size of copy: " << copyArray.size() << std::endl;
    }

    // Test 4: verify getters
    {
        uint32_t size3 = 6;
        float* aux = (float*)calloc(size3, sizeof(float));
        Array<uint32_t, float> testArray(size3);
        for (uint32_t i = 0; i < size3; ++i)
        {
            testArray[i] = static_cast<float>(i) * 2.0f; // Fill with some values
        }
        if (testArray.size() == size3)
        {
            std::cout << "Size getter works. Size: " << testArray.size() << std::endl;
        }
        else
        {
            std::cout << "Size getter failed." << std::endl;
        }
        aux = testArray.data();
        for (uint32_t i = 0; i < size3; ++i)
        {
            if ( aux[i] != testArray[i] )
            {
                std::cout << "Data getter failed at index " << i << ". Expected: " << aux[i] << ", got: " << testArray[i] << std::endl;
                exit(EXIT_FAILURE);
            }
        }
        std::cout << "Data getter works." << std::endl;
        aux = nullptr;
    }

    // Test 5: verify setters
    {
        uint32_t size3 = 6;
        float *aux = (float *)calloc(size3, sizeof(float));
        Array<uint32_t, float> testArray;
        for (uint32_t i = 0; i < size3; ++i)
        {
            aux[i] = static_cast<float>(i) * 2.0f; // Fill with some values
        }
        testArray.setSize(size3);
        std::cout << "Set size works. Size: " << testArray.size() << std::endl;
        testArray.setData(size3, aux);
        for (uint32_t i = 0; i < size3; ++i)
        {
            if (testArray[i] != aux[i])
            {
                std::cout << "Data setter failed at index " << i << ". Expected: " << aux[i] << ", got: " << testArray[i] << std::endl;
                exit(EXIT_FAILURE);
            }
        }
        std::cout << "Data setter works." << std::endl;
        free(aux);
    }

    // Test 6: verify that resize works;
    {
        uint32_t size1 = 5;
        uint32_t size2 = 10;
        uint32_t size3 = 4;
        Array<uint32_t, float> testArray(size1);
        for (uint32_t i = 0; i < size1; ++i)
        {
            testArray[i] = static_cast<float>(i) + 1.0f; // Fill with some values
        }
        testArray.resize(size2);
        testArray.print();
        testArray.resize(size3);
        testArray.print();
        for (uint32_t i = 0; i < size3; ++i)
        {
            if (testArray[i] != static_cast<float>(i) + 1.0f)
            {
                std::cout << "Resize failed at index " << i << ". Expected: " << static_cast<float>(i) + 1.0f << ", got: " << testArray[i] << std::endl;
                exit(EXIT_FAILURE);
            }
        }
        std::cout << "Resize works." << std::endl;
    }

    // Test 7: verify that append works
    {
        uint32_t size1 = 5;
        float value = 6.0f;
        Array<uint32_t, float> testArray(size1);
        for (uint32_t i = 0; i < size1; ++i)
        {
            testArray[i] = static_cast<float>(i) + 1.0f; // Fill with some values
        }
        testArray.append(value);
        testArray.print();
        for (uint32_t i = 0; i < size1+1; ++i)
        {
            if (testArray[i] != static_cast<float>(i) + 1.0f)
            {
                std::cout << "Append failed at index " << i << ". Expected: " << static_cast<float>(i) + 1.0f << ", got: " << testArray[i] << std::endl;
                exit(EXIT_FAILURE);
            }
        }
        std::cout << "Append works." << std::endl;
    }

    // Test 8: verify that insert works
    {
        uint32_t size1 = 6;
        uint32_t idx = 3;
        float value = 10.0f;
        Array<uint32_t, float> testArray(size1);
        for (uint32_t i = 0; i < size1; ++i)
        {
            testArray[i] = static_cast<float>(i) + 1.0f; // Fill with some values
        }
        testArray.insert(idx, value);
        testArray.print();
        if ( testArray[idx] != value || testArray[size1] != 6.0f )
        {
            std::cout << "Insert failed." << std::endl;
            exit(EXIT_FAILURE);
        }
        std::cout << "Insert works." << std::endl;
    }

    // Test 8: verify that remove works
    {
        uint32_t size1 = 6;
        uint32_t idx = 3;
        Array<uint32_t, float> testArray(size1);
        for (uint32_t i = 0; i < size1; ++i)
        {
            testArray[i] = static_cast<float>(i) + 1.0f; // Fill with some values
        }
        testArray.remove(idx);
        testArray.print();
        if (testArray.size() != size1 - 1 || testArray[idx] != 5.0f)
        {
            std::cout << "Remove failed." << std::endl;
            exit(EXIT_FAILURE);
        }
        std::cout << "Remove works." << std::endl;
    }

    // Test 9: test range operator
    {
        uint32_t size1 = 10;
        uint32_t idxStart = 2;
        uint32_t idxEnd = 5;
        Array<uint32_t, float> testArray(size1);
        for (uint32_t i = 0; i < size1; ++i)
        {
            testArray[i] = static_cast<float>(i) + 1.0f; // Fill with some values
        }
        Array<uint32_t, float> slice = testArray(idxStart, idxEnd);
        slice.print();
        for (uint32_t i = 0; i < slice.size(); i++)
        {
            if (slice[i] != testArray[idxStart + i])
            {
                std::cout << "Range operator failed at index " << i << ". Expected: " << testArray[idxStart + i] << ", got: " << slice[i] << std::endl;
                exit(EXIT_FAILURE);
            }
        }
        std::cout << "Range operator works." << std::endl;
    }

    // Test 10: test assignment operator
    {
        uint32_t size1 = 5;
        Array<uint32_t, float> testArray(size1);
        for (uint32_t i = 0; i < size1; ++i)
        {
            testArray[i] = static_cast<float>(i) + 1.0f; // Fill with some values
        }
        Array<uint32_t, float> assignedArray = testArray;
        assignedArray.print();
        for (uint32_t i = 0; i < size1; ++i)
        {
            if (assignedArray[i] != testArray[i])
            {
                std::cout << "Assignment operator failed at index " << i << ". Expected: " << testArray[i] << ", got: " << assignedArray[i] << std::endl;
                exit(EXIT_FAILURE);
            }
        }
        std::cout << "Assignment operator works." << std::endl;
    }

    // Test 11: verify the addition operator
    {
        uint32_t size1 = 5;
        Array<uint32_t, float> testArray1(size1);
        Array<uint32_t, float> testArray2(size1);
        for (uint32_t i = 0; i < size1; ++i)
        {
            testArray1[i] = static_cast<float>(i) + 1.0f; // Fill with some values
            testArray2[i] = static_cast<float>(i) + 2.0f; // Fill with some values
        }
        Array<uint32_t, float> sumArray = testArray1 + testArray2;
        sumArray.print();
        for (uint32_t i = 0; i < size1; ++i)
        {
            if (sumArray[i] != (testArray1[i] + testArray2[i]))
            {
                std::cout << "Addition operator failed at index " << i << ". Expected: " << (testArray1[i] + testArray2[i]) << ", got: " << sumArray[i] << std::endl;
                exit(EXIT_FAILURE);
            }
        }
        std::cout << "Addition operator works." << std::endl;
    }

    // Test 12: verify the accumulation operator
    {
        uint32_t size1 = 5;
        Array<uint32_t, float> testArray1(size1);
        Array<uint32_t, float> testArray2(size1);
        for (uint32_t i = 0; i < size1; ++i)
        {
            testArray1[i] = static_cast<float>(i) + 1.0f; // Fill with some values
            testArray2[i] = static_cast<float>(i) + 2.0f; // Fill with some values
        }
        testArray1 += testArray2;
        testArray1.print();
        for (uint32_t i = 0; i < size1; ++i)
        {
            if (testArray1[i] != (static_cast<float>(i) + 1.0f + testArray2[i]))
            {
                std::cout << "Accumulation operator failed at index " << i << ". Expected: " << (static_cast<float>(i) + 1.0f + testArray2[i]) << ", got: " << testArray1[i] << std::endl;
                exit(EXIT_FAILURE);
            }
        }
        std::cout << "Accumulation operator works." << std::endl;
    }

    // Test 13: verify the dot prodcut
    {
        uint32_t size1 = 10000;
        uint64_t expectedResult = 0;
        Array<uint32_t, float> testArray1(size1);
        Array<uint32_t, float> testArray2(size1);
        for (uint32_t i = 0; i < size1; ++i)
        {
            testArray1[i] = static_cast<float>(1);
            testArray2[i] = static_cast<float>(i+1);
            expectedResult += (1 * (i + 1));
        }
        std::cout << "Expected dot product result: " << expectedResult << std::endl;
        float dotResult = testArray1.dotProduct(testArray2);
        std::cout << "Dot product result: " << dotResult << std::endl;
        if (dotResult != static_cast<float>(expectedResult))
        {
            std::cout << "Dot product failed. Expected: " << expectedResult << ", got: " << dotResult << std::endl;
            exit(EXIT_FAILURE);
        }
        std::cout << "Dot product works." << std::endl;
    }

    // Test 14: verify the max norm
    {
        uint32_t size1 = 10;
        Array<uint32_t, float> testArray(size1);
        for (uint32_t i = 0; i < size1; ++i)
        {
            testArray[i] = static_cast<float>(i) + 1.0f; // Fill with some values
        }
        float maxNormValue = testArray.maxNorm();
        std::cout << "Max norm value: " << maxNormValue << std::endl;
        if (maxNormValue != 10.0f)
        {
            std::cout << "Max norm failed. Expected: 10.0, got: " << maxNormValue << std::endl;
            exit(EXIT_FAILURE);
        }
        std::cout << "Max norm works." << std::endl;
    }

    // Test 15: verify the sum norm
    {
        uint32_t size1 = 10;
        Array<uint32_t, float> testArray(size1);
        for (uint32_t i = 0; i < size1; ++i)
        {
            testArray[i] = static_cast<float>(i) + 1.0f; // Fill with some values
        }
        float sumNormValue = testArray.sumNorm();
        std::cout << "Sum norm value: " << sumNormValue << std::endl;
        if (sumNormValue != 55.0f) // Sum of first 10 natural numbers
        {
            std::cout << "Sum norm failed. Expected: 55.0, got: " << sumNormValue << std::endl;
            exit(EXIT_FAILURE);
        }
        std::cout << "Sum norm works." << std::endl;
    }

    // Test 16: verify the euclidean norm
    {
        uint32_t size1 = 10;
        Array<uint32_t, float> testArray(size1);
        for (uint32_t i = 0; i < size1; ++i)
        {
            testArray[i] = static_cast<float>(i) + 1.0f; // Fill with some values
        }
        float euclideanNormValue = testArray.euclideanNorm();
        std::cout << "Euclidean norm value: " << euclideanNormValue << std::endl;
        if (euclideanNormValue != std::sqrt(385.0f)) // sqrt(1^2 + 2^2 + ... + 10^2)
        {
            std::cout << "Euclidean norm failed. Expected: " << std::sqrt(385.0f) << ", got: " << euclideanNormValue << std::endl;
            exit(EXIT_FAILURE);
        }
        std::cout << "Euclidean norm works." << std::endl;
    }

    return 0;
}