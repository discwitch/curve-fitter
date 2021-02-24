#ifndef READ_CSV
#define READ_CSV

#include "type_definitions.h"

void create_filename(char *filename, header_t header);
long int findSize(char *filename);
int readCSV(char *filename, record_t* records, header_t* header);
void write_lin(char *filename, lin_coefficients coefficients, error_t errors, int mode);
void write_poly(char *filename, double *coefficients, error_t errors, int degree);

#endif