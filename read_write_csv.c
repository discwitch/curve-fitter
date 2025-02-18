#include <stdio.h>
#include <stdlib.h>
#include "type_definitions.h"
#include <time.h>
#include <string.h>
#include <stdbool.h>

void no_file_path_error() {
    printf("No file-path.\n");
}

void create_filepath(char *filepath, char *original_filename, bool export_to_csv) {
    time_t timer;
    char buffer[26];
    struct tm* tm_info;
    timer = time(NULL);
    tm_info = localtime(&timer);
    strftime(buffer, 26, "%Y-%m-%d-%H:%M:%S", tm_info);
    
    strcpy(filepath, "./results/");
    strcat(filepath, original_filename);
    strcat(filepath, "-");
    strcat(filepath, buffer);
    if (export_to_csv) {
        strcat(filepath, ".csv");
    } else {
        strcat(filepath, ".txt");
    }
}

long int findSize(char *filename) 
{ 
  FILE *fp;
  fp=fopen(filename, "r");
  long int lines = 0;

  if ( fp == NULL ) {
    return -1;
  }

  while (EOF != (fscanf(fp, "%*[^\n]"), fscanf(fp,"%*c")))
        lines++;
  
  fclose(fp);

  return lines;
} 

long int readCSV(char *filename, record_t* recordsP, header_t* headerP) {
    FILE *fp;
    size_t count = 0;

    fp = fopen(filename, "r");
    if (fp == NULL) {
        fprintf(stderr, "Error reading file\n");
        return 0;
    }
    while (count == 0) {
    while (fscanf(fp, "%127[^;\n];%127[^;\n]", headerP -> col1, headerP -> col2) == 2) {
        count++;
    }}

    while (EOF != (fscanf(fp, "%*[^\n]"), fscanf(fp, "%lf;%lf", &recordsP[count-1].X, &recordsP[count-1].Y))) {
        count++;
    }

    fclose(fp);

    return count - 1;
}

void write_lin(char *filepath, lin_coefficients coefficients, error_t errors, int mode, bool write_to_csv) {


    FILE *fp;

    fp = fopen(filepath, "a");
    if (fp == NULL) {
        fprintf(stderr, "\n");
        fprintf(stderr, "Error opening file\n");
    }
    if (mode == 0) {
        if (write_to_csv) {
            fprintf(fp, "linear;%0.6lf;%0.6lf;%0.6lf;%0.6lf;d = %lf;k = %lf\n", errors.std_error, errors.r_squared, errors.sse, errors.mse, coefficients.d, coefficients.k);
        } else {
            fprintf(fp, "%-20s", "linear");
            fprintf(fp, "%-25.6lf%-25.6lf%-25.6lf%-25.6lf", errors.std_error, errors.r_squared, errors.sse, errors.mse);
            fprintf(fp, "%-sd = %lf, k = %lf\n", "", coefficients.d, coefficients.k);
        }
    } else if (mode == 1){
        if (write_to_csv) {
            fprintf(fp, "exponential;%0.6lf;%0.6lf;%0.6lf;%0.6lf;A = %lf;k = %lf\n", errors.std_error, errors.r_squared, errors.sse, errors.mse, coefficients.d, coefficients.k);
        } else {
            fprintf(fp, "%-20s", "exponential");
            fprintf(fp, "%-25.6lf%-25.6lf%-25.6lf%-25.6lf", errors.std_error, errors.r_squared, errors.sse, errors.mse);
            fprintf(fp, "%-sA = %lf, k = %lf\n", "", coefficients.d, coefficients.k);
        }
    } else if (mode == 2){
        if (write_to_csv) {
            fprintf(fp, "logarithmic;%0.6lf;%0.6lf;%0.6lf;%0.6lf;d = %lf;k = %lf\n", errors.std_error, errors.r_squared, errors.sse, errors.mse, coefficients.d, coefficients.k);
        } else {
            fprintf(fp, "%-20s", "logarithmic");
            fprintf(fp, "%-25.6lf%-25.6lf%-25.6lf%-25.6lf", errors.std_error, errors.r_squared, errors.sse, errors.mse);
            fprintf(fp, "%-sd = %lf, k = %lf\n", "", coefficients.d, coefficients.k);
        }       
    }
    fclose(fp);
}

void write_poly(char *filepath, double *coefficients, error_t errors, int degree, bool write_to_csv) {

    FILE *fp;

    fp = fopen(filepath, "a");
    if (fp == NULL) {
        fprintf(stderr, "\n");
        fprintf(stderr, "Error opening file\n");
    }
    if (write_to_csv)
    {   
        fprintf(fp, "polynomial: %i;%0.6lf;%0.6lf;%0.6lf;%0.6lf;", degree, errors.std_error, errors.r_squared, errors.sse, errors.mse);
        for(int i=0; i<degree+1; i++)
	    {
            fprintf(fp, "a[%d] = %lf", i, coefficients[i]);
            if (i != degree) fprintf(fp, ";");
	    }
        fprintf(fp, "\n");
    } else {
        fprintf(fp, "%-12s%-8i", "polynomial: ", degree);
        fprintf(fp, "%-25.6lf%-25.6lf%-25.6lf%-25.6lf", errors.std_error, errors.r_squared, errors.sse, errors.mse);
        fprintf(fp, "%-s", "");
        for(int i=0; i<degree+1; i++)
        {
            fprintf(fp, "a[%d] = %lf", i, coefficients[i]);
            if (i != degree) fprintf(fp, ", ");
        }
        fprintf(fp, "\n");
    }
    fclose(fp);
}

bool poly_parse(char *input_string, poly_t *limits) {
    char delim[] = ":";
    if (strlen(input_string) <= 2 || strchr(input_string, ':') == 0) {
        return false;
    }

	char *ptr = strtok(input_string, delim);
	limits -> begin = atoi(ptr);
    ptr = strtok(NULL, delim);
    limits -> end = atoi(ptr);

    if (limits->begin != 0 && limits->end != 0) {
        return true;
    } else return false;
}