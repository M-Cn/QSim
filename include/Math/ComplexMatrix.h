#ifndef COMPLEX_MATRIX_H
#define COMPLEX_MATRIX_H

#define MAX_SIZE 100

#include <stdlib.h>

typedef struct Complex Complex;

typedef struct ComplexMatrix
{
    size_t m_size;
    Complex** m_data;
} ComplexMatrix;

// Creates a sizexsize complex identity matrix. REMEMBER TO CALL ComplexMatrixFree AFTERWARDS!
ComplexMatrix CreateComplexMatrix(const size_t size);

// Destructor
void ComplexMatrixFree(ComplexMatrix* self);

// Set the element at idx
void ComplexMatrixSetElement(const ComplexMatrix* self, const size_t row, const size_t col, Complex value);

// Get the element at idx
Complex ComplexMatrixGetElement(const ComplexMatrix* self, const size_t row, const size_t col);

// Multiplies the matrix by a complex scalar
ComplexMatrix ComplexMatrixDot(const ComplexMatrix in, const Complex complex);

// Multiplies the matrix by another matrix
ComplexMatrix ComplexMatrixMultiply(const ComplexMatrix in1, const ComplexMatrix in2);

#endif