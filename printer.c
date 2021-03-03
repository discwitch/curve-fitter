#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "type_definitions.h"

void print_header() {
    printf("\n");
    printf("%-20s%-25s%-25s%-25s%-25s%-s\n", "Fit", "RMSE", "R2", "SSE", "MSE", "Coefficients");
    printf("––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––\n");
}

void print_error(error_t errors) {
    printf("%-25.6lf%-25.6lf%-25.6lf%-25.6lf", errors.std_error, errors.r_squared, errors.sse, errors.mse);
}

void print_result_lin(lin_coefficients coefficients, error_t errors, int mode) {
    if (mode == 0) {
        printf("%-20s", "linear");
        print_error(errors);
        printf("%-sd = %lf, k = %lf\n", "", coefficients.d, coefficients.k);
    } else if (mode == 1){
        printf("%-20s", "exponential");
        print_error(errors);
        printf("%-sA = %lf, k = %lf\n", "", coefficients.d, coefficients.k);
    } else if (mode == 2){
        printf("%-20s", "logarithmic");
        print_error(errors);
        printf("%-sd = %lf, k = %lf\n", "", coefficients.d, coefficients.k);        
    }
}

void print_result_poly(double *coefficients, error_t errors, int degree) {
    printf("%-12s%-8i", "polynomial: ", degree);
    print_error(errors);
    printf("%-s", "");
    for(int i=0; i<degree+1; i++)
	{
	    printf("a[%d] = %lf", i, coefficients[i]);
        if (i != degree) printf(", ");
	}
    printf("\n");
}