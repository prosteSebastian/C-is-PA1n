//zadani: dostanete na vstup kladne cislo uvedene ve spojacich
//ukol: vypocitat mocninu a vratit vysledek ve spojaku
//neplatne vstupy: 
//  spojak zacina na nule, krom nuly
//  spojak obsahuje jine znaky nez cislo
//  spojak je prazdny

#ifndef __PROGTEST__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

typedef struct tnode {
  struct tnode * m_Next;
  char m_Digit;
} Tnode;

Tnode * createItem ( char digit, Tnode * next ) {
  Tnode * list = (Tnode*) malloc ( sizeof (*list) );
  list->m_Next = next;
  list->m_Digit = digit;
  return list;
}

void deleteList ( Tnode * list ) {
  if ( list != NULL )
    deleteList ( list->m_Next );
  free ( list );
}
#endif /* __PROGTEST__ */

//if list contain a character or a zero digit at the end
//return NULL
//count size of helper array
int check ( Tnode * list, int * size ) {
  (*size) = 0;
  if ( list->m_Digit == '0' && list->m_Next == NULL ) {
    (*size)++;
    return 1;
  }
  
  for ( ; list->m_Next != NULL ; list = list->m_Next ) {
    if ( list->m_Digit < '0' || list->m_Digit > '9' )
      return 0;
    (*size)++;
  }
  if ( list->m_Digit <= '0' || list->m_Digit > '9' ) 
    return 0;

  (*size)++;
  return 1;
}

void printList ( Tnode * list ) {
  printf("Digit");
  for ( ; list != NULL ; list = list->m_Next )
    printf (" -> %c", list->m_Digit);
  printf ("\n");
}

void printArray ( int * arr, int i ) {
  printf ("Array");
  for ( int k = 0 ; k < i ; ++k )
    printf (" %i", arr[k]);
  printf("\n");
}

int toInt ( char c ) {
  int i = c - '0';
  return i;
}

char toChar ( int i ) {
  char c = i + '0';
  return c;
}

//push item in list to array
void pushToArray ( Tnode * list, int * arr ) {
  int i = 0;
  for ( ; list != NULL ; list = list->m_Next , ++i )
    arr[i] = toInt ( list->m_Digit );
}
 
void multiplication ( int * res, int * arr, int size ) {
  int reminder = 0, result = 0, index = 0, index2 = 0;
  for ( int i = 0 ; i < size ; ++i ) {
    index2 = index;
    for ( int j = 0 ; j <= size ; ++j ) {
      //after the last multiplication check reminder
      if ( j == size && reminder )
        res[index2] = reminder;
      else if ( j == size && !reminder )
        res[index2] = 0;
      else {
        result = ( arr[i] * arr[j] + reminder ) % 10;
        reminder = ( arr[i] * arr[j] + reminder ) / 10;
        res[index2] += result; 
        if ( res[index2] > 9 ) { 
          result = res[index2];
          res[index2] = result % 10;
          reminder = reminder + result / 10;
        }
        index2++;
      }
    }
    reminder = 0; index++;  
  }
}

//return copied result array to result list
Tnode * toList ( int * arr, int size ) {
  Tnode * list = createItem ( '0' , NULL );
  Tnode * head = list;

  for ( int i = 0 ; i < size ; ++i ) {
    list->m_Next = createItem ( toChar ( arr[i] ), NULL );
    list = list->m_Next;
  }

  if ( list->m_Digit == '0' ) {
    Tnode * preLast = head;
    while ( preLast->m_Next->m_Next != NULL )
      preLast = preLast->m_Next;
    free ( list );
    preLast->m_Next = NULL;
  }

  Tnode * tmp = head->m_Next;
  free ( head );
  head = tmp;

  return head;
}

//return list of results
//copy list into helper array for better counting
Tnode * getResult ( Tnode * list, int numOfDigit ) {
  int * arr = (int*) malloc ( sizeof (*arr) * numOfDigit );
  pushToArray ( list, arr );
  
  int * resArr = (int*) malloc ( sizeof (*arr) * numOfDigit * 2 );
  memset ( resArr, 0, sizeof (*arr) * numOfDigit * 2 );
  
  multiplication ( resArr, arr, numOfDigit );

  Tnode * resList = NULL;
  resList = toList ( resArr, numOfDigit * 2 );

//  printArray ( arr, numOfDigit );
//  printArray ( resArr, numOfDigit * 2 );
  free ( arr );
  free ( resArr );
  return resList;
}

