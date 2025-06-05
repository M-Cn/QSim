#ifndef PROPERTIES_H
#define PROPERTIES_H

#include "../QuantumGate.h"
#include "../QuantumState.h"

typedef struct Property Property;

typedef struct Properties
{
    Property* m_pRoot;
} Properties;

Properties CreateProperties(const char* filename);

void AddProperty(Properties* self, Property* pNewProp);

int GetPropertyInt(const Properties* self, const char* name);

QuantumState GetPropertyQuantumState(Properties* self, const char* name, const int numQBits);

QuantumGate GetPropertyQuantumGate(Properties* self, const char* name, const int numQBits);

#endif