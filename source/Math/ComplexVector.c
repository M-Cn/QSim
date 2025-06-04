#include <math.h>
#include "../../include/Error.h"
#include "../../include/Math/ComplexVector.h"
#include "../../include/Math/ComplexMatrix.h"
#include "../../include/Math/Complex.h"

ComplexVector CreateComplexVector(const size_t size)
{
    ASSERT_MSG(size < MAX_SIZE, "Exceeding maximum ComplexMatrix size\n");

    ComplexVector result;

    result.m_size = size;
    result.m_data = (Complex*)calloc(size, sizeof(Complex));

    if (result.m_data == NULL) PANIC("Failed to allocate memory for ComplexVector\n");
    
    // calloc initializes memory to 0, this is in case we want to change the default value in the future
    for (size_t i = 0; i < size; i++)
        ComplexVectorSetElement(&result, i, CreateComplex(0.f, 0.f));
    
    return result;
}

void ComplexVectorFree(ComplexVector* self)
{
    if ((self == NULL) || (self->m_data == NULL)) PANIC("Attempting to free unallocated memory for ComplexVector\n");
    
    free(self->m_data);

    self->m_data = NULL;
    self->m_size = 0;
}

void ComplexVectorSetElement(const ComplexVector* self, const size_t idx, const Complex value)
{
    if (self == NULL) PANIC("ComplexVectorSetElement() failed. self was nullptr\n");
    
    if (idx < self->m_size)
        self->m_data[idx] = value; return;

    THROW_ERROR("Attempted to set an out of bound value for ComplexVector (requested=%zu, size=%zu)\n", idx, self->m_size);
}

Complex ComplexVectorGetElement(const ComplexVector* self, const size_t idx)
{
    if (self == NULL) PANIC("ComplexVectorGetElement() failed. self was nullptr\n");

    if (idx < self->m_size) return self->m_data[idx];

    PANIC("Attempting to read out of bound array for ComplexVector (requested=%zu, size=%zu)\n", idx, self->m_size);
}

ComplexVector ComplexVectorAdd(const ComplexVector in1, const ComplexVector in2)
{
    ASSERT_MSG(in1.m_size == in2.m_size, "Attempting to add two ComplexVector objects with different sizes\n");
    
    ComplexVector result = CreateComplexVector(in1.m_size);

    for (size_t i = 0; i < in1.m_size; i++)
    {
        Complex v1 = ComplexVectorGetElement(&in1, i);
        Complex v2 = ComplexVectorGetElement(&in2, i);

        ComplexVectorSetElement(&result, i, ComplexAdd(v1, v2));
    }
    
    return result;
}

ComplexVector ComplexVectorSubtract(const ComplexVector in1, const ComplexVector in2)
{
    ASSERT_MSG(in1.m_size == in2.m_size, "Attempting to subtract two ComplexVector objects with different sizes\n");
    
    ComplexVector result = CreateComplexVector(in1.m_size);

    for (size_t i = 0; i < in1.m_size; i++)
    {
        Complex v1 = ComplexVectorGetElement(&in1, i);
        Complex v2 = ComplexVectorGetElement(&in2, i);

        ComplexVectorSetElement(&result, i, ComplexSubtract(v1, v2));
    }
    
    return result;
}

ComplexVector ComplexVectorScalarMultiply(const ComplexVector in, const Complex scalar)
{
    ComplexVector result = CreateComplexVector(in.m_size);

    for (size_t i = 0; i < in.m_size; i++)
    {
        Complex v = ComplexVectorGetElement(&in, i);
        ComplexVectorSetElement(&result, i, ComplexMultiply(v, scalar));
    }

    return result;
}

Complex ComplexVectorDotProduct(const ComplexVector in1, const ComplexVector in2)
{
    ASSERT_MSG(in1.m_size == in2.m_size, "Attempting to scalarly multiply two ComplexVector objects with different sizes\n");

    Complex result = CreateComplex(0.f, 0.f);
    
    for (size_t i = 0; i < in1.m_size; i++)
    {
        Complex v1 = ComplexVectorGetElement(&in1, i);
        Complex v2 = ComplexVectorGetElement(&in2, i);

        Complex conjugate = ComplexConjugate(v2);
        Complex product = ComplexMultiply(v1, conjugate);

        result = ComplexAdd(result, product);
    }
    
    return result;
}

double ComplexVectorMagnitude(const ComplexVector in)
{
    double result = 0.f;

    for (size_t i = 0; i < in.m_size; i++)
    {
        Complex v = ComplexVectorGetElement(&in, i);
        double magnitude = ComplexMagnitude(v);

        result += magnitude * magnitude;
    }
    
    return sqrt(result);
}

ComplexVector ComplexVectorTransform(ComplexVector in, ComplexMatrix transform)
{
    ASSERT_MSG(in.m_size == transform.m_size, "Attempting to transform a complex vector with a matrix of mismatching size!\n");

    const size_t size = in.m_size;

    ComplexVector result = CreateComplexVector(in.m_size);

    for (size_t row = 0; row < size; row++)
    {
        Complex sum = CreateComplex(0, 0);

        for (size_t col = 0; col < size; col++)
        {
            Complex m_elem = ComplexMatrixGetElement(&transform, row, col);
            Complex v_elem = ComplexVectorGetElement(&in, col);

            sum = ComplexAdd(sum, ComplexMultiply(m_elem, v_elem));
        }

        ComplexVectorSetElement(&result, row, sum);
    }

    return result;
}

void ComplexVectorPrint(const ComplexVector in)
{
    printf("[\n");

    for (size_t i = 0; i < in.m_size; i++)
    {
        ComplexPrint(ComplexVectorGetElement(&in, i));
        printf("\n");
    }
    
    printf("]\n");
}