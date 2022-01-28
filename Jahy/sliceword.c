#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int isWord ( char * word, int len )
{
    for (int i = 0; i < len; i++)
    {
        if ( !((*word >= 'a' && *word <= 'z') ||
         (*word >= 'A' && *word <= 'Z') ))
        {
            return 0;
        }
        if ( isdigit(*word++) == 1 )
        {
            return 0;
        }
    }
    return 1;
}

int slice ( char * word, int len, int min, int max, int cnt )
{
    char * newWord = (char*) malloc( (len + 2) * sizeof(char));
    int a = 0;
    if ( cnt >= min && cnt <= max )
    {
        free (newWord);
        return cnt;
    }
    newWord[cnt] = ' ';
    for (int i = 0; i < len; i++)
    {
        if ( i == cnt )
        {
            newWord[i+1] = word[i];
            a = 1;
        }
        else
        {
            newWord[i+a] = word[i];
        }
    }
    newWord[len+1] = '\0';
    printf("%s\n", newWord);
    free (newWord);
    return slice(word,len,min,max,++cnt);
}

int checkInput ( )
{
    char * word = (char*) malloc( 101 * sizeof(char));
    int min = 0, max = 0;

    printf("Vstup:\n");
    scanf("%s", word);
    int len = strlen(word);
    if ( isWord(word, len) == 0 )
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

    scanf("%d %d", &min, &max);
    if ( min > max || min <= 0 || max <= 0 )
    {
        printf("Nespravny vstup.\n");
        free(word);
        return 0;
    }

    int cnt = 0;
    cnt = slice(word,len,min,max,cnt);
    printf("Pocet: %d\n", cnt);

    free(word);
    return 1;
}

int main ( void )
{
    checkInput();
    return 0;
}