//return list of results
Tnode * power ( Tnode * list ) {
//  printList ( list );
  int numOfDigit = 0;
  if ( list == NULL ) return NULL;
  if ( !check ( list, &numOfDigit ) ) return NULL;

  Tnode * result = NULL;
  result = getResult ( list, numOfDigit );
  printList ( result );

  return result;
}

#ifndef __PROGTEST__
int main ( int argc, char * argv [] )
{
  Tnode * a;
  Tnode * res;

  a = createItem ( '9', 
        createItem ( '9', 
          createItem ( '9', NULL )));
  res = power ( a );
  assert ( res->m_Digit == '1' );
  assert ( res->m_Next->m_Digit == '0' );
  assert ( res->m_Next->m_Next->m_Digit == '0' );
  assert ( res->m_Next->m_Next->m_Next->m_Digit == '8' );
  assert ( res->m_Next->m_Next->m_Next->m_Next->m_Digit == '9' );
  assert ( res->m_Next->m_Next->m_Next->m_Next->m_Next->m_Digit == '9' );
  assert ( res->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next == NULL );
  deleteList ( a );
  deleteList ( res );
  
  a = createItem ( '0', NULL );
  res = power ( a );
  assert ( res->m_Digit == '0' );
  assert ( res->m_Next == NULL );
  deleteList ( a );
  deleteList ( res );

  a = createItem ( '2', NULL );
  res = power ( a );
  assert ( res->m_Digit == '4' );
  assert ( res->m_Next == NULL );
  deleteList ( a );
  deleteList ( res );

  a = createItem ( '3', 
        createItem ( '2', 
          createItem ( '1', NULL )));
  res = power( a );
  assert ( res->m_Digit == '9' );
  assert ( res->m_Next->m_Digit == '2' );
  assert ( res->m_Next->m_Next->m_Digit == '1' );
  assert ( res->m_Next->m_Next->m_Next->m_Digit == '5' );
  assert ( res->m_Next->m_Next->m_Next->m_Next->m_Digit == '1' );
  assert ( res->m_Next->m_Next->m_Next->m_Next->m_Next == NULL );
  deleteList ( a );
  deleteList ( res );
  
  a = createItem ( '3', 
        createItem ( 'a', NULL ) );
  res = power ( a );
  assert ( res == NULL );
  deleteList ( a );

  a = createItem ( '3', 
        createItem ( '0', NULL ) );
  res = power ( a );
  assert ( res == NULL );
  deleteList ( a );


  a = createItem('3', createItem('2', createItem('3', createItem('2', createItem('3', createItem('2', createItem('3', NULL)))))));
  res = power(a);
  assert(res->m_Digit == '9');
  assert(res->m_Next->m_Digit == '2');
  assert(res->m_Next->m_Next->m_Digit == '3');
  assert(res->m_Next->m_Next->m_Next->m_Digit == '6');
  assert(res->m_Next->m_Next->m_Next->m_Next->m_Digit == '7');
  assert(res->m_Next->m_Next->m_Next->m_Next->m_Next->m_Digit == '9');
  assert(res->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Digit == '1');
  assert(res->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Digit == '1');
  assert(res->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Digit == '9');
  assert(res->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Digit == '7');
  assert(res->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Digit == '4');
  assert(res->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Digit == '4');
  assert(res->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Digit == '0');
  assert(res->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Digit == '1');
  assert(res->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next == NULL);
  deleteList(a);
  deleteList(res);
  return 0;
}
#endif /* __PROGTEST__ */


