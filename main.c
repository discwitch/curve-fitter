#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include "type_definitions.h"
#include "read_csv.h"
#include "calculations.h"
#include "linear_regression.h"
#include "fit_assessment.h"


int main(void)
{   
    long int size = findSize();
    record_t records[size];
    header_t header;

    long int numOfEntries = readCSV(records, &header);
    lin_coefficients linCoefficients = linearRegression(records, numOfEntries);
    double score = standard_error_regression(linCoefficients, records, numOfEntries);

    /* printf("%s, %s\n", header.col1, header.col2);

    for (long i = 1; i < size - 1; i++) {
        printf("%lf, %lf\n", records[i].xAxis, records[i].yAxis);
    } */

    printf("Linear Coefficients: k = %lf, d = %lf\n", linCoefficients.k, linCoefficients.d);
    printf("Regression Fit Score: %lf\n", score);


    return 0;
}

