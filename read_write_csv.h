#ifndef READ_CSV
#define READ_CSV

#include "type_definitions.h"

long int findSize(char *filename);
int readCSV(char *filename, record_t* records, header_t* header);

#endif