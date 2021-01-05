#include "type_definitions.h"
#include <math.h>

record_t sumXY(record_t *recordP, long int numOfEntries) {
    record_t sum;

    sum.X = 0;
    sum.Y = 0;
    for (int i = 0; i < numOfEntries; i ++) {
        sum.X += recordP[i].X;
        sum.Y += recordP[i].Y;
    }
    return sum;
}

record_t powerSumXY(record_t *recordP, long int numOfEntries) {
    record_t powerSum;

    powerSum.X = 0;
    powerSum.Y = 0;
    for (int i = 0; i < numOfEntries; i ++) {
        powerSum.X += recordP[i].X * recordP[i].X;
        powerSum.Y += recordP[i].Y * recordP[i].Y;
    }
    return powerSum;
}

double sumProductXY(record_t *recordP, long int numOfEntries) {
    double sumProductXY = 0;

    for (int i = 0; i < numOfEntries; i ++) {
        sumProductXY += recordP[i].X * recordP[i].Y;
    }
    return sumProductXY;
}

double linear(double x, double k, double d) {
    double y = k * x + d;
    return y;
}

double exponential(double x, double k, double A) {
    double y = A * exp(k * x);
    return y;
}

double logarithmic(double x, double k, double d) {
    double y = k * log(x) + d;
    return y;
}

double polynomial(double x, double *coefficients, long int degree) {
    record_t terms[degree + 1];
    terms[0].X = 1;
    terms[0].Y = coefficients[0];

    for (int i = 1; i <= degree; i++) {
        terms[i].X = terms[i-1].X * x;
        terms[i].Y = coefficients[i];
    }

    double y = 0;
    for (int j = 0; j <= degree; j++ ) {
        y = y + terms[j].X * terms[j].Y;
    }

    return y;
}