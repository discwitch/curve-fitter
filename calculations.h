#ifndef MATH
#define MATH

#include "type_definitions.h"

record_t sumXY(record_t *recordP, long int numOfEntries);
record_t powerSumXY(record_t *recordP, long int numOfEntries);
double sumProductXY(record_t *recordP, long int numOfEntries);
double linear(double x, double k, double d);
double exponential(double x, double k, double A);
double logarithmic(double x, double k, double A);
double polynomial(double x, double *coefficients, int degree);
double power(double x, int exponent);
void power_arrays(record_t *recordP, int record_size, double *matrix_entries, double *extended_Y, int n);
void create_extended_matrix(double *array, double *matrix_entries, double *extended_Y, int n);
void gaussian_elimination(int n, double *matrix, double *coefficients);

#endif