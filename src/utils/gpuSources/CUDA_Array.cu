#include "CUDA_Array.cuh"

// Constructors:

// Empty constructor
template <typename ITYPE, typename RTYPE>
CUDA_Array<ITYPE, RTYPE>::CUDA_Array()
{
    Array<ITYPE, RTYPE>::arrSize = 0;
    d_data = nullptr;
}

// Parametrized constructor, extends the base class constructor
template <typename ITYPE, typename RTYPE>
CUDA_Array<ITYPE, RTYPE>::CUDA_Array(ITYPE& n)
{
    Array<ITYPE, RTYPE>::arrSize = n;
    // Allocate device memory for the data
    CUDA_CHECK(cudaMalloc((void**)&d_data, n * sizeof(RTYPE)));
}

// Destructor
template <typename ITYPE, typename RTYPE>
CUDA_Array<ITYPE, RTYPE>::~CUDA_Array()
{
    // Free device memory
    if (d_data != nullptr) {
        CUDA_CHECK(cudaFree(d_data));
        d_data = nullptr;
    }
}

// Getters:

// New implementation of data getter to account for device memory
template <typename ITYPE, typename RTYPE>
RTYPE* CUDA_Array<ITYPE, RTYPE>::data()
{
    // Since is called from Host code, need to copy data from device to host
    RTYPE* h_data = (RTYPE*)calloc(Array<ITYPE, RTYPE>::arrSize, sizeof(RTYPE));
    CUDA_CHECK(cudaMemcpy(h_data, d_data, Array<ITYPE, RTYPE>::arrSize * sizeof(RTYPE), cudaMemcpyDeviceToHost));
    return h_data; // Return host pointer
}

// Setters:

// New setSize method to allocate device memory
template <typename ITYPE, typename RTYPE>
void CUDA_Array<ITYPE, RTYPE>::setSize(ITYPE& n)
{
    // Check that the array is empty before allocating new memory
    if (this->arrSize != 0) {
        this->errorCode = 5;
        this->handleError(this->errorCode);
    }

    // Sert the new size
    if (n <= 0)
    {
        this->errorCode = 1;
        this->handleError(this->errorCode);
    }
    this->arrSize = n;

    // Allocate device memory for the data
    CUDA_CHECK(cudaMalloc((void**)&d_data, n * sizeof(RTYPE)));
}

// Set data now copies from host to device
template <typename ITYPE, typename RTYPE>
void CUDA_Array<ITYPE, RTYPE>::setData(ITYPE& n, RTYPE* data)
{
    // Check that the array is not empty
    if (this->arrSize == 0) {
        this->errorCode = 6;
        this->handleError(this->errorCode);
    }
    if (n != this->arrSize) {
        this->errorCode = 2;
        this->handleError(this->errorCode);
    }

    // Set the data with host2device copy
    CUDA_CHECK(cudaMemcpy(d_data, data, n * sizeof(RTYPE), cudaMemcpyHostToDevice));
}

// Define specific implementations
template class CUDA_Array<uint32_t, float>;
template class CUDA_Array<uint64_t, float>;
template class CUDA_Array<uint32_t, double>;
template class CUDA_Array<uint64_t, double>;