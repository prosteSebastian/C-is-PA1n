#ifndef __PROGTEST__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

typedef struct tnode {
  struct tnode * m_Next;
  int m_Val;
} Tnode;

Tnode * createItem ( int i ,Tnode * next ) {
  Tnode * l = (Tnode*) malloc ( sizeof(*l) );
  l->m_Val = i;
  l->m_Next = next;
  return l;
}

void delList ( Tnode * l ) {
  if ( l != NULL )
    delList ( l->m_Next );
  free ( l );
}
#endif /* __PROGTEST__ */

void printList ( Tnode * l ) {
  printf("Digit");
  for ( ; l != NULL ; l = l->m_Next )
    printf(" -> %i", l->m_Val);
  printf("\n");
}

int checkList ( Tnode ** a, int nr ) {
  for ( int i = 0 ; i < nr ; ++i )
    if ( a[i] == NULL )
      return 1;
  return 0;
}

int checkSizes ( Tnode ** a, int nr ) {
  Tnode * tmp1;
  for ( int i = 0 ; i < nr ; ++i ) {
    tmp1 = a[i];
    for ( ; tmp1->m_Next != NULL ; tmp1 = tmp1->m_Next ) {
      if ( tmp1->m_Val > tmp1->m_Next->m_Val )
        return 1;
    }
  }
  return 0;
}

void delArr ( Tnode ** a, int nr ) {
  for ( int i = 0 ; i < nr ; ++i )
    delList ( a[i] );
}

Tnode * compareList ( Tnode ** a, int nr ) {
  if ( checkList ( a, nr ) || checkSizes ( a, nr ) ) {
    delArr ( a, nr );
    return NULL; 
  }

  Tnode * res = a[0];
  return res;
}

#ifndef __PROGTEST__
int main ( int argc, char * argv [] ) {
  Tnode * a[5];
  Tnode * res;
  
  // a[0] = createItem ( 1,
  //          createItem ( 7,
  //            createItem ( 24, NULL )));
  // a[1] = createItem ( 3,
  //          createItem ( 5,
  //            createItem ( 17, NULL )));
  // a[2] = createItem ( -3,
  //          createItem ( 19, NULL ));
  // res = compareList ( a, 3 );
  // delList ( res );

  // a[0] = createItem ( 15,
  //          createItem ( 19,
  //            createItem ( 23,
  //              createItem ( 192, NULL ))));
  // a[1] = createItem ( 17,
  //          createItem ( 18,
  //            createItem ( 18,
  //              createItem ( 21, NULL ))));
  // a[2] = createItem ( -3,
  //         createItem ( 19, NULL ));
  // res = compareList ( a, 3 );
  // delList ( res );
  
  a[0] = createItem ( 15,
           createItem ( 19,
             createItem ( 19,
               createItem ( 2, NULL ))));
  a[1] = createItem ( 17,
           createItem ( 18,
             createItem ( 18,
               createItem ( 21, NULL ))));
  res = compareList ( a, 2 );
  assert ( res == NULL );

  a[0] = createItem ( 15,
           createItem ( 19,
             createItem ( 19,
               createItem ( 2, NULL ))));
  a[1] = NULL;
  a[2] = createItem ( -2,
           createItem ( 1,
             createItem ( 10,
               createItem ( 11, NULL ))));
  res = compareList ( a, 3 );
  assert ( res == NULL );

  return 0;
}
#endif /* __PROGTEST__ */


