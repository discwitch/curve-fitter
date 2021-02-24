#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "type_definitions.h"

void print_error(error_t errors) {
    printf("\n");
    printf("Regression Standard Error: %lf\n", errors.std_error);
    printf("Regression R2: %lf\n", errors.r_squared);
    printf("SSE: %lf\n", errors.sse);
    printf("MSE: %lf\n", errors.mse);
}

void print_result_lin(lin_coefficients coefficients, error_t errors, int mode) {
    printf("\n");
    if (mode == 0) {
        printf("~~~~~~~~ LINEAR REGRESSION: y = kx * d ~~~~~~~~\n");
        printf("\n");
        printf("Linear Coefficients: k = %lf, d = %lf\n", coefficients.k, coefficients.d);
    } else if (mode == 1){
        printf("~~~~~~~~ EXPONENTIAL REGRESSION: y = A * exp(kx) ~~~~~~~~\n");
        printf("\n");
        printf("Exponential Coefficients: A = %lf, k = %lf\n", coefficients.d, coefficients.k);
    } else if (mode == 2){
        printf("~~~~~~~~ LOGARITHMIC REGRESSION: y = d + k * ln(x) ~~~~~~~~\n");
        printf("\n");
        printf("Logarithmic Coefficients: d = %lf, k = %lf\n", coefficients.d, coefficients.k);        
    }
    print_error(errors);
}

void print_result_poly(double *coefficients, error_t errors, int degree) {
    printf("\n");
    printf("~~~~~~~~ POLYNOMIAL REGRESSION: Degree = %i ~~~~~~~~\n", degree);
    printf("\n");
    printf("Coefficients: \n");
    for(int i=0; i<degree+1; i++)
	{
	    printf("a[%d] = %0.3lf\n", i, coefficients[i]);
	}
    print_error(errors);
}