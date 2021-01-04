#ifndef TYPE_DEFINITIONS
#define TYPE_DEFINITIONS

typedef struct {
    double X;
    double Y;
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