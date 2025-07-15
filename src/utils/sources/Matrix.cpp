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

// Methods:

// Print method for matrix
template <typename ITYPE, typename RTYPE>
void Matrix<ITYPE, RTYPE>::print() const
{
    std::cout << "Matrix size: " << this->arrSize << std::endl;
    std::cout << "Matrix dimensions: " << nRows << " x " << nCols << std::endl;
    std::cout << "Matrix contents: " << std::endl;
    for (ITYPE i = 0; i < nRows; i++)
    {
        for (ITYPE j = 0; j < nCols; j++)
        {
            std::cout << this->arrData[i * nCols + j] << " ";
        }
        std::cout << std::endl;
    }
}

// Add a new row
template <typename ITYPE, typename RTYPE>
void Matrix<ITYPE, RTYPE>::addRow(ITYPE &iRow, RTYPE *data)
{
    // Check for out-of-bounds access
    // NOTE: iRow is 0-indexed, so it should be between 0 and nRows-1
    if (iRow < 0 || iRow > nRows-1)
    {
        this->errorCode = 3; // Set error code for out-of-bounds access
        this->handleError(this->errorCode);
    }

    // Resize the array
    nRows++;
    ITYPE newSize = nRows * nCols;
    this->resize(newSize);

    // Adjust the matrix:
    // If the index to add the new row is at the end of the original matrix, no shifting is needed
    if (iRow == nRows - 2) // NOTE: indexing from 0 to nRows-1, but nRows++
    {
        // Advance iRow to new row position
        iRow++;
        for (ITYPE j = 0; j < nCols; ++j)
        {
            this->arrData[iRow * nCols + j] = data[j];
        }
    }
    // Otherwise, we need to shift the rows below the new row down
    else
    {
        // Shift rows down
        // NOTE: remember that nRows++ has already been done
        for (ITYPE i = nRows - 1; i > iRow; --i)
        {
            for (ITYPE j = 0; j < nCols; ++j)
            {
                this->arrData[i * nCols + j] = this->arrData[(i - 1) * nCols + j];
            }
        }
        // Set the new row data
        for (ITYPE j = 0; j < nCols; ++j)
        {
            this->arrData[iRow * nCols + j] = data[j];
        }
    }
}

// Add a new column
template <typename ITYPE, typename RTYPE>
void Matrix<ITYPE, RTYPE>::addColumn(ITYPE &iCol, RTYPE *data)
{
    // Check for out-of-bounds access
    // NOTE: iCol is 0-indexed, so it should be between 0 and nCols-1
    if (iCol < 0 || iCol > nCols - 1)
    {
        this->errorCode = 3; // Set error code for out-of-bounds access
        this->handleError(this->errorCode);
    }

    // Create a new array to restructure the matrix with the new column
    ITYPE newSize = nRows * (nCols + 1);
    RTYPE *newData = (RTYPE *)calloc(newSize, sizeof(RTYPE));

    for (ITYPE i = 0; i < nRows; ++i)
    {
        for (ITYPE j = 0; j < nCols; j++)
        {
            // Entries before iCol get copied to the same column position
            if (j < iCol)
            {
                newData[i * (nCols + 1) + j] = this->arrData[i * nCols + j];
            }
            // Entries after iCol get shifted to the right by 1
            else if (j >= iCol)
            {
                newData[i * (nCols + 1) + (j+1)] = this->arrData[i * nCols + j];
            }
        }
        // With the data reordered, add the new column data
        newData[i * (nCols + 1) + iCol] = data[i];
    }

    nCols++;
    this->resize(newSize);
    this->arrData = newData;
}

// Retrieve a row as an Array object
template <typename ITYPE, typename RTYPE>
Array<ITYPE, RTYPE> Matrix<ITYPE, RTYPE>::getRow(ITYPE &rowIndex)
{
    // Check for out-of-bounds access
    if (rowIndex < 0 || rowIndex >= nRows)
    {
        this->errorCode = 3; // Set error code for out-of-bounds access
        this->handleError(this->errorCode);
    }

    // Create a new Array object for the row
    Array<ITYPE, RTYPE> rowArray(nCols);
    for (ITYPE j = 0; j < nCols; ++j)
    {
        rowArray[j] = this->arrData[rowIndex * nCols + j];
    }

    return rowArray;
}

// Retrieve a column as an Array object
template <typename ITYPE, typename RTYPE>
Array<ITYPE, RTYPE> Matrix<ITYPE, RTYPE>::getCol(ITYPE &colIndex)
{
    // Check for out-of-bounds access
    if (colIndex < 0 || colIndex >= nCols)
    {
        this->errorCode = 3; // Set error code for out-of-bounds access
        this->handleError(this->errorCode);
    }

    // Create a new Array object for the column
    Array<ITYPE, RTYPE> colArray(nRows);
    for (ITYPE i = 0; i < nRows; ++i)
    {
        colArray[i] = this->arrData[i * nCols + colIndex];
    }

    return colArray;
}

// Assignment operator
template <typename ITYPE, typename RTYPE>
Matrix<ITYPE, RTYPE> &Matrix<ITYPE, RTYPE>::operator=(const Matrix<ITYPE, RTYPE> &other)
{

    // Guard self-assignment
    if (this == &other) return *this;

    // If destination matrix is empty, allocate memory
    if (this->arrData == nullptr)
    {
        this->nRows = other.nRows;
        this->nCols = other.nCols;
        this->arrSize = other.arrSize;
        this->arrData = (RTYPE*)calloc(this->arrSize, sizeof(RTYPE));
    }

    // Copy the data from the other matrix
    for (ITYPE i = 0; i < this->nRows; ++i)
    {
        for (ITYPE j = 0; j < this->nCols; ++j)
        {
            this->arrData[i * this->nCols + j] = other.arrData[i * other.nCols + j];
        }
    }
    return *this;
}

