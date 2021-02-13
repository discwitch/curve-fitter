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

double standard_error_poly(double *coefficients, record_t *recordP, long int numOfEntries, int degree) {
    record_t diff[numOfEntries];

    for (int i = 0; i < numOfEntries; i ++) {
        diff[i].X = polynomial(recordP[i].X, coefficients, degree);
        diff[i].Y = recordP[i].Y - diff[i].X;
    }

    record_t sumSquares = powerSumXY(diff, numOfEntries);

    double standard_error_poly = sqrt(sumSquares.Y / numOfEntries);

    return standard_error_poly;
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

    record_t residuals[numOfEntries];
    for (int i = 0; i < numOfEntries; i ++) {
        residuals[i].X = Y_modelY[i].X - meanY;
        residuals[i].Y = Y_modelY[i].Y - mean_modelY;
    }

    record_t SQT_SQE = powerSumXY(residuals, numOfEntries);

    double r_squared = SQT_SQE.Y / SQT_SQE.X;

    return r_squared;
}

double r_squared_poly(double* coefficients, record_t *recordP, long int numOfEntries, int degree) {
    record_t Y_modelY[numOfEntries];
    for (int i = 0; i < numOfEntries; i ++) {
        Y_modelY[i].X = recordP[i].Y;
        Y_modelY[i].Y = polynomial(recordP[i].X, coefficients, degree);        
    }

    record_t sums_Y_modelY = sumXY(Y_modelY, numOfEntries);
    double meanY = sums_Y_modelY.X / numOfEntries;
    double mean_modelY = sums_Y_modelY.Y / numOfEntries;

    record_t residuals[numOfEntries];
    for (int i = 0; i < numOfEntries; i ++) {
        residuals[i].X = Y_modelY[i].X - meanY;
        residuals[i].Y = Y_modelY[i].Y - mean_modelY;
    }

    record_t SQT_SQE = powerSumXY(residuals, numOfEntries);

    double r_squared_poly = SQT_SQE.Y / SQT_SQE.X;

    return r_squared_poly;
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

double sse_poly(double *coefficients, record_t *recordP, long int numOfEntries, int degree) {
    record_t diff_modelY[numOfEntries];

    for (int i = 0; i < numOfEntries; i ++) {
        diff_modelY[i].Y = polynomial(recordP[i].X, coefficients, degree);        
        diff_modelY[i].X = recordP[i].Y - diff_modelY[i].Y;
    }

    record_t powerSums_diff_modelY = powerSumXY(diff_modelY, numOfEntries);

    return powerSums_diff_modelY.X;
}

double mse(lin_coefficients coefficients, record_t *recordP, long int numOfEntries, int mode) {
    double sum_squared_errors = sse(coefficients, recordP, numOfEntries, mode);
    return sum_squared_errors / numOfEntries;
}

double mse_poly(double *coefficients, record_t *recordP, long int numOfEntries, int degree) {
    double sum_squared_errors = sse_poly(coefficients, recordP, numOfEntries, degree);
    return sum_squared_errors / numOfEntries;
}

double rsse_poly(double *coefficients, record_t *recordP, long int numOfEntries, int degree, double alpha) {
    double sum_squared_errors = sse_poly(coefficients, recordP, numOfEntries, degree);
    double coefficients_squared_sum = 0;
    for (int i = 0; i < degree +1; i++) {
        coefficients_squared_sum += coefficients[i] * coefficients[i];
    }
    return sum_squared_errors + alpha * coefficients_squared_sum;
}

error_t calculate_error_lin(lin_coefficients coefficients, record_t *recordP, long int numOfEntries, int mode) {
    error_t errors;
    errors.std_error = standard_error(coefficients, recordP, numOfEntries, mode);
    errors.r_squared = r_squared(coefficients, recordP, numOfEntries, mode);
    errors.sse = sse(coefficients, recordP, numOfEntries, mode);
    errors.mse = mse(coefficients, recordP, numOfEntries, mode);
    return errors;
}

error_t calculate_error_poly(double *coefficients, record_t *recordP, long int numOfEntries, int degree) {
    error_t errors;
    errors.std_error = standard_error_poly(coefficients, recordP, numOfEntries, degree);
    errors.r_squared = r_squared_poly(coefficients, recordP, numOfEntries, degree);
    errors.sse = sse_poly(coefficients, recordP, numOfEntries, degree);
    errors.mse = mse_poly(coefficients, recordP, numOfEntries, degree);
    return errors;
}