#ifndef READ_CSV
#define READ_CSV

#include "type_definitions.h"
#include <stdbool.h>

void no_file_path_error();
void create_filepath(char *filepath, char *original_filename, bool export_to_csv);
long int findSize(char *filename);
int readCSV(char *filename, record_t* records, header_t* header);
void write_lin(char *filepath, lin_coefficients coefficients, error_t errors, int mode, bool write_to_csv);
void write_poly(char *filepath, double *coefficients, error_t errors, int degree, bool write_to_csv);
bool poly_parse(char *input_string, poly_t *limits);

#endif