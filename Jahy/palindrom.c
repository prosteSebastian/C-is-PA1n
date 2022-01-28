#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int isPalindrom ( char * palin ) {
    int len = strlen(palin)-1;
    int i = 0;
    int lcase = 0;
    //printf("%c a %c \n", palin[i], pain[len]);
    while (i != len)
    {
        while (isalpha(palin[i]) == 0 || palin[i] == ' ' )
        {
            i++;
        }
        while (isalpha(palin[len]) == 0 || palin[len] == ' ' )
        {
            len--;
        }
        if ((palin[i]) == palin[len])
        {
           lcase = 1;
        }
        if (tolower(palin[i]) != tolower(palin[len]))
        {
            printf("Retezec neni palindrom.\n");
            return 0;
        }
        len--;
        i++;
    }
    if (lcase) {
        printf("Retezec je palindrom (case-sensitive).\n");
    }
    else {
        printf("Retezec je palindrom (case-insensitive).\n");
    }
    return 1;
}

int main() {

    char * palin = NULL;
    size_t len;
    char a[]="kob bok";
    isPalindrom(a);
    while ( getline(&palin,&len,stdin) > 0 ) {
        isPalindrom(palin);
    }
    free(palin);
    return 1;
}
