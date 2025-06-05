#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "../include/Debug.h"
#include "../include/QSim.h"
#include "../include/QuantumState.h"
#include "../include/QuantumGate.h"
#include "../include/Math/Complex.h"

#define NUM_QBITS 1

#define PRINT_QUANTUM_GATE_NAMED(name, gate) \
    printf("%s:\n", name); \
    ComplexMatrixPrint(gate); \
    printf("\n");

#define PRINT_QUANTUM_STATE_NAMED(name, gate) \
    printf("%s:\n", name); \
    ComplexVectorPrint(gate); \
    printf("\n");

typedef enum MenuStep
{
    kBoot,
    kMain,
    kSetConfigFilepath,
    kMenuStepNum
} MenuStep;

bool g_bDone;
int g_menuStep;
char g_initConfigFilepath[MAX_INPUT];
char g_circConfigFilepath[MAX_INPUT];

void BootMenuUpdate()
{
    printf("Select action:\n");
    printf("\t1) Main\n");
    printf("\t2) Set Config Filepaths\n");
    printf("\tc) Clear Terminal\n");
    printf("\tq) Exit\n");

    printf("(Initial state filepath: %s)\n", g_initConfigFilepath);
    printf("(Circuit def filepath: %s)\n", g_circConfigFilepath);

read_input:
    switch (getchar())
    {
        case '1':
            g_menuStep = kMain;
            break;
        case '2':
            g_menuStep = kSetConfigFilepath;
            break;
        case 'c':
            system("clear");
            break;
        case 'q':
            g_bDone = true;
            break;
        default:
            goto read_input;
            break;
    }
}

bool DoesFileExist(const char* filename)
{
    bool bExists = true;

    FILE* pFile = fopen(filename, "r");

    if (pFile == NULL) bExists = false;

    fclose(pFile);

    return bExists;
}

void MainUpdate()
{
    if (!DoesFileExist(g_initConfigFilepath)) { THROW_ERROR("Input initial state file %s does not exist.\n", g_initConfigFilepath); goto ret;}
    if (!DoesFileExist(g_initConfigFilepath)) { THROW_ERROR("Input circuit def file %s does not exist.\n", g_circConfigFilepath); goto ret; }

    QSim qsim = CreateQSim(g_initConfigFilepath, g_circConfigFilepath);

    if (qsim.m_numQBits > NUM_MAX_QBITS) { THROW_ERROR("Exceeding maximum number of qbits (value=%d, max=%d)\n", qsim.m_numQBits, NUM_MAX_QBITS); goto ret; }
    if (qsim.m_numGates > NUM_MAX_GATES) { THROW_ERROR("Exceeding maximum number of gates (value=%d, max=%d)\n", qsim.m_numGates, NUM_MAX_GATES); goto ret; }

    PRINT_QUANTUM_STATE_NAMED("Initial State", qsim.m_initialState);

    QSimRun(&qsim);

    PRINT_QUANTUM_STATE_NAMED("Final State", qsim.m_finalState);

ret:
    QSimFree(&qsim);

    g_menuStep = kBoot;
}

void SetConfigFilepathUpdate()
{
    do
    {
        printf("Insert initial state config filepath:\n");
        scanf("%s", g_initConfigFilepath);

        if (!DoesFileExist(g_initConfigFilepath)) THROW_ERROR("The specified file does not exist. Insert a valid filepath.\n");   
    } while (!DoesFileExist(g_initConfigFilepath));

    do
    {
        printf("Insert circuit config filepath:\n");
        scanf("%s", g_circConfigFilepath);

        if (!DoesFileExist(g_circConfigFilepath)) THROW_ERROR("The specified file does not exist. Insert a valid filepath.\n");  
    } while (!DoesFileExist(g_circConfigFilepath));

    g_menuStep = kBoot;
}

// Generic signature for the update functions
typedef void (*UpdateFn)();

// Update functions table
UpdateFn g_updateFunctions[] = {
    BootMenuUpdate,
    MainUpdate,
    SetConfigFilepathUpdate
};

int main(int argc, char** argv)
{
    g_bDone = false;
    g_menuStep = kSetConfigFilepath;

    while (!g_bDone)
    {
        if (g_menuStep < kMenuStepNum) g_updateFunctions[g_menuStep]();
        else PANIC("Invalid menu step %d\n", g_menuStep);
    }

    return 0;
}