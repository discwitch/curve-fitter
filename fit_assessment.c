#include "type_definitions.h"
#include "calculations.h"
#include <math.h>

double standard_error_regression(lin_coefficients coefficients, record_t *recordP, long int numOfEntries) {
    record_t diff[numOfEntries];

    for (int i = 0; i < numOfEntries; i ++) {
        diff[i].xAxis = linear(recordP[i].xAxis, coefficients.k, coefficients.d);
        diff[i].yAxis = recordP[i].yAxis - diff[i].xAxis;
    }

    record_t sumSquares = powerSumXY(diff, numOfEntries);

    double standardError = sqrt(sumSquares.yAxis / numOfEntries);

    return standardError;
}