#ifndef QDIRECTIVEHANDLER_H
#define QDIRECTIVEHANDLER_H

#include "QDirective.h"
#include "QuantumGate.h"
#include "QuantumState.h"

typedef struct QSim QSim;


/// @brief Handles the input directive
/// @param pQSim Where to register the parsed directive
/// @param directive The directive to handle
void HandleDirective(QSim* pQSim, QDirective directive);

typedef void(*DirectiveHandlerFn)(QSim* pQSim, QDirective directive);

void HandleNoneDirective(QSim* pQSim, QDirective directive);
void HandleNumQBitsDirective(QSim* pQSim, QDirective directive);
void HandleInitialStateDirective(QSim* pQSim, QDirective directive);
void HandleGateDefDirective(QSim* pQSim, QDirective directive);
void HandleCircuitDefDirective(QSim* pQSim, QDirective directive);

#endif