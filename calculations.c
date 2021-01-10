#include "type_definitions.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

record_t sumXY(record_t *recordP, long int numOfEntries) {
    record_t sum;

    sum.X = 0;
    sum.Y = 0;
    for (int i = 0; i < numOfEntries; i ++) {
        sum.X += recordP[i].X;
        sum.Y += recordP[i].Y;
    }
    return sum;
}

record_t powerSumXY(record_t *recordP, long int numOfEntries) {
    record_t powerSum;

    powerSum.X = 0;
    powerSum.Y = 0;
    for (int i = 0; i < numOfEntries; i ++) {
        powerSum.X += recordP[i].X * recordP[i].X;
        powerSum.Y += recordP[i].Y * recordP[i].Y;
    }
    return powerSum;
}

double sumProductXY(record_t *recordP, long int numOfEntries) {
    double sumProductXY = 0;

    for (int i = 0; i < numOfEntries; i ++) {
        sumProductXY += recordP[i].X * recordP[i].Y;
    }
    return sumProductXY;
}

double linear(double x, double k, double d) {
    double y = k * x + d;
    return y;
}

double exponential(double x, double k, double A) {
    double y = A * exp(k * x);
    return y;
}

double logarithmic(double x, double k, double d) {
    double y = k * log(x) + d;
    return y;
}

double polynomial(double x, double *coefficients, long int degree) {
    record_t terms[degree + 1];
    terms[0].X = 1;
    terms[0].Y = coefficients[0];

    for (int i = 1; i <= degree; i++) {
        terms[i].X = terms[i-1].X * x;
        terms[i].Y = coefficients[i];
    }

    double y = 0;
    for (int j = 0; j <= degree; j++ ) {
        y = y + terms[j].X * terms[j].Y;
    }

    return y;
}

void gaussian_elimination(int n, double *matrix)
{   
    double a[n+1][n+2], x[n+1], ratio;
	int i, j, k;

    for (int l = 1; l <= n; l++){
        for (int m = 1; m <= n+1; m++) {
            a[l][m] = matrix[(l-1)*(n + 1) + (m-1)];
            printf("%lf   ", a[l][m]);
        }
        printf("\n");
    }

	
	/* Applying Gauss Elimination */
	for(i=1;i<=n-1;i++)
	 {
		  if(a[i][i] == 0.0)
		  {
			   printf("Mathematical Error!");
			   exit(0);
		  }
		  for(j=i+1;j<=n;j++)
		  {
			   ratio = a[j][i]/a[i][i];
			   
			   for(k=1;k<=n+1;k++)
			   {
			  		a[j][k] = a[j][k] - ratio*a[i][k];
			   }
		  }
	 }
	 /* Obtaining Solution by Back Subsitution */
	 x[n] = a[n][n+1]/a[n][n];
	
	 for(i=n-1;i>=1;i--)
	 {
		  x[i] = a[i][n+1];
		  for(j=i+1;j<=n;j++)
		  {
		  		x[i] = x[i] - a[i][j]*x[j];
		  }
		  x[i] = x[i]/a[i][i];
	 }
	 /* Displaying Solution */ 
	 printf("\nSolution:\n");
	 for(i=1;i<=n;i++)
	 {
	  	printf("x[%d] = %0.3lf\n",i, x[i]);
	 }
    }