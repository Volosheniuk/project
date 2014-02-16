#include <stdio.h>
#include <stdlib.h>

#include "../head/command.h"
#include "../head/storage.h"
#include "../head/function.h"
#include "../head/input.h"

int main( int argc, char ** argv )
{
  vector_t ** vectors = 0;
  command( &vectors );
  vectors_remove_all( &vectors );
  return 0;
}
