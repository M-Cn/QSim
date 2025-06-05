#ifndef QCIRCUITDEF_H
#define QCIRCUITDEF_H

#define MAX_NUM_GATES 100
#include "QuantumGate.h"

typedef struct QuantumCircuitDef
{
    int m_numGates;
    QuantumGate m_gates[MAX_NUM_GATES];
} QuantumCircuitDef;

#endif