#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
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
    kAutoTest,
    kMain,
    kMenuStepNum
} MenuStep;

bool g_bDone;
int g_menuStep;

void BootMenuUpdate()
{
    printf("Boot menu:\n");
    printf("\t1) AutoTest\n");
    printf("\t2) Main\n");
    printf("\tq) Exit\n");

    switch (getchar())
    {
        case '1':
            g_menuStep = kAutoTest;
            break;
        case '2':
            g_menuStep = kMain;
            break;
        case 'q':
            g_bDone = true;
            break;
    }
}

void AutoTestUpdate()
{
    printf("autotest exited with code %d\n", system("./autotest"));

    g_menuStep = kBoot;
}

void MainUpdate()
{
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

    PRINT_QUANTUM_STATE_NAMED("initState", initState);
    PRINT_QUANTUM_GATE_NAMED("X", X);
    PRINT_QUANTUM_GATE_NAMED("I", I);
    PRINT_QUANTUM_GATE_NAMED("Y", Y);

    QuantumState state = ComplexVectorTransform(initState, I);
    state = ComplexVectorTransform(state, X);
    state = ComplexVectorTransform(state, Y);

    QuantumState finalState = state;

    PRINT_QUANTUM_STATE_NAMED("finalState", finalState);

    g_menuStep = kBoot;
}

// Generic signature for the main update functions
typedef void (*UpdateFn)();

UpdateFn g_updateFunctions[] = {
    BootMenuUpdate, // 0
    AutoTestUpdate, // 1
    MainUpdate // 2
};

int main(int argc, char** argv)
{
    g_bDone = false;
    g_menuStep = kBoot;

    while (!g_bDone)
    {
        if (g_menuStep < kMenuStepNum)
            g_updateFunctions[g_menuStep]();
    }

    return 0;
}