#ifndef QDIRECTIVEHANDLER_H
#define QDIRECTIVEHANDLER_H

#include "QDirective.h"
#include "QuantumGate.h"
#include "QuantumState.h"

typedef struct QSim QSim;

// Signature for the handler functions
typedef void(*DirectiveHandlerFn)(QSim* pQSim, QDirective directive);

/// @brief Handles the input directive
/// @param pQSim Where to register the parsed directive
/// @param directive The directive to handle
void HandleDirective(QSim* pQSim, QDirective directive);

/// @brief Handles a kDirTypeNone directive.
/// @param pQSim The simulation object.
/// @param directive The input directive.
void HandleNoneDirective(QSim* pQSim, QDirective directive);

/// @brief Handles a kDirTypeNumQBits directive.
/// @param pQSim The simulation object.
/// @param directive The input directive.
void HandleNumQBitsDirective(QSim* pQSim, QDirective directive);

/// @brief Handles a kDirTypeNumQBits directive.
/// @param pQSim The simulation object.
/// @param directive The input directive.
void HandleInitialStateDirective(QSim* pQSim, QDirective directive);

/// @brief Handles a kDirTypeGateDef directive.
/// @param pQSim The simulation object.
/// @param directive The input directive.
void HandleGateDefDirective(QSim* pQSim, QDirective directive);

/// @brief Handles a kDirTypeCircuitDef directive.
/// @param pQSim The simulation object.
/// @param directive The input directive.
void HandleCircuitDefDirective(QSim* pQSim, QDirective directive);

#endif