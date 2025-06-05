#ifndef QSIM_H
#define QSIM_H

#define NUM_MAX_QBITS 100
#define NUM_MAX_GATES 100

#include <limits.h>
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
    char m_gateNames[NUM_MAX_GATES][MAX_INPUT];
    QuantumCircuitDef m_circuitDef;
} QSim;

/// @brief Creates a QSim object by loading its parameters from the specified initial state and circuit definition file. Remember to free the allocated memory by calling QSimFree when done using it.
/// @param initStateFilename The initial state filename.
/// @param circFileName The circuit definition filename.
/// @return The QSim object.
QSim CreateQSim(const char* initStateFilename, const char* circFileName);

/// @brief Frees memory allocated by CreateQSim.
/// @param self The simulation object.
void QSimFree(QSim* self);

/// @brief Runs the simulation.
/// @param self The simulation object.
void QSimRun(QSim* self);

/// @brief Returns the QuantumGate object with the specified name. If none exists, returns NULL.
/// @param self The simulation objct.
/// @param name The quantum gate name.
/// @return A pointer to the desired quantum gate, if it exists. NONE otherwise.
const QuantumGate* GetGateByName(const QSim* self, const char* name);

/// @brief Returns the QuantumGate object ID with the specified name. If none exists, returns -1.
/// @param self The simulation objct.
/// @param name The quantum gate name.
/// @return The ID of the desired quantum gate, if it exists. -1 otherwise.
const int GetGateIDByName(const QSim* self, const char* name);

#endif