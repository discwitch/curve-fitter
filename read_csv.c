#include <stdio.h>
#include "type_definitions.h"

long int findSize(void) 
{ 
  FILE *fp;
  fp=fopen("CovidFaelle_Wien_juni_dez.csv", "r");
  long int lines = 0;

  if ( fp == NULL ) {
    return -1;
  }

  while (EOF != (fscanf(fp, "%*[^\n]"), fscanf(fp,"%*c")))
        ++lines;
  
  fclose(fp);

  return lines;
} 

long int readCSV(record_t* recordsP, header_t* headerP) {
    FILE *fp;
    size_t count = 0;

    fp = fopen("CovidFaelle_Wien_juni_dez.csv", "r");
    if (fp == NULL) {
        fprintf(stderr, "Error reading file\n");
        return 0;
    }
    while (count == 0) {
    while (fscanf(fp, "%127[^;\n];%127[^;\n]", headerP -> col1, headerP -> col2) == 2) {
        count++;
    }}

    while (fscanf(fp, " %lf;%lf", &recordsP[count].xAxis, &recordsP[count].yAxis) == 2) {
        count++;
    }

    fclose(fp);

    return count - 1;
}