#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printNames ( char * name ) {
  printf ("NAME: ");
  for ( ; *name != '\0' ; name++ )
    printf("%c", *name);
  printf ("\n");
}

char * ptrToSurname ( char * fullName ) {
  char * lastName = fullName;
  while ( *lastName != '\n' )
      lastName++;
  while ( *lastName != ' ' )
      lastName--;
  return lastName; 
}

//return size of string 
//without additional space from old string
size_t strSizeNoSpace ( char ** str ) {
  char * head = *str;
  size_t size = 0;
  while ( **str != '\n' ) {
    if ( **str == '\t' )
        **str = ' ';    
    else if ( **str == ' ' && *(*str)+1 == ' ' )
      (*str)++;
    else {
      size++;
      (*str)++;
    }  
  }
  *str = head;
  return size;
}

//return a new string with no additional space
char * cpyStr ( char * oldStr, size_t * size ) {
  char * newStr;
  newStr = (char*) malloc ( (*size + 2) * sizeof(*newStr) );
  *size = 0;
  while ( *oldStr != '\0' ) {
    if ( *oldStr == ' ' && *(oldStr+1) == ' ' )
      oldStr++;
    else {
      newStr[*size] = *oldStr;
      (*size)++;
      oldStr++;
    }  
  }
  return newStr; 
}

//return a new string
//delete the first space before the first word
char * rmFirstSpace ( char ** oldStr ) {
  char * cpStr = strdup ( *oldStr + 1 );
  free ( *oldStr );
  return cpStr;
}

//return a new string
//delete the last space before the newline
char * rmLastSpace ( char ** oldStr, size_t size ) {
  (*oldStr)[size - 3] = '\n';  
  (*oldStr)[size - 2] = '\0';
  char * cpStr = (char*) realloc ( *oldStr, size - 1 );
  return cpStr;
}

//return a new string 
//with no additional space 
char * rmAdditionalSpace ( char ** oldStr ) {
  char * newStr;
  size_t strSize = 0;

  strSize = strSizeNoSpace ( oldStr );
  newStr = cpyStr ( *oldStr, &strSize );
  newStr[strSize] = '\0';

  if ( newStr[0] == ' ' )
    newStr = rmFirstSpace ( &newStr );

  size_t newSize = strlen ( newStr ) + 1;
  if ( newStr[newSize - 3] == ' ' )
    newStr = rmLastSpace ( &newStr, newSize );

  free( *oldStr );
  return newStr;
}

//return the number of names
size_t nameCounter ( char * str ) {
  size_t counter = 0;
  for ( ; *str != '\n' ; str++ )
    if ( *str == ' ' )
      counter++;
  return counter;
}

//edit the old string - no additional space
//return the number of names in edited string
int getStr ( char ** tmpStr ) {
  size_t numOfNames = 0;
  *tmpStr = rmAdditionalSpace( tmpStr );
  numOfNames = nameCounter ( *tmpStr );    
  return numOfNames;
}

//create a new array first time
//scaling the old array next time
void createArr ( char **** arr, char * str,
                 size_t size, size_t oldSize ) {
  size_t nSize = 0, fromIndex = size - oldSize;
  //printf ("size %lu\n", size);
  **arr = (char**) realloc ( **arr, size * sizeof (**arr) );
  char ** head = **arr;
  **arr = **arr + fromIndex;
  while ( *str != '\0' ) {
    if ( *str == ' ' ) {
      //printf("size of name is: %lu\n", nSize);
      ***arr = (char*) malloc ( sizeof(char) * (nSize + 1) );
      nSize = 0;
      (**arr)++;
      (str)++;
    }
    else {
      nSize++;
      (str)++;
    }
  }
  **arr = head;
}

void pushNames ( char *** arr, char * str,
                 size_t names, size_t newNames ) {
  createArr ( &arr, str, names, newNames );

  for ( size_t i = names - newNames ; i < names ; ++i ) {
    char * head = (*arr)[i];
    size_t j = 0;

    for ( ; *str != ' ' ; (str)++ ) {
      (*arr)[i][j] = *str;
      j++;
    }
    (*arr)[i][j] = '\0';
    (*arr)[i] = head;
    str++;
  }
}

void delArr ( char ** arr ) {
  free ( *arr );
  *arr = NULL;
}

void del2DArr ( char *** arr, size_t size ) {
  for ( size_t i = 0 ; i < size ; ++i )
    free ( (*arr)[i] );
  free ( *arr );
}

//return 1 if aPtr > bPtr
//return 0 if aPTr == bPtr
//return -1 if aPtr < bPtr
int cmpNames ( const void * a, const void * b ) {
  const char ** aPtr = (const char **) a;
  const char ** bPtr = (const char **) b;
  return strcmp ( *aPtr, *bPtr );
}

//return the number of the most frequent name
size_t maxFreq ( char ** arr, size_t size ) {
  size_t freq = 1, max = 1;

  for ( size_t i = 1 ; i < size ; ++i ) {
    if ( freq > max )
      max = freq;
    if ( strcmp ( arr[i-1], arr[i] ) == 0 )
      freq++;
    else
      freq = 1;
  }
  printf ("MAX FREQUENCY: %lu\n", max);
  return max;
}

//print the most frequent name
//if last one is also the most equal than print it too
void mostFrequent ( char ** arr, size_t size ) {
  size_t max = maxFreq ( arr, size ), freq = 1;

  printf("THE MOST FREQUENT NAMES:\n");
  for ( size_t i = 1 ; i < size ; ++i ) {
    if ( freq == max )
      printf ( "%s\n", arr[i-1] );
    if ( strcmp ( arr[i-1], arr[i] ) == 0 )
      freq++;
    else
      freq = 1;
  }
  if ( max == freq )
    printf("%s\n", arr[size-1]);
}

void printFullName ( char * arr ) {
  printf ("ENTERED FULL NAME: ");
  for ( ; *arr != '\0' ; arr++ )
    printf ("%c", *arr);
}

int main ( void ) {
  char * fullName = NULL, **nameArr = NULL;
  size_t size = 0, numOfNames = 0;

  printf ("Enter a full name:\n");
  while ( getline ( &fullName, &size, stdin ) != EOF ) {
    size_t newNames = 0;
    
    if ( feof ( stdin ) ) break;
    if ( *fullName == '\n' ) {
      delArr ( &fullName );
      continue;
    }

    newNames = getStr( &fullName );
    if ( newNames > 0 ) {
      numOfNames += newNames;
      pushNames ( &nameArr, fullName, numOfNames, newNames );
      printFullName ( fullName );
      delArr ( &fullName );
    }
    else {
      printFullName ( fullName );
      delArr ( &fullName );
    }
  }

  qsort ( nameArr, numOfNames, sizeof (*nameArr), cmpNames );
  for ( size_t i = 0 ; i < numOfNames ; ++i )
    printNames ( nameArr[i] );

  mostFrequent ( nameArr, numOfNames );

  delArr ( &fullName );
  del2DArr ( &nameArr, numOfNames );
  return EXIT_SUCCESS;
}
