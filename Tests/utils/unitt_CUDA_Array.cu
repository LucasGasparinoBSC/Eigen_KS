#include "CUDA_Array.cuh"

int main()
{
    // Test the empty constructor
    {
        CUDA_Array<uint32_t, float> emptyArray;
    }

    // Test the parametrized constructor
    {
        uint32_t size = 10;
        CUDA_Array<uint32_t, float> paramArray(size);
    }

    // Test that the size() method from Array can be called
    {
        uint32_t size = 20;
        CUDA_Array<uint32_t, float> testArray(size);
        if (testArray.size() != size) {
            std::cerr << "Size mismatch: expected " << size << ", got " << testArray.size() << std::endl;
            exit(EXIT_FAILURE);
        }
    }

    // Test the data getter
    {
        uint32_t size = 5;
        CUDA_Array<uint32_t, float> testArray(size);
        float* data = testArray.data();
        // Check if the data pointer is not null
        if (data == nullptr) {
            std::cerr << "Data pointer is null!" << std::endl;
            exit(EXIT_FAILURE);
        }
    }

    // Test that setSize works correctly
    {
        uint32_t size = 15;
        CUDA_Array<uint32_t, float> testArray;
        testArray.setSize(size);
        if (testArray.size() != size) {
            std::cerr << "Size mismatch after setSize: expected " << size << ", got " << testArray.size() << std::endl;
            exit(EXIT_FAILURE);
        }
    }

    // Test that setData works correctly
    {
        uint32_t size = 10;
        CUDA_Array<uint32_t, float> testArray(size);
        float* hostData = (float*)malloc(size * sizeof(float));
        for (uint32_t i = 0; i < size; ++i) {
            hostData[i] = static_cast<float>(i);
        }
        testArray.setData(size, hostData);
    }
    return 0;
}