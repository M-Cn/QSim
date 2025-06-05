#ifndef COMPLEX_MATRIX_H
#define COMPLEX_MATRIX_H

#include <stdlib.h>

typedef struct Complex Complex;

typedef struct ComplexMatrix
{
    size_t m_size;
    Complex** m_data;
} ComplexMatrix;

/// @brief Creates a complex square identity matrix of the specified size. Remember to free memory by calling ComplexMatrixFree when done using it.
/// @param size The size of the matrix.
/// @return The identity matrix.
ComplexMatrix CreateComplexMatrix(const size_t size);

/// @brief Frees memory allocated by CreateComplexMatrix.
/// @param self The matrix object to free.
void ComplexMatrixFree(ComplexMatrix* self);

/// @brief Sets the complex number at the specified row and column.
/// @param self The matrix object of which to set the element.
/// @param row The row index.
/// @param col The column index.
/// @param value The target value.
void ComplexMatrixSetElement(const ComplexMatrix* self, const size_t row, const size_t col, Complex value);

/// @brief Returns the complex number at the specified row and column.
/// @param self The matrix object of which to return the element from.
/// @param row The row index.
/// @param col The column index.
/// @return The complex number at the specified position.
Complex ComplexMatrixGetElement(const ComplexMatrix* self, const size_t row, const size_t col);

/// @brief Performs the scalar product between the input matrix and the input complex.
/// @param in The input matrix.
/// @param complex The input complex.
/// @return The operation's result.
ComplexMatrix ComplexMatrixDot(const ComplexMatrix in, const Complex complex);

/// @brief Performs the matrix multiplication between the two input matrices.
/// @param in1 The first matrix.
/// @param in2 The second matrix.
/// @return The operation's result.
ComplexMatrix ComplexMatrixMultiply(const ComplexMatrix in1, const ComplexMatrix in2);


/// @brief Prints the input matrix to screen.
/// @param in The input matrix.
void ComplexMatrixPrint(const ComplexMatrix in);

#endif