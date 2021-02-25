#ifndef READ_CSV
#define READ_CSV

#include "type_definitions.h"

void no_file_path_error();
void create_filepath(char *filepath, char *original_filename);
long int findSize(char *filename);
int readCSV(char *filename, record_t* records, header_t* header);
void write_lin(char *filepath, lin_coefficients coefficients, error_t errors, int mode);
void write_poly(char *filepath, double *coefficients, error_t errors, int degree);

#endif