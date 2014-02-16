#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "../head/command.h"
#include "../head/function.h"
#include "../head/storage.h"
#include "../head/input.h"
#include "../head/plot.h"

#define N_MAX 1000

void command(vector_t *** vecs)
{
int terminated = 0;
int i = 0;
int N = 0, rc = 0;
int fr = 0, fsk = 0, fpr = 0, fskkv = 0, fkav = 0, max = 0;
char input[N_MAX];
char *p, *p2, *output;
vector_t * vec, * vec1;
double val;

vector_t ** vectors = *vecs;

while (!terminated) {

  printf("\n> ");
  gets( input );
  
  fr = fsk = fpr = fskkv = 0;
  for (i = 0; i < strlen(input); i ++) {
    if (input[i] == '=') fr = 1;
    if ((input[i] == '(') || (input[i] == ')')) fsk = 1;
    if (input[i] == ' ') fpr = 1;
    if (input[i] == '[') fskkv = 1;
    if (input[i] == '"') fkav = 1;
  }
    
  if ((fr == 0) && (fsk == 0) && (fpr == 0) && (fskkv == 0)) {
    if (strcmp("ls", input) == 0) 
	ls(vectors);

    else if (strcmp("help", input) == 0) 
	help();

    else if (strcmp("quit", input) == 0)
	terminated = 1;

    else printf("Command is not found\n");
  }


  if ((fr == 0) && (fsk == 1)) {
    p = strtok(input, "(");

    if (strcmp(p, "disp") == 0) {
	p = strtok(NULL, ")");
	vec = vectors_search( vectors, p);
	if (vec)
	  printf("dispersion %s = %f\n", p, disp(vec->size, vec->vals));
        else
          printf("ERROR: Parameter '%s' not found\n", p );
    }

    else if (strcmp(p, "avg") == 0) {
	p = strtok(NULL, ")");
	vec = vectors_search( vectors, p);
	if (vec)
	  printf("average %s = %f\n", p, avg(vec->size, vec->vals));
        else
          printf("ERROR: Parameter '%s' not found\n", p );
 
    }

    else if (strcmp(p, "print") == 0) {
	p = strtok(NULL, ")");
	vec = vectors_search( vectors, p);
	if (vec) {
	  printf("Vector %s: \n", p);
	  vector_print(vec);
        }
        else
          printf("ERROR: Parameter '%s' not found\n", p );
 
    }
    
    else if (strcmp(p, "load") == 0)
    {
      p = strtok(NULL, ")");
      rc = load_csv(&vectors, p);
      if (rc == -1) printf("Failed to load file: %s \n", p);
    }

    else if (strcmp(p, "save") == 0)
    {
      p = strtok(NULL, ")");
      rc = save_csv(vectors, p);
      if (rc == -1) printf("Failed to save file: %s \n", p);
    }


    else if (strcmp(p, "delete") == 0)
    {
      p = strtok(NULL, ")");
      vec = vectors_search( vectors, p);
	if (vec) {
	  vectors_remove(&vectors, vec);
        }
        else
          printf("ERROR: Parameter '%s' not found\n", p );
    }

    else if (strcmp(p, "gnuplot") == 0)
    {
      p = strtok(NULL, ")");
      gcmd(p);
    }

    else printf("Command is not found\n");
  } 


  if ((fr == 1) && (fskkv == 1)) {
    p = strtok(input, " =");

    vec = (vector_t*) malloc (sizeof( vector_t ) );
    vector_init( p, 0, vec );
    
    p = strtok(NULL, "= [,]");
    while ( p )
    {
      val = strtod( p, &p2 );
      if ( p == p2 )
      { 
        vector_clear( vec );
        free( vec );
        vec = 0;
        printf( "ERROR: Input data is invalid\n" );
        break;
      }
      else
      {
         vector_append( vec, 1, &val );
      }
      p = strtok(NULL, " ,]");
    }	

    if ( vec )
    {
      vec1 = vectors_search( vectors, vec->name );
      if (vec1) 
      {
	vector_clear( vec1 );
        vector_append( vec1, vec->size, vec->vals );
        vector_clear( vec );
        free( vec );
        vec = 0;
      }
      else
      { 
        vectors_add( &vectors, vec );

      }   
    }		
  }

  if ((fr == 1) && (fskkv == 0))
  {
    for (i = 0; i < vectors_count(vectors); i ++)
      if (max < vectors[i]->size) max = vectors[i]->size;
    printf("%d\n", max);
    printf("%d\n", vectors_count(vectors));
    sergey(vectors, input, max, vectors_count(vectors));
  }

  if ((fpr == 1) && (fskkv == 0) && (fsk == 0))
  {
    p = strtok(input, " ");
    if (strcmp(p, "plot") == 0)
    {
      p = strtok(NULL, " ");
      vec = vectors_search(vectors, p);
      if (vec)
      {
        p = strtok(NULL, " ");
        vec1 = vectors_search(vectors, p);
        if (vec1)
        {
          p = strtok(NULL, " ");
          output = p;
          if (strcmp(p, "wxt") == 0) { output = NULL; }
          p = strtok(NULL, ".");
          N = atoi(p);
          gplot_vector(vec, vec1, output, N);
        }
      }
   }
   else printf("Command is not found\n");
  }
}
 *vecs = vectors;
}
