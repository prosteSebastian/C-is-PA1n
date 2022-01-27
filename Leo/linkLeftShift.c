#ifndef __PROGTEST__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
 
typedef struct TNode
{
    struct TNode * m_Next;
    char           m_Digit;
} TNODE;
 
TNODE * createNode ( char digit, TNODE * next )
{
    TNODE * n = (TNODE *) malloc (sizeof ( *n ));
    n -> m_Digit = digit;
    n -> m_Next = next;
    return n;
}
 
void deleteList (TNODE * l)
{
    while (l)
    {
        TNODE * tmp = l -> m_Next;
        free (l);
        l = tmp;
    }
}
#endif /* __PROGTEST__ */

void printList ( TNODE * a ) {
  printf("My digits");
  for ( ; a != NULL;  a = a->m_Next )
    printf(" -> %c", a->m_Digit);
  printf("\n");
}

//if the digit exists then return 1; 
//if the number begins with zero or does not exits return 0;
int digitCheck ( TNODE * array ) {
  if ( array->m_Digit == '0' && array->m_Next == NULL )
    return 1;

  for ( ; array->m_Next != NULL ; array = array ->m_Next )
    if ( !( array->m_Digit >= '0' && array->m_Digit <= '9' ) 
        && !( array->m_Digit >= 'a' && array->m_Digit <= 'f' ) )
      return 0;

  if ( !( array->m_Digit > '0' && array->m_Digit <= '9' ) 
     && !( array->m_Digit >= 'a' && array->m_Digit <= 'f' ) )
      return 0;
  
  return 1;
}

//convert char to integer for more convinient counting
//return integer
int toInt ( char a ) {
  int digit = 0;
  if ( a >= '0' && a <= '9' )
    digit = a - 48;
  else
    digit = a - 87;
  return digit;
}

char toChar ( int resInt, int * reminder ) {
  char result;
  if ( resInt > 15 ) {
    resInt -= 16;
    if ( resInt < 10 )
      result = resInt + '0';
    else
      result = ( resInt - 10 ) + 'a';
    *reminder = 1;
  }
  else
    if ( resInt < 10 )
      result = resInt + '0';
    else
      result = ( resInt - 10 ) + 'a';
  return result;
}

//using alphabhet for number bigger than 9 in hex
char getDigit ( char a, int multiplicator, int * reminder ) {
  int digit, resInt = 0;

  digit = toInt ( a );
  resInt = digit * multiplicator;
  
  if ( *reminder == 1 ) {
    resInt++;
    *reminder = 0;
  }

  a = toChar ( resInt, reminder );
  return a;
}

//return the pointer to result
TNODE * multiplication ( TNODE * arr ) {
  
  TNODE * result = NULL, * headResult = NULL;
  int reminder = 0;

  //first element
  result = createNode ( getDigit ( arr->m_Digit, 2, &reminder ), NULL );
  arr = arr->m_Next;
  headResult = result;

  for ( ; arr != NULL ; arr = arr->m_Next ) {
    result->m_Next = createNode ( getDigit ( arr->m_Digit, 2, &reminder ), NULL );
    result = result->m_Next;
  } 

  //if last element has a reminder
  if ( reminder == 1 )
    result->m_Next = createNode ( getDigit ( '0' , 2, &reminder ), NULL );

  return headResult;
}

//return copied array
TNODE * cpArr ( TNODE * arr ) {
  TNODE * result = NULL, * headResult = NULL;
  int reminder = 0;

  result = createNode ( getDigit ( arr->m_Digit, 1, &reminder ), NULL );
  arr = arr->m_Next;
  headResult = result;

  
  for ( ; arr != NULL ; arr = arr->m_Next ) {
    result->m_Next = createNode ( getDigit ( arr->m_Digit, 1, &reminder ), NULL );
    result = result->m_Next;
  }

  return headResult; 
}

