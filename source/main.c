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

    RunQSim(&qsim);

    PRINT_QUANTUM_STATE_NAMED("Final State", qsim.m_finalState);

    /*
    const int size = 1 << NUM_QBITS; // 2 ^ NUM_QBITS

    QuantumState initState = CreateComplexVector(size);
    ComplexVectorSetElement(&initState, 0, CreateComplex(0.5f, 0.5f));
    ComplexVectorSetElement(&initState, 1, CreateComplex(0.5f, -0.5f));

    QuantumGate X = CreateComplexMatrix(size);
    ComplexMatrixSetElement(&X, 0, 0, CreateComplex(0, 0));
    ComplexMatrixSetElement(&X, 0, 1, CreateComplex(1, 0));
    ComplexMatrixSetElement(&X, 1, 0, CreateComplex(1, 0));
    ComplexMatrixSetElement(&X, 1, 1, CreateComplex(0, 0));

    QuantumGate I = CreateComplexMatrix(size);
    ComplexMatrixSetElement(&I, 0, 0, CreateComplex(1, 0));
    ComplexMatrixSetElement(&I, 0, 1, CreateComplex(0, 0));
    ComplexMatrixSetElement(&I, 1, 0, CreateComplex(0, 0));
    ComplexMatrixSetElement(&I, 1, 1, CreateComplex(1, 0));

    QuantumGate Y = CreateComplexMatrix(size);
    ComplexMatrixSetElement(&Y, 0, 0, CreateComplex(0, 0));
    ComplexMatrixSetElement(&Y, 0, 1, CreateComplex(0, -1));
    ComplexMatrixSetElement(&Y, 1, 0, CreateComplex(0, 1));
    ComplexMatrixSetElement(&Y, 1, 1, CreateComplex(0, 0));

    PRINT_QUANTUM_STATE_NAMED("Initial State", initState);
    PRINT_QUANTUM_GATE_NAMED("X", X);
    PRINT_QUANTUM_GATE_NAMED("I", I);
    PRINT_QUANTUM_GATE_NAMED("Y", Y);

    QuantumState state = ComplexVectorTransform(initState, I);
    state = ComplexVectorTransform(state, X);
    state = ComplexVectorTransform(state, Y);

    QuantumState finalState = state;

    PRINT_QUANTUM_STATE_NAMED("Final State", finalState);
    */

    g_menuStep = kBoot;
}

// Generic signature for the update functions
typedef void (*UpdateFn)();

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
        if (g_menuStep < kMenuStepNum)
            g_updateFunctions[g_menuStep]();
        else PANIC("Invalid menu step %d\n", g_menuStep);
    }

    return 0;
}