// Pointwise sum operator
template <typename ITYPE, typename RTYPE>
Matrix<ITYPE, RTYPE> Matrix<ITYPE, RTYPE>::operator+(const Matrix<ITYPE, RTYPE> &other)
{
    // Check for size compatibility
    if (this->nRows != other.nRows || this->nCols != other.nCols)
    {
        this->errorCode = 2; // Set error code for size mismatch
        this->handleError(this->errorCode);
    }

    // Create a new Matrix object for the result
    Matrix<ITYPE, RTYPE> result(this->nRows, this->nCols);
    for (ITYPE i = 0; i < this->nRows; ++i)
    {
        for (ITYPE j = 0; j < this->nCols; ++j)
        {
            result(i, j) = this->arrData[i * this->nCols + j] + other.arrData[i * other.nCols + j];
        }
    }
    return result;
}

// Pointwise subtraction operator
template <typename ITYPE, typename RTYPE>
Matrix<ITYPE, RTYPE> Matrix<ITYPE, RTYPE>::operator-(const Matrix<ITYPE, RTYPE> &other)
{
    // Check for size compatibility
    if (this->nRows != other.nRows || this->nCols != other.nCols)
    {
        this->errorCode = 2; // Set error code for size mismatch
        this->handleError(this->errorCode);
    }

    // Create a new Matrix object for the result
    Matrix<ITYPE, RTYPE> result(this->nRows, this->nCols);
    for (ITYPE i = 0; i < this->nRows; ++i)
    {
        for (ITYPE j = 0; j < this->nCols; ++j)
        {
            result(i, j) = this->arrData[i * this->nCols + j] - other.arrData[i * other.nCols + j];
        }
    }
    return result;
}

// Pointwise multiplication operator
template <typename ITYPE, typename RTYPE>
Matrix<ITYPE, RTYPE> Matrix<ITYPE, RTYPE>::operator*(const Matrix<ITYPE, RTYPE> &other)
{
    // Check for size compatibility
    if (this->nRows != other.nRows || this->nCols != other.nCols)
    {
        this->errorCode = 2; // Set error code for size mismatch
        this->handleError(this->errorCode);
    }

    // Create a new Matrix object for the result
    Matrix<ITYPE, RTYPE> result(this->nRows, this->nCols);
    for (ITYPE i = 0; i < this->nRows; ++i)
    {
        for (ITYPE j = 0; j < this->nCols; ++j)
        {
            result(i, j) = this->arrData[i * this->nCols + j] * other.arrData[i * other.nCols + j];
        }
    }
    return result;
}

// Pointwise accumulation operator
template <typename ITYPE, typename RTYPE>
Matrix<ITYPE, RTYPE> &Matrix<ITYPE, RTYPE>::operator+=(const Matrix<ITYPE, RTYPE> &other)
{
    // Check for size compatibility
    if (this->nRows != other.nRows || this->nCols != other.nCols)
    {
        this->errorCode = 2; // Set error code for size mismatch
        this->handleError(this->errorCode);
    }

    // Perform pointwise accumulation
    for (ITYPE i = 0; i < this->nRows; ++i)
    {
        for (ITYPE j = 0; j < this->nCols; ++j)
        {
            this->arrData[i * this->nCols + j] += other.arrData[i * other.nCols + j];
        }
    }
    return *this;
}

// Pointwise reduction operator
template <typename ITYPE, typename RTYPE>
Matrix<ITYPE, RTYPE> &Matrix<ITYPE, RTYPE>::operator-=(const Matrix<ITYPE, RTYPE> &other)
{
    // Check for size compatibility
    if (this->nRows != other.nRows || this->nCols != other.nCols)
    {
        this->errorCode = 2; // Set error code for size mismatch
        this->handleError(this->errorCode);
    }

    // Perform pointwise accumulation
    for (ITYPE i = 0; i < this->nRows; ++i)
    {
        for (ITYPE j = 0; j < this->nCols; ++j)
        {
            this->arrData[i * this->nCols + j] -= other.arrData[i * other.nCols + j];
        }
    }
    return *this;
}

// Pointwise self-product operator
template <typename ITYPE, typename RTYPE>
Matrix<ITYPE, RTYPE> &Matrix<ITYPE, RTYPE>::operator*=(const Matrix<ITYPE, RTYPE> &other)
{
    // Check for size compatibility
    if (this->nRows != other.nRows || this->nCols != other.nCols)
    {
        this->errorCode = 2; // Set error code for size mismatch
        this->handleError(this->errorCode);
    }

    // Perform pointwise accumulation
    for (ITYPE i = 0; i < this->nRows; ++i)
    {
        for (ITYPE j = 0; j < this->nCols; ++j)
        {
            this->arrData[i * this->nCols + j] *= other.arrData[i * other.nCols + j];
        }
    }
    return *this;
}

// Define specific implementations
template class Matrix<uint32_t, float>;
template class Matrix<uint64_t, float>;
template class Matrix<uint32_t, double>;
template class Matrix<uint64_t, double>;