#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum MenuStep
{
    kBootMenu,
    kAutoTest,
    kMenuStepNum,
} MenuStep;

bool g_bDone;
int g_menuStep;

void BootMenuUpdate()
{
    printf("Boot menu:\n");
    printf("\t1) AutoTest\n");
    printf("\tq) Exit\n");

    switch (getchar())
    {
        case '1':
            g_menuStep = kAutoTest;
            break;
        case 'q':
            g_bDone = true;
            break;
    }
}

void AutoTestUpdate()
{
    printf("autotest exited with code %d\n", system("./autotest"));

    g_menuStep = kBootMenu;
}

// Generic signature for the main update functions
typedef void (*UpdateFn)();

UpdateFn g_updateFunctions[] = {
    BootMenuUpdate, // 0
    AutoTestUpdate, // 1
};

int main(int argc, char** argv)
{
    g_bDone = false;
    g_menuStep = kBootMenu;

    while (!g_bDone)
    {
        if (g_menuStep < kMenuStepNum)
            g_updateFunctions[g_menuStep]();
    }

    return 0;
}