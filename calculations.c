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

double logarithmic(double x, double k, double A) {
    double y = k * log(x) + A;
    return y;
}