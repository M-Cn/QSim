#ifndef PROPERTY_H
#define PROPERTY_H

#include "../QuantumGate.h"
#include "../QuantumState.h"

typedef struct Property
{
    char* m_name;
    char* m_value;
    struct Property* m_pNext;
    struct Property* m_pPrev;
} Property;

Property CreateProperty(const char* name, const char* value);

int GetPropertyValueAsInt(const Property* self);

QuantumState GetPropertyValueAsQuantumState(const Property* self, const int numQBits);

QuantumGate GetPropertyValueAsQuantumGate(const Property* self, const int numQBits);
#endif