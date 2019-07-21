// Dalio, Brian A.
// dalioba
// 2019-07-06
//--------#---------#---------#---------#--------#
static inline void exchangeInt( int *a, int *b ) { int c = *a; *a = *b; *b = c; }
static inline int  maxInt( int a, int b ) { return (a > b) ? a : b; }
static inline int  minInt( int a, int b ) { return (a < b) ? a : b; }

//--------#---------#---------#---------#--------#
enum { ASCENDING, DESCENDING, SHUFFLE };
#define ORDER_STR(o) (ASCENDING == (o) ? "Ascending" : DESCENDING == (o) ? "Descending" : "Shuffle" )

//--------#---------#---------#---------#--------#
int checkArray( int *A, int n );
double fillArray( int *A, int n, int order );
void getArgs( int argc, char *argv[], int *n, int *ascending, int *descending, int *shuffle );

//--------#---------#---------#---------#--------#
void heapSort( int *A, int size );
void mergeSortTop( int *A, int size );

//--------#---------#---------#---------#--------#
