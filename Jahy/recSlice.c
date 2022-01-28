#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int isWord ( char * word, int len )
{
    for (int i = 0; i < len; i++)
    {
        if ( isdigit(*word++) == 0 )
        {
            return 0;
        }
    }
    return 1;
}

int slice ( char * word, int len, int space, int pos, int cnt )
{
    char * newWord = (char*) malloc( 101 * sizeof(char));
    int a = 0;
    if ( space >= (len-1) || pos >= (len-1) )
    {
        free(newWord);
        return cnt;
    }
    newWord[pos] = ' ';
    for (int i = 0; i < len+pos-1; i++)
    {
        if ( i == cnt )
        {
            newWord[i+1] = word[i];
            a = pos;
        }
        else
        {
            newWord[i+a] = word[i];
        }
    }
    newWord[len] = '\0';
    for (int i = 0; i < len; i++)
    {
        word[i] = newWord[i];
    }
    printf("%s\n", word);
    free(newWord);
    return slice(word,len,space,++pos,++cnt);
}

int checkInput ( )
{
    char * word = (char*) malloc( 101 * sizeof(char));
    int min = 0, max = 0, len = 0;
    size_t buffer;

    printf("Vstup:\n");
    len = getline(&word,&buffer,stdin);
    if ( isWord(word, len-1) == 0 || len < 1 || len > 101 )
    {
        printf("Nespravny vstup.\n");
        free(word);
        return 0;
    }
    if ( feof(stdin) )
    {
        printf("Nespravny vstup.\n");
        free(word);
        return 0;
    }
    word[len-1]='\0';
    scanf("%d %d", &min, &max);
    if ( min > max || min <= 0 || max <= 0 )
    {
        printf("Nespravny vstup.\n");
        free(word);
        return 0;
    }

    int cnt = 1;
    printf("%s\n", word);
    cnt = slice(word,len,0,1,cnt);
    printf("Celkem: %d\n", cnt);

    free(word);
    return 1;
}

int main ( void )
{
    checkInput();
    return 0;
}