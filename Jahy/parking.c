#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct parking {
  int obsazeno; // 1 = ano, 0 = ne
  char rz[11];
} TNODE;

void chyba () {
  printf("Chyba.\n");
}

void freeList ( TNODE ** arr, int x )
{
  for (int i = 0; i < x; i++)
  {
    free(arr[i]);
  }
  free(arr);
}

int main (void) 
{
  printf("Velikost:\n");
  int x = 0, y = 0;
  if ( scanf("%d %d", &x, &y) != 2 || x <= 0 || y <= 0 )
  {
    chyba();
    return 0;
  }
  printf("Pozadavky:\n");
  
  char smer;
  char spz[11];
  int patro = 0, pozice = 0, end = 0, flag = 0;
  TNODE ** arr = (TNODE**) malloc( x * sizeof(TNODE*));
  for (int i = 0; i < x; i++)
  {
    arr[i] = (TNODE*) malloc( y * sizeof(TNODE));
  }

  while ( (end = scanf(" %c", &smer)) == 1 ) {
    if ( smer != '+' && smer != '-' ) {
      printf("alknalf\n");
      chyba();
      freeList(arr, x);
      return 0;
    }
    
    if ( smer == '+' ) {
      scanf(" %d %d %10s", &patro, &pozice, spz);
      if ( patro < 0 || patro >= x )
      {
        chyba();
        freeList(arr, x);
        return 0;
      }
      if ( pozice < 0 || pozice >= y )
      {
        chyba();
        freeList(arr, x);
        return 0;
      }
      if ( strlen(spz) > 10 )
      {
        chyba();
        freeList(arr, x);
        return 0;
      }
      if ( arr[patro][pozice].obsazeno == 1 )
      {
        printf("Obsazeno.\n");
      }
      else
      {
        arr[patro][pozice].obsazeno = 1;
        strcpy( arr[patro][pozice].rz, spz );
        printf("OK\n");
      }
    }
    else if ( smer == '-' ) {
      scanf(" %10s", spz);
      if ( strlen(spz) > 10 )
      {
        printf("aaa\n");
        chyba();
        freeList(arr, x);
        return 0;
      }
      flag = 0;
      for (int i = 0; i < x; i++)
      {
        for (int j = 0; j < y; j++)
        {
          if ( strcmp(arr[i][j].rz,spz) == 0 )
          {
            arr[i][j].obsazeno = 0;
            strcpy( arr[i][j].rz, "" );
            printf("OK\n");
            flag = 1;
            break;
          }
        }
      }
      if ( !flag )
      {
        printf("Nenalezeno.\n");
      }
    }

  }
  freeList(arr, x);
  return 1;
}