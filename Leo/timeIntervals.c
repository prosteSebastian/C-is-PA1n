#include <stdio.h>
#include <stdlib.h>

#define SIZE 10

//return 1 on correct values
//return -1 on EOF
//return 0 0n incorrect values
int input( int * workLoad, size_t * index1, size_t * index2 ) {
    int check = scanf(" %d: %lu... %lu\n", workLoad, index1, index2 );
    if ( check == 3 ) return 1;
    else if ( check == EOF ) return -1;
    else return 0;
}

void printArray ( int * array, size_t * size ) {
    printf("Moje pole:\n");

    printf("index");
    for ( size_t m = 0; m < *size; ++m )
        printf(" %5lu", m);
    printf("\n");

    printf("prvek");
    for ( size_t l = 0; l < *size; ++l )
        printf(" %5d", array[l]);
    printf("\n");
}

//initialize the array
void initArray ( int * inArray, size_t size, size_t from ) {
    for ( size_t i = from; i < size; ++i )
    inArray[i] = 0;
}

void pushToArray ( int ** inArray, size_t index1, size_t index2, 
                   int * workLoad, size_t * arrCount, size_t * arrSize ) {

    for ( size_t k = index1; k < index2; ++k ) {
        //in case of small array
        if( k >= *arrSize || *arrCount == *arrSize ) {
            int oldSize = *arrSize;
            *arrSize = (*arrSize) * 2;
            *inArray = (int*) realloc ( *inArray, (*arrSize) * sizeof(int) );
            initArray ( *inArray, *arrSize, oldSize );
        }

        if ( (**inArray+k) != 0 )
            (*inArray)[k] = (*inArray)[k] + *workLoad;
        else if ( (*inArray)[k] == 0 ) { 
            (*inArray)[k] = *workLoad;
            (*arrCount)++;
        }
        else {
            printf("neco se podelalo\n");
            free(*inArray);
            exit(1);
        }
    }
}

//return max value
int findMax( int * array, int size ) {
    int max = 0;
    for ( int n = 0; n < size; ++n ) {
        if ( array[n] > max )
            max = array[n];
    }
    return max;    
}

void findIntervals( int * array, int size, int max ) {
    for ( int p = 0; p < size; ++p ) {
        if ( array[p] == max ) {
            printf("%d...", p);
            p++;
            while( array[p] == max )
                p++;
            printf("%d\n", p);
        }
    }
}

int main ( void ) {
    
    int * inArray;  
    int workLoad;
    size_t index1, index2, arrSize = SIZE, arrCount = 0;

    printf("Enter work_load:from...to\n");

    inArray = (int*) malloc ( sizeof(inArray) * SIZE );
    initArray ( inArray, SIZE, 0 );

    while ( 1 ) {
        int check = input( &workLoad, &index1, &index2 );
        if ( check == 1 ) 
            pushToArray ( &inArray, index1, index2, 
                          &workLoad, &arrCount, &arrSize );
        else if ( check == -1 ) {
            int max = findMax (inArray, arrSize);
            findIntervals ( inArray, arrSize, max );
            break;
        }
        else {
            printf("neco se podelalo\n");
            free(inArray);
            return 1;
        }
    }

    printArray ( inArray, &arrSize );
    free(inArray);

    return 0;
}
