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

typedef struct {
    double std_error;
    double r_squared;
    double sse;
    double mse;
} error_t;
typedef struct {
    char filename[64];
    char limiter[1];
    char mode[3];
    int degree;
    int automatic;
    int write;
} args_t;

#endif