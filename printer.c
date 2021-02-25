#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "type_definitions.h"

void print_header() {
    printf("\n");
    printf("Fit \t\t |     Std. Error    | \t R2 \t | \t SSE \t | \t MSE \t | \t Coefficients \n");
    printf("–––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––\n");
    printf("\n");
}

void print_error(error_t errors) {
    printf("       %0.6lf       %0.6lf\t   %0.6lf    %0.6lf", errors.std_error, errors.r_squared, errors.sse, errors.mse);
}

void print_result_lin(lin_coefficients coefficients, error_t errors, int mode) {
    if (mode == 0) {
        printf("linear\t\t");
        print_error(errors);
        printf("    d = %lf, k = %lf\n", coefficients.d, coefficients.k);
    } else if (mode == 1){
        printf("exponential\t");
        print_error(errors);
        printf("    A = %lf, k = %lf\n", coefficients.d, coefficients.k);
    } else if (mode == 2){
        printf("logarithmic\t");
        print_error(errors);
        printf("    d = %lf, k = %lf\n", coefficients.d, coefficients.k);        
    }
}

void print_result_poly(double *coefficients, error_t errors, int degree) {
    printf("polynomial: %i\t", degree);
    print_error(errors);
    printf("    ");
    for(int i=0; i<degree+1; i++)
	{
	    printf("a[%d] = %lf", i, coefficients[i]);
        if (i != degree) printf(", ");
	}
    printf("\n");
}