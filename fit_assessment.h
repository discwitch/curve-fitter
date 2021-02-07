#ifndef FIT_ASSESSMENT
#define FIT_ASSESSMENT

#include "type_definitions.h"

double standard_error(lin_coefficients coefficients, record_t *recordP, long int numOfEntries, int mode);
double standard_error_poly(double *coefficients, record_t *recordP, long int numOfEntries, int degree);
double r_squared(lin_coefficients coefficients, record_t *recordP, long int numOfEntries, int mode);
double r_squared_poly(double* coefficients, record_t *recordP, long int numOfEntries, int degree);
double sse(lin_coefficients coefficients, record_t *recordP, long int numOfEntries, int mode);
double sse_poly(double *coefficients, record_t *recordP, long int numOfEntries, int degree);
double mse(lin_coefficients coefficients, record_t *recordP, long int numOfEntries, int mode);
double mse_poly(double *coefficients, record_t *recordP, long int numOfEntries, int degree);
double rsse_poly(double *coefficients, record_t *recordP, long int numOfEntries, int degree, double alpha);

#endif