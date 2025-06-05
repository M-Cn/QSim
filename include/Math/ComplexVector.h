#ifndef COMPLEX_VECTOR_H
#define COMPLEX_VECTOR_H

#include <stdlib.h>

typedef struct Complex Complex;
typedef struct ComplexMatrix ComplexMatrix;

typedef struct ComplexVector
{
    size_t m_size;
    Complex* m_data;
} ComplexVector;

// Creates a complex vector and initializes to (0 + 0i). REMEMBER TO CALL ComplexVectorFree AFTERWARDS!
ComplexVector CreateComplexVector(const size_t size);

// Destructor
void ComplexVectorFree(ComplexVector* self);

// Set the element at idx
void ComplexVectorSetElement(const ComplexVector* self, const size_t idx, const Complex value);

// Get the element at idx
Complex ComplexVectorGetElement(const ComplexVector* self, const size_t idx);

// Adds two complex vectors
ComplexVector ComplexVectorAdd(const ComplexVector in1, const ComplexVector in2);

// Subtracts two complex vectors
ComplexVector ComplexVectorSubtract(const ComplexVector in1, const ComplexVector in2);

// Scalarly multiplies a complex vector by a complex scalar
ComplexVector ComplexVectorScalarMultiply(const ComplexVector in, const Complex scalar);

// Calculates the inner product of two complex vectors
Complex ComplexVectorDotProduct(const ComplexVector in1, const ComplexVector in2);

// Calculates the magnitude of the input complex vector
double ComplexVectorMagnitude(const ComplexVector in);

// Transforms the input complex vector by the input complex matrix
ComplexVector ComplexVectorTransform(ComplexVector in, ComplexMatrix transform);

// Print the complex vector
void ComplexVectorPrint(const ComplexVector in);

#endif