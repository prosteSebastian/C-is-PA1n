#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct poly
{
  int num;
  int moc;
  struct poly * next;
} TNODE;

TNODE * createNode ( TNODE * a, int num, int moc )
{
  TNODE * b = (TNODE*) malloc(sizeof(TNODE));
  b->num = num;
  b->moc = moc;
  b->next = a;
  return b;
}

void freeNode ( TNODE * a )
{
  if ( a== NULL )
  {
    return;
  }
  TNODE * tmp = a->next;
  free(a);
  freeNode(tmp);
}

TNODE * copyNode ( TNODE * a )
{
  TNODE * head_a = a;
  while ( a )
  {
    if ( a->next != NULL )
    {
      if ( a->moc > a->next->moc )
      {
        return NULL;
      }
      if (a->moc==NULL)
      {
        return NULL;
      }
    }
    a = a->next;
  }
  a = head_a;
  TNODE * c = (TNODE*) malloc(sizeof(TNODE));
  TNODE * head_c = c;
  while ( a )
  {
    if ( a->next == NULL )
    {
      c->next = NULL;
      c->num = a->num;
      c->moc = a->moc;
    }
    else
    {
      c->next = (TNODE*) malloc(sizeof(TNODE));
      c->moc = a->moc;
      c->num = a->num;
      c = c->next;
    }
    a = a->next;
  }
  return head_c;
}

TNODE * getPoly ( TNODE * a, TNODE * b )
{
  if ( a == NULL && b != NULL )
  {
    TNODE * c = copyNode(b);
    return c;
  }
  if ( a != NULL && b == NULL )
  {
    TNODE * c = copyNode(a);
    return c;
  }
  if ( a == NULL && b == NULL )
  {
    return NULL;
  }
  if ( a->num == 0 && a->moc == 0 && a->next == NULL )
  {
    TNODE * c = copyNode(b);
    return c;
  }
  if ( b->num == 0 && b->moc == 0 && b->next == NULL )
  {
    TNODE * c = copyNode(a);
    return c;
  }

  TNODE * head_b = b;
  while ( b )
  {
    if ( b->next != NULL )
    {
      if ( b->moc > b->next->moc )
      {
        return NULL;
      }
      if (b->moc==NULL)
      {
        return NULL;
      }
    }
    b = b->next;
  }
  b = head_b;
  //copy 'a' to 'c'
  TNODE * c = copyNode(a);
  if ( c == NULL )
  {
    return NULL;
  }
  TNODE * head_c = c;

  c = head_c;
  while ( b )
  {
    if ( b->moc == c->moc )
    {
      c->num += b->num;
      c = c->next;
      b = b->next;
    }
    else if ( b->moc < c->moc )
    {
      TNODE * tmp = (TNODE*) malloc(sizeof(TNODE));
      tmp->num = c->num;
      tmp->moc = c->moc;
      tmp->next = c->next;

      c->moc = b->moc;
      c->num = b->num;
      c->next = tmp;

      b = b->next;
    }
    else
    {
      c = c->next;
    }
  }
  return head_c;
}

int main ( void )
{
  TNODE * a = NULL;
  TNODE * head_a = NULL;
  TNODE * b = NULL;
  TNODE * head_b = NULL;
  TNODE * c = NULL;
  TNODE * head_c = NULL;
  
  a = createNode(a,9,3);
  a = createNode(a,2,1);
  a = createNode(a,3,0);
  head_a = a;
  /*
  a = createNode(a,9,3);
  a = createNode(a,2,4);
  a = createNode(a,3,0);
  head_a = a;
  */
  
  b = createNode(b,-1,3);
  b = createNode(b,4,2);
  b = createNode(b,7,0);
  head_b = b;
  
  /*
  b = createNode(b,7,NULL);
  head_b = b;
  */
  /*
  b = createNode(b,0,0);
  head_b = b;
  */
  /*
  b = createNode(b,-1,3);
  b = createNode(b,4,4);
  b = createNode(b,7,0);
  head_b = b;
  */
  c = getPoly( a, b );
  head_c = c;

  if ( c != NULL )
  {
    while (c)
    {
      printf("%d^%d\n",c->num,c->moc);
      c = c->next;
    }
  }

  a = head_a;
  b = head_b;
  c = head_c;
  if (a != NULL){freeNode(a);}
  if (b != NULL){freeNode(b);}
  if (c != NULL){freeNode(c);}
  return 0;
}