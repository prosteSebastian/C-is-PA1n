#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct {
  int m_Elev;
  int m_Dist;
} Tpath;

void printArr ( Tpath * a, size_t i ) {
  printf("Distance ");
  for ( size_t j = 0 ; j < i ; ++j )
    printf (" %4d", a[j].m_Dist);
  printf("\n");

  printf("Elevation");
  for ( size_t j = 0 ; j < i ; ++j )
    printf (" %4d", a[j].m_Elev);
  printf("\n");
}

void scaleUpArr ( Tpath ** a, size_t * size ) {
  size_t newS = (*size) * 2; 
  *a = (Tpath*) realloc ( *a, sizeof(*a) * newS );
  (*size) = newS;
}

void getInput ( Tpath ** arr, size_t * i, size_t * size ) {
  Tpath * tmp = (Tpath*) malloc ( sizeof(*tmp) );
  int input;

  printf("*Cyklotrasa:*\n");
  scanf (" %d", &((*arr+*i)->m_Elev));
  (*arr+*i)->m_Dist = 0;
  (*i)++;

  while ( 1 ) {
    input = scanf (" + %d %d", &(tmp->m_Dist), &(tmp->m_Elev));
    if ( input == 2 ) {
      if ( *i >= *size )
        scaleUpArr ( arr, size );      
      (*arr+*i)->m_Dist = tmp->m_Dist;
      (*arr+*i)->m_Elev = tmp->m_Elev;
      (*i)++;
    }
    else {
      break;
    }
  }
  free ( tmp );
}

int getMaxValues ( Tpath * arr, Tpath * max,
                  size_t size, int * maxE, int * maxD ) {
  int resElev, resDist, cnt = 0;

  for ( size_t j = 1 ; j < size ; ++j ) {
    if ( arr[j].m_Elev <= max->m_Elev ) {
      resElev = max->m_Elev - arr[j].m_Elev;     
      resDist = arr[j].m_Dist - max->m_Dist;
      
      if ( resElev > *maxE ) {
        *maxE = resElev; 
        cnt = 0;
      }
      
      if ( resElev == *maxE && resDist >= *maxD ) {
        if ( resDist == *maxD )
          cnt++;
        else {
          *maxD = resDist; 
          cnt = 1;
        } 
      }
    }
    else {
      max = (arr+j);      
    }
  }
  return cnt;
}

void printPaths ( Tpath * a, Tpath * max, 
                size_t size, int elev, int dist ) {
  
  int resElev, resDist;

  for ( size_t j = 1 ; j < size ; ++j ) {
    if ( a[j].m_Elev <= max->m_Elev ) {
      resElev = max->m_Elev - a[j].m_Elev;     
      resDist = a[j].m_Dist - max->m_Dist;
      
      if ( resElev == elev && resDist == dist ) {
        printf ("*+ %d (%d) -> + %d (%d)*\n", max->m_Dist
                                            , max->m_Elev
                                            , a[j].m_Dist
                                            , a[j].m_Elev);
      }
    }
    else {
      max = (a+j);      
    }
  }
}

void getPaths ( Tpath * arr, size_t size ) {
  Tpath * max = arr;
  int maxElev = 0, maxDist = 0, cnt = 0;

  cnt = getMaxValues ( arr, max, size, &maxElev, &maxDist );
  if ( cnt == 0 ) {
    printf ("*Nenalezeno*\n");
  }
  else {
    printf ("*%d km, klesani: %d m, varianty: %d*\n", maxDist
                                                    , maxElev
                                                    , cnt);
    printPaths ( arr, max, size, maxElev, maxDist );
  }
}

int main (  ) {
  Tpath * paths;
  size_t index = 0, size = 5;
  paths = (Tpath*) malloc ( sizeof(*paths) * size );
  
  getInput ( &paths, &index, &size );

  //printArr ( paths, index );

  getPaths ( paths, index ); 

  free ( paths );
  return 0;
}