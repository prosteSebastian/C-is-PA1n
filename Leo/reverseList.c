#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

typedef struct TItem {
  struct TItem * m_Next;
  int m_Data;
} TITEM;

TITEM * createItem ( int i, TITEM * next ) {
  TITEM * a = (TITEM*) malloc ( sizeof (*a) );
  a->m_Next = next;
  a->m_Data = i;
  return a;
}

void printList ( TITEM * a ) {
  printf ("digit ");
  for ( ; a ; a = a->m_Next )
    printf (" -> %i", a->m_Data);
  printf ("\n");
}

void deleteList ( TITEM * a ) {
  if ( a )
    deleteList ( a->m_Next );
  free ( a );
}

TITEM * copyList ( TITEM * a ) {
  TITEM * copied, * head;
  copied = createItem ( a->m_Data, NULL );
  a = a->m_Next;
  head = copied;

  for ( ; a ; a = a->m_Next ) {
    copied->m_Next = createItem ( a->m_Data, NULL );
    copied = copied->m_Next;
  }
  return head;
}

TITEM * reverseList ( TITEM * a ) {
  TITEM * rev, * next;
  rev = createItem ( a->m_Data, NULL );
  a = a->m_Next;
  for ( ; a ; a = a->m_Next ) {
    next = createItem ( a->m_Data, rev );
    rev = next;
  }
  return rev;
}

TITEM * copyList2 ( TITEM * a ) {
  TITEM * copied, * head, *tmp;
  copied = createItem ( a->m_Data, NULL );
  tmp = a->m_Next;
  free ( a );
  a = tmp;
  head = copied;

  for ( ; a ; a = tmp ) {
    copied->m_Next = createItem ( a->m_Data, NULL );
    tmp = a-> m_Next;
    free ( a );
    copied = copied->m_Next;
  }
  return head;
}

TITEM * reverseList2 ( TITEM * a ) {
  TITEM * rev, * next, * tmp;
  rev = createItem ( a->m_Data, NULL );
  tmp = a->m_Next;
  free ( a );
  a = tmp;
  for ( ; a ; a = tmp ) {
    next = createItem ( a->m_Data, rev );
    rev = next;
    tmp = a->m_Next;
    free ( a );
  }
  return rev;
}

int main ( void ) {
  TITEM * a, * cpy, * rev;
  a = createItem ( 1,
        createItem ( 2,
          createItem ( 3,
            createItem ( 4,
              createItem ( 5, NULL )))));
  printList ( a );
  cpy = copyList ( a );
  printList ( cpy );
  rev = reverseList ( a );
  printList ( rev );
  deleteList ( rev );
  deleteList ( cpy );
  deleteList ( a );

  //option with delete of the old list in function

  TITEM * b, * cpy2, * rev2;
  b = createItem ( 1,
        createItem ( 2,
          createItem ( 3,
            createItem ( 4,
              createItem ( 5, NULL )))));
  printList ( b );
  cpy2 = copyList2 ( b );
  printList ( cpy2 );
  rev2 = reverseList2 ( cpy2 );
  printList ( rev2 );
  deleteList ( rev2 );
}