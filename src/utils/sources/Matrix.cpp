#include "Matrix.h"

// Constructors:

// Empty constructor
template <typename ITYPE, typename RTYPE>
Matrix<ITYPE, RTYPE>::Matrix() : nRows(0), nCols(0)
{
    this->arrSize = 0;
    this->arrData = nullptr;
}

// Parametrized constructor
template <typename ITYPE, typename RTYPE>
Matrix<ITYPE, RTYPE>::Matrix(ITYPE &nr, ITYPE &nc) : nRows(nr), nCols(nc)
{
    // Set the array size
    Array<ITYPE, RTYPE>::arrSize = nRows * nCols;

    // Check if array has valid size
    if (Array<ITYPE,RTYPE>::arrSize <= 0)
    {
        this->errorCode = 1; // Set error code for invalid array size
        this->handleError(this->errorCode);
    }

    this->arrData = (RTYPE*)calloc(this->arrSize, sizeof(RTYPE));
}

// Copy constructor
template <typename ITYPE, typename RTYPE>
Matrix<ITYPE, RTYPE>::Matrix(const Matrix<ITYPE, RTYPE> &other) : Array<ITYPE, RTYPE>(other)
{
    this->nRows = other.nRows;
    this->nCols = other.nCols;
    this->arrSize = other.arrSize;

    // Allocate memory for arrData
    this->arrData = (RTYPE*)calloc(this->arrSize, sizeof(RTYPE));

    for (ITYPE i = 0; i < this->arrSize; i++)
    {
        this->arrData[i] = other.arrData[i];
    }
}

// Destructor
template <typename ITYPE, typename RTYPE>
Matrix<ITYPE, RTYPE>::~Matrix()
{
    // Deallocate arrData if it was allocated
    if (this->arrData != nullptr)
    {
        free(this->arrData);
        this->arrData = nullptr; // Set to nullptr to avoid dangling pointer
    }
}

// Setters:

// Overload of setSize receiving rows and columns
template <typename ITYPE, typename RTYPE>
void Matrix<ITYPE, RTYPE>::setSize(ITYPE &nr, ITYPE &nc)
{
    // Check that this is an empty array
    if (this->arrSize != 0)
    {
        this->errorCode = 5; // Set error code for non-empty array
        this->handleError(this->errorCode);
    }

    this->arrSize = nr * nc;

    // Check if array has valid size
    if (this->arrSize <= 0)
    {
        this->errorCode = 1; // Set error code for invalid array size
        this->handleError(this->errorCode);
    }

    // Allocate array with calloc to ensure memory is initialized to zero
    this->arrData = (RTYPE *)calloc(this->arrSize, sizeof(RTYPE));

    // Check if memory allocation was successful
    if (this->arrData == nullptr)
    {
        this->errorCode = 4; // Set error code for memory allocation failure
        this->handleError(this->errorCode);
    }
}

// Define specific implementations
template class Matrix<uint32_t, float>;
template class Matrix<uint64_t, float>;
template class Matrix<uint32_t, double>;
template class Matrix<uint64_t, double>;