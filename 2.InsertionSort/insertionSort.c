// Gangadhara, Karthik.
// kxg7851
// 2019-06-15
//--------#---------#---------#---------#--------#
#include <stdio.h>
#include <time.h>

#include "support.h"

//--------#---------#---------#---------#--------#
void insertionSort( int *A, int size )
{
  //********//********//********//********//******//
  int j,i,key;
  for(j = 1; j < size; j++){
    key = A[j];
    i = j-1;
    while(i >= 0 && A[i] > key){
      A[i+1] = A[i];
      i = i-1;
    }
    A[i+1] = key;
  }
  //********//********//********//********//******//
}

//--------#---------#---------#---------#--------#
