#ifndef __PROGTEST__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
 
typedef struct TItem
{
    struct TItem * m_Next;
    char           m_Digit;
} TITEM;
 
TITEM * createItem ( char digit, TITEM * next )
{
    TITEM * n = (TITEM *) malloc (sizeof ( *n ));
    n -> m_Digit = digit;
    n -> m_Next = next;
    return n;
}
 
void deleteList (TITEM * l)
{
    while (l)
    {
        TITEM * tmp = l -> m_Next;
        free (l);
        l = tmp;
    }
}
#endif /* __PROGTEST__ */

int checkAlphas ( TITEM *a, int nr ) {
  for ( ; a != NULL ; a = a->m_Next )
    if ( a->m_Digit < '0' || a->m_Digit > '9' )
      return 1;
  return 0;
} 

int checkDigit ( TITEM ** a, int nr ) {
  for ( int i = 0 ; i < nr ; ++i ) {
    if ( a[i] == NULL )
      return 1;
    if ( checkAlphas ( a[i], nr ) )
      return 1;        
  }
  return 0;
}

void printList ( TITEM * a ) {
  printf("Maximum digit");
  for ( ; a != NULL ; a = a->m_Next )
    printf (" -> %c", a->m_Digit);
  printf("\n");
}

int finishIt ( TITEM * a ) {
  for ( ; a != NULL ; a = a->m_Next ) { 
    if ( a->m_Digit > '0' )
      return 1;
  }
  return 0;
}

TITEM * shorter ( TITEM * a, TITEM * b, 
                TITEM * ptrA, TITEM * ptrB ) {
  if ( b->m_Digit < a->m_Digit ) {
    return ptrA;
  } 
  else if ( finishIt ( a->m_Next ) ) {
    return ptrA;
  }
  else {
    return ptrB;
  }
}

TITEM * compare ( TITEM * a, TITEM * b ) {
  int mode = 0; //max on a
  TITEM * max = a;

  if ( a->m_Digit < b->m_Digit ) {
    max = b;
    mode = 1;
  }

  TITEM * ptrA = a, * ptrB = b;

  while ( a != NULL || b != NULL ) {
    if ( mode ) { //max on b
      if ( b->m_Next == NULL && a->m_Next != NULL ) {
        max = shorter ( a, b, ptrA, ptrB );
        break;
      }
      else if ( b->m_Next != NULL && a->m_Next == NULL ) {
        if ( b->m_Digit < a->m_Digit ) {
          max = ptrA;
          mode = 0;
        }
        else {
          break;
        }
      }
      else if ( b->m_Digit >= a->m_Digit ) {
        b = b->m_Next;
        a = a->m_Next;
      }
      else {
        max = ptrA;
        mode = 1;
      }
    }
    else { //max on a
      if ( a->m_Next == NULL && b->m_Next != NULL ) {
        max = shorter ( b, a, ptrB, ptrA );
        break;
      }
      else if ( a->m_Next != NULL && b->m_Next == NULL ) {
        if ( a->m_Digit < b->m_Digit ) {
          max = ptrB;
          mode = 1;
        }
        else {
          break;
        }
      }
      else if ( a->m_Digit >= b->m_Digit ) {
        a = a->m_Next;
        b = b->m_Next;
      }
      else {
        max = ptrB;
        mode = 1;
      }
    }
  }
  return max;
}

TITEM * maxOf (TITEM ** a, int nr ) {
  //check if ok
  if ( checkDigit ( a, nr ) )
    return NULL;

  TITEM * max = a[0];
  for ( int i = 1 ; i < nr ; ++i ) {
    max = compare( max, a[i] );
    //printList ( max );
  }
  printList ( max );
  return max;
}
 
