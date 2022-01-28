#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

int main ()
{
  FILE * fp;
  //printf("Napis jmeno souboru:\n");
  //char name[32];
  //scanf("%s", name);
  char name[] = "a.txt";
  fp = fopen(name,"w");
  if ( !fp )
  {
    return 1;
  }
  int num, sum = 0;
  while ( num != 0 )
  {
    scanf("%d", &num);
    fprintf(fp,"%d",num);
    fprintf(fp, " ");
  }
  fprintf(fp,"\n");
  if ( fclose(fp) == EOF )
  {
    return 2;
  }

  int a;
  fp = fopen(name,"r");
  while ( a )
  {
    fscanf(fp,"%d",&a);
    printf("%d ", a);
    sum += a;
  }
  fclose(fp);
  printf("\nsuma: %d\n", sum);
  return 0;
}