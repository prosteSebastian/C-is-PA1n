#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct vyska_kles
{
  int km;
  int vyska;
} TNODE;

typedef struct vyska_kles2
{
  int a1_km;
  int a1_vyska;
  int a2_km;
  int a2_vyska;
} TNODE_res;

void printEnd ( TNODE_res * arr, int cnt, int max, int max_km )
{
  printf("%d km, klesani: %d m, varianty: %d\n", max_km, max, cnt);
  for (int i = 0; i < cnt; i++)
  {
    printf("+ %d (%d) -> + %d (%d)\n", arr[i].a1_km, arr[i].a1_vyska, arr[i].a2_km, arr[i].a2_vyska);
  }
}

int main (void)
{
  int start = 0, km = 0, vyska = 0, n = 0, max = -1, len = 2, tmp = 0, tmp2 = 0, cnt = 0, j = 1, max_km = 0;
  char * line = NULL;
  size_t buffer;
  TNODE * arr = (TNODE*) malloc( len * sizeof(TNODE) );
  TNODE_res * arr_res = (TNODE_res*) malloc( 100 * sizeof(TNODE_res) );
  printf("Cyklovylet:\n");
  
  while ( getline(&line, &buffer, stdin) )
  {
    if ( feof(stdin) )
    {
      free(line);
      break;
    }
    
    if ( n == 0 )
    {
      sscanf( line, "%d", &start );
      arr[n].vyska = start;
      arr[n].km = 0;
      n++;
      continue;
    }

    sscanf( line, "+ %d %d", &km, &vyska );
    arr[n].km = km;
    arr[n].vyska = vyska;
    if ( n > 0 && arr[n-j].vyska >= arr[n].vyska && arr[n-j].km <= arr[n].km )
    {
      tmp = arr[n-j].vyska - arr[n].vyska;
      //printf("tmp: %d = [%d]%d - [%d]%d\n", tmp, n-j,arr[n-j].vyska, n,arr[n].vyska);
      tmp2 = arr[n].km - arr[n-j].km; 
      //printf("tmp2: %d = %d - %d\n", tmp2, arr[n].km, arr[n-j].km);
      if ( tmp >= max && tmp2 >= max_km )
      {
        if ( tmp > max || tmp2 > max_km )
        {
          cnt = 0;
        }
        max = tmp;
        max_km = tmp2;

        arr_res[cnt].a1_km = arr[n-j].km;
        arr_res[cnt].a1_vyska = arr[n-j].vyska;
        arr_res[cnt].a2_km = arr[n].km;
        arr_res[cnt].a2_vyska = arr[n].vyska;
        cnt++;
      }
      j++;
    }
    else
    {
      if ( j != 1 )
      {
        j = 1;
      }
    }

    n++;
    if ( n == len )
    {
      len *= 2;
      arr = (TNODE*) realloc( arr, len * sizeof(TNODE) );
    }
  }
  free(arr);

  if ( cnt == 0 )
  {
    printf("Nenalezeno\n");
  }
  else
  {
    printEnd(arr_res, cnt, max, max_km);
  }
  free(arr_res);
  return 0;
}