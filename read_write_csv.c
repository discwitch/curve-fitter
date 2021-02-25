#include <stdio.h>
#include "type_definitions.h"
#include <time.h>
#include <string.h>

void no_file_path_error() {
    printf("No file-path.\n");
}

void create_filepath(char *filepath, char *original_filename) {
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
    strcat(filepath, ".txt");
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

void write_lin(char *filepath, lin_coefficients coefficients, error_t errors, int mode) {


    FILE *fp;

    fp = fopen(filepath, "a");
    if (fp == NULL) {
        fprintf(stderr, "\n");
        fprintf(stderr, "Error opening file\n");
    }
    if (mode == 0) {
        fprintf(fp, "linear\t\t");
        fprintf(fp, "       %0.6lf       %0.6lf\t   %0.6lf    %0.6lf", errors.std_error, errors.r_squared, errors.sse, errors.mse);
        fprintf(fp, "    d = %lf, k = %lf\n", coefficients.d, coefficients.k);
    } else if (mode == 1){
        fprintf(fp, "exponential\t");
        fprintf(fp, "       %0.6lf       %0.6lf\t   %0.6lf    %0.6lf", errors.std_error, errors.r_squared, errors.sse, errors.mse);
        fprintf(fp, "    A = %lf, k = %lf\n", coefficients.d, coefficients.k);
    } else if (mode == 2){
        fprintf(fp, "logarithmic\t");
        fprintf(fp, "       %0.6lf       %0.6lf\t   %0.6lf    %0.6lf", errors.std_error, errors.r_squared, errors.sse, errors.mse);
        fprintf(fp, "    d = %lf, k = %lf\n", coefficients.d, coefficients.k);        
    }
    fclose(fp);
}

void write_poly(char *filepath, double *coefficients, error_t errors, int degree) {

    FILE *fp;

    fp = fopen(filepath, "a");
    if (fp == NULL) {
        fprintf(stderr, "\n");
        fprintf(stderr, "Error opening file\n");
    }
    fprintf(fp, "polynomial: %i\t", degree);
    fprintf(fp, "       %0.6lf       %0.6lf\t   %0.6lf    %0.6lf", errors.std_error, errors.r_squared, errors.sse, errors.mse);
    fprintf(fp, "    ");
    for(int i=0; i<degree+1; i++)
	{
	    fprintf(fp, "a[%d] = %lf", i, coefficients[i]);
        if (i != degree) fprintf(fp, ", ");
	}
    fprintf(fp, "\n");
    fclose(fp);
}