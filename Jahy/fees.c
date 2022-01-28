#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct fees
{
  int day;
  int hour;
  int minutes;
  char rz[11];
} TNODE;

int toInt ( char min )
{
  int n = min - '0';
  return ( n<0 || n>9 ) ? -1 : n;
}

void freeList ( TNODE ** a, int n )
{
  if ( a == NULL )
  {
    return;
  }
  for (int i = 0; i < n; i++)
  {
    if ( a[i] != NULL ) {
      free(a[i]);
    }
  }  
  free(a);
}

// return index (i) of RZ or (-1) if not found
int findRZ ( TNODE ** a, int n, char * spz )
{
  for (int i = 0; i < n; i++)
  {
    if ( a[i] != NULL ) {
      if ( strcmp(spz, a[i]->rz) == 0 )
      {
        return i;
      }
    }
  }
  return -1;
}

// return cost of parking
int findCost ( int cost )
{
  if ( cost <= 30 )
  {
    cost = 0;
  }
  else if ( cost > 30 && cost <= 60 )
  {
    cost = 30;
  }
  else if ( cost > 60 && cost <= 1440 )
  {
    if ( (cost%60) == 0 )
    {
      cost = (cost/60) * 40;
    }
    else
    {
      cost = (cost/60) * 40;
      cost += 40;
    }
  }
  else
  {
    if ( (cost%1440) == 0 )
    {
      cost = (cost/1440) * 1000;
    }
    else
    {
      cost = (cost/1440) * 1000;
      cost += 1000;
    }
  }
  return cost;
}

// return (451) for valid or (0) for invalid input
int checkIn ( int h, int min, int in, TNODE ** arr, int n ) 
{
  if ( in != 3 )
  {
    return 0;
  }
  if ( h < 0 || h > 23 )
  {
    return 0;
  }
  if ( min < 0 || min > 59 )
  {
    return 0;
  }
  return 451;
}

int main (void) 
{
  TNODE ** arr = (TNODE**) malloc( 100 * sizeof(TNODE*) );
  int h = 0, min = 0, min1 = 0, min2 = 0, n = 0, in = 0, cnt = 0, cost = 0, out = 0;
  char inf;
  char m[3];
  char spz[11];

  printf("Log:\n");
  while ( !feof(stdin) )
  {
    in = scanf("%d:%2s %c", &h, m, &inf);
    min1 = toInt(m[0]);
    min2 = toInt(m[1]);
    min = (min1*10) + min2;

    if ( feof(stdin) )
    {
      printf("Pocet aut: %d\n", cnt);
      break;
    }
    if ( checkIn(h,min,in,arr,n) == 0 )
    {
      printf("Nespravny vstup.\n");
      freeList(arr,n);
      return 0;
    }
    
    if ( inf == '+' ) 
    {
      scanf("%10s", spz);

      // if RZ not found
      if ( findRZ(arr,n,spz) == -1 )
      {
        arr[n] = (TNODE*) malloc( 11 * sizeof(TNODE) );
        arr[n]->hour = h;
        arr[n]->minutes = min;
        arr[n]->day = 0;
        strncpy(arr[n]->rz,spz,sizeof(spz));
        n++;
        // total parked cars
        cnt++;
        printf("OK\n");
      }
      else
      {
        printf("Uz tu je.\n");
      }
    }
    if ( inf == '-' )
    {
      scanf("%10s", spz);
      out = findRZ(arr,n,spz);
      // RZ not found
      if ( out == -1 )
      {
        printf("Nenalezeno.\n");
      }
      else
      {
        // cost = time car left - time car arrived
        cost += ( (h*60) + min );
        cost -= ( (arr[out]->hour*60) + arr[out]->minutes );
        // if car leave before arrive
        if ( cost < 0 )
        {
          printf("Nespravny vstup.\n");
          freeList(arr,n);
          return 0;
        }
        // add 1440 mins for every day car stays
        if ( arr[out]->day > 0 )
        {
          cost += arr[out]->day * 1440;
        }
        printf("RZ: %s, cena %d\n", spz, findCost(cost) );
        // NULL everything
        cost = 0;
        arr[out]->hour = 0;
        arr[out]->minutes = 0;
        strncpy( arr[out]->rz, "", 1 );
        // car left = -1 parked car
        cnt--;
      }
    }
    if ( inf == '=' )
    {
      // if time is not '0:00'
      if ( h != 0 || min != 0 )
      {
        printf("Nespravny vstup.\n");
        freeList(arr,n);
        return 0;
      }
      // adds 1day to every parked car
      for (int i = 0; i < n; i++)
      {
        arr[i]->day += 1 ;
      }
    }
  }
  freeList(arr,n);
  return 1;
}