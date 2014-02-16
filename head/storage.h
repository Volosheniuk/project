#ifndef STORAGE_H
#define STORAGE_H

#define MAXCHARS 1024

typedef struct
{
  char name[MAXCHARS];
  unsigned int size;
  double * vals;
} vector_t;



/// Vector initialization 
int vector_init( const char* name, unsigned int size, vector_t * vector );

/// Vector deinitialization
int vector_clear( vector_t * vector );

/// Reallocate memory for values
int vector_realloc( vector_t * vector, unsigned int size );

/// Append value(s) to vector
int vector_append( vector_t * vector, unsigned int cnt, double * vals );

/// Print vector
void vector_print ( vector_t * vector );

/// Count vectors in array
int vectors_count ( vector_t ** vectors );

/// Add vector to vectors array
int vectors_add( vector_t *** vectors, vector_t * vector );

/// Search vector by name
vector_t * vectors_search ( vector_t ** vectors , const char * name );

/// Delete vector from vectors
int vectors_remove ( vector_t *** vectors, vector_t * vector);

/// Remove all
void vectors_remove_all ( vector_t *** vectors);

#endif
