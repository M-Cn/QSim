#include <string.h>
#include "../include/Debug.h"
#include "../include/QDirective.h"

/// @brief Gets the DirectiveType from the input string.
/// @param str The input string.
/// @return The corresponding directive type.
DirectiveType GetDirTypeFromInputString(const char* str)
{
    if (strcmp(str, "qubits") == 0) return kDirTypeNumQBit;
    else if (strcmp(str, "init") == 0) return kDirTypeInititalState;
    else if (strcmp(str, "define") == 0) return kDirTypeGateDef;
    else if (strcmp(str, "circ") == 0) return kDirTypeCircuitDef;
    else return kDirTypeNone;
}

QDirective CreateQDirective(const char* str)
{
    char dirStr[MAX_INPUT];
    char argStr[MAX_INPUT];
    sscanf(str, "#%s %[^\n]", dirStr, argStr);

    QDirective directive;
    directive.m_type = GetDirTypeFromInputString(dirStr);
    strncpy(directive.m_value, argStr, MAX_INPUT);

    DEBUG_OUTPUT("Generated directive (%s, %s) from input %s\n", GetDirTypeName(directive.m_type), directive.m_value, str);

    return directive;
}

const char* GetDirTypeName(DirectiveType type)
{
    switch (type)
    {
        case kDirTypeNone:           return "None";
        case kDirTypeNumQBit:        return "NumQBit";
        case kDirTypeInititalState:  return "InitialState";
        case kDirTypeGateDef:        return "GateDef";
        case kDirTypeCircuitDef:     return "CircuitDef";
        case kDirTypeNum:            return "Num";
        default:                     return "Unknown";
    }
}