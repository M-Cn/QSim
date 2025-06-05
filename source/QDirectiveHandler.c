#include <string.h>
#include "../include/Debug.h"
#include "../include/QDirectiveHandler.h"
#include "../include/Math/Complex.h"
#include "../include/QSim.h"

#define TOKEN_LEN MAX_INPUT

#define ASSERT_DIR_TYPE_MISMATCH(EXPECTED, ACTUAL) \
ASSERT_MSG(EXPECTED == ACTUAL, "Mismatching directive type! (expecting %s, got %s)\n", GetDirTypeName(EXPECTED), GetDirTypeName(ACTUAL))

// Directive handler functions table.
DirectiveHandlerFn g_directiveHandlers[] = {
    HandleNoneDirective,
    HandleNumQBitsDirective,
    HandleInitialStateDirective,
    HandleGateDefDirective,
    HandleCircuitDefDirective
};

/// @brief Removes the delimiting [] of the input string.
/// @param buffer The input string.
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

/// @brief Removes the () delimiters in the input vector string.
/// @param buffer The input vector string.
void RemoveVectorDelimiter(char* buffer)
{
    // Remove leading '('
    if (buffer[0] == '(')
        memmove(buffer, buffer + 1, strlen(buffer));

    // Remove trailing ')'
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == ')')
        buffer[len - 1] = '\0';
}

/// @brief Splits the input vector list string into each individual vector and stores the result in tokenList.
/// @param input The input vector list string.
/// @param tokenList The output vector list.
void SplitVectorStringList(const char* input, char tokenList[][TOKEN_LEN])
{
    char* buffer = strdup(input); //Create a writable copy of the value input for usage within strtok
    
    RemoveInputDelimiter(buffer);

    char* token = strtok(buffer, ", "); 
    int currentTokenIdx = 0;

    // Recursively parse tokens. Splits strings either at commas or whitespaces
    while (token != NULL)
    {
        strncpy(tokenList[currentTokenIdx], token, TOKEN_LEN - 1);
        tokenList[currentTokenIdx][TOKEN_LEN - 1] = 0; //Make sure it's null terminated

        currentTokenIdx++;
        token = strtok(NULL, ", ");
    }

    free(buffer);
}

/// @brief Splits the input complex vector string into each individual complex number and stores the result in parts.
/// @param input The input vector string.
/// @param parts The output complex number list.
/// @param count The number of previously parsed elements. Used to read the correct coordinate in the vector.
void SplitVectorString(const char* input, char parts[][TOKEN_LEN], int* count) 
{
    const char* p = input;
    int offset = 0;
    char token[TOKEN_LEN];

    // Recursively parse tokens. Parse everything that's not a ','
    while (sscanf(p, " %[^,]%n", token, &offset) == 1) 
    {
        strncpy(parts[*count], token, TOKEN_LEN - 1);
        parts[*count][TOKEN_LEN - 1] = '\0';

        (*count)++;
        p += offset;
        
        // If we find a comma, we skip ahead
        if (*p == ',') p++;
        else break;
    }
}

/// @brief Splits the input matrix string into each individual vector component and stores the result in tokenList.
/// @param input The input matrix string.
/// @param tokenList The output vector list.
void SplitMatrixString(const char* input, char tokenList[][TOKEN_LEN])
{
    char* buffer = strdup(input); //Create a writable copy of the value input for usage within strtok
    
    RemoveInputDelimiter(buffer);

    char tmp[256];
    int numChrRead = 0;
    int currentTokenIdx = 0;

    // Recursively parse tokens. Parse everything that's not a whitespace ' '
    while (sscanf(buffer, "%[^ ] %n", tmp, &numChrRead) != EOF)
    {
        RemoveVectorDelimiter(tmp);

        char vectorStr[TOKEN_LEN];
        strncpy(vectorStr, tmp, TOKEN_LEN - 1);
        vectorStr[TOKEN_LEN - 1] = '\0'; //Make sure it's null terminated
        
        SplitVectorString(vectorStr, tokenList, &currentTokenIdx);

        buffer += numChrRead;
    }
}

/// @brief Splits the input quantum circuit string into each individual gate name.
/// @param input The input quantim circuit definition string.
/// @param tokenList The output list of gate names.
/// @param pNumGates Pointer to the previously processed elements. Used to store the name in the correct position.
void SplitCircuitString(const char* input, char tokenList[][TOKEN_LEN], int* pNumGates)
{
    char* buffer = strdup(input); //Create a writable copy of the value input for usage within strtok
    
    char* token = strtok(buffer, " "); 

    // Recursively parse tokens. Splits strings at whitespaces
    while (token != NULL)
    {
        strncpy(tokenList[*pNumGates], token, TOKEN_LEN - 1);
        tokenList[*pNumGates][TOKEN_LEN - 1] = 0; //Make sure it's null terminated

        *pNumGates += 1;
        token = strtok(NULL, " ");
    }

    free(buffer);
}

