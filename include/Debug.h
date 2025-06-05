#ifndef ERROR_H
#define ERROR_H

#include <stdio.h>
#include <assert.h>

// Prints a green formatted text to stdout
#define PRINT_SUCCESS(fmt, ...) printf("\033[32m" fmt "\033[0m", ##__VA_ARGS__)

// Prints a red formatted text to stderr
#define PRINT_FAILURE(fmt, ...) fprintf(stderr, "\033[31m" fmt "\033[0m", ##__VA_ARGS__)

// Displays an error message in red and executes the program with code 1
#define PANIC(...) do { PRINT_FAILURE(__VA_ARGS__); exit(1); } while(0)

// Displays an error message in red
#define THROW_ERROR(...) do { PRINT_FAILURE(__VA_ARGS__); } while(0)

// Displays a message only if _DEBUG is defined. Compile in debug mode to enable this
#ifdef _DEBUG
    #define DEBUG_OUTPUT(...) do { printf(__VA_ARGS__); } while (0)
#else
    #define DEBUG_OUTPUT(...)
#endif

// Displays an error message if the condition specified is not met, then asserts
#define ASSERT_MSG(cond, fmt, ...) \
    do { \
        if (!(cond)) \
        { \
            PRINT_FAILURE(fmt, ##__VA_ARGS__); \
            fflush(stderr); \
            assert(cond); \
        } \
    } while(0);

#endif