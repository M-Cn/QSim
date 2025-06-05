#ifndef QCIRCUITDEF_H
#define QCIRCUITDEF_H

#define MAX_NUM_GATES 100

typedef struct QuantumCircuitDef
{
    int m_numGates;
    int m_gateIDs[MAX_NUM_GATES];
} QuantumCircuitDef;

#endif