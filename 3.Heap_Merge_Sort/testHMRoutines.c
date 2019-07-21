// Dalio, Brian A.
// dalioba
// 2019-07-06
//--------#---------#---------#---------#--------#
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "support.h"

//--------#---------#---------#---------#--------#
// DO NOT CHANGE ANYTHING IN THIS FILE!
//--------#---------#---------#---------#--------#
void doTestSeries( void (*sortFunc)( int *, int ), int which, char *title, int howMany, int *A, int n );

//--------#---------#---------#---------#--------#
double testSort( void (*sortFunc)( int *, int ), int *A, int size )
{
  clock_t begin;
  clock_t end;
  double  elapsed;

  begin = clock();
  (*sortFunc)( A, size );
  end = clock();

  elapsed = (double) ( end - begin ) / CLOCKS_PER_SEC;

  return elapsed;
}

//--------#---------#---------#---------#--------#
int main( int argc, char *argv[] ) {
  int n;
  int ascending;
  int descending;
  int shuffle;
  int *A;

  double fill;
  double elapsed;
  double total;
  int errs;

  // No buffering of output.
  setbuf( stdout, NULL );

  // Enable thousand separators in printf().
  setlocale( LC_NUMERIC, "" );

  // Initialize the pseudorandom number generator.
  srand48( time( NULL ) );

  // Get how many items to sort, and whether we should
  // do an ascending test, a descending test, and/or
  // a shuffle test.
  getArgs( argc, argv, &n, &ascending, &descending, &shuffle );

  // Allocate the array.
  A = (int *) malloc( sizeof( int ) * n );
  if ( NULL == A ) {
    printf( "%s: unable to allocate %'u-element array.\n", argv[0], n );
    exit( 1 );
  }
  printf( "%'u item%s in array.\n", n, n == 1 ? "" : "s" );

  //------------------------------------------------
  // Do the requested tests.
  printf( "=== Heap Sort ===\n" );

  doTestSeries( heapSort, ASCENDING, "Ascending", ascending, A, n );
  doTestSeries( heapSort, DESCENDING, "Descending", descending, A, n );
  doTestSeries( heapSort, SHUFFLE, "Shuffle", shuffle, A, n );

  printf( "=== Merge Sort ===\n" );

  doTestSeries( mergeSortTop, ASCENDING, "Ascending", ascending, A, n );
  doTestSeries( mergeSortTop, DESCENDING, "Descending", descending, A, n );
  doTestSeries( mergeSortTop, SHUFFLE, "Shuffle", shuffle, A, n );

  //------------------------------------------------
  // All done!  Free the allocated array.
  free( A );
}

void doTestSeries( void (*sortFunc)( int *, int ), int which, char *title, int howMany, int *A, int n ) {
  double fill;
  double elapsed;
  double total;
  int errs;

  if ( howMany > 0 ) {
    printf( "--- %s test\n", title );

    total = 0.0;
    for ( int i=0; i < howMany; i++ ) {
      fill = fillArray( A, n, which );
      elapsed = testSort( sortFunc, A, n );
      total += elapsed;
      errs = checkArray( A, n );

      printf( "%2d/%2d: fill %.3fs, run %.3fs, %d error%s.\n",
        i+1, howMany, fill, elapsed, errs, errs == 1 ? "" : "s"  );
    }

    if ( howMany > 1 ) {
      printf( "Average run time %.3fs\n", total / howMany );
    }
  }
}

//--------#---------#---------#---------#--------#
