#include "Array.h"

// Error handling method
template <typename ITYPE, typename RTYPE>
void Array<ITYPE, RTYPE>::handleError(int errorCode)
{
    switch (errorCode)
    {
        case 1:
            printf("--! SEVERE: Invalid array size. Aborting...\n");
            exit(EXIT_FAILURE);
        case 2:
            printf("--! SEVERE: Array size mismatch. Aborting...\n");
            exit(EXIT_FAILURE);
        case 3:
            printf("--! SEVERE: Out-of-bounds access. Aborting...\n");
            exit(EXIT_FAILURE);
        case 4:
            printf("--! SEVERE: Memory allocation failure. Aborting...\n");
            exit(EXIT_FAILURE);
        case 5:
            printf("--! SEVERE: Cannot set size of non-empty array. Aborting...\n");
            exit(EXIT_FAILURE);
        case 6:
            printf("--| SEVERE: Cannot set data for an empty array. Aborting...\n");
        default:
            break;
    }
}

// Empty constructor
template <typename ITYPE, typename RTYPE>
Array<ITYPE,RTYPE>::Array() : arrSize(0), arrData(nullptr) {}

// Parametrized constructor
template <typename ITYPE, typename RTYPE>
Array<ITYPE,RTYPE>::Array(ITYPE &n) : arrSize(n)
{
    // Check if array has valid size
    if ( arrSize <= 0 )
    {
        errorCode = 1; // Set error code for invalid array size
        handleError(errorCode);
    }

    // Allocate array with calloc to ensure memory is initialized to zero
    arrData = (RTYPE*)calloc(arrSize, sizeof(RTYPE));

    // Check if memory allocation was successful
    if (arrData == nullptr)
    {
        errorCode = 4; // Set error code for memory allocation failure
        handleError(errorCode);
    }
}

// Copy constructor
template <typename ITYPE, typename RTYPE>
Array<ITYPE,RTYPE>::Array(const Array<ITYPE, RTYPE> &other) : arrSize(other.arrSize)
{
    // Allocate memory for arrData
    arrData = (RTYPE*)calloc(arrSize, sizeof(RTYPE));

    // No error handling needed here, as we assume the other array is valid
    for (ITYPE i = 0; i < arrSize; ++i)
    {
        arrData[i] = other.arrData[i];
    }
}

// Destructor
template <typename ITYPE, typename RTYPE>
Array<ITYPE,RTYPE>::~Array()
{
    // Deallocate arrData if it was allocated
    if (arrData != nullptr)
    {
        free(arrData);
        arrData = nullptr; // Set to nullptr to avoid dangling pointer
    }
}

// Setters:

// Set size: sets the size of the array and allocates data
// NOTE: requires an empty Array object to be created first, as it does not allocate memory.
template <typename ITYPE, typename RTYPE>
void Array<ITYPE, RTYPE>::setSize(ITYPE &n)
{
    // Check that this is an empty array
    if ( arrSize != 0 )
    {
        errorCode = 5; // Set error code for non-empty array
        handleError(errorCode);
    }

    arrSize = n;
    // Check if array has valid size
    if (arrSize <= 0)
    {
        errorCode = 1; // Set error code for invalid array size
        handleError(errorCode);
    }

    // Allocate array with calloc to ensure memory is initialized to zero
    arrData = (RTYPE *)calloc(arrSize, sizeof(RTYPE));

    // Check if memory allocation was successful
    if (arrData == nullptr)
    {
        errorCode = 4; // Set error code for memory allocation failure
        handleError(errorCode);
    }
}

// Set data: given a pointer, setes the data pointer to its entries
// NOTE: requires a non-empty array
template <typename ITYPE, typename RTYPE>
void Array<ITYPE, RTYPE>::setData(ITYPE &n, RTYPE *data)
{
    // Check that the array is not empty, and that the size matches
    if (arrSize == 0)
    {
        errorCode = 6; // Set error code for empty array
        handleError(errorCode);
    }
    if (arrSize != n)
    {
        errorCode = 2; // Set error code for size mismatch
        handleError(errorCode);
    }

    // Set the data
    for (ITYPE i = 0; i < arrSize; ++i)
    {
        arrData[i] = data[i];
    }
}

// Methods:

