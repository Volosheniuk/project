#include <stdio.h>
#include "storage.h"

// Plots arrays
void gplot_vector(vector_t *A, vector_t *B, const char *output, int N);
// Send command to GNUplot
void gcmd(const char *cmd, ...);

// Approximation with polynom degree N (N >= 0)
void approx_polynom(double *A, double *B, int N, double *a);
// Linear approximation: y = kx + b
void approx_linear(double *A, double *B, int n, double *k, double *b);
// Averange value
double averange(double *A, int n);
// Other
double sqr(double a);
#define min(a, b) ((a) > (b) ? (b) : (a))



