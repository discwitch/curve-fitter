#ifndef FITTING_FUNCTIONS
#define FITTING_FUNCTIONS

#include "type_definitions.h"
#include "calculations.h"

lin_coefficients linearRegression(record_t *recordP, long int numOfEntries);
lin_coefficients exponentialRegression(record_t *recordP, long int numOfEntries);
lin_coefficients doubleExponentialRegression(record_t *recordP, long int numOfEntries);
lin_coefficients logarithmicRegression(record_t *recordP, long int numOfEntries);

#endif