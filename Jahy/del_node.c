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

SinglyLinkedListNode* deleteNode(SinglyLinkedListNode* llist, int position)
{
    if ( llist == NULL )
    {
        return NULL;
    }

    SinglyLinkedListNode * head = llist;
    SinglyLinkedListNode * cpy = NULL;
    if ( position == 0 )
    {
      if ( llist->next != NULL )
      {
        cpy = llist->next;
      }
      else
      {
        return NULL;
      }
      //free(llist);
      return cpy;
    }
    else
    {
      for (int i = 0; i < position; i++)
      {
        if ( (i+1) >= position )
        {
          cpy = llist;
        }
        llist = llist->next;
      }

      if ( llist->next != NULL )
      {
        cpy->next = llist->next;
      }
      else
      {
        cpy->next = NULL;
      }
    }
    free(llist);
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

int main ( void ) 
{
  SinglyLinkedListNode * a = NULL;

  a = insert_tail(a,1);
  a = insert_tail(a,2);
  a = insert_tail(a,3);
  a = insert_tail(a,4);
  SinglyLinkedListNode * head = a;

  a = head;
  a = deleteNode(a,0);
  
  while(a)
  {
    printf("data: %d\n", a->data);
    a=a->next;
  }
  a = head;
  freeNode(a);
  return 1;
}