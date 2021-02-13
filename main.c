#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include "type_definitions.h"
#include "read_write_csv.h"
#include "calculations.h"
#include "fitting_functions.h"
#include "fit_assessment.h"
#include "printer.h"


int main(int argc, char **argv)
{   
    long int size = findSize(argv[1]);

    record_t records[size];
    header_t header;
    long int numOfEntries = readCSV(argv[1], records, &header);



    /* for (long i = 1; i < numOfEntries; i++) {
        printf("%lf, %lf\n", records[i].X, records[i].Y);
    } */

    // double alpha = 0;
    // int maxDegree = 12;
    // int degree = bestPolynomialFit(records, numOfEntries, maxDegree, alpha);
    
    int degree = 3;
    double coefficients[degree + 1];
    polynomialRegression(records, numOfEntries, coefficients, degree);
    error_t poly = calculate_error_poly(coefficients, records, numOfEntries, degree);
    print_result_poly(coefficients, poly, degree);
    
    lin_coefficients linCoefficients = linearRegression(records, numOfEntries);
    error_t lin = calculate_error_lin(linCoefficients, records, numOfEntries, 0);
    print_result_lin(linCoefficients, lin, 0);


    lin_coefficients expCoefficients = exponentialRegression(records, numOfEntries);
    error_t exp = calculate_error_lin(expCoefficients, records, numOfEntries, 1);
    print_result_lin(linCoefficients, exp, 1);

    
    lin_coefficients logCoefficients = logarithmicRegression(records, numOfEntries);
    error_t log = calculate_error_lin(logCoefficients, records, numOfEntries, 2);
    print_result_lin(linCoefficients, log, 2);

    return 0;
}

