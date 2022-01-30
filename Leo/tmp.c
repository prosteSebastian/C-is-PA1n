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
      if ( *i >= *size ) {
        scaleUpArr ( arr, size ); 
      }
        
      (*arr+*i)->m_Dist = tmp->m_Dist;
      (*arr+*i)->m_Elev = tmp->m_Elev;
      (*i)++;
    }
    else {
      break;
    }
  }
  printArr ( *arr, *i );
  free ( tmp );
}

int main (  ) {
  Tpath * paths;
  size_t index = 0, size = 5;
  paths = (Tpath*) malloc ( sizeof(*paths) * size );
  getInput ( &paths, &index, &size );
  printArr ( paths, index ); 
  free ( paths );
  return 0;
}
