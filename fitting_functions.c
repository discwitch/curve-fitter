#include "type_definitions.h"
#include "calculations.h"
#include "fit_assessment.h"
#include <math.h>

lin_coefficients linearRegression(record_t *recordP, long int numOfEntries) {
    lin_coefficients coefficients;

    record_t sums = sumXY(recordP, numOfEntries);
    record_t powerSums = powerSumXY(recordP, numOfEntries);
    double sumProduct = sumProductXY(recordP, numOfEntries);

    coefficients.k = (numOfEntries * sumProduct - sums.X * sums.Y) / (numOfEntries * powerSums.X - sums.X * sums.X); // k
    coefficients.d = (sums.Y * powerSums.X - sums.X * sumProduct ) / ( numOfEntries * powerSums.X - sums.X * sums.X); // d

    return coefficients;
}

lin_coefficients exponentialRegression(record_t *recordP, long int numOfEntries) {
    record_t convertToLinear[numOfEntries];

    for (int i = 0; i < numOfEntries; i ++) {
        convertToLinear[i].X = recordP[i].X;
        convertToLinear[i].Y = log(recordP[i].Y);
    }

    lin_coefficients expCoefficients = linearRegression(convertToLinear, numOfEntries);
    expCoefficients.d = exp(expCoefficients.d);

    return expCoefficients;
}

lin_coefficients logarithmicRegression(record_t *recordP, long int numOfEntries) {
    record_t convertToLinear[numOfEntries];

    for (int i = 0; i < numOfEntries; i ++) {
        convertToLinear[i].X = log(recordP[i].X);
        convertToLinear[i].Y = recordP[i].Y;
    }

    lin_coefficients logCoefficients = linearRegression(convertToLinear, numOfEntries);
    return logCoefficients;
}

lin_coefficients doubleExponentialRegression(record_t *recordP, long int numOfEntries) {
    record_t convertToLinear[numOfEntries];

    for (int i = 0; i < numOfEntries; i ++) {
        convertToLinear[i].X = log(recordP[i].X);
        convertToLinear[i].Y = log(recordP[i].Y);
    }

    lin_coefficients expCoefficients = linearRegression(convertToLinear, numOfEntries);
    return expCoefficients;
}

void polynomialRegression(record_t *recordP, long int numOfEntries, double *coefficients, int degree) {

    int n = degree + 1;
    double matrix_entries[2*degree + 1];
    double extended_Y[n];
    double matrix[n*(n+1)];

    power_arrays(recordP, numOfEntries, matrix_entries, extended_Y, degree);
    create_extended_matrix(matrix, matrix_entries, extended_Y, n);
    gaussian_elimination(n, matrix, coefficients);
}

int bestPolynomialFit(record_t *recordP, long int numOfEntries, int maxDegree, double alpha) {
    int degree;
    double RSSE, newRSSE;
    for (int k = 2; k < maxDegree; k += 1) {
        double coefficients[k+1];
        polynomialRegression(recordP, numOfEntries, coefficients, k);
        newRSSE = rsse_poly(coefficients, recordP, numOfEntries, k, alpha);
        if (k == 2) { 
            RSSE = newRSSE;
            degree = k;
        } else if (newRSSE < RSSE) {
            RSSE = newRSSE;
            degree = k;
        }
    }
    return degree;
}