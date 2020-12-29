#ifndef TYPE_DEFINITIONS
#define TYPE_DEFINITIONS

typedef struct {
    double xAxis;
    double yAxis;
} record_t;

typedef struct {
    double k;
    double d;
} lin_coefficients;

typedef struct {
    char col1[64];
    char col2[64];
} header_t;

#endif