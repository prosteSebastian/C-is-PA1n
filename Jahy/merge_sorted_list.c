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


SinglyLinkedListNode* mergeLists(SinglyLinkedListNode* head1, SinglyLinkedListNode* head2)
{
    if (head1==NULL || head2==NULL)
    {
        return NULL;
    }
    SinglyLinkedListNode * c = (SinglyLinkedListNode*)malloc(sizeof(SinglyLinkedListNode));
    SinglyLinkedListNode * head_c = c;
    while (head1)
    {
        if (head1->next == NULL)
        {
            c->next = NULL;
            c->data = head1->data;
        }
        else
        {
            c->next = (SinglyLinkedListNode*)malloc(sizeof(SinglyLinkedListNode));
            c->data = head1->data;
            c = c->next;
        }
        head1 = head1->next;
    }
    c = head_c;
    SinglyLinkedListNode * tmp = NULL;
    while(head2)
    {
        if ( c->data >= head2->data )
        {
            tmp = (SinglyLinkedListNode*)malloc(sizeof(SinglyLinkedListNode));
            tmp->data = c->data;
            tmp->next = c->next;
            c->data = head2->data;
            c->next = tmp;
            c = c->next;
            head2 = head2->next;
        }
        else 
        {
            c = c->next;
        }
    }
    return head_c;
}

int main (void)
{
  SinglyLinkedListNode * a = NULL;
  SinglyLinkedListNode * b = NULL;
  SinglyLinkedListNode * c = NULL;

  a = insert_tail(a,1);
  a = insert_tail(a,3);
  a = insert_tail(a,7);
  SinglyLinkedListNode * head_a = a;

  b = insert_tail(b,1);
  b = insert_tail(b,2);
  SinglyLinkedListNode * head_b = b;

  a = head_a;
  b = head_b;
  c = mergeLists(a,b);
  SinglyLinkedListNode * head_c = c;
  
  while(c)
  {
    printf("data: %d\n", c->data);
    c=c->next;
  }
  a = head_a;
  b = head_b;
  c = head_c;
  freeNode(a);
  freeNode(b);
  freeNode(c);
  return 1;
}