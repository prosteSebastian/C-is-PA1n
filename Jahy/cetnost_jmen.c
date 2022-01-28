#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct cetnost_jmen
{
  int cnt;
  char * name;
} NAME;

int compare_ints(const void* a, const void* b)
{
  struct cetnost_jmen * arg1 = (struct cetnost_jmen *)a;
  struct cetnost_jmen * arg2 = (struct cetnost_jmen *)b;

  if (arg1->cnt > arg2->cnt) return -1;
  if (arg1->cnt < arg2->cnt) return 1;
  return 0;
}

void freeName( NAME * arr, int n )
{
  for (int i = 0; i < n; i++)
  {
    free(arr[i].name);
  }
  free(arr);
}

void printName ( NAME * arr, int n )
{
  qsort( arr, n, sizeof(NAME), compare_ints );
  printf("Nejcastejsi jmeno: %dx\n", arr[0].cnt);
  for (int i = 0; i < n; i++)
  {
    printf("%s\n",arr[i].name);
    if ( i+1 >= n )
    {
      break;
    }
    else {
      if ( arr[i+1].cnt != arr[i].cnt )
      {
        break;
      }
    }
  }
  freeName(arr,n);
}

int findDup ( NAME * arr, int n, char * names )
{
  for (int i = 0; i < n; i++)
  {
    if ( strcasecmp(arr[i].name,names) == 0 )
    {
      return i;
    }
  }
  return -1;
}

int main (void)
{
  printf("Jmena:\n");
  int size_arr = 2, input = 0, n = 0, dup = 0, len = 0, sto = 2;
  NAME * arr = (NAME*) malloc( size_arr * sizeof(NAME) );  
  char * names = (char*) malloc( sto * sizeof(char) );
  char * full = NULL;
  size_t buffer;

  while ( 1 )
  {
    input = getline(&full,&buffer,stdin);
    if ( input == EOF && n > 0 )
    {
      free(full);
      free(names);
      printName(arr,n);
      return 0;
    }
    if ( strlen(full) > 100 )
    {
      sto *= 2;
      names = (char*)realloc(names,sto*sizeof(char));
    }
    strncpy(names," ",len);
    len = strlen(full);
    int wasAplha = 0;
    for (int i = len; i >= 0; i--)
    {
      if ( isalpha(full[i]) )
      {
        wasAplha++;
      }
      if ( isspace(full[i]) != 0 && wasAplha > 0 )
      {
        //printf("-%d %d\n", len, i);
        strncpy(names,full,i);
        names[i+1] = '\0';
        //printf("-%s\n", names);
        break;
      }
    }

    dup = findDup(arr,n,names);

    if ( dup != (-1) )
    {
      arr[dup].cnt += 1;
    }
    else
    {
      len = strlen(names)+1;
      arr[n].name = (char*) malloc( len * sizeof(char) );
      strncpy( arr[n].name, names, strlen(names)+1 );
      arr[n].cnt = 1;
      n++;
      if ( n == size_arr )
      {
        size_arr *= 2;
        arr = (NAME*)realloc(arr,size_arr*sizeof(NAME));
      }
    }
  }

  return 1;
}