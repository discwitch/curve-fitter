#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include "type_definitions.h"
#include "read_csv.h"
#include "calculations.h"
#include "fitting_functions.h"
#include "fit_assessment.h"


int main(void)
{   
    long int size = findSize();

    record_t records[size];
    header_t header;

    long int numOfEntries = readCSV(records, &header);

    /* for (long i = 1; i < numOfEntries; i++) {
        printf("%lf, %lf\n", records[i].X, records[i].Y);
    } */


    lin_coefficients linCoefficients = linearRegression(records, numOfEntries);
    double score = standard_error(linCoefficients, records, numOfEntries, 0);
    double r2_score = r_squared(linCoefficients, records, numOfEntries, 0);
    double sse_lin_score = sse(linCoefficients, records, numOfEntries, 0);

    printf("Linear Coefficients: k = %lf, d = %lf\n", linCoefficients.k, linCoefficients.d);
    printf("Regression Standard Error: %lf\n", score);
    printf("SSE: %lf\n", sse_lin_score);
    printf("Regression R2: %lf\n", r2_score);

    lin_coefficients expCoefficients = exponentialRegression(records, numOfEntries);
    double exp_score = standard_error(expCoefficients, records, numOfEntries, 1);
    double exp_r2_score = r_squared(expCoefficients, records, numOfEntries, 1);
    double sse_exp_score = sse(expCoefficients, records, numOfEntries, 1);

    printf("Exponential Coefficients: A = %lf, k = %lf\n", expCoefficients.d, expCoefficients.k);
    printf("Regression Standard Error: %lf\n", exp_score);
    printf("SSE: %lf\n", sse_exp_score);
    printf("Regression R2: %lf\n", exp_r2_score);

    lin_coefficients logCoefficients = logarithmicRegression(records, numOfEntries);
    double log_score = standard_error(logCoefficients, records, numOfEntries, 2);
    double log_r2_score = r_squared(logCoefficients, records, numOfEntries, 2);
    double log_exp_score = sse(logCoefficients, records, numOfEntries, 2);

    printf("Logarithmic Coefficients: d = %lf, k = %lf\n", logCoefficients.d, logCoefficients.k);
    printf("Regression Standard Error: %lf\n", log_score);
    printf("SSE: %lf\n", log_exp_score);
    printf("Regression R2: %lf\n", log_r2_score);   
    
    return 0;
}

