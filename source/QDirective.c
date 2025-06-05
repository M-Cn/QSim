#include <string.h>
#include "../include/QDirective.h"

DirectiveType GetDirTypeFromInputString(const char* str)
{
    if (strcmp(str, "qbits")) return kDirTypeNumQBit;
    else if (strcmp(str, "init")) return kDirTypeInititalState;
    else if (strcmp(str, "define")) return kDirTypeGateDef;
    else if (strcmp(str, "circ")) return kDirTypeCircuitDef;
    else return kDirTypeNone;
}

QDirective CreateQDirective(const char* str)
{
    char dirStr[MAX_INPUT];
    char argStr[MAX_INPUT];
    sscanf(str, "#%s %s", dirStr, argStr);

    DirectiveType dirType = GetDirTypeFromInputString(dirStr);
    QDirective directive = { dirType, argStr};

    return directive;
}