//realloc sranda
/*
//zadani: dostanete na vstup kladne cislo uvedene ve spojacich
//ukol: vypocitat mocninu a vratit vysledek ve spojaku
//neplatne vstupy: 
//spojak zacina na nule, krom nuly
//spojak obsahuje jine znaky nez cislo
//spojak je prazdny

#ifndef __PROGTEST__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

typedef struct tnode {
  struct tnode * m_Next;
  char m_Digit;
} Tnode;

Tnode * createItem ( char digit, Tnode * next ) {
  Tnode * list = (Tnode*) malloc ( sizeof (*list) );
  list->m_Next = next;
  list->m_Digit = digit;
  return list;
}

void deleteList ( Tnode * list ) {
  if ( list != NULL )
    deleteList ( list->m_Next );
  free ( list );
}
#endif  __PROGTEST__ 

//if list contain a character 
//or zero digit at the end
//return NULL
int check ( Tnode * list ) {
  if ( list->m_Digit == '0' && list->m_Next == NULL )
    return 1;

  for ( ; list->m_Next != NULL ; list = list->m_Next )
    if ( list->m_Digit < '0' || list->m_Digit > '9' )
      return 0;
  if ( list->m_Digit <= '0' || list->m_Digit > '9' ) 
    return 0;

  return 1;
}

void printList ( Tnode * list ) {
  printf("Digit");
  for ( ; list != NULL ; list = list->m_Next )
    printf (" -> %c", list->m_Digit);
  printf ("\n");
}

void printArray ( int * arr, int i ) {
  printf ("Array");
  for ( int k = 0 ; k < i ; ++k )
    printf (" %i", arr[k]);
  printf("\n");
}

int toInt ( char c ) {
  int i = c - '0';
  return i;
}

size_t toArr ( Tnode * list, int ** arr, int size ) {
  size_t i = 0;
  for ( ; list != NULL ; list = list->m_Next ) {
    if ( i == ( size/sizeof (**arr) ) ) {
      int newSize = sizeof (**arr) * 2 * size;
      *arr = (int*) realloc ( *arr, newSize );
      size = newSize;
    }
    (*arr)[i] = toInt ( list->m_Digit );
    ++i;
  }
  return i;
}

Tnode * getResult ( Tnode * list ) {
  int * arr = (int*) malloc ( sizeof (*arr) * 1 );
  size_t index = toArr ( list, &arr, 1 );
  printArray ( arr, index );
  free ( arr );
  return list;
}

Tnode * power ( Tnode * list ) {
  printList ( list );
  if ( list == NULL ) return NULL;
  if ( !check ( list ) ) return NULL;

  Tnode * result = NULL;
  result = getResult ( list );
  printList ( result );

  return result;
}

#ifndef __PROGTEST__
int main ( int argc, char * argv [] )
{
  Tnode * a;
  Tnode * res;

  a = createItem ( '9', 
        createItem ( '9', 
          createItem ( '9', NULL )));
  res = power ( a );
//   assert ( res->m_Digit == '1' );
//   assert ( res->m_Next->m_Digit == '0' );
//   assert ( res->m_Next->m_Next->m_Digit == '0' );
//   assert ( res->m_Next->m_Next->m_Next->m_Digit == '8' );
//   assert ( res->m_Next->m_Next->m_Next->m_Next->m_Digit == '9' );
//   assert ( res->m_Next->m_Next->m_Next->m_Next->m_Next->m_Digit == '9' );
//   assert ( res->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next == NULL );
  deleteList ( a );
  //deleteList ( res );

  a = createItem ( '0', NULL );
  res = power ( a );
  assert ( res->m_Digit == '0' );
  assert ( res->m_Next == NULL );
  deleteList ( a );
  deleteList ( res );

  a = createItem ( '3', 
        createItem ( '2', 
          createItem ( '1', NULL )));
  res = power( a );
  assert ( res->m_Digit == '9' );
  assert ( res->m_Next->m_Digit == '2' );
  assert ( res->m_Next->m_Next->m_Digit == '1' );
  assert ( res->m_Next->m_Next->m_Next->m_Digit == '5' );
  assert ( res->m_Next->m_Next->m_Next->m_Next->m_Digit == '1' );
  assert ( res->m_Next->m_Next->m_Next->m_Next->m_Next == NULL );
  deleteList ( a );
  deleteList ( res );

  a = createItem ( '3', 
        createItem ( 'a', NULL ) );
  res = power ( a );
  assert ( res == NULL );
  deleteList ( a );

  a = createItem ( '3', 
        createItem ( '0', NULL ) );
  res = power ( a );
  assert ( res == NULL );
  deleteList ( a );

  return 0;
}
#endif // __PROGTEST__ //
*/