//repeat multiplication if shift is larger than 1
//return final result 
TNODE * getResult ( TNODE * arr, unsigned int shift ) {
  TNODE * result = NULL;
  TNODE * oldResult = NULL;

  //if shift is zero, return a copied list
  if ( shift == 0 ) {
    result = cpArr ( arr );
    return result;
  }
    

  result = multiplication ( arr );
  for ( unsigned int i = 1 ; i < shift ; ++i ) {
    oldResult = result;
    result = multiplication ( result );
    deleteList ( oldResult );
  }
  return result;
}

//return list of results
TNODE * shiftLeft ( TNODE * a, unsigned int shift )
{
  if ( a == NULL ) return NULL;
  if ( ! digitCheck ( a ) ) return NULL;

  TNODE * result = getResult ( a, shift );

  printList ( result );
  return result;
}
 
#ifndef __PROGTEST__
int main (int argc, char * argv [])
{
  TNODE * a = NULL, * res = NULL;

  a = createNode ( '0', 
        createNode ( '0', NULL ));
  res = shiftLeft ( a, 1 );
  assert ( res == NULL );
  deleteList ( a );

  a = createNode ( '0', NULL );
  res = shiftLeft ( a, 2 );
  assert ( res -> m_Digit == '0' );
  deleteList ( a );
  deleteList ( res );

  a = createNode ( '8', NULL);
  res = shiftLeft ( a, 1 );
  assert ( res -> m_Digit == '0' );
  assert ( res -> m_Next -> m_Digit == '1' );
  deleteList ( a );
  deleteList ( res );

  a = createNode ( '8', NULL);
  res = shiftLeft ( a, 0 );
  assert ( res -> m_Digit == '8' );
  assert ( res -> m_Next == NULL );
  deleteList ( a );
  deleteList ( res );

  a = createNode ( '3',
        createNode ( '2',
          createNode ( '1', NULL )));
  res = shiftLeft ( a, 1 );
  assert ( res -> m_Digit == '6' );
  assert ( res -> m_Next -> m_Digit == '4' );
  assert ( res -> m_Next -> m_Next -> m_Digit == '2' );
  assert ( res -> m_Next -> m_Next -> m_Next == NULL );
  deleteList ( a );
  deleteList ( res );
  
  a = createNode ( 'f',
        createNode ( 'a',
          createNode ( '1', NULL )));
  res = shiftLeft ( a, 3 );
  assert ( res -> m_Digit == '8' );
  assert ( res -> m_Next -> m_Digit == '7' );
  assert ( res -> m_Next -> m_Next -> m_Digit == 'd' );
  assert ( res -> m_Next -> m_Next -> m_Next == NULL );
  deleteList ( a );
  deleteList ( res );
  
  a = createNode ( 'c',
        createNode ( '5',
          createNode ( '4',
            createNode ( 'd',
              createNode ( '1', NULL )))));
  res = shiftLeft ( a, 5 );
  assert ( res -> m_Digit == '0' );
  assert ( res -> m_Next -> m_Digit == '8' );
  assert ( res -> m_Next -> m_Next -> m_Digit == 'b' );
  assert ( res -> m_Next -> m_Next -> m_Next -> m_Digit == '8' );
  assert ( res -> m_Next -> m_Next -> m_Next -> m_Next -> m_Digit == 'a' );
  assert ( res -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Digit == '3' );
  assert ( res -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
  deleteList ( a );
  deleteList ( res );
  
  a = createNode ( 'a',
        createNode ( '1',
          createNode ( 'w', NULL )));
  res = shiftLeft ( a, 12 );
  assert ( res == NULL );
  deleteList ( a );
  
  a = NULL;
  res = shiftLeft ( a, 1 );
  assert ( res == NULL );

  a = createNode ( 'a',
        createNode ( '1',
          createNode ( '0', NULL)));
  res = shiftLeft ( a, 1 );
  assert ( res == NULL );
  deleteList ( a );

  return 0;
}
#endif /* __PROGTEST__ */