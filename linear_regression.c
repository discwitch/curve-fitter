#include "type_definitions.h"
#include "calculations.h"

lin_coefficients linearRegression(record_t *recordP, long int numOfEntries) {
    lin_coefficients coefficients;

    record_t sums = sumXY(recordP, numOfEntries);
    record_t powerSums = powerSumXY(recordP, numOfEntries);
    double sumProduct = sumProductXY(recordP, numOfEntries);

    coefficients.k = (numOfEntries * sumProduct - sums.xAxis * sums.yAxis) / (numOfEntries * powerSums.xAxis - sums.xAxis * sums.xAxis); // k
    coefficients.d = (sums.yAxis - coefficients.k*sums.xAxis) / numOfEntries; // d

    return coefficients;
}