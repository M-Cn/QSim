#ifndef QUANTUM_GATE_H
#define QUANTUM_GATE_H

#include <stdbool.h>

typedef struct ComplexMatrix ComplexMatrix;
typedef ComplexMatrix QuantumGate;

// Verifies that the input quantum gate is valid
bool QuantumGateVerify(const QuantumGate in);

#endif