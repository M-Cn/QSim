#ifndef UTILS_H
#define UTILS_H

#define EPSILON 1e-9

// Performs comparison between two doubles with an error margin.
#define DOUBLE_EQUALS(x, y) (fabs(x - y) < EPSILON)

#endif