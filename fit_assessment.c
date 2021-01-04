#include "type_definitions.h"
#include "calculations.h"
#include <math.h>

double standard_error(lin_coefficients coefficients, record_t *recordP, long int numOfEntries, int mode) {
    record_t diff[numOfEntries];

    for (int i = 0; i < numOfEntries; i ++) {
        switch (mode)
        {
            case 0: 
                diff[i].X = linear(recordP[i].X, coefficients.k, coefficients.d);
                break;
            case 1:
                diff[i].X = exponential(recordP[i].X, coefficients.k, coefficients.d);
                break;
            case 2:
                diff[i].X = logarithmic(recordP[i].X, coefficients.k, coefficients.d);
                break;
        }
        diff[i].Y = recordP[i].Y - diff[i].X;
    }

    record_t sumSquares = powerSumXY(diff, numOfEntries);

    double standard_error = sqrt(sumSquares.Y / numOfEntries);

    return standard_error;
}

double r_squared(lin_coefficients coefficients, record_t *recordP, long int numOfEntries, int mode) {
    record_t Y_modelY[numOfEntries];
    for (int i = 0; i < numOfEntries; i ++) {
        Y_modelY[i].X = recordP[i].Y;
        switch (mode)
        {
            case 0: 
                Y_modelY[i].Y = linear(recordP[i].X, coefficients.k, coefficients.d);
                break;
            case 1:
                Y_modelY[i].Y = exponential(recordP[i].X, coefficients.k, coefficients.d);
                break;
            case 2:
                Y_modelY[i].Y = logarithmic(recordP[i].X, coefficients.k, coefficients.d);
                break;
        }
    }

    record_t sums_Y_modelY = sumXY(Y_modelY, numOfEntries);
    double meanY = sums_Y_modelY.X / numOfEntries;
    double mean_modelY = sums_Y_modelY.Y / numOfEntries;

    record_t residuums[numOfEntries];
    for (int i = 0; i < numOfEntries; i ++) {
        residuums[i].X = Y_modelY[i].X - meanY;
        residuums[i].Y = Y_modelY[i].Y - mean_modelY;
    }

    record_t SQT_SQE = powerSumXY(residuums, numOfEntries);

    double r_squared = SQT_SQE.Y / SQT_SQE.X;

    return r_squared;
}

double sse(lin_coefficients coefficients, record_t *recordP, long int numOfEntries, int mode) {
    record_t diff_modelY[numOfEntries];

    for (int i = 0; i < numOfEntries; i ++) {
        switch (mode)
        {
            case 0: 
                diff_modelY[i].Y = linear(recordP[i].X, coefficients.k, coefficients.d);
                break;
            case 1:
                diff_modelY[i].Y = exponential(recordP[i].X, coefficients.k, coefficients.d);
                break;
            case 2:
                diff_modelY[i].Y = logarithmic(recordP[i].X, coefficients.k, coefficients.d);
                break;
        }
        diff_modelY[i].X = recordP[i].Y - diff_modelY[i].Y;
    }

    record_t powerSums_diff_modelY = powerSumXY(diff_modelY, numOfEntries);

    return powerSums_diff_modelY.X;
}