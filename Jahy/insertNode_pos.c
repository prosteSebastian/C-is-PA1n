#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

typedef struct SinglyLinkedList 
{
  int data;
  struct SinglyLinkedList* next;
} SinglyLinkedListNode;

SinglyLinkedListNode* insertNodeAtPosition(SinglyLinkedListNode* llist, int data, int position)
{
  SinglyLinkedListNode * head = llist;
  SinglyLinkedListNode * cpy = (SinglyLinkedListNode*) malloc(sizeof(SinglyLinkedListNode));
  for (int i = 0; i < position; i++)
  {
    if ( llist->next == NULL )
    {
      cpy->next = NULL;
      cpy->data = data;
      llist->next = cpy;
      return head;
    }
    llist = llist->next;
  }
  cpy->next = llist->next;
  cpy->data = llist->data;
  llist->data = data;
  llist->next = cpy;

  return head;
}

SinglyLinkedListNode * insert_tail ( SinglyLinkedListNode * head, int data )
{
  if ( head == NULL )
  {
  head = (SinglyLinkedListNode *) malloc(sizeof(SinglyLinkedListNode));
  head->next = NULL;
  head->data = data;
  return head;
  }
  else
  {
  SinglyLinkedListNode * newhead = head;
  while( head->next != NULL )
  {
    head=head->next;
  }
  head->next = (SinglyLinkedListNode *) malloc(sizeof(SinglyLinkedListNode));
  head->next->next = NULL;
  head->next->data = data;
  return newhead;
  }
}

void  freeNode ( SinglyLinkedListNode * a )
{
  if (a == NULL)
  {
    return;
  }
  SinglyLinkedListNode * tmp = a->next;
  free(a);
  freeNode(tmp);
}

int main (void)
{
  SinglyLinkedListNode * a = NULL;

  a = insert_tail(a,1);
  a = insert_tail(a,2);
  a = insert_tail(a,3);
  a = insert_tail(a,4);
  SinglyLinkedListNode * head = a;

  a = head;
  a = insertNodeAtPosition(a,6,4);
  
  while(a)
  {
    printf("data: %d\n", a->data);
    a=a->next;
  }
  a = head;
  freeNode(a);
  return 1;
}