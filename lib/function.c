#include <stdio.h>
#include "../head/function.h"
#include "../head/storage.h"

double disp(int count, double *a)
{
int i;
double disp = 0.0, sr;
sr = avg(count, a);
for (i = 0; i < count; i ++)
	disp = disp + (a[i] - sr) * (a[i] - sr);
disp = disp / (count - 1);
return disp;
}

double avg(int count, double *a) 
{
int i;
double sr = 0.0;
for (i = 0; i < count; i ++) 
	sr = sr + a[i];
sr = sr / count;
return sr;
}

void ls (vector_t ** vectors)
{
  vector_t ** ptr = vectors;
  printf ("Vectors list:\n");
 if (ptr) {
  while ( *ptr )
  {
    printf( "Name: %s; size: %d \n", (*ptr)->name, (*ptr)->size );
    ptr++;
  }
 }
}


void help ( void ) {
   printf("List of commands:\n");
   printf("avg(name_of_vector)                  Search for average of vector with the name name_of_vector and print\n");
   printf("                                     it on the screen\n");
   printf("delete(name_of_vector)               Delete vector with name name_of_vector\n");
   printf("disp(name_of vector)                 Search for variance (dispersion) of vector with the name name_of_vector\n");
   printf("                                     and print it on the screen\n");
   printf("gnuplot(command)                     Send command to gnuplot\n");
   printf("help                                 Print on the screen information about different commands\n");
   printf("load(name_of_file)                   Load csv file to input\n");
   printf("ls                                   Print on the screen list of vectors and their sizes\n");
   printf("plot vector_1 vector_2 name_of_file N.\n");
   printf("                                     Build dependance vector_1 from vector_2 and save graphic to name_of_file\n");
   printf("                                     If name_of_file == wxt, print graphic on the screen\n");
   printf("                                     N = {-1, 0, 1} -1 = non-approximation, 0 = average, 1 = linear\n");  
   printf("print(name_of_vector)                Print on the screen vector with the name name_of_vector\n");
   printf("save(name_of_file)                   Save all vectors in file with name name_of_file\n");
   printf("quit                                 Exit\n");
   printf("\n");
   printf("X = [arg1, arg2, .. , argn]          Create new or rewrite vector with the name X and fill it\n");
   printf("                                     with arg1, .. , argn\n");
   printf("Attention: arg1, arg2, .. , argn must be the type of integer or double!!!\n");
   printf("\n");
}

