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
        fprintf(fp, "~~~~~~~~ LINEAR REGRESSION: y = kx * d ~~~~~~~~\n");
        fprintf(fp, "\n");
        fprintf(fp, "Linear Coefficients: k = %lf, d = %lf\n", coefficients.k, coefficients.d);
    } else if (mode == 1){
        fprintf(fp, "~~~~~~~~ EXPONENTIAL REGRESSION: y = A * exp(kx) ~~~~~~~~\n");
        fprintf(fp, "\n");
        fprintf(fp, "Exponential Coefficients: A = %lf, k = %lf\n", coefficients.d, coefficients.k);
    } else if (mode == 2){
        fprintf(fp, "~~~~~~~~ LOGARITHMIC REGRESSION: y = d + k * ln(x) ~~~~~~~~\n");
        fprintf(fp, "\n");
        fprintf(fp, "Logarithmic Coefficients: d = %lf, k = %lf\n", coefficients.d, coefficients.k);        
    }
    fprintf(fp, "\n");
    fprintf(fp, "Regression Standard Error: %lf\n", errors.std_error);
    fprintf(fp, "Regression R2: %lf\n", errors.r_squared);
    fprintf(fp, "SSE: %lf\n", errors.sse);
    fprintf(fp, "MSE: %lf\n", errors.mse);
    fprintf(fp, "\n");
    fclose(fp);
}

void write_poly(char *filepath, double *coefficients, error_t errors, int degree) {

    FILE *fp;

    fp = fopen(filepath, "a");
    if (fp == NULL) {
        fprintf(stderr, "\n");
        fprintf(stderr, "Error opening file\n");
    }
    fprintf(fp, "~~~~~~~~ POLYNOMIAL REGRESSION: Degree = %i ~~~~~~~~\n", degree);
    fprintf(fp, "\n");
    fprintf(fp, "Coefficients: \n");
    for(int i=0; i<degree+1; i++)
	{
	    fprintf(fp, "a[%d] = %0.3lf\n", i, coefficients[i]);
	}
    fprintf(fp, "\n");
    fprintf(fp, "Regression Standard Error: %lf\n", errors.std_error);
    fprintf(fp, "Regression R2: %lf\n", errors.r_squared);
    fprintf(fp, "SSE: %lf\n", errors.sse);
    fprintf(fp, "MSE: %lf\n", errors.mse);
    fprintf(fp, "\n");
    fclose(fp);
}