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

SinglyLinkedListNode* reverse(SinglyLinkedListNode* llist)
{
  if (llist==NULL)
  {
    return NULL;
  }
  SinglyLinkedListNode * head = llist;
  int arr[100];
  int n = 0;
  for(;llist;llist=llist->next)
  {
    arr[n] = llist->data;
    n++;
  }
  llist = head;
  for (int i = n-1; i >= 0; i--)
  {
    llist->data = arr[i];
    llist = llist->next;
  }
  return head;
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
  a = reverse(a);
  
  while(a)
  {
    printf("data: %d\n", a->data);
    a=a->next;
  }
  a = head;
  freeNode(a);
  return 1;
}