#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct ean{
    int count;
    int num;
    struct ean *next;
}Tea;

int compare_ints(const void* a, const void* b){
    int arg1 = *(const int*)a;
    int arg2 = *(const int*)b;
 
    if (arg1 > arg2) return -1;
    if (arg1 < arg2) return 1;
    return 0;
}

Tea * newEan ( Tea * b, int ean )
{
    Tea * a = (Tea*) malloc (sizeof(Tea));
    a->num = ean;
    a->count = 1;
    a->next = b;
    return a;
}

int duplicate ( Tea * array, int j, int ean )
{
    for (int i = 0; i < j; i++)
    {
        if ( array[i].num == ean )
        {
            return i;
        }
    }
    return -1;
}

void freeBostonTea (Tea * a )
{
    if (a == NULL)
    {
        return;
    }
    Tea * tmp = a->next;
    free(a);
    freeBostonTea(tmp);
}

void findEAN( Tea * array, int len){
    qsort(array,len,sizeof(Tea),compare_ints);
    if ( len > 10 )
    {
        len = 10;
    }
    for (int i = 0; i < len; i++)
    {
        printf("%d %dx\n", array[i].num, array[i].count);
    }
}

int main ()
{
    int ean = 0, i = 0, len = 3, dup = 0;
    Tea * a = NULL;
    Tea * array = (Tea*) malloc ( len * sizeof(Tea) );

    while ( scanf("%d", &ean) != EOF )
    {
        if ( (dup = duplicate(array,i,ean)) >= 0 )
        {
            //printf("dup: %d\n", dup);
            array[dup].count += 1;
            //printf("pocet: %d\n", array[dup].count);
            i--;
        }
        else
        {
            a = newEan(a,ean);
            array[i].num = a->num;
            array[i].count = a->count;
        }
        i++;
        if ( i > (len-1) )
        {
            len *= 2;
            array = (Tea*)realloc(array, len*sizeof(Tea));
            //printf("realoc\n");
        }
    }
    printf("\n");
    findEAN(array, i);
    freeBostonTea(a);
    free(array);
    return 1;
}