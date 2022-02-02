#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

typedef struct Titem
{
  struct Titem * m_Next;
  int m_Val;
} TITEM;

TITEM * createItem ( int val, TITEM * next )
{
  TITEM * a = (TITEM*) malloc ( sizeof(TITEM) );
  a->m_Val = val;
  a->m_Next = next;
  return a;
}

void delList ( TITEM * a )
{
  if ( a == NULL )
  {
    return;
  }
  TITEM * tmp = a->m_Next;
  free(a);
  delList(tmp);
}

int checkNULL ( TITEM ** a, int nr )
{
  for (int i = 0; i < nr; i++)
  {
    if ( a[i] == NULL )
    {
      return 1;
    }
  }
  return 0;
}

int notBigger ( TITEM ** a, int nr )
{
  TITEM * tmp;
  for (int i = 0; i < nr; i++)
  {
    tmp = a[i];
    while ( tmp )
    {
      if ( tmp->m_Next != NULL && tmp->m_Val > tmp->m_Next->m_Val )
      {
        return 1;
      }
      tmp = tmp->m_Next;
    }
  }
  return 0;
}

void printNode ( TITEM * a )
{
  while ( a )
  {
    printf("%d -> ", a->m_Val);
    a = a->m_Next;
  }
  printf("\n");
}

int comp(const void* a, const void* b)
{
    int arg1 = *(const int*)a;
    int arg2 = *(const int*)b;
 
    if (arg1 < arg2) return -1;
    if (arg1 > arg2) return 1;
    return 0;
}

TITEM * compareList ( TITEM ** x, int nr )
{
  if ( checkNULL( x, nr ) ) { return NULL; }
  if ( notBigger( x, nr ) ) { return NULL; }

  TITEM * tmp;
  int len = 2, n = 0;
  int * arr = (int*) malloc ( len * sizeof(int) );
  
  for (int i = 0; i < nr; i++)
  {
    tmp = x[i];
    while ( tmp )
    {
      arr[n] = tmp->m_Val;
      n++;
      if ( n == len )
      {
        len *= 2;
        arr = (int*) realloc( arr, len * sizeof(int) );
      }
      tmp = tmp->m_Next;
    }
  }

  for (int i = 0; i < nr; i++)
  {
    delList(x[i]);
  }
  

  qsort( arr, n, sizeof(int), comp);

  TITEM * res = (TITEM*) malloc ( sizeof(TITEM) );
  TITEM * head = res;
  for (int i = 0; i < n; i++)
  {
    if ( i == (n-1) )
    {
      res->m_Val = arr[i];
      res->m_Next = NULL;
    }
    else
    {
      res->m_Next = (TITEM*) malloc ( sizeof(TITEM) );
      res->m_Val = arr[i];
      res = res->m_Next;
    }
  }
  
  free(arr);
  printNode(res=head);
  return head;
}

int main ( int argc, char * argv [] )
{
  TITEM * a[5];
  TITEM * res;
  
  a[0] = createItem ( 1,
           createItem ( 7,
             createItem ( 24, NULL )));
  a[1] = createItem ( 3,
           createItem ( 5,
             createItem ( 17, NULL )));
  a[2] = createItem ( -3,
           createItem ( 19, NULL ));
  res = compareList ( a, 3 );
  delList ( res );
  
  
  a[0] = createItem ( 15,
           createItem ( 19,
             createItem ( 23,
               createItem ( 192, NULL ))));
  a[1] = createItem ( 17,
           createItem ( 18,
             createItem ( 18,
               createItem ( 21, NULL ))));
  a[2] = createItem ( -3,
          createItem ( 19, NULL ));
  res = compareList ( a, 3 );
  delList ( res );
  
  a[0] = createItem ( 15,
           createItem ( 19,
             createItem ( 19,
               createItem ( 2, NULL ))));
  a[1] = createItem ( 17,
           createItem ( 18,
             createItem ( 18,
               createItem ( 21, NULL ))));
  res = compareList ( a, 2 );
  assert ( res == NULL );
  delList(a[0]);
  delList(a[1]);

  a[0] = createItem ( 15,
           createItem ( 19,
             createItem ( 19,
               createItem ( 2, NULL ))));
  a[1] = NULL;
  a[2] = createItem ( -2,
           createItem ( 1,
             createItem ( 10,
               createItem ( 11, NULL ))));
  res = compareList ( a, 3 );
  assert ( res == NULL );
  delList(a[0]);
  delList(a[2]);


  
    a[0] = createItem(5, NULL);
    a[1] = createItem(1,
                      createItem(2,
                                 createItem(6,
                                            createItem(7,
                                                       createItem(8,
                                                                  createItem(9, NULL))))));                                                             
    res = compareList(a, 2);
    delList(res);
   
   return 0;
}