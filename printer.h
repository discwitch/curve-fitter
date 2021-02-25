#ifndef PRINTER
#define PRINTER

#include "type_definitions.h"

void print_header();
void print_error(error_t errors);
void print_result_lin(lin_coefficients coefficients, error_t errors, int mode);
void print_result_poly(double *coefficients, error_t errors, int degree);

#endif