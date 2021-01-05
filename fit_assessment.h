#ifndef FIT_ASSESSMENT
#define FIT_ASSESSMENT

#include "type_definitions.h"

double standard_error(lin_coefficients coefficients, record_t *recordP, long int numOfEntries, int mode);
double r_squared(lin_coefficients coefficients, record_t *recordP, long int numOfEntries, int mode);
double sse(lin_coefficients coefficients, record_t *recordP, long int numOfEntries, int mode);
double mse(lin_coefficients coefficients, record_t *recordP, long int numOfEntries, int mode);
#endif