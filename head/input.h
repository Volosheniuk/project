#ifndef INPUT_H
#define INPUT_H

#include "storage.h"

/// Load data from CSV file
int load_csv(vector_t *** vectors, const char * fname);

/// Save vars to CSV file
int save_csv(vector_t ** vectors, const char * fname);

#endif
