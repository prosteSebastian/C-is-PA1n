#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct eancode {
    int count;
    char num[101];
} Tean;

int isNum ( char * ean )
{
  int len = strlen(ean);
  for (int i = 0; i < len; i++)
  {
    if ( isdigit(ean[i]) == 0 )
    {
      return 0;
    }
  }
  return 1;
}

void freeNode ( Tean ** a, int n )
{
  if ( a == NULL )
  {
    return;
  }
  for (int i = 0; i < n; i++)
  {
    free(a[i]);
  }
  free(a);
}

int findEAN ( Tean ** arr, int n, char * newEAN )
{
  for (int i = 0; i < n; i++)
  {
    if ( strcmp( newEAN, arr[i]->num ) == 0 )
    {
      return i;
    }
  }
  return -1;  
}

int checkIn ( Tean ** arr, int n, char * ean )
{
  if ( isNum(ean) == 0 )
  {
    printf("EAN neni cislo\n");
    freeNode(arr,n);
    return 0;
  }
  int len = strlen(ean)+1;
  if ( len < 6 || len > 101 )
  {
    printf("ean neni 4<EAN<101\n");
    freeNode(arr,n);
    return 0;
  }
  return 1;
}

int main ( void )
{
  char inf[2], yx;
  int cnt = 0, n = 0, now = 0;
  char ean[101];
  Tean ** arr = (Tean**) malloc( 100 * sizeof(Tean*) );

  printf("Operace:\n");
  while ( !feof(stdin) )
  {
    scanf("%s", inf);
    if ( inf[0] != '+' && inf[0] != '-' )
    {
      printf("Spatny\n");
      freeNode(arr,n);
      return 0;
    }
    if ( feof(stdin) )
    {
      for (int i = 0; i < n; i++)
      {
        printf("pocet: %dx %s\n", arr[i]->count, arr[i]->num );
      }
    }
    
    if ( inf[0] == '+' )
    {
      scanf(" %d%c %s", &cnt, &yx, ean);
      if ( yx != 'x' )
      {
        printf("Chybi x\n");
        freeNode(arr,n);
        return 0;
      }
      if ( checkIn(arr,n,ean) == 0 ) {
        return 0;
      }
      now = findEAN(arr,n,ean);
      if ( now == (-1) )
      {
        arr[n] = (Tean*) malloc( 101 * sizeof(Tean) );
        arr[n]->count = cnt;
        strncpy( arr[n]->num, ean, sizeof(ean) );
        printf("%dx\n", arr[n]->count);
        n++;
      }
      else
      {
        arr[now]->count += cnt;
        printf("%dx\n", arr[now]->count);
      }
    }
    if ( inf[0] == '-' )
    {
      scanf(" %d%c %s", &cnt, &yx, ean);
      if ( yx != 'x' )
      {
        printf("Chybi x\n");
        freeNode(arr,n);
        return 0;
      }
      if ( checkIn(arr,n,ean) == 0 ) {
        return 0;
      }
      now = findEAN(arr,n,ean);
      if ( now != (-1) )
      {
        if ( arr[now]->count < cnt )
        {
          printf("neni dost kusu\n");
        }
        else {
          arr[now]->count -= cnt;
          printf("%dx\n", arr[now]->count);
        }
      }
      else
      {
        printf("Spatne EAN\n");
        freeNode(arr,n);
        return 0;
      }
    }
  }

  freeNode(arr,n);
  return 1;
}