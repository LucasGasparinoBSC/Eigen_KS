// Inherits from Array to form a CUDA array
#ifndef CUDA_ARRAY_CUH
#define CUDA_ARRAY_CUH

#pragma once

#include "Array.h"
#include "cudaUtils.cuh"
#include <cuda.h>
#include <cuda_runtime.h>
#include <nvtx3/nvToolsExt.h>

template <typename ITYPE, typename RTYPE>
class CUDA_Array : public Array<ITYPE, RTYPE>
{
    private:
    protected:
        // Device pointer for data storage
        RTYPE* d_data;
    public:
        // Constructors:
            // Empty constructor
            CUDA_Array();
            // Parametrized constructor, extends the base class constructor
            CUDA_Array(ITYPE& n);
        // Destructor
            ~CUDA_Array();
        // Getters:
            // New implementation of data getter to account for device memory
            RTYPE* data();
        // Setters:
            // New setSize method to allocate device memory
            void setSize(ITYPE& n);
            // Set data now copies from host to device
            void setData(ITYPE& n, RTYPE* data);
};

#endif //! CUDA_ARRAY_CUH