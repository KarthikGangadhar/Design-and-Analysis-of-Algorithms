// Gangadhara, Karthik.
// kxg7851
// 2019-07-18
//--------#---------#---------#---------#--------#
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "support.h"

//--------#---------#---------#---------#--------#
//********//********//********//********//******//
// LEFT() and RIGHT() are useful in maxHeapify().
// PARENT() is useful in buildMaxHeap().
//********//********//********//********//******//
static inline int LEFT(int i)   { return 2*i+1; }
static inline int RIGHT(int i)  { return 2*i+2; }
static inline int PARENT(int i) { return  (floor(i/2)); }

static void maxHeapify( int *A, int size, int heapsize, int i )
{
    int l,r,largest = i;
    l = LEFT(i);
    r = RIGHT(i);

    if(l < heapsize && A[l] > A[largest]){
      largest = l;
    }

    if(r < heapsize && A[r] > A[largest]){
      largest = r;
    }

    if(largest != i){
      exchangeInt(&A[i],&A[largest]);
      maxHeapify(A, size, heapsize, largest);
    }      

}

static void buildMaxHeap( int *A, int size )
{
  for(int i= size /2 -1; i >= 0; i--)
    maxHeapify(A, size, size, i);
}

void heapSort( int *A, int size )
{
  buildMaxHeap(A, size);

  for(int j= size-1; j >= 0; j--){
    exchangeInt(&A[0], &A[j]);  
    maxHeapify(A, size, j, 0);
  }
}

//--------#---------#---------#---------#--------#
static int *L;
static int *R;

static void merge( int *A, int p, int q, int r )
{
  int i,j,k;
  int n1 = q - p + 1;
  int n2 = r - q;
  int *L =  malloc( (n1+1) * sizeof(int) );
  int *R =  malloc( (n2+1) * sizeof(int) );

  for(i = 0; i < n1; i++){
    L[i] = A[p+i];
  }
  for(j = 0; j < n2; j++){
    R[j] = A[q + j + 1];
  }

  L[n1] = INT_MAX;
  R[n2] = INT_MAX;
  i = j = 0;
  for(k = p; k <= r; k++){
    if(L[i] <= R[j]){
      A[k] = L[i];
      i = i + 1;
    }else{
      A[k] = R[j];
      j = j + 1;
    }
  }
  free( L );
  free( R );
}

static void mergeSort( int *A, int p, int r )
{
  if(p < r){
    int q = floor((p+r)/2);
    mergeSort(A,p,q);
    mergeSort(A,q+1,r);
    merge(A,p,q,r);
  }
}

//--------#---------#---------#---------#--------#
// DO NOT CHANGE THIS FUNCTION!
//--------#---------#---------#---------#--------#
void mergeSortTop( int *A, int size )
{
  L = (int *) malloc( ( size/2 + 1 + 1 )*sizeof(int) );
  R = (int *) malloc( ( size/2 + 1 + 1 )*sizeof(int) );

  mergeSort( A, 0, size-1 );

  free( L );
  free( R );
}

//--------#---------#---------#---------#--------#
