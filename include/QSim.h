#ifndef QSIM_H
#define QSIM

#define NUM_MAX_QBITS 100
#define NUM_MAX_GATES 100

#include "QuantumGate.h"
#include "QuantumState.h"
#include "QuantumCircuitDef.h"

typedef struct QSim
{
    int m_numQBits;
    int m_numGates;
    QuantumState m_initialState;
    QuantumState m_finalState;
    QuantumGate m_gateList[NUM_MAX_GATES];
    char m_gateNames[NUM_MAX_GATES];
    QuantumCircuitDef m_circuitDef;
} QSim;

QSim CreateQSim(const char* filename);

QuantumGate* GetGateByName(const QSim* self, const char* name);

#endif