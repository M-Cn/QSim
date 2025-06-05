#include <stdio.h>
#include <limits.h>
#include <string.h>
#include "../include/QSim.h"
#include "../include/QDirective.h"
#include "../include/QDirectiveHandler.h"
#include "../include/Math/Complex.h"

void LoadDirectiveFile(QSim* self, const char* filename)
{
    FILE* pFile = fopen(filename, "r");
    char line[MAX_INPUT];

    while (fgets(line, sizeof(line), pFile))
    {
        QDirective directive = CreateQDirective(line);

        HandleDirective(self, directive);
    }
    
    fclose(pFile);
}

QSim CreateQSim(const char* initStateFilename, const char* circFileName)
{
    QSim qsim;

    LoadDirectiveFile(&qsim, initStateFilename);
    LoadDirectiveFile(&qsim, circFileName);

    return qsim;
}

const QuantumGate* GetGateByName(const QSim* self, const char* name)
{
    for (size_t i = 0; i < self->m_numGates; i++)
        if (strcmp(self->m_gateNames[i], name) == 0) return &self->m_gateList[i];

    return NULL;
}