#include <stdio.h>
#include <limits.h>
#include <string.h>
#include "../../include/Error.h"
#include "../../include/Properties/Properties.h"
#include "../../include/Properties/Property.h"

void LoadFromFile(Properties* self, const char* filename)
{
    FILE* pFile = fopen(filename, "r");

    if (pFile == NULL) { THROW_ERROR("Error creating Properties. File %s not found\n", filename); return; }

    char line[MAX_INPUT];
    while (fgets(line, sizeof(line), pFile))
    {
        char name[256];
        char value[256];

        sscanf(line, "%s %s", name, value);

        printf("Found property (%s, %s)\n", name, value);

        Property property = CreateProperty(name, value);
        AddProperty(self, &property);
    } 

    fclose(pFile);
}

Properties CreateProperties(const char* filename)
{
    Properties prop;
    prop.m_pRoot = NULL;

    LoadFromFile(&prop, filename);
    
    return prop;
}

void AddProperty(Properties* self, Property* pNewProp)
{
    if (self->m_pRoot == NULL)
    {
        self->m_pRoot = pNewProp;
        return;
    }

    Property* pLastProp = self->m_pRoot;

    while(pLastProp->m_pNext) pLastProp = pLastProp->m_pNext; //Get the last property from the linked list
    pNewProp->m_pPrev = pLastProp;
    pLastProp->m_pNext = pNewProp;
}

Property* GetPropertyByName(const Properties* self, const char* name)
{
    Property* pProp = self->m_pRoot;

    while (pProp->m_pNext != NULL)
    {
        if (strcmp(pProp->m_name, name) == 0) return pProp;
        
        pProp = pProp->m_pNext;
    }
    
    return NULL;
}

int GetPropertyInt(const Properties* self, const char* name)
{
    Property* pProp = GetPropertyByName(self, name);
    
    if (pProp == NULL)
        return -1;   
        
    return GetPropertyValueAsInt(pProp);
}

QuantumState GetPropertyQuantumState(Properties* self, const char* name, const int numQBits)
{
    Property* pProp = GetPropertyByName(self, name);
    
    if (pProp == NULL)
        return CreateComplexVector(0);   
        
    return GetPropertyValueAsQuantumState(pProp, numQBits);
}

QuantumGate GetPropertyQuantumGate(Properties* self, const char* name, const int numQBits)
{
    Property* pProp = GetPropertyByName(self, name);
    
    if (pProp == NULL)
        return CreateComplexMatrix(0);   
        
    return GetPropertyValueAsQuantumGate(pProp, numQBits);
}