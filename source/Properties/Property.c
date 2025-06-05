#include <string.h>
#include "../../include/Error.h"
#include "../../include/Properties/Property.h"
#include "../../include/Math/Complex.h"

#define MAX_TOKEN_LEN 256

Property CreateProperty(const char* name, const char* value)
{
    Property prop;
    prop.m_name = strdup(name);
    prop.m_value = strdup(value);
    prop.m_pNext = NULL;
    prop.m_pPrev = NULL;

    return prop;
}

int GetPropertyValueAsInt(const Property* self)
{
    return atoi(self->m_value);
}

void CreateComplexVectorStrList(const char* input, char tokenList[][MAX_TOKEN_LEN])
{
    char* buffer = strdup(input); //Create a writable copy of the value input for usage within strtok
    
    // Remove leading '['
    if (buffer[0] == '[')
        memmove(buffer, buffer + 1, strlen(buffer)); // shift string left by 1

    // Remove trailing ']'
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == ']')
        buffer[len - 1] = '\0';

    char* token = strtok(buffer, ", "); 
    int currentTokenIdx = 0;

    // Parse each individual token
    while (token != NULL)
    {
        strncpy(tokenList[currentTokenIdx], token, MAX_TOKEN_LEN - 1);
        tokenList[currentTokenIdx][MAX_TOKEN_LEN - 1] = 0; //Make sure it's null terminated

        currentTokenIdx++;
        token = strtok(NULL, ", ");
    }
}

void SplitCommaSeparated(const char* input, char parts[][MAX_TOKEN_LEN], int* count) 
{
    const char* p = input;
    int offset = 0;
    char token[MAX_TOKEN_LEN];

    while (sscanf(p, " %[^,]%n", token, &offset) == 1) 
    {
        strncpy(parts[*count], token, MAX_TOKEN_LEN - 1);
        parts[*count][MAX_TOKEN_LEN - 1] = '\0';

        (*count)++;
        p += offset;

        if (*p == ',') p++;
        else break;
    }
}

void CreateComplexMatrixStrList(const char* input, char tokenList[][MAX_TOKEN_LEN])
{
    char* buffer = strdup(input); //Create a writable copy of the value input for usage within strtok
    
    // Remove leading '['
    if (buffer[0] == '[')
        memmove(buffer, buffer + 1, strlen(buffer)); // shift string left by 1

    // Remove trailing ']'
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == ']')
        buffer[len - 1] = '\0';

    int numChrRead = 0;
    char tmp[256];
    int currentTokenIdx = 0;

    while (sscanf(buffer, "(%[^)]) %n", tmp, &numChrRead) != EOF)
    {
        char vectorStr[MAX_TOKEN_LEN];
        strncpy(vectorStr, tmp, MAX_TOKEN_LEN - 1);
        vectorStr[MAX_TOKEN_LEN - 1] = 0; //Make sure it's null terminated
        
        SplitCommaSeparated(vectorStr, tokenList, &currentTokenIdx);

        buffer += numChrRead;
    }
}

Complex GetComplexFromString(const char* str)
{
    Complex num = CreateComplex(0, 0);

    if (sscanf(str, "%lf+%lfi", &num.m_re, &num.m_im) == 2) 
    {
        return num;
    }
    else if (sscanf(str, "%lf-%lfi", &num.m_re, &num.m_im) == 2) 
    {
        num.m_im = -num.m_im;
        return num;
    }
    else if (sscanf(str, "%lf", &num.m_re) == 1) 
    {
        num.m_im = 0.0;
        return num;
    }
    else if (sscanf(str, "%lfi", &num.m_im) == 1) 
    {
        num.m_re = 0.0;
        return num;
    }
    else if (strcmp(str, "i") == 0) 
    {
        num.m_re = 0.0;
        num.m_im = 1.0;
        return num;
    }
    else if (strcmp(str, "-i") == 0) 
    {
        num.m_re = 0.0;
        num.m_im = -1.0;
        return num;
    }

    return num;
}

QuantumState GetPropertyValueAsQuantumState(const Property* self, const int numQBits)
{
    const int size = 1 << numQBits;
    QuantumState state = CreateComplexVector(size);

    char tokenList[MAX_TOKEN_LEN][MAX_TOKEN_LEN];
    CreateComplexVectorStrList(self->m_value, tokenList);

    for (size_t i = 0; i < size; i++)
    {        
        Complex num = GetComplexFromString(tokenList[i]);

        ComplexVectorSetElement(&state, i, num);
    }
    
    return state;
}

QuantumGate GetPropertyValueAsQuantumGate(const Property* self, const int numQBits)
{
    const int size = 1 << numQBits;
    QuantumGate gate = CreateComplexMatrix(size);

    char elemList[256];
    char name[256];

    sscanf(self->m_value, "%s %[^\n]", name, elemList);

    char tokenList[MAX_TOKEN_LEN][MAX_TOKEN_LEN];
    CreateComplexMatrixStrList(elemList, tokenList);
    
    int listIdx = 0;
    for (size_t row = 0; row < size; row++)
    {
        for (size_t col = 0; col < size; col++)
        {
            Complex num = GetComplexFromString(tokenList[listIdx++]);
            
            ComplexMatrixSetElement(&gate, row, col, num);
        }     
    }
    
    return gate;
}