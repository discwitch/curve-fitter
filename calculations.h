#ifndef MATH
#define MATH

#include "type_definitions.h"

record_t sumXY(record_t *recordP, long int numOfEntries);
record_t powerSumXY(record_t *recordP, long int numOfEntries);
double sumProductXY(record_t *recordP, long int numOfEntries);
double linear(double x, double k, double d);
double exponential(double x, double k, double A);
double logarithmic(double x, double k, double A);

#endif