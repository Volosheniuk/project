#include "../head/plot.h"
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

// Plot array
void gplot_vector(vector_t *A, vector_t *B, const char *output, int N) {
	FILE *gp = popen("gnuplot", "w");
	unsigned int sleep_time = 10;
	fprintf(gp, "load \"../system/setup.gp\"\n");
	if (output) {
		fprintf(gp, "set term postscript\n", output); 
		fprintf(gp, "set output \"%s.eps\"\n", output); 
		sleep_time = 0;
	} else { 
		fprintf(gp, "set term x11\n"); 
	}
	fprintf(gp, "set xlabel \"%s\"\n set ylabel \"%s\"\n", B->name, A->name);
	
	if (N < 0) {
		fprintf(gp, "plot '-' title \"%s(%s)\"\n", A->name, B->name);
	}
	if (N == 0) {
		double avg = averange(A->vals, A->size);
		fprintf(gp, "plot %lg, '-' title \"%s(%s)\"\n", avg, A->name, B->name);
	}
	if (N == 1) {
		double a1, a0;
		approx_linear(A->vals, B->vals, min(A->size, B->size), &a1, &a0);
		fprintf(gp, "plot %lg*x+%lg, '-' title \"%s(%s)\"\n", a1, a0, A->name, B->name);   
	}
	unsigned int i;
	for (i = 0; i < min(A->size, B->size); i++) {
		fprintf(gp, "%lg %lg\n", B->vals[i], A->vals[i]);
	}
	fprintf(gp, "e\n");
	fflush(gp);
	sleep(sleep_time);	
	pclose(gp);
	return;
}
// Command
void gcmd(char const *cmd, ...) {
        FILE *gp;
        if ( !(gp = popen("gnuplot", "w")) ) 
                {return;}
        va_list ap;
        va_start(ap, cmd);
        vfprintf(gp, cmd, ap);
        va_end(ap);
        fputs("\n", gp);
        fflush(gp);
        pclose(gp);
        return;
}



// Approximation with polynom degree N (N >= 0)
void approx_polynom(double *A, double *B, int N, double *a) {
	
	return;
}

void approx_linear(double *A, double *B, int n, double *k, double *b) {
	int i = 0;	
	double x = 0.0, y = 0.0, xy = 0.0, x2 = 0.0, y2 = 0.0;
	for (i = 0; i < n; i++) {
		x += *(B+i);
		y += *(A+i);
		x2 += sqr(*(B+i));
		y2 += sqr(*(A+i));
		xy += ( (*(B+i))*(*(A+i)) );
	}
	x = x/n;	y = y/n;
	x2 = x2/n;	y2 = y2/n;
	xy = xy/n;
	*k = (xy - x*y)/(x2 - sqr(x));
	*b = y - (*k)*x;
}
double averange(double *A, int n) {
	int i = 0;
	double a = 0.0;
	for (i = 0; i < n; i++) {
		a += A[i];
	}
	a = a/n;
	printf("%lg", a);
	return a;
}
double sqr(double a) {
	return a*a;
}
