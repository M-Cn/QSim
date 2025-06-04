#include <stdio.h>
#include "../../include/Math/ComplexMatrix.h"
#include "../../include/Math/Complex.h"
#include "../../include/Error.h"

ComplexMatrix CreateComplexMatrix(const size_t size)
{
    ASSERT_MSG(size < MAX_SIZE, "Exceeding maximum ComplexMatrix size\n");
    
    ComplexMatrix ret;
    ret.m_size = size;
    ret.m_data = (Complex**)calloc(size, sizeof(Complex*));

    if (ret.m_data == NULL) PANIC("Failed to allocate memory for ComplexMatrix\n");

    for (size_t row = 0; row < size; row++)
    {
        ret.m_data[row] = (Complex*)calloc(size, sizeof(Complex));

        if (ret.m_data[row] == NULL) PANIC("Failed to allocate memory at row %zu\n", row);

        for (size_t col = 0; col < size; col++)
            if (row == col) ret.m_data[row][col] = CreateComplex(1.f, 0.f);        
    }

    return ret;
}

void ComplexMatrixFree(ComplexMatrix* self)
{
    if ((self == NULL) || (self->m_data) == NULL) THROW_ERROR("Attempting to free unallocated memory for ComplexMatrix\n"); return;

    for (size_t i = 0; i < self->m_size; i++)
        free(self->m_data[i]);
    
    free(self->m_data);

    self->m_size = 0;
    self->m_data = NULL;
}

void ComplexMatrixSetElement(const ComplexMatrix* self, const size_t row, const size_t col, Complex value)
{
    if (self == NULL) PANIC("ComplexMatrixSetElement() failed. self was nullptr\n");

    if ((row < self->m_size) && (col < self->m_size))
        self->m_data[row][col] = value; return;

    THROW_ERROR("Attempted to set an out of bound value for ComplexMatrix (requested_row=%zu, requested_col=%zu, size=%zu)\n", row, col, self->m_size);
}

Complex ComplexMatrixGetElement(const ComplexMatrix* self, const size_t row, const size_t col)
{
    if (self == NULL) PANIC("ComplexMatrixGetElement() failed. self was nullptr\n");

    if ((row < self->m_size) && (col < self->m_size)) return self->m_data[row][col];

    PANIC("Attempted to read an out of bound value for ComplexMatrix (requested_row=%zu, requested_col=%zu, size=%zu)\n", row, col, self->m_size);
}

ComplexMatrix ComplexMatrixDot(const ComplexMatrix in, const Complex complex)
{
    ComplexMatrix result = CreateComplexMatrix(in.m_size);

    for (size_t row = 0; row < in.m_size; row++)
    {
        for (size_t col = 0; col < in.m_size; col++)
            result.m_data[row][col] = ComplexMultiply(in.m_data[row][col], complex);
    }
    
    return result;
}

ComplexMatrix ComplexMatrixMultiply(const ComplexMatrix in1, const ComplexMatrix in2)
{
    ASSERT_MSG(in1.m_size == in2.m_size, "Attempting to multiply two ComplexMatrix objects with different sizes\n"); 
    
    ComplexMatrix result = CreateComplexMatrix(in1.m_size);

    for (size_t row = 0; row < in1.m_size; row++) 
    {
        for (size_t col = 0; col < in1.m_size; col++) 
        {
            Complex sum = CreateComplex(0, 0);

            for (size_t k = 0; k < in1.m_size; k++) 
            {
                Complex prod = ComplexMultiply(in1.m_data[row][k], in2.m_data[k][col]);
                sum = ComplexAdd(sum, prod);
            }

            result.m_data[row][col] = sum;
        }
    }

    return result;
}

void ComplexMatrixPrint(const ComplexMatrix in)
{
    const size_t size = in.m_size;

    for (size_t row = 0; row < size; row++)
    {
        printf("[");
        for (size_t col = 0; col < size; col++)
        {            
            ComplexPrint(ComplexMatrixGetElement(&in, col, row));
            
            if (col < size - 1) printf("\t");
        }

        printf("]\n");
    }
}