#ifndef __PROGTEST__
int main (int argc, char * argv [])
{
    TITEM * a[5];
 
    a[0] = createItem ( '4',
            createItem ( '3',
             createItem ( '2',
              createItem ( '1', NULL ))));
    a[1] = createItem ( '2',
            createItem ( '3',
             createItem ( '4',
              createItem ( '5', NULL))));
    assert ( maxOf ( a, 2 ) == a[1] );
    deleteList( a[0] );
    deleteList( a[1] );
 
    a[0] = createItem ( '0',
            createItem ( '0',
             createItem ( '0',
              createItem ( '1', NULL ))));
    a[1] = createItem ( '2',
            createItem ( '0',
             createItem ( '0',
              createItem ( '1', NULL ))));
    a[2] = createItem ( '1',
            createItem ( '0',
             createItem ( '0',
              createItem ( '1', NULL))));
    a[3] = createItem ( '2',
            createItem ( '0',
             createItem ( '0',
              createItem ( '1',
               createItem ( '0',
                createItem ( '0', NULL ))))));
    assert ( maxOf ( a, 4 ) == a[1] );
    deleteList ( a[0] );
    deleteList ( a[1] );
    deleteList ( a[2] );
    deleteList ( a[3] );
 
    a[0] = createItem ( '1',
            createItem ( '0',
             createItem ( '0',
              createItem ( '0',
               createItem ( '0',
                createItem ( '0', NULL ))))));
    a[1] = createItem ( '0',
            createItem ( '0',
             createItem ( '1', NULL )));
    a[2] = createItem ( '1',
            createItem ( '0',
             createItem ( '0',
              createItem ( '0',
               createItem ( '0',
                createItem ( '9', NULL ))))));
    a[3] = createItem ( '0',
            createItem ( '0',
             createItem ( '0',
              createItem ( '0',
               createItem ( '0',
                createItem ( '0',
                 createItem ( '0',
                  createItem ( '0',
                   createItem ( '0',
                    createItem ( '0',
                     createItem ( '0',
                      createItem ( '0',
                       createItem ( '0',
                        createItem ( '0',
                         createItem ( '0', NULL )))))))))))))));
    assert ( maxOf (a, 4) == a[2] );
    deleteList ( a[0] );
    deleteList ( a[1] );
    deleteList ( a[2] );
    deleteList ( a[3] );
 
    a[0] = createItem ( '0',
            createItem ( '0',
             createItem ( '0',
              createItem ( '0',
               createItem ( '0',
                createItem ( '0',
                 createItem ( '0',
                  createItem ( '0',
                   createItem ( '0',
                    createItem ( '0',
                     createItem ( '0',
                      createItem ( '0',
                       createItem ( '0',
                        createItem ( '0',
                         createItem ( '0',
                          createItem ( '0',
                           createItem ( '0',
                            createItem ( '0',
                             createItem ( '0',
                              createItem ( '0',
                               createItem ( '0',
                                createItem ( '1', NULL ))))))))))))))))))))));
    a[1] = createItem ( '1',
            createItem ( '0',
             createItem ( '0',
              createItem ( '0',
               createItem ( '0',
                createItem ( '0',
                 createItem ( '0',
                  createItem ( '0',
                   createItem ( '0',
                    createItem ( '0',
                     createItem ( '0',
                      createItem ( '0',
                       createItem ( '0',
                        createItem ( '0',
                         createItem ( '0',
                          createItem ( '0',
                           createItem ( '0',
                            createItem ( '0',
                             createItem ( '0',
                              createItem ( '0',
                               createItem ( '0',
                                createItem ( '1', NULL ))))))))))))))))))))));
    assert ( maxOf ( a, 2 ) == a[1] );
    deleteList ( a[0] );
    deleteList ( a[1] );
 
    a[0] = createItem ( '3',
            createItem ( '2',
             createItem ( '1', NULL )));
    a[1] = NULL;
    a[2] = createItem ( '9',
            createItem ( 'c',
             createItem ( 'b',
              createItem ( '9',
               createItem ( '9', NULL )))));
    assert ( maxOf ( a, 3 ) == NULL);
    deleteList ( a[0] );
    deleteList ( a[2] );

    a[0] = createItem ( '3',
            createItem ( '2',
             createItem ( '1', NULL )));
    a[1] = createItem ( '6',
            createItem ( '5',
             createItem ( '4', NULL )));
    a[2] = createItem ( '9',
            createItem ( 'c',
             createItem ( 'b',
              createItem ( '9',
               createItem ( '9', NULL )))));
    assert ( maxOf ( a, 3 ) == NULL);
    deleteList ( a[0] );
    deleteList ( a[1] );
    deleteList ( a[2] );
 
    return 0;
}
#endif /* __PROGTEST__ */