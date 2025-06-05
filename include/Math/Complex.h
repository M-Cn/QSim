#ifndef COMPLEX_H
#define COMPLEX_H

#include <stdbool.h>

typedef struct ComplexMatrix ComplexMatrix;

typedef struct Complex
{
    double m_re;
    double m_im;
} Complex;

/// @brief Creates a complex number.
/// @param re The real part.
/// @param im The imaginary part.
/// @return The complex number.
Complex CreateComplex(const double re, const double im);

/// @brief Adds two complex numbers.
/// @param in1 The first complex number.
/// @param in2 The second complex number.
/// @return The result of the addition.
Complex ComplexAdd(const Complex in1, const Complex in2);

/// @brief Subtracts two complex numbers.
/// @param in1 The first complex number.
/// @param in2 The second complex number.
/// @return The result of the subtraction.
Complex ComplexSubtract(const Complex in1, const Complex in2);

/// @brief Multiplies two complex numbers.
/// @param in1 The first complex number.
/// @param in2 The second complex number.
/// @return The result of the multiplication.
Complex ComplexMultiply(const Complex in1, const Complex in2);

/// @brief Divides two complex numbers.
/// @param in1 The first complex number.
/// @param in2 The second complex number.
/// @return The result of the division.
Complex ComplexDivide(const Complex in1, const Complex in2);

/// @brief Returns the complex conjugate of the input complex number.
/// @param in The complex number to conjugate.
/// @return The input's complex conjugate.
Complex ComplexConjugate(const Complex in);

/// @brief Returns the magnitude of the input complex number.
/// @param in The complex number of which to compute the magnitude.
/// @return The input's magnitude.
double ComplexMagnitude(const Complex in);

/// @brief Returns the argument of the complex number.
/// @param in The complex number of which to compute the argument.
/// @return The input's argument.
double ComplexArgument(const Complex in);

/// @brief Returns true if the two complex numbers are identical.
/// @param in1 The first complex number.
/// @param in2 The second complex number.
/// @return Whether or not the inputs are identical.
bool ComplexIsEqualTo(const Complex in1, const Complex in2);

/// @brief Prints the input complex number to terminal.
/// @param in The number to print.
void ComplexPrint(const Complex in);

#endif