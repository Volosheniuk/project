#include "../head/storage.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int vector_init( const char* name, unsigned int size, vector_t * vector )
{
  // Check input arguments
  if ( !name || !vector )
    return -1;

  strncpy( vector->name, name, MAXCHARS );

  vector->size = 0;
  vector->vals = 0;

  if ( size )
    return vector_realloc( vector, size );

  return 0;
}

/// Vector deinitialization
int vector_clear( vector_t * vector )
{
  // Check input arguments
  if ( !vector )
    return -1;
  
  if ( vector->vals )
  {
     free( vector->vals );
     vector->vals = 0;
     vector->size = 0;
  }

  return 0;
}

/// Reallocate memory for values
int vector_realloc( vector_t * vector, unsigned int size )
{
   // Check input arguments
  if ( !vector )
    return -1;
  
  vector->size = size;
  vector->vals = (double*) realloc( vector->vals, size * sizeof(double) );

  return 0;
}

/// Append value(s) to vector
int vector_append( vector_t * vector, unsigned int cnt, double * vals )
{
  int rc = -1;
  int i;

  if ( !vector || !vals )
    return -1;

  rc = vector_realloc( vector, vector->size + cnt );

  if ( rc == 0 )
  {
    for( i = 0 ; i < cnt; i ++ ) 
      vector->vals[i + vector->size - cnt] = vals[i];
  }
  return rc;    
}

/// Print vector
void vector_print ( vector_t * vector )
{
  unsigned int i;
  if ( !vector )
    return;
  
  printf( "%s [1..%d]\n", vector->name, vector->size );
  
  for ( i = 0; i < vector->size; i ++ )
    printf( "%f\n", vector->vals[i] );
}



/// Count vectors in array
int vectors_count ( vector_t ** vectors )
{
  vector_t **first_ptr, **end_ptr;
  if ( !vectors )
    return 0;

  first_ptr = vectors;
  end_ptr = first_ptr;

  while ( *end_ptr )
    end_ptr++;

  return end_ptr - first_ptr;
}

/// Add vector to vectors array
int vectors_add( vector_t *** vectors, vector_t * vector )
{
  int cnt = 0;

  if ( ! vector )
    return -1;

  cnt = vectors_count( *vectors );

  if ( cnt &&  vectors_search ( *vectors, vector->name ) ) 
    return -2;

  cnt ++ ;
  *vectors = ( vector_t ** )  realloc ( *vectors, (cnt + 1) * sizeof( vector_t *) );

  (*vectors)[cnt-1] = vector;
  (*vectors)[cnt] = 0;

  return cnt - 1;
}

/// Search vector by name
vector_t * vectors_search ( vector_t ** vectors , const char * name )
{
  if ( !vectors || !name )
    return 0;

  while ( *vectors )
  {
    if ( strcmp( (*vectors)->name, name ) == 0 )
      return *vectors;
    vectors++;
  }
  return 0;
}


/// Delete vector from vectors
int vectors_remove ( vector_t *** vectors, vector_t * vector)
{
  int cnt, rc = -1;
  vector_t **curr = *vectors;
  // Search vector position
  while ( *curr && *curr != vector )
	curr++;
  if ( *curr )
  {
     cnt = vectors_count ( *vectors );
     while ( *curr )
     {
       *curr = *( curr+1 );
       curr++;
     }
     *vectors = ( vector_t ** )  realloc ( *vectors, ( cnt ) * sizeof( vector_t *) );
     if ( vector )
     {
        if ( vector->vals )
           free( vector->vals );
        free( vector );
     }
     rc = 0;
  }
  return rc;
}

/// Remove all
void vectors_remove_all ( vector_t *** vectors)
{
  vector_t **curr = *vectors;
 if (curr) { 
  while ( *curr )
  {
     if ( (*curr)->vals )
           free( (*curr)->vals );
     free( *curr );
     curr++;
  }
  free( *vectors );
  *vectors = 0;    
 }
}



