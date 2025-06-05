#ifndef ERROR_H
#define ERROR_H

#include <stdio.h>
#include <assert.h>

#define PRINT_SUCCESS(fmt, ...) printf("\033[32m" fmt "\033[0m", ##__VA_ARGS__)
#define PRINT_FAILURE(fmt, ...) fprintf(stderr, "\033[31m" fmt "\033[0m", ##__VA_ARGS__)

#define PANIC(...) do { PRINT_FAILURE(__VA_ARGS__); exit(1); } while(0)
#define THROW_ERROR(...) do { PRINT_FAILURE(__VA_ARGS__); } while(0)

#ifdef _DEBUG
    #define DEBUG_OUTPUT(...) do { printf(__VA_ARGS__); } while (0)
#else
    #define DEBUG_OUTPUT(...)
#endif

#define ASSERT_MSG(cond, msg) \
    do { \
        if (!(cond)) \
        { \
            PRINT_FAILURE("%s\n", msg); \
            fflush(stderr); \
            assert(cond); \
        } \
    } while(0);

#endif