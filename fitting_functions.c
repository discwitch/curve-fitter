#include "type_definitions.h"
#include "calculations.h"
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

lin_coefficients doubleExponentialRegression(record_t *recordP, long int numOfEntries) {
    record_t convertToLinear[numOfEntries];

    for (int i = 0; i < numOfEntries; i ++) {
        convertToLinear[i].X = log(recordP[i].X);
        convertToLinear[i].Y = log(recordP[i].Y);
    }

    lin_coefficients expCoefficients = linearRegression(convertToLinear, numOfEntries);
    return expCoefficients;
}
