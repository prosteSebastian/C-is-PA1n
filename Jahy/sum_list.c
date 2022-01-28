#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
 
typedef struct TItem {
    struct TItem * m_Next;
    char m_Digit;
} TITEM;
 
TITEM * createItem ( char digit, TITEM * a ) {
  TITEM * b = (TITEM*) malloc( sizeof(TITEM) );
  b->m_Digit = digit;
  b->m_Next = a;
  return b;
}

void deleteList ( TITEM * a ) {
  if ( a == NULL ) {
    return;
  }
  TITEM * tmp = a->m_Next;
  free(a);
  deleteList(tmp);
}

int toInt ( char digit ) {
  int n = digit - '0';
  return ( n < 0 || n > 9 ) ? -1 : n;
}

char toChar ( int n ) {
  char digit = n + '0';
  return digit;
}

TITEM * addList ( TITEM * a, TITEM * b ) {
  if ( a == NULL || b == NULL ) {
    return NULL;
  }
  TITEM * x = a;
  TITEM * y = b;
  int lenX = 0, lenY = 0;
  while ( x ) {
    if ( toInt(x->m_Digit) == -1 || ( lenX!=0 && x->m_Next == NULL && x->m_Digit == '0' ) ) {
      return NULL;
    }
    x = x->m_Next;
    lenX++;
  }
  while ( y ) {
    if ( toInt(y->m_Digit) == -1 || ( lenY!=0 && y->m_Next == NULL && y->m_Digit == '0' ) ) {
      return NULL;
    }
    y = y->m_Next;
    lenY++;
  }
  if ( lenX >= lenY ) {
    x = a;
    y = b;
  }
  else {
    x = b;
    y = a;
  }

  TITEM * c = (TITEM*) malloc( sizeof(TITEM) );
  TITEM * head = c;

  for (; x; x = x->m_Next) {
    c->m_Digit = x->m_Digit;
    c->m_Next = NULL;
    if ( x->m_Next ) {
      c->m_Next = (TITEM*) malloc( sizeof(TITEM) );
      c = c->m_Next;
    }
  }

  c = head;
  int sum = 0, rem = 0, tmp = 0;
  for (; c; c = c->m_Next) {
    if ( y!=NULL ) {
      tmp = toInt(c->m_Digit);
      if ( tmp == -1 )
      {
        tmp = 0;
      }
      sum = tmp + toInt(y->m_Digit) + rem;
    }
    else {
      sum = toInt(c->m_Digit) + rem;
    }
    
    rem = 0;
    if ( sum < 10 ) {
      c->m_Digit = toChar(sum);
    }
    else {
      c->m_Digit = toChar(sum%10);
      rem = 1;
      if ( c->m_Next==NULL )
      {
        c->m_Next = (TITEM*) malloc( sizeof(TITEM) );
        c->m_Next->m_Next = NULL;
        c->m_Digit = '0';
      }
    }
    if ( y->m_Next!=NULL ) {
      y = y->m_Next;
    }
    else {
      y->m_Digit = '0';
    }
    sum=0;
  }
  
  return head;
}

int main ( int argc, char *argv[] ) {
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

    a = createItem('2', createItem('3', createItem('3', NULL)));
    b = createItem('5', createItem('3', createItem('1', NULL)));
    res = addList(a, b);
    assert (res->m_Digit == '7');
    assert (res->m_Next->m_Digit == '6');
    assert (res->m_Next->m_Next->m_Digit == '4');
    assert (res->m_Next->m_Next->m_Next == NULL);
    deleteList(res);
    deleteList(a);
    deleteList(b);
 
    a = createItem('2', createItem('3', createItem('9', NULL)));
    b = createItem('5', createItem('3', createItem('1', NULL)));
    res = addList(a, b);
    assert (res->m_Digit == '7');
    assert (res->m_Next->m_Digit == '6');
    assert (res->m_Next->m_Next->m_Digit == '0');
    assert (res->m_Next->m_Next->m_Next->m_Digit == '1');
    assert (res->m_Next->m_Next->m_Next->m_Next == NULL);
    deleteList(res);
    deleteList(a);
    deleteList(b);

    return 0;
}