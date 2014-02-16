#include "../head/input.h"
#include <stdio.h> 
#include <string.h>
#include <stdlib.h>
#include <math.h>

#ifndef MAXCHARS
  #define MAXCHARS 1024
#endif

int load_csv(vector_t *** vectors, const char * fname)
{  
  int rc = -1, 
	i, 
	fk = 0;
  char str[MAXCHARS];
  char *p;
  vector_t * vec;
  int cnt = 0;
  double val;
  char nm[MAXCHARS];
  int lc = 0;
  vector_t** vecs = 0;
  vector_t ** curr = 0;
  vector_t * vec1 = 0;
 

  FILE* fp = fopen( fname, "r" );
  if ( fp )
  { 
    fgets( str, MAXCHARS, fp );
    for (i = 0; i < strlen(str); i ++) 
      if (str[i] == '"') fk = 1;
    if (fk == 1)
    {
      p = strtok(str, "\"\n");
      
      while ( p )
      { 
        vec = (vector_t*)malloc ( sizeof( vector_t ) );
        vector_init( p, 0, vec );   
        vectors_add( &vecs, vec );
        p = strtok( NULL, "\",\n"); 
      } 
    }
    else
    {
      p = strtok(str, ",\n");

      while ( p )
      {
        cnt++;
        sprintf( nm, "X%d", cnt );
        val = atof( p );
        vec = (vector_t*)malloc ( sizeof( vector_t ) );
        vector_init( nm, 0, vec ); 
	if( !isnan(val) ) 
	{
	  vector_append( vec, 1, &val );
	}
        vectors_add( &vecs, vec ); 

        p = strtok( NULL, ",\n");  
      }
       
    }
    while( fgets( str, MAXCHARS, fp ) )
    {
      if ( strlen(str) )
      {
        p = strtok(str, ",\n");
        i = 0;
        while ( p )
        {
          if ( strlen( p ) )
          {
            val = atof( p );
	    if( !isnan(val) )
	      vector_append( vecs[i], 1, &val );
          }
 	  p = strtok( NULL, ",\n" );
          i++;
        }
      }
    }
    fclose( fp );
    
    curr = vecs;
    
    while (*curr) 
    {
      vec1 = vectors_search( *vectors, (*curr)->name );
      if ( vec1 )
      { 
        vec1->size = (*curr)->size;
        free( vec1->vals );
        vec1->vals = (*curr)->vals;
        free( *curr ); 
      }
      else
      { 
        vectors_add( vectors, *curr );
      }
      curr++;  
    }
    free( vecs );

    rc = 0;
  }
  return rc;
}



int save_csv(vector_t ** vectors, const char * fname)
{  
  int rc = -1;
  int size_max;
  int cnt;
  int i,j;
  FILE* fp;
  
  if ( !vectors )
    return rc;
  
  cnt = vectors_count( vectors );

  fp = fopen( fname, "w" );
  if ( fp )
  {
    
    size_max = vectors[0]->size;
    fprintf( fp, "\"%s\"", vectors[0]->name );
    for ( i=1; i<cnt; i++ )
      {
	if ( vectors[i]->size > size_max ) 
	  size_max = vectors[i]->size;
	fprintf( fp, ",\"%s\"", vectors[i]->name );
      }
    fprintf( fp, "\n" );

    for ( j=0; j<size_max; j++ )
      {
	if ( j < vectors[0]->size )
	  fprintf( fp, "%f", vectors[0]->vals[j] );
	else
	  fprintf( fp, "nan" );
	for ( i=1; i<cnt; i++ )
	  {
	    if ( j < vectors[i]->size )
	      fprintf( fp, ",%f", vectors[i]->vals[j] );
	    else
	      fprintf( fp, ",nan" );
	  }
	fprintf( fp, "\n" );
      }
    fclose( fp );
    rc = 0;
  }
  

  return rc;
} 
