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

QDirective CreateQDirective(const char* str);

const char* GetDirTypeName(DirectiveType type);

#endif