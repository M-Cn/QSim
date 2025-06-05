#include <string.h>
#include "../include/Debug.h"
#include "../include/QDirectiveHandler.h"
#include "../include/Math/Complex.h"
#include "../include/QSim.h"

#define TOKEN_LEN 256

DirectiveHandlerFn g_directiveHandlers[] = {
    HandleNoneDirective,
    HandleNumQBitsDirective,
    HandleInitialStateDirective,
    HandleGateDefDirective,
    HandleCircuitDefDirective
};

void RemoveInputDelimiter(char* buffer)
{
    // Remove leading '['
    if (buffer[0] == '[')
        memmove(buffer, buffer + 1, strlen(buffer));

    // Remove trailing ']'
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == ']')
        buffer[len - 1] = '\0';
}

void CreateComplexVectorStrList(const char* input, char tokenList[][TOKEN_LEN])
{
    char* buffer = strdup(input); //Create a writable copy of the value input for usage within strtok
    
    RemoveInputDelimiter(buffer);

    char* token = strtok(buffer, ", "); 
    int currentTokenIdx = 0;

    // Parse each individual token
    while (token != NULL)
    {
        strncpy(tokenList[currentTokenIdx], token, TOKEN_LEN - 1);
        tokenList[currentTokenIdx][TOKEN_LEN - 1] = 0; //Make sure it's null terminated

        currentTokenIdx++;
        token = strtok(NULL, ", ");
    }

    free(buffer);
}

// Splits comma-separated complex numbers and registers them in parts
void SplitCommaSeparatedComplex(const char* input, char parts[][TOKEN_LEN], int* count) 
{
    const char* p = input;
    int offset = 0;
    char token[TOKEN_LEN];

    while (sscanf(p, " %[^,]%n", token, &offset) == 1) 
    {
        strncpy(parts[*count], token, TOKEN_LEN - 1);
        parts[*count][TOKEN_LEN - 1] = '\0';

        (*count)++;
        p += offset;

        if (*p == ',') p++;
        else break;
    }
}

void CreateComplexMatrixStrList(const char* input, char tokenList[][TOKEN_LEN])
{
    char* buffer = strdup(input); //Create a writable copy of the value input for usage within strtok
    
    RemoveInputDelimiter(buffer);

    char tmp[256];
    int numChrRead = 0;
    int currentTokenIdx = 0;

    while (sscanf(buffer, "(%[^ ] %n", tmp, &numChrRead) != EOF)
    {
        char vectorStr[TOKEN_LEN];
        strncpy(vectorStr, tmp, TOKEN_LEN - 1);
        vectorStr[TOKEN_LEN - 1] = '\0'; //Make sure it's null terminated
                
        SplitCommaSeparatedComplex(vectorStr, tokenList, &currentTokenIdx);

        buffer += numChrRead;
    }
}

void CreateCircuitStrList(const char* input, char tokenList[][TOKEN_LEN], int* pNumGates)
{
    char* buffer = strdup(input); //Create a writable copy of the value input for usage within strtok
    
    char* token = strtok(buffer, " "); 

    // Parse each individual token
    while (token != NULL)
    {
        strncpy(tokenList[*pNumGates], token, TOKEN_LEN - 1);
        tokenList[*pNumGates][TOKEN_LEN - 1] = 0; //Make sure it's null terminated

        *pNumGates += 1;
        token = strtok(NULL, " ");
    }

    free(buffer);
}

Complex GetComplexFromString(const char* str)
{
    Complex num = CreateComplex(0, 0);

    if (sscanf(str, "%lf+i%lf", &num.m_re, &num.m_im) == 2) 
    {
        return num;
    }
    else if (sscanf(str, "%lf-i%lf", &num.m_re, &num.m_im) == 2) 
    {
        num.m_im = -num.m_im;
        return num;
    }
    else if (sscanf(str, "%lf", &num.m_re) == 1) 
    {
        num.m_im = 0.0;
        return num;
    }
    else if (sscanf(str, "i%lf", &num.m_im) == 1) 
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

QuantumState GetQuantumStateFromDirective(const QDirective* self, const int numQBits)
{
    const int size = 1 << numQBits;
    QuantumState state = CreateComplexVector(size);

    char tokenList[TOKEN_LEN][TOKEN_LEN];
    CreateComplexVectorStrList(self->m_value, tokenList);

    for (size_t i = 0; i < size; i++)
    {        
        Complex num = GetComplexFromString(tokenList[i]);

        ComplexVectorSetElement(&state, i, num);
    }
    
    return state;
}

void GetQuantumGateDefFromDirective(const QDirective* self, QuantumGate* pQuantumGate, char pName[][MAX_INPUT], const int numQBits)
{
    const int size = 1 << numQBits;
    QuantumGate gate = CreateComplexMatrix(size);

    char elemList[TOKEN_LEN];

    sscanf(self->m_value, "%s %[^\n]", *pName, elemList);

    char tokenList[TOKEN_LEN][TOKEN_LEN];
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
}

QuantumCircuitDef GetCircuitDefFromDirective(const QDirective* self, QSim* pQSim)
{
    QuantumCircuitDef circuitDef;
    circuitDef.m_numGates = 0;
    
    char tokenList[TOKEN_LEN][TOKEN_LEN];
    CreateCircuitStrList(self->m_value, tokenList, &circuitDef.m_numGates);

    for (size_t i = 0; i < circuitDef.m_numGates; i++)
    {
        const int gateID = GetGateIDByName(pQSim, tokenList[i]);

        if (gateID == -1) THROW_ERROR("Gate %s not found.\n", tokenList[i]);

        circuitDef.m_gateIDs[i] = gateID;

        DEBUG_OUTPUT("circuitDef.gateIDs[%zu]=%d\n", i, gateID);
    }
    
    return circuitDef;
}

void HandleDirective(QSim* pQSim, QDirective directive)
{
    DEBUG_OUTPUT("Handling QDirective=(%s, %s)\n", GetDirTypeName(directive.m_type), directive.m_value);

    if (directive.m_type < kDirTypeNum)
        return g_directiveHandlers[directive.m_type](pQSim, directive);
    
    THROW_ERROR("Unhandled directive type");
}

void HandleNoneDirective(QSim* pQSim, QDirective directive)
{
    ASSERT_MSG(directive.m_type == kDirTypeNone, "Mismatching directive type!");
}

void HandleNumQBitsDirective(QSim* pQSim, QDirective directive)
{
    ASSERT_MSG(directive.m_type == kDirTypeNumQBit, "Mismatching directive type!");

    pQSim->m_numQBits = atoi(directive.m_value);
}

void HandleInitialStateDirective(QSim* pQSim, QDirective directive)
{
    ASSERT_MSG(directive.m_type == kDirTypeInititalState, "Mismatching directive type!");

    pQSim->m_initialState = GetQuantumStateFromDirective(&directive, pQSim->m_numQBits);
}

void HandleGateDefDirective(QSim* pQSim, QDirective directive)
{
    ASSERT_MSG(directive.m_type == kDirTypeGateDef, "Mismatching directive type!");

    GetQuantumGateDefFromDirective(&directive, &pQSim->m_gateList[pQSim->m_numGates], &pQSim->m_gateNames[pQSim->m_numGates], pQSim->m_numQBits);

    pQSim->m_numGates++;
}

void HandleCircuitDefDirective(QSim* pQSim, QDirective directive)
{
    ASSERT_MSG(directive.m_type == kDirTypeCircuitDef, "Mismatching directive type!");

    pQSim->m_circuitDef = GetCircuitDefFromDirective(&directive, pQSim);
}