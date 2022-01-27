//Neručím za 100% přesnost... Ale mělo by to víceméně ono...

#ifndef __PROGTEST__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

typedef struct TItem
{
    struct TItem * m_Next;
    int m_Mul;
    int m_Pow;
} TITEM;
 
TITEM * createItem ( int mul, int pow, TITEM * next )
{
    TITEM * n = (TITEM *) malloc (sizeof ( *n ));
    n -> m_Mul = mul;
    n -> m_Pow = pow;
    n -> m_Next = next;
    return n;
}
 
void deleteList (TITEM * l)
{
    while (l)
    {
        TITEM * tmp = l -> m_Next;
        free (l);
        l = tmp;
    }
}
#endif /* __PROGTEST__ */

void printList( TITEM * a ) {
    TITEM * head = a;

    printf("Mul ");
    for ( ; a != NULL ; a = a->m_Next )
        printf("-> %d ", a->m_Mul);
    printf("\n");

    a = head;
    printf("Pow ");
    for ( ; a != NULL ; a = a->m_Next )
        printf("-> %d ", a->m_Pow);
    printf("\n");
}

//check if exponent is sorted from the smallest to the largest
//if sorted return 1
//if not return 0
int checkIfSorted ( TITEM * a ) {
    for ( ; a->m_Next != NULL ; a = a->m_Next )
        if ( a->m_Pow >= a->m_Next->m_Pow )
            return 0;
    return 1;
}

TITEM * getRes ( TITEM * a, TITEM * b ) {
    TITEM *  head, * result;
    int resMul;

    result = createItem ( 0, 0, NULL );
    head = result;

    while ( a != NULL || b != NULL ) {
        if ( a == NULL && b != NULL ) {
            result->m_Next = createItem ( b->m_Mul, b->m_Pow, NULL );
            b = b->m_Next;
            result = result->m_Next;
            continue;
        }
        else if ( b == NULL && a != NULL ) {
            result->m_Next = createItem ( a->m_Mul, a->m_Pow, NULL );
            a = a->m_Next;
            result = result->m_Next;
            continue;
        }
        else if ( a->m_Pow < b->m_Pow ) {
            if ( a->m_Mul == 0 ) { 
                a = a->m_Next;
                continue;
            }
            else {
                result->m_Next = createItem ( a->m_Mul, a->m_Pow, NULL );
                a = a->m_Next;
                result = result->m_Next;
                continue;
            }        
        }
        else if ( a->m_Pow > b->m_Pow ) {
            if ( b->m_Mul == 0 ) {
                b = b->m_Next;
                continue;
            }
            else {
                result->m_Next = createItem ( b->m_Mul, b->m_Pow, NULL );
                b = b->m_Next;
                result = result->m_Next;
                continue;
            }
        }
        else if ( a->m_Pow == b->m_Pow ) {
            resMul = a->m_Mul + b->m_Mul;
            if ( resMul == 0 ) {
                a = a->m_Next;
                b = b->m_Next;
                continue;
            }
            else 
                result->m_Next = createItem ( resMul, a->m_Pow, NULL );
        }
        else
            printf("something gets wrong\n");

        a = a->m_Next;
        b = b->m_Next;
        result = result->m_Next;
    }

    if ( head->m_Next != NULL ) {
        TITEM * tmp = head;
        head = head->m_Next;
        free ( tmp );
        tmp = NULL;
    }

    return head;
}

TITEM * addPoly ( TITEM * a , TITEM * b )
{
    if ( a == NULL || b == NULL ) return NULL;

    if ( !checkIfSorted ( a ) || !checkIfSorted ( b ) )
        return NULL;

    TITEM * result = NULL;
    result = getRes ( a, b );

    printList ( result );
    
    return result;
}

#ifndef __PROGTEST__
int main ( int argc, char * argv [] )
{
    TITEM * a, * b;
    TITEM * res;

    a = createItem (2,1,NULL);
    b = createItem (0,0,NULL);
    res = addPoly(a,b);
    assert ( res -> m_Mul == 2 );
    assert ( res -> m_Pow == 1 );
    assert ( res -> m_Next == NULL );
    deleteList ( a );
    deleteList ( b );
    deleteList ( res );

    a = createItem (2,1,NULL);
    b = createItem (3,1,createItem (4,2,createItem (2,3,createItem(1,0,NULL))));
    res = addPoly(a,b);
    assert ( res == NULL );
    deleteList ( a );
    deleteList ( b );
    deleteList ( res );

    a = createItem (2,1,NULL);
    b = createItem (3,1,createItem (4,1,NULL));
    res = addPoly(a,b);
    assert ( res == NULL );
    deleteList ( a );
    deleteList ( b );
    deleteList ( res );

    a = createItem (3,0,createItem (2,1,createItem (9,3,NULL)));
    b = createItem (0,0,createItem (4,2,createItem (-1,3,NULL)));
    res = addPoly(a,b);
    assert ( res -> m_Mul == 3 );
    assert ( res -> m_Pow == 0 );
    assert ( res -> m_Next -> m_Mul == 2 );
    assert ( res -> m_Next -> m_Pow == 1 );
    assert ( res -> m_Next -> m_Next -> m_Mul == 4 );
    assert ( res -> m_Next -> m_Next -> m_Pow == 2 );
    assert ( res -> m_Next -> m_Next -> m_Next -> m_Mul == 8 );
    assert ( res -> m_Next -> m_Next -> m_Next -> m_Pow == 3 );
    assert ( res -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
    deleteList ( a );
    deleteList ( b );
    deleteList ( res );

    a = createItem (3,0,createItem (2,1,createItem (5,3,NULL)));
    b = createItem (-7,0,createItem (-2,1,createItem (-5,3,NULL)));
    res = addPoly(a,b);
    assert ( res -> m_Mul == -4 );
    assert ( res -> m_Pow == 0 );
    assert ( res -> m_Next == NULL );
    deleteList ( a );
    deleteList ( b );
    deleteList ( res );

    a = createItem (3,1,createItem (-2,2,createItem (4,3,NULL)));
    b = createItem (-3,1,createItem (2,2,createItem (-4,3,NULL)));
    res = addPoly(a,b);
    assert ( res -> m_Mul == 0 );
    assert ( res -> m_Pow == 0 );
    assert ( res -> m_Next == NULL );
    deleteList ( a );
    deleteList ( b );
    deleteList ( res );

    return 0;
}
#endif /* __PROGTEST__ */