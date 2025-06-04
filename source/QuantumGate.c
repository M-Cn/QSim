#include "../include/QuantumGate.h"
#include "../include/Math/ComplexMatrix.h"
#include "../include/Math/Complex.h"
#include "../include/utils.h"

bool QuantumGateVerify(const QuantumGate in)
{
    const size_t size = in.m_size;

    for (size_t row = 0; row < size; row++)
    {
        for (size_t col = 0; col < size; col++)
        {
            Complex v = ComplexMatrixGetElement(&in, row, col);

            if (!DOUBLE_EQUALS(ComplexMagnitude(v), 1.f)) return false;
        }  
    }
    
    return true;
}