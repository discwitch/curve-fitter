#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <getopt.h>

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

    char filename[strlen(argv[1]) + 30];
    create_filename(filename, argv[1]);
    


    // consistent: mode 0: linear, mode 2: exponential, mode 3: logarithmic

    static struct option long_options[] =
    {
    {"lin", no_argument, NULL, '0'},
    {"exp", no_argument, NULL, '1'},
    {"log", no_argument, NULL, '2'},
    {"pol", required_argument, NULL, 'p'},
    {"all", required_argument, NULL, 'a'},
    {NULL, 0, NULL, 0}
    };

    int option;
    int write = 0;
    while ((option = getopt_long(argc, argv, "w", long_options, NULL)) != -1) {
        switch (option) {
            case 'w':
                {
                write = 1;
                FILE *fp;
                fp = fopen(filename, "w");
                fprintf(fp, "%s-%s\n", header.col1, header.col2);
                fprintf(fp, "\n");
                fclose(fp);
                }
                break;
            case 'a':
                {
                lin_coefficients linCoefficients = linearRegression(records, numOfEntries);
                error_t lin = calculate_error_lin(linCoefficients, records, numOfEntries, 0);
                print_result_lin(linCoefficients, lin, 0);

                lin_coefficients expCoefficients = exponentialRegression(records, numOfEntries);
                error_t exp = calculate_error_lin(expCoefficients, records, numOfEntries, 1);
                print_result_lin(expCoefficients, exp, 1);

                lin_coefficients logCoefficients = logarithmicRegression(records, numOfEntries);
                error_t log = calculate_error_lin(logCoefficients, records, numOfEntries, 2);
                print_result_lin(logCoefficients, log, 2);

                int degree = atoi(optarg);
                if (degree == 0) {
                    fprintf(stderr, "invalid -pol option \"%s\" - expecting an integer\n", 
                    optarg?optarg:"");
                    exit(EXIT_FAILURE);
                }

                double coefficients[degree + 1];
                polynomialRegression(records, numOfEntries, coefficients, degree);
                error_t poly = calculate_error_poly(coefficients, records, numOfEntries, degree);
                print_result_poly(coefficients, poly, degree);

                if (write == 1) {
                    write_lin(filename, linCoefficients, lin, 0);
                    write_lin(filename, expCoefficients, exp, 1);
                    write_lin(filename, logCoefficients, log, 2);
                    write_poly(filename, coefficients, poly, degree);
                }
                }
                break;
            case '0':
                {
                lin_coefficients linCoefficients = linearRegression(records, numOfEntries);
                error_t lin = calculate_error_lin(linCoefficients, records, numOfEntries, 0);
                print_result_lin(linCoefficients, lin, 0);
                if (write == 1) write_lin(filename, linCoefficients, lin, 0);
                }
                break;
            case '1': 
                {
                lin_coefficients expCoefficients = exponentialRegression(records, numOfEntries);
                error_t exp = calculate_error_lin(expCoefficients, records, numOfEntries, 1);
                print_result_lin(expCoefficients, exp, 1);
                if (write == 1) write_lin(filename, expCoefficients, exp, 1);
                }
                break;
            case '2': 
                {
                lin_coefficients logCoefficients = logarithmicRegression(records, numOfEntries);
                error_t log = calculate_error_lin(logCoefficients, records, numOfEntries, 2);
                print_result_lin(logCoefficients, log, 2);
                if (write == 1) write_lin(filename, logCoefficients, log, 2);
                }
                break;
            case 'p': 
                {
                int degree = atoi(optarg);
                if (degree == 0) {
                    fprintf(stderr, "invalid -pol option \"%s\" - expecting an integer\n", 
                    optarg?optarg:"");
                    exit(EXIT_FAILURE);
                    }
                double coefficients[degree + 1];
                polynomialRegression(records, numOfEntries, coefficients, degree);
                error_t poly = calculate_error_poly(coefficients, records, numOfEntries, degree);
                print_result_poly(coefficients, poly, degree);
                if (write == 1) write_poly(filename, coefficients, poly, degree);
                }
                break;
        }
    }



    /* for (long i = 1; i < numOfEntries; i++) {
        printf("%lf, %lf\n", records[i].X, records[i].Y);
    } */

    // double alpha = 0;
    // int maxDegree = 12;
    // int degree = bestPolynomialFit(records, numOfEntries, maxDegree, alpha);

    return 0;
}

