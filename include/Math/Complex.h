#ifndef COMPLEX_H
#define COMPLEX_H

#include <stdbool.h>

typedef struct ComplexMatrix ComplexMatrix;

typedef struct Complex
{
    double m_re;
    double m_im;
} Complex;

// Creates a complex number with re as real part, and im as imaginary part
Complex CreateComplex(const double re, const double im);

// Returns the sum between two Complex
Complex ComplexAdd(const Complex in1, const Complex in2);

// Returns the subtraction between two Complex
Complex ComplexSubtract(const Complex in1, const Complex in2);

// Returns the multiplication between two Complex
Complex ComplexMultiply(const Complex in1, const Complex in2);

// Returns the division between two Complex
Complex ComplexDivide(const Complex in1, const Complex in2);

// Returns the complex conjugate of the input Complex
Complex ComplexConjugate(const Complex in);

// Returns the magnitude of a Complex
double ComplexMagnitude(const Complex in);

// Returns the arguments of the input Complex
double ComplexArgument(const Complex in);

// Returns true if the two input Complex are identical. False otherwise
bool ComplexIsEqualTo(const Complex in1, const Complex in2);

// Prints the complex number
void ComplexPrint(const Complex in);

#endif