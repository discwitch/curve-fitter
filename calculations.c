#include "type_definitions.h"

record_t sumXY(record_t *recordP, long int numOfEntries) {
    record_t sum;

    sum.xAxis = 0;
    sum.yAxis = 0;
    for (int i = 0; i < numOfEntries; i ++) {
        sum.xAxis += recordP[i].xAxis;
        sum.yAxis += recordP[i].yAxis;
    }
    return sum;
}

record_t powerSumXY(record_t *recordP, long int numOfEntries) {
    record_t powerSum;

    powerSum.xAxis = 0;
    powerSum.yAxis = 0;
    for (int i = 0; i < numOfEntries; i ++) {
        powerSum.xAxis += recordP[i].xAxis * recordP[i].xAxis;
        powerSum.yAxis += recordP[i].yAxis * recordP[i].yAxis;
    }
    return powerSum;
}

double sumProductXY(record_t *recordP, long int numOfEntries) {
    double sumProductXY = 0;

    for (int i = 0; i < numOfEntries; i ++) {
        sumProductXY += recordP[i].xAxis * recordP[i].yAxis;
    }
    return sumProductXY;
}

double linear(double x, double k, double d) {
    double y = k * x + d;
    return y;
}