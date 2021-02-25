#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <getopt.h>
#include <unistd.h>
#include <stdbool.h>
#include <libgen.h>

#include "type_definitions.h"
#include "read_write_csv.h"
#include "calculations.h"
#include "fitting_functions.h"
#include "fit_assessment.h"
#include "printer.h"


int main(int argc, char **argv)
{   

    if (argc == 1) {
        printf("No file-path or instructions.\n");
        printf("\"./fit --help\" to list commands\n");
    }
    // consistent: mode 0: linear, mode 2: exponential, mode 3: logarithmic

    static struct option long_options[] =
    {
    {"lin", no_argument, NULL, '0'},
    {"exp", no_argument, NULL, '1'},
    {"log", no_argument, NULL, '2'},
    {"pol", required_argument, NULL, 'p'},
    {"all", required_argument, NULL, 'a'},
    {"help", no_argument, NULL, 'h'},
    {"version", no_argument, NULL, 'v'},
    {"info", no_argument, NULL, 'i'},
    {NULL, no_argument, NULL, 'n'}
    };

    int option;
    bool write = false; // if true, results are written to file
    bool silent = false; // if true, there will be no console logging
    bool file_path_exists = false; // set to true if <file-path> has been provided
    bool header_printed = false; // set to true when header has been displayed

    long int size = 0; 
    long int numOfEntries;
    char export_path[128];

    if (access( argv[1], R_OK ) == 0) {
        file_path_exists = true;
    }

    if (file_path_exists) size = findSize(argv[1]);
    record_t records[size];
    header_t header;
    if (file_path_exists) {
        char *filename = basename(argv[1]);
        numOfEntries = readCSV(argv[1], records, &header);
        create_filepath(export_path, filename); 
    }

    while ((option = getopt_long(argc, argv, "ws", long_options, NULL)) != -1) {
        switch (option) {
            case 'v':
                {
                printf("curve-fitter version 1.0.0\n" );
                }
                break;
            case 'h':
                {
                printf("\n");
                printf("usage: ./fit [--version] [--help] [<file-path> <write/silent> <commands>]\n");
                printf("\n");
                printf("Regression Standard Error, R2, Sum of Squared Errors (SSE)\n");
                printf("and Mean Squared Error (MSE) are returned for all fits.\n");
                printf("\n");
                printf("Write/Export and Silent tags must be set after <file-path> \n");
                printf("and before curve-fitting instructions.\n");
                printf("\t  -w \t\t Write/Export following fitting instructions to file.\n");
                printf("\t  -s \t\t Disable console logging.\n");
                printf("\n");
                printf("Curve-Fitting Commands:\n");
                printf("\t --lin \t\t Linear regression\n");
                printf("\t --exp \t\t Exponential regression\n");
                printf("\t --log \t\t Logarithmic regression (natural logarithm ln)\n");
                printf("\t --pol <int> \t Polynomial Regression, requires input for degree\n");
                printf("\t --all <int> \t all four regression variants,\n");
                printf("\t\t\t requires input for polynomial degree\n");
                printf("\n");
                printf("Fitting commands can be chained, e.g. \"--pol 2 --pol 3 --lin -- exp\"\n");
                printf("\n");
                }
                break;
            case 'i':
                {
                printf("Coefficient nomenclature:\n" );
                printf("    Linear Regression: \t\t y = k * x + d \n");
                printf("    Exponential Regression: \t y = A * exp(k * x) \n");
                printf("    Logarithmic Regression: \t y = d + k * ln(x) \n");
                printf("    Polynomial Regression: \t a[0] + a[1] * x + a[2] * x^2 + ... + a[n]*x^n = y \n");
                }
                break;
            case 's':
                {
                silent = true;
                }
                break;
            case 'w':
                {
                    if (file_path_exists) {
                        write = true;
                        FILE *fp;
                        fp = fopen(export_path, "w");
                            fprintf(fp, "Fit \t\t |     Std. Error    | \t R2 \t | \t SSE \t | \t MSE \t | \t Coefficients \n");
                            fprintf(fp, "–––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––\n");
                            fprintf(fp, "\n");
                        fclose(fp);

                        printf("\n");
                        printf("Results exported to %s", export_path);
                        printf("\n");
                    } else {
                        no_file_path_error();
                    }
                }
                break;
            case 'a':
                if (file_path_exists) {
                    lin_coefficients linCoefficients = linearRegression(records, numOfEntries);
                    error_t lin = calculate_error_lin(linCoefficients, records, numOfEntries, 0);
                    
                    lin_coefficients expCoefficients = exponentialRegression(records, numOfEntries);
                    error_t exp = calculate_error_lin(expCoefficients, records, numOfEntries, 1);

                    lin_coefficients logCoefficients = logarithmicRegression(records, numOfEntries);
                    error_t log = calculate_error_lin(logCoefficients, records, numOfEntries, 2);

                    int degree = atoi(optarg);
                    if (degree == 0) {
                        fprintf(stderr, "invalid -pol option \"%s\" - expecting an integer\n", 
                        optarg?optarg:"");
                        exit(EXIT_FAILURE);
                        }
                    double coefficients[degree + 1];
                    polynomialRegression(records, numOfEntries, coefficients, degree);
                    error_t poly = calculate_error_poly(coefficients, records, numOfEntries, degree);
                    
                    if (!silent) {
                        if (!header_printed) {
                            print_header();
                            header_printed = true;
                        }
                        print_result_lin(linCoefficients, lin, 0);
                        print_result_lin(expCoefficients, exp, 1);
                        print_result_lin(logCoefficients, log, 2);
                        print_result_poly(coefficients, poly, degree);
                    }

                    if (write) {
                        write_lin(export_path, linCoefficients, lin, 0);
                        write_lin(export_path, expCoefficients, exp, 1);
                        write_lin(export_path, logCoefficients, log, 2);
                        write_poly(export_path, coefficients, poly, degree);
                    }
                } else {
                    no_file_path_error();
                }
                break;
            case '0':
                if (file_path_exists) {
                    lin_coefficients linCoefficients = linearRegression(records, numOfEntries);
                    error_t lin = calculate_error_lin(linCoefficients, records, numOfEntries, 0);
                    if (!silent) print_result_lin(linCoefficients, lin, 0);
                    if (write) write_lin(export_path, linCoefficients, lin, 0);
                }
                break;
            case '1': 
                if (file_path_exists) {
                    lin_coefficients expCoefficients = exponentialRegression(records, numOfEntries);
                    error_t exp = calculate_error_lin(expCoefficients, records, numOfEntries, 1);
                    if (!silent) {
                        if (!header_printed) {
                            print_header();
                            header_printed = true;
                        }
                        print_result_lin(expCoefficients, exp, 1);
                    }
                    if (write) write_lin(export_path, expCoefficients, exp, 1);
                } else {
                    no_file_path_error();
                }
                break;
            case '2': 
                if (file_path_exists) {
                    lin_coefficients logCoefficients = logarithmicRegression(records, numOfEntries);
                    error_t log = calculate_error_lin(logCoefficients, records, numOfEntries, 2);
                    if (!silent) {
                        if (!header_printed) {
                            print_header();
                            header_printed = true;
                        }
                        print_result_lin(logCoefficients, log, 2); 
                        }
                    if (write) write_lin(export_path, logCoefficients, log, 2);
                } else {
                    no_file_path_error();
                }
                break;
            case 'p': 
                if (file_path_exists) {
                    int degree = atoi(optarg);
                    if (degree == 0) {
                        fprintf(stderr, "invalid -pol option \"%s\" - expecting an integer\n", 
                        optarg?optarg:"");
                        exit(EXIT_FAILURE);
                        }
                    double coefficients[degree + 1];
                    polynomialRegression(records, numOfEntries, coefficients, degree);
                    error_t poly = calculate_error_poly(coefficients, records, numOfEntries, degree);
                    if (!silent) {
                        if (!header_printed) {
                            print_header();
                            header_printed = true;
                        }
                        print_result_poly(coefficients, poly, degree);
                    }
                    if (write) write_poly(export_path, coefficients, poly, degree);
                } else {
                    no_file_path_error();
                }
                break;
        }
    }
    /* for (long i = 1; i < numOfEntries; i++) {
        printf("%lf, %lf\n", records[i].X, records[i].Y);
    } */

    // double alpha = 1;
    // int maxDegree = 12;
    // int degree = bestPolynomialFit(records, numOfEntries, maxDegree, alpha);

    return 0;
}

