// Gangadhara, Karthik.
// kxg7851
// 2019-07-31
//--------#---------#---------#---------#--------#
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include "Huffman.h"

static void minHeapify( HuffmanHeapPtr h, int i );
//--------#---------#---------#---------#--------#
static inline void exchangePtr( HuffmanNodePtr *a, HuffmanNodePtr *b ) \
  {  HuffmanNodePtr c = *a; *a = *b; *b = c; }

//--------#---------#---------#---------#--------#
static inline int LEFT(int i)   { return (2*i+1); }
static inline int RIGHT(int i)  { return (2*i+2); }
static inline int PARENT(int i) { return ((i-1)/2); }

//--------#---------#---------#---------#--------#
void addElement( HuffmanHeapPtr h, HuffmanNodePtr newNodePtr )
{
  int i = h-> heapsize;
  (h-> heapsize) = h-> heapsize + 1;
  while(i!=0 && (newNodePtr->frequency) < (h->A[PARENT(i)]->frequency)){
     exchangePtr(&(h->A[i]), &(h->A[PARENT(i)]));
      i = PARENT(i);
  }
  h->A[i] = newNodePtr;
}

//--------#---------#---------#---------#--------#
HuffmanNodePtr buildHuffmanCode( HuffmanHeapPtr h )
{
  while (h->heapsize > 1)
  {
    HuffmanNodePtr m = extractMin(h);
    HuffmanNodePtr n = extractMin(h);

    HuffmanNodePtr o = makeHuffmanNode(-1, m->frequency + n->frequency);
    o->left=m;
    o->right=n;
    addElement(h,o);
  }
  return extractMin(h);
 
}

//--------#---------#---------#---------#--------#
int dumpHuffmanCode( HuffmanNodePtr n )
{  
    char arr[128];
    int root = 0;
    if(n->left != NULL)
    {
      dumpHuffmanCode(n->left);
    }
    if(n->right != NULL)    
    {
      dumpHuffmanCode(n->right);
    }
    if(n->left == NULL && n->right == NULL)
    {
      printArr(arr, root);
    }
}

//--------#---------#---------#---------#--------#
HuffmanNodePtr extractMin( HuffmanHeapPtr h )
{
  HuffmanNodePtr root = h->A[0];
  h->A[0] = h->A[h->heapsize - 1];
  h->heapsize = h->heapsize - 1;
  minHeapify(h, 0);
  return root;
}

//--------#---------#---------#---------#--------#
HuffmanHeapPtr makeHuffmanHeap( int size )
{
    HuffmanHeapPtr huffmanHeap = (HuffmanHeapPtr) calloc(size, sizeof(HuffmanHeap)); 
    huffmanHeap -> size = size;  
    huffmanHeap -> heapsize = 0;
    huffmanHeap -> A = calloc(huffmanHeap-> size, sizeof(HuffmanNodePtr));
    return huffmanHeap; 
}

//--------#---------#---------#---------#--------#
HuffmanNodePtr makeHuffmanNode( int character, int frequency )
{
  HuffmanNode* temp = (HuffmanNode*) malloc(sizeof(HuffmanNode)); 
  if(temp){
    temp->left= NULL;
    temp -> right = NULL;
    temp ->character = character;
    temp ->frequency = frequency;
  }
  return temp; 
}

//--------#---------#---------#---------#--------#
static void minHeapify( HuffmanHeapPtr h, int i )
{
  int l = LEFT(i);
  int r = RIGHT(i);
  int smallest;
  if(l < h->heapsize && h->A[l]-> frequency < h->A[i] -> frequency )
    smallest = l;
  else{
    smallest = i;
  }
  if(l < h->heapsize && h->A[r]-> frequency < h->A[smallest]-> frequency )
    smallest = r;
  if(smallest != i){
    exchangePtr(&h->A[i], &h->A[smallest]);
    minHeapify(h, smallest);
  }
}

//--------#---------#---------#---------#--------#
void dumpHuffmanHeap( HuffmanHeapPtr h )
{
  printf( "===== Huffman Heap =====\n" );
  printf( "size %d, heapsize %d\n", h->size, h->heapsize );
  for ( int i=0; i < h->heapsize; i++ ) {
    dumpHuffmanNode( h->A[i], 1 );
  }
}

//--------#---------#---------#---------#--------#
void dumpHuffmanNode( HuffmanNodePtr n, int indent )
{
  printf( "%*c", indent*2, ' ' );

  if ( n->character == -1 ) {
    printf( "[Interior] %d\n", n->frequency );
    dumpHuffmanNode( n->left, indent+1 );
    dumpHuffmanNode( n->right, indent+1 );
  } else {
    if ( isprint( n->character ) ) {
      printf( "'%c' %d\n", n->character, n->frequency );
    } else {
      printf( "%03d %d\n", n->character, n->frequency );
    }
  }
}

//--------#---------#---------#---------#--------#
