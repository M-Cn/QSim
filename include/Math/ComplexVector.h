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


/// @brief Creates a zero complex vector of the specified size. Remember to free the memory by calling ComplexVectorFree when done using it.
/// @param size The desired size (dimension).
/// @return The created vector.
ComplexVector CreateComplexVector(const size_t size);

/// @brief Frees memory allocated by CreateComplexVector.
/// @param self The complex vector object to free.
void ComplexVectorFree(ComplexVector* self);

/// @brief Sets the value of the specified complex coordinate in the input vector.
/// @param self The input vector.
/// @param idx The index of the coordinate to set.
/// @param value The new coordinate's value.
void ComplexVectorSetElement(const ComplexVector* self, const size_t idx, const Complex value);

/// @brief Returns the value of the specified complex coordinate in the input vector.
/// @param self The input vector.
/// @param idx The index of the coordinate to get.
/// @return The coordinate's value.
Complex ComplexVectorGetElement(const ComplexVector* self, const size_t idx);

/// @brief Adds two complex vectors together.
/// @param in1 The first input vector.
/// @param in2 The second input vector.
/// @return The operation's result.
ComplexVector ComplexVectorAdd(const ComplexVector in1, const ComplexVector in2);

/// @brief Subtracts two complex vectors.
/// @param in1 The first input vector.
/// @param in2 The second input vector.
/// @return The operation's result.
ComplexVector ComplexVectorSubtract(const ComplexVector in1, const ComplexVector in2);

/// @brief Computes the scalar product between a vector and a complex number.
/// @param in The input vector.
/// @param scalar The input scalar.
/// @return The operation's result.
ComplexVector ComplexVectorScalarMultiply(const ComplexVector in, const Complex scalar);

/// @brief Computes the inner (cross) product between two vectors.
/// @param in1 The first input vector.
/// @param in2 The second input vector.
/// @return The operation's result.
Complex ComplexVectorDotProduct(const ComplexVector in1, const ComplexVector in2);

/// @brief Computes the magnitude of the input vector.
/// @param in The input vector.
/// @return The operation's result.
double ComplexVectorMagnitude(const ComplexVector in);

/// @brief Transforms the input vector by the input matrix.
/// @param in The input vector.
/// @param transform The input matrix.
/// @return The transformed vector.
ComplexVector ComplexVectorTransform(ComplexVector in, ComplexMatrix transform);

/// @brief Prints the input vector to screen.
/// @param in The input vector.
void ComplexVectorPrint(const ComplexVector in);

#endif