#ifndef QDIRECTIVE_H
#define QDIRECTIVE_H

#include <stdio.h>
#include <limits.h>

typedef enum DirectiveType
{
    kDirTypeNone,
    kDirTypeNumQBit,
    kDirTypeInititalState,
    kDirTypeGateDef,
    kDirTypeCircuitDef,
    kDirTypeNum
} DirectiveType;

typedef struct QDirective
{
    DirectiveType m_type;
    char m_value[MAX_INPUT];
} QDirective;


/// @brief Creates a QDirective object from an input string.
/// @param str The input string.
/// @return The QDirective object.
QDirective CreateQDirective(const char* str);


/// @brief Returns the corresponding string name for the DirectiveType enum value.
/// @param type The enum value.
/// @return The string.
const char* GetDirTypeName(DirectiveType type);

#endif