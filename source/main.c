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
    kMenuStepNum
} MenuStep;

bool g_bDone;
int g_menuStep;

void BootMenuUpdate()
{
    printf("Boot menu:\n");
    printf("\t1) Main\n");
    printf("\tc) Clear Terminal\n");
    printf("\tq) Exit\n");

read_input:
    switch (getchar())
    {
        case '1':
            g_menuStep = kMain;
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

void MainUpdate()
{
    QSim qsim = CreateQSim("input/init.txt", "input/circ.txt");

    PRINT_QUANTUM_STATE_NAMED("Initial State", qsim.m_initialState);

    QSimRun(&qsim);

    PRINT_QUANTUM_STATE_NAMED("Final State", qsim.m_finalState);

    QSimFree(&qsim);

    g_menuStep = kBoot;
}

// Generic signature for the update functions
typedef void (*UpdateFn)();

// Update functions table
UpdateFn g_updateFunctions[] = {
    BootMenuUpdate,
    MainUpdate
};

int main(int argc, char** argv)
{
    g_bDone = false;
    g_menuStep = kBoot;

    while (!g_bDone)
    {
        if (g_menuStep < kMenuStepNum) g_updateFunctions[g_menuStep]();
        else PANIC("Invalid menu step %d\n", g_menuStep);
    }

    return 0;
}