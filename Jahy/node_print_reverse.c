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

void reversePrint(SinglyLinkedListNode* llist) {
    int len = 2;
    int * arr = (int*) malloc( len * sizeof(int) );
    int n = 0;
    while (llist)
    {
        arr[n] = llist->data;
        llist = llist->next;
        n++;
        if (n >= len)
        {
            len *= 2;
            arr = (int*)realloc(arr, len * sizeof(int));
        }
    }
    n -= 1;
    for (; n >= 0; n--) {
        printf("%d\n", arr[n]);
    }
    free(arr);
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
  reversePrint(a);
  /*
  while(a)
  {
    printf("data: %d\n", a->data);
    a=a->next;
  }*/
  a = head;
  freeNode(a);
  return 1;
}