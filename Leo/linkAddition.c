#ifndef __PROGTEST__
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
 
typedef struct TItem {
    struct TItem * m_Next;
    char m_Digit;
} TITEM;
 
TITEM * createItem(char digit, TITEM * next) {
    TITEM *n = (TITEM *) malloc(sizeof(*n));
    n->m_Digit = digit;
    n->m_Next = next;
    return n;
}
 
void deleteList(TITEM * l) {
    while (l) {
        TITEM *tmp = l->m_Next;
        free(l);
        l = tmp;
    }
}
 
#endif /* __PROGTEST__ */

void printList ( TITEM * r ) {
  printf ("Digit");
  for ( ; r ; r = r->m_Next )
    printf (" -> %c", r->m_Digit);
  printf ("\n");
}

int checkDigits ( TITEM * a, TITEM * b ) {
  //control a
  if ( a->m_Digit == '0' && !(a->m_Next) ) return 0;  
  for ( ; a->m_Next ; a = a->m_Next )
    if ( ! ( a->m_Digit >= '0' && a->m_Digit <= '9' ) )
      return 1;
  if ( !( a->m_Digit > '0' && a->m_Digit <= '9' ) ) 
    return 1;

  //control b
  if ( b->m_Digit == '0' && !(b->m_Next) ) return 0;
  for ( ; b->m_Next ; b = b->m_Next )
    if ( ! ( b->m_Digit >= '0' && b->m_Digit <= '9' ) )
      return 1;
  if ( !( b->m_Digit > '0' && b->m_Digit <= '9' ) ) 
    return 1;

  return 0;
}

void shift1 ( TITEM ** a, TITEM ** b ) {
  (*a) = (*a)->m_Next;
  (*b) = (*b)->m_Next;
}

void shift2 ( TITEM ** res, TITEM ** a, TITEM ** b ) {
  (*a) = (*a)->m_Next;
  (*b) = (*b)->m_Next;
  (*res) = (*res)->m_Next;
}

int toInt ( char c ) {
 int i = c - '0';
 return i;
}

char toChar ( int i ) {
  char c = i + '0';
  return c;
}

char addition ( char a, char b, int * rem ) {
  char cRes;
  int iA = toInt ( a ), iB = toInt ( b ), iRes;
  iRes = iA + iB;
  
  if ( *rem ) {
    iRes ++;
    *rem = 0;
  }

  if ( iRes > 9 ) {
    iRes %= 10;
    *rem = 1;
  }

  cRes = toChar ( iRes );
  return cRes;
}

void createZero ( TITEM * a, TITEM * b ) {
  if ( !(a->m_Next) && b->m_Next )
    a->m_Next = createItem ( '0', NULL );      
  if ( !(b->m_Next) && a->m_Next )
    b->m_Next = createItem ( '0', NULL );
}

TITEM * resList ( TITEM * a, TITEM * b ) {
  TITEM * res;

  int rem = 0;
  char digit = addition ( a->m_Digit, b->m_Digit, &rem );
  res = createItem ( digit , NULL );
  TITEM * head = res;

  createZero ( a, b );
  shift1 ( &a, &b );

  while ( a || b ) {
    createZero ( a, b );
    digit = addition ( a->m_Digit, b->m_Digit, &rem );
    res->m_Next = createItem ( digit, NULL );
    shift2 ( &res, &a, &b );
  }

  if ( rem == 1 ) {
    res->m_Next = createItem ( '1', NULL );
  }
  return head;
}

TITEM * addList ( TITEM * a, TITEM * b ) {
  printf ("a ");
  printList ( a );
  printf ("b ");
  printList ( b );
  printf ("\n");

  if ( !a || !b ) return NULL;
  if ( checkDigits ( a, b ) ) return NULL;

  TITEM * res = resList ( a, b );
  printf ("result ");
  printList ( res );
  printf ("\n");
  return res;
}
 
#ifndef __PROGTEST__
 
int main(int argc, char *argv[]) {
    TITEM * a, * b, * res;
 
    a = createItem('x', NULL);
    b = createItem('3', NULL);
    res = addList(a, b);
    assert (res == NULL);
    deleteList(a);
    deleteList(b);
 
    a = createItem('5',
         createItem('0',
          createItem('0', NULL)));
    b = createItem('3', NULL);
    res = addList(a, b);
    assert (res == NULL);
    deleteList(a);
    deleteList(b);
 
    a = createItem('3',
         createItem('4',
          createItem('5', NULL)));
    b = createItem('0', NULL);
    res = addList(a, b);
    assert (res->m_Digit == '3');
    assert (res->m_Next->m_Digit == '4');
    assert (res->m_Next->m_Next->m_Digit == '5');
    assert (res->m_Next->m_Next->m_Next == NULL);
    deleteList(res);
    deleteList(a);
    deleteList(b);

    a = createItem('9',
         createItem('9',
          createItem('9', NULL)));
    b = createItem('1', NULL);
    res = addList(a, b);
    assert (res->m_Digit == '0');
    assert (res->m_Next->m_Digit == '0');
    assert (res->m_Next->m_Next->m_Digit == '0');
    assert (res->m_Next->m_Next->m_Next->m_Digit == '1');
    assert (res->m_Next->m_Next->m_Next->m_Next == NULL);
    deleteList(res);
    deleteList(a);
    deleteList(b);

    a = createItem('3',
         createItem('4',
          createItem('1', NULL)));
    b = createItem('3',
         createItem('4',
          createItem('1', NULL)));
    res = addList(a, b);
    assert (res->m_Digit == '6');
    assert (res->m_Next->m_Digit == '8');
    assert (res->m_Next->m_Next->m_Digit == '2');
    assert (res->m_Next->m_Next->m_Next == NULL);
    deleteList(res);
    deleteList(a);
    deleteList(b);

    a = createItem('3',
         createItem('4',
          createItem('5', NULL)));
    b = createItem('3',
         createItem('4',
          createItem('5', NULL)));
    res = addList(a, b);
    assert (res->m_Digit == '6');
    assert (res->m_Next->m_Digit == '8');
    assert (res->m_Next->m_Next->m_Digit == '0');
    assert (res->m_Next->m_Next->m_Next->m_Digit == '1');
    assert (res->m_Next->m_Next->m_Next->m_Next == NULL);
    deleteList(res);
    deleteList(a);
    deleteList(b);

    a = createItem('3',
         createItem('4',
          createItem('5', NULL)));
    b = createItem('3',
         createItem('4',
          createItem('x', NULL)));
    res = addList(a, b);
    assert (res == NULL);
    deleteList(a);
    deleteList(b);

    a = createItem('3',
         createItem('4',
          createItem('5', NULL)));
    b = createItem('3',
         createItem('e',
          createItem('3', NULL)));
    res = addList(a, b);
    assert (res == NULL);
    deleteList(a);
    deleteList(b);

    a = createItem('3',
        createItem('4',
        createItem('5', NULL)));
    b = NULL;
    res = addList(a, b);
    assert (res == NULL);
    deleteList (a);

    return 0;
}
 
#endif /* __PROGTEST__ */