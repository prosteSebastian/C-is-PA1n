#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

typedef struct insertNode_tail
{
  int data;
  struct insertNode_tail * next;
} TNODE;

TNODE * insert_tail ( TNODE * head, int data )
{
  if ( head == NULL )
  {
    head = (TNODE *) malloc(sizeof(TNODE));
    head->next = NULL;
    head->data = data;
    return head;
  }
  else
  {
    TNODE * newhead = head;
    while( head->next != NULL )
    {
      head=head->next;
    }
    head->next = (TNODE *) malloc(sizeof(TNODE));
    head->next->next = NULL;
    head->next->data = data;
    return newhead;
  }
}

void  freeNode ( TNODE * a )
{
  if (a == NULL)
  {
    return;
  }
  TNODE * tmp = a->next;
  free(a);
  freeNode(tmp);
}

int main ( void ) 
{
  TNODE * a = NULL;

  a = insert_tail(a,141);
  a = insert_tail(a,666);
  a = insert_tail(a,777);
  a = insert_tail(a,451);
  TNODE * head = a;
  while(a)
  {
    printf("data: %d\n", a->data);
    a=a->next;
  }
  a = head;
  freeNode(a);
  return 1;
}