/// @brief Translates the input complex number string into an actual complex number.
/// @param str The input complex string.
/// @return The output complex number.
Complex CreateComplexFromString(const char* str)
{
    Complex num = CreateComplex(0.f, 0.f);

    if (sscanf(str, "%lf+i%lf", &num.m_re, &num.m_im) == 2)         {}
    else if (sscanf(str, "%lf-i%lf", &num.m_re, &num.m_im) == 2)    { num.m_im = -num.m_im; }
    else if (sscanf(str, "%lf", &num.m_re) == 1)                    { num.m_im = 0.0; }
    else if (sscanf(str, "i%lf", &num.m_im) == 1)                   { num.m_re = 0.0; }
    else if (strcmp(str, "i") == 0)                                 { num.m_im = 1.0; }
    else if (strcmp(str, "-i") == 0)                                { num.m_im = -1.0; }

    DEBUG_OUTPUT("Generated complex (%.3lf, %.3lf) from input %s\n", num.m_re, num.m_im, str);

    return num;
}

/// @brief Creates a quantum state object from the input directive.
/// @param self The input directive.
/// @param numQBits The number of quantum bits.
/// @return The quantum state object.
QuantumState CreateQuantumStateDefFromDirective(const QDirective* self, const int numQBits)
{
    const int size = 1 << numQBits;
    QuantumState state = CreateComplexVector(size);

    char tokenList[TOKEN_LEN][TOKEN_LEN];
    SplitVectorStringList(self->m_value, tokenList);

    for (size_t i = 0; i < size; i++)
    {        
        Complex num = CreateComplexFromString(tokenList[i]);

        ComplexVectorSetElement(&state, i, num);
    }
    
    return state;
}

/// @brief Creates a quantum gate object from the input directive.
/// @param self The input directive.
/// @param pName A pointer to where to store the gate's name.
/// @param numQBits The number of quantum bits.
/// @return The quantum gate object.
QuantumGate CreateQuantumGateDefFromDirective(const QDirective* self, char pName[][MAX_INPUT], const int numQBits)
{
    const int size = 1 << numQBits;
    QuantumGate gate = CreateComplexMatrix(size);

    char elemList[TOKEN_LEN];

    sscanf(self->m_value, "%s %[^\n]", *pName, elemList);

    char tokenList[TOKEN_LEN][TOKEN_LEN];
    SplitMatrixString(elemList, tokenList);
    
    int listIdx = 0;
    for (size_t row = 0; row < size; row++)
    {
        for (size_t col = 0; col < size; col++)
        {
            Complex num = CreateComplexFromString(tokenList[listIdx++]);
            
            ComplexMatrixSetElement(&gate, row, col, num);
        }     
    }

    return gate;
}

/// @brief Creates a circuit definition object from the input directive.
/// @param self The input directive.
/// @param pQSim The simulation object in which the circuit exists.
/// @return The circuit definition object.
QuantumCircuitDef CreateCircuitDefFromDirective(const QDirective* self, QSim* pQSim)
{
    QuantumCircuitDef circuitDef;
    circuitDef.m_numGates = 0;
    
    char tokenList[TOKEN_LEN][TOKEN_LEN];
    SplitCircuitString(self->m_value, tokenList, &circuitDef.m_numGates);

    for (size_t i = 0; i < circuitDef.m_numGates; i++)
    {
        const int gateID = GetGateIDByName(pQSim, tokenList[i]);

        if (gateID == -1) THROW_ERROR("Gate %s not found.\n", tokenList[i]);

        circuitDef.m_gateIDs[i] = gateID;
    }
    
    return circuitDef;
}

void HandleDirective(QSim* pQSim, QDirective directive)
{
    DEBUG_OUTPUT("Handling QDirective=(%s, %s)\n", GetDirTypeName(directive.m_type), directive.m_value);

    if (directive.m_type < kDirTypeNum) return g_directiveHandlers[directive.m_type](pQSim, directive);
    
    THROW_ERROR("Unhandled directive type %d\n", directive.m_type);
}

void HandleNoneDirective(QSim* pQSim, QDirective directive)
{
    ASSERT_DIR_TYPE_MISMATCH(kDirTypeNone, directive.m_type);
}

void HandleNumQBitsDirective(QSim* pQSim, QDirective directive)
{
    ASSERT_DIR_TYPE_MISMATCH(kDirTypeNumQBit, directive.m_type);

    pQSim->m_numQBits = atoi(directive.m_value);
}

void HandleInitialStateDirective(QSim* pQSim, QDirective directive)
{
    ASSERT_DIR_TYPE_MISMATCH(kDirTypeInititalStateDef, directive.m_type);

    pQSim->m_initialState = CreateQuantumStateDefFromDirective(&directive, pQSim->m_numQBits);
}

void HandleGateDefDirective(QSim* pQSim, QDirective directive)
{
    ASSERT_DIR_TYPE_MISMATCH(kDirTypeGateDef, directive.m_type);

    const int lastGateID = pQSim->m_numGates;

    pQSim->m_gateList[lastGateID] = CreateQuantumGateDefFromDirective(&directive, &pQSim->m_gateNames[lastGateID], pQSim->m_numQBits);

    pQSim->m_numGates++;
}

void HandleCircuitDefDirective(QSim* pQSim, QDirective directive)
{
    ASSERT_DIR_TYPE_MISMATCH(kDirTypeCircuitDef, directive.m_type);

    pQSim->m_circuitDef = CreateCircuitDefFromDirective(&directive, pQSim);
}