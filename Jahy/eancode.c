#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct ean{
    int order;
    int count;
    char * num;
}Tea;

int duplicate ( Tea * array, int j, char * ean )
{
    for (int i = 0; i < j; i++)
    {
        if ( strcmp(array[i].num,ean) == 0 )
        {
            return i;
        }
    }
    return -1;
}

int compare (const void* a, const void* b){
    Tea * aa = (Tea*) a;
    Tea * bb = (Tea*) b;
    if (aa->count > bb->count) return -1;
    if (aa->count < bb->count) return 1;
    if (aa->count == bb->count){
        return aa->order - bb->order;
    }
    return 0;
}

void findEAN( Tea * array, int len){
    qsort(array,len,sizeof(Tea),compare);
    if ( len > 10 )
    {
        len = 10;
    }
    for (int i = 0; i < len; i++)
    {
        array[i].num[strlen(array[i].num)-1]='\0';
        printf("%s %dx\n", array[i].num, array[i].count);
    }
}

int isNum ( char * word, int len )
{
    for (int i = 0; i < len; i++)
    {
        if ( isdigit(*word) == 0 )
        {
            return 0;
        }
    }
    return 1;
}

void readInput ( Tea * array, int len )
{
    array = (Tea*) malloc( len * sizeof(Tea));
    char * word = NULL;
    size_t buffer;
    int chars = 0, cnt = 0, dup = 0;
    while ( 1 )
    {
        chars = getline(&word,&buffer,stdin);
        if ( feof(stdin) && cnt>0 )
        {
            break;
        }
        if ( isNum(word,chars-1) == 0 )
        {
            printf("Nespravny vstup.\n");
            free(word);
            if ( cnt > 0)
            {
                for (int i = 0; i < cnt; i++)
                {
                    free(array[i].num);
                }
            }
            free(array);
            return;
        }
        if ( chars < 6 || chars > 101 )
        {
            printf("Nespravny vstup.\n");
            free(word);
            if ( cnt > 0)
            {
                for (int i = 0; i < cnt; i++)
                {
                    free(array[i].num);
                }
            }
            free(array);
            return;
        }
        dup=duplicate(array,cnt,word);
        if ( dup != -1 )
        {
            array[dup].count += 1;
            cnt--;
        }
        else
        {
            array[cnt].order = cnt;
            strcpy(array[cnt].num = (char*) malloc( (chars+1) * sizeof(char)),word);
            //array[cnt].num[chars-1]='\0';
            array[cnt].count = 1;
        }
        cnt++;
        if ( cnt > (len-1) )
        {
            len *= 2;
            array = (Tea*)realloc(array, len*sizeof(Tea));
        }
    }
    free(word);
    findEAN(array,cnt);
    if ( cnt > 0) {
        for (int i = 0; i < cnt; i++)
        {
            free(array[i].num);
        }
        free(array);
    }
    return;
}

int main ( void ) {
    int len = 3;
    Tea * array = NULL;
    readInput(array, len);

    return 0;
}