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
    for ( ; tmp1->m_Next != NULL ; tmp1 = tmp1->m_Next )
      if ( tmp1->m_Val > tmp1->m_Next->m_Val )
        return 1;
  }
  return 0;
}

void delArr ( Tnode ** a, int nr ) {
  for ( int i = 0 ; i < nr ; ++i )
    delList ( a[i] );
}

Tnode * resList ( Tnode * a, Tnode * b ) {
  Tnode * res = a, * tmp, * head;
  int mode = 0; //on a[0]/a branch

  if ( a->m_Val > b->m_Val ) {
    mode = 1; //on a[i]/b branch 
    res = b;
  }

  head = res;

  while ( a != NULL || b!= NULL ) {
    if ( mode ) { //on a[i]/b branch
      if ( res->m_Next == NULL && a != NULL ) {
        res->m_Next = a;
        break;
      }
      else if ( a == NULL ) {
        break;
      }
      else if ( res->m_Next->m_Val <= a->m_Val ) {
        res = res->m_Next;
        b = b->m_Next;
      }
      else if ( res->m_Next->m_Val > a->m_Val ) {
        tmp = b->m_Next;
        res->m_Next = a;
        mode = 0;
        b = tmp;
        res = res->m_Next;
      }
    }
    else {
      if ( res->m_Next == NULL && b != NULL ) {
        res->m_Next = b;
        break;
      }
      else if ( b == NULL ) {
        break;
      }
      else if ( res->m_Next->m_Val <= b->m_Val ) {
        res = res->m_Next;
        a = a->m_Next;
      }
      else if ( res->m_Next->m_Val > a->m_Val ) {
        tmp = a->m_Next;
        res->m_Next = b;
        mode = 1;
        a = tmp;
        res = res->m_Next;
      }
    }
  }

  return head;
}

Tnode * compareList ( Tnode ** a, int nr ) {
  if ( checkList ( a, nr ) || checkSizes ( a, nr ) ) {
    delArr ( a, nr );
    return NULL; 
  }

  Tnode * res = a[0];

  for ( int i = 1 ; i < nr ; ++i ) {
    res = resList ( res, a[i] );
  }

  Tnode * headTmp = res;;
  printList ( headTmp );

  return res;
}

#ifndef __PROGTEST__
int main ( int argc, char * argv [] ) {
  Tnode * a[5];
  Tnode * res;

  a[0] = createItem ( 5, NULL );
  a[1] = createItem ( 1,
           createItem ( 2,
             createItem ( 6,
               createItem ( 7,
                 createItem ( 8,
                   createItem ( 9, NULL ))))));
  res = compareList ( a, 2 );
  delList ( res );
  
  a[0] = createItem ( 1,
           createItem ( 7,
             createItem ( 24, NULL )));
  a[1] = createItem ( 3,
           createItem ( 5,
             createItem ( 17, NULL )));
  a[2] = createItem ( -3,
           createItem ( 19, NULL ));
  res = compareList ( a, 3 );
  delList ( res );

  a[0] = createItem ( 15,
           createItem ( 19,
             createItem ( 23,
               createItem ( 192, NULL ))));
  a[1] = createItem ( 17,
           createItem ( 18,
             createItem ( 18,
               createItem ( 21, NULL ))));
  a[2] = createItem ( -3,
          createItem ( 19, NULL ));
  res = compareList ( a, 3 );
  delList ( res );

  a[0] = createItem ( -4,
           createItem ( 2,
             createItem ( 4,
               createItem ( 7, NULL ))));
  a[1] = createItem ( 12, 
           createItem ( 18, 
             createItem ( 20, NULL )));
  a[2] = createItem ( -6, 
           createItem ( 3, 
             createItem ( 4,
               createItem ( 11,
                 createItem ( 14,
                   createItem ( 15, 
                     createItem ( 19, NULL )))))));
  res = compareList ( a, 3 );
  delList ( res );

  a[0] = createItem ( 15,
           createItem ( 19,
             createItem ( 23,
               createItem ( 142, NULL ))));
  a[1] = createItem ( 17,
           createItem ( 18, 
             createItem ( 18,
               createItem ( 21, NULL ))));
  a[2] = createItem ( 11,
           createItem ( 18,
             createItem ( 19,
               createItem ( 40, NULL ))));      
  res = compareList ( a, 3 );
  delList ( res );

  a[0] = createItem ( 1, NULL );
  a[1] = createItem ( 2, NULL );
  a[2] = createItem ( 5, NULL );
  a[3] = createItem ( 4, NULL );
  res = compareList ( a, 4 );
  delList ( res );

  a[0] = createItem ( -4,
           createItem ( 2,
             createItem ( 4,
               createItem ( 7, NULL ))));
  a[1] = createItem ( 12, 
           createItem ( 18, 
             createItem ( 20, NULL )));
  a[2] = createItem ( -6, 
           createItem ( 3, 
             createItem ( 4,
               createItem ( 11,
                 createItem ( 1,
                   createItem ( 15, 
                     createItem ( 19, NULL )))))));
  res = compareList ( a, 3 );
  assert ( res == NULL );

  a[0] = createItem ( -4,
           createItem ( 2,
             createItem ( 4,
               createItem ( 7, NULL ))));
  a[1] = createItem ( 12, NULL );
  a[2] = createItem ( 3, NULL );
  res = compareList ( a, 3 );
  delList ( res );

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