// Resize: changes the size of the array
template <typename ITYPE, typename RTYPE>
void Array<ITYPE, RTYPE>::resize(ITYPE newSize)
{
    // Check if new size is valid
    if (newSize <= 0)
    {
        errorCode = 1; // Set error code for invalid array size
        handleError(errorCode);
    }

    // Use realloc to resize the array
    RTYPE* newData = (RTYPE*)realloc(arrData, newSize * sizeof(RTYPE));
    if (newData == nullptr)
    {
        errorCode = 4; // Set error code for memory allocation failure
        handleError(errorCode);
    }
    arrData = newData;

    // Initialize new elements to zero if the array is expanded
    if (newSize > arrSize)
    {        for (ITYPE i = arrSize; i < newSize; ++i)
        {
            arrData[i] = 0.0;
        }
    }

    // Update the size
    arrSize = newSize;
}

// Append: inserts a value at the end of the array
template <typename ITYPE, typename RTYPE>
void Array<ITYPE, RTYPE>::append(RTYPE value)
{
    // Resize the array
    ITYPE newSize = arrSize + 1;
    resize(newSize);

    // Append the value at the end
    arrData[arrSize - 1] = value;
}

// Insert: inserts a value at a specific index
template <typename ITYPE, typename RTYPE>
void Array<ITYPE, RTYPE>::insert(ITYPE index, RTYPE value)
{
    // Check if index is within bounds
    if (index < 0 || index > arrSize)
    {
        errorCode = 3; // Set error code for out-of-bounds access
        handleError(errorCode);
    }

    // Resize the array
    ITYPE newSize = arrSize + 1;
    resize(newSize);

    // Shift elements to the right
    for (ITYPE i = arrSize - 1; i > index; --i)
    {
        arrData[i] = arrData[i - 1];
    }

    // Insert the new value
    arrData[index] = value;
}

// Remove: removes an element at a specific index
template <typename ITYPE, typename RTYPE>
void Array<ITYPE, RTYPE>::remove(ITYPE index)
{
    // Check if index is within bounds
    if (index < 0 || index > arrSize)
    {
        errorCode = 3; // Set error code for out-of-bounds access
        handleError(errorCode);
    }

    // Shift elements to the left
    for (ITYPE i = index; i < arrSize - 1; ++i)
    {
        arrData[i] = arrData[i + 1];
    }

    // Resize the array
    ITYPE newSize = arrSize - 1;
    resize(newSize);
}

// Print: prints the array elements
template <typename ITYPE, typename RTYPE>
void Array<ITYPE, RTYPE>::print() const
{
    std::cout << "Array size: " << arrSize << std::endl;
    std::cout << "Array contents: " << arrSize << std::endl;
    for (ITYPE i = 0; i < arrSize; ++i)
    {
        std::cout << "  arrData[" << i << "] = " << arrData[i] << std::endl;
    }
    std::cout << "End of array." << std::endl;
}

// Operators:
// NOTE: for now, no error handling is done in operators, as we assume the arrays are valid and of the same size where needed.
//TODO: Implement error handling in operators if necessary.

// Access operator
template <typename ITYPE, typename RTYPE>
RTYPE &Array<ITYPE, RTYPE>::operator[](ITYPE index)
{
    return arrData[index];
}

// Const access operator
template <typename ITYPE, typename RTYPE>
const RTYPE &Array<ITYPE, RTYPE>::operator[](ITYPE index) const
{
    return arrData[index];
}

// Range operator
template <typename ITYPE, typename RTYPE>
Array<ITYPE, RTYPE> Array<ITYPE, RTYPE>::operator()(ITYPE start, ITYPE end)
{
    // Check if start and end are within bounds
    if (start < 0 || end >= arrSize || start > end)
    {
        errorCode = 3; // Set error code for out-of-bounds access
        handleError(errorCode);
    }

    // Compute slice size
    ITYPE sliceSize = end - start + 1;

    // Create a new Array object for the slice
    Array<ITYPE, RTYPE> slice(sliceSize);
    for (ITYPE i = 0; i < sliceSize; ++i)
    {
        slice.arrData[i] = arrData[start + i];
    }
    return slice;
}

// Assignment operator
template <typename ITYPE, typename RTYPE>
Array<ITYPE, RTYPE> &Array<ITYPE, RTYPE>::operator=(const Array<ITYPE, RTYPE> &other)
{
    // Guard self-assignment
    if (this == &other) return *this;

    // If destination array is empty, allocate memory
    if (arrData == nullptr)
    {
        arrSize = other.arrSize;
        arrData = (RTYPE*)calloc(arrSize, sizeof(RTYPE));
    }

    for ( ITYPE i = 0; i < arrSize; ++i)
    {
        arrData[i] = other.arrData[i];
    }
    return *this;
}

// Define specific implementations
template class Array<uint32_t, float>;
template class Array<uint64_t, float>;
template class Array<uint32_t, double>;
template class Array<uint64_t, double>;