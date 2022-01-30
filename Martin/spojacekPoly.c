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
int validList (TITEM * a) {
    if (!a) return 0;
    int tmpPow = a->m_Pow;
    a = a->m_Next;
    while (a) {
        if (tmpPow >= a->m_Pow) return 0;
        if (a->m_Mul == 0) return 0;
        a = a->m_Next;
    }
    return 1;
}
void printList (TITEM *a) {
    while (a) {
        printf("MUL: %d POW: %d ->", a->m_Mul, a->m_Pow);
        a = a->m_Next;
    }
    printf("\n");
}
TITEM * reverseList (TITEM *a) {
    TITEM * cur = a;
    TITEM * tmp;
    TITEM * p = NULL;
    while (cur){
        tmp = cur;
        cur = cur->m_Next;
        tmp->m_Next = p;
        p = tmp;
    }
    return tmp;
}

TITEM * addPoly ( TITEM * a , TITEM * b ) {
    if (!validList(a) || !validList(b)) return NULL;
    TITEM * res = NULL;
    int counter = 0;
    while (a && b) {
        if (!counter && !a->m_Mul && !a->m_Pow) {
            a = a->m_Next;
            continue;
        }
        if (!counter && !b->m_Mul && !b->m_Pow) {
            b = b->m_Next;
            continue;
        }
        if (a->m_Pow > b->m_Pow) {
            res = createItem(b->m_Mul, b->m_Pow, res);
            b = b->m_Next;
        } else if ( a->m_Pow < b->m_Pow) {
            res = createItem(a->m_Mul, a->m_Pow, res);
            a = a->m_Next;
        } else {
            if (a->m_Mul + b->m_Mul) {
                res = createItem(a->m_Mul + b->m_Mul, a->m_Pow, res);
            } else if (!counter) {
                res = createItem(0,0,res);
            }
            a = a->m_Next;
            b = b->m_Next;
        }
        counter++;
    }
    while (a) {
        res = createItem(a->m_Mul, a->m_Pow, res);
        a = a->m_Next;
    }
    while (b) {
        res = createItem(b->m_Mul, b->m_Pow, res);
        b = b->m_Next;
    }
    res = reverseList(res);
    //printList(res);
    return res;
}

#ifndef __PROGTEST__
int main ( int argc, char * argv [] )
{
    TITEM * a, * b;
    TITEM * res;

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

    a = createItem (2,1,NULL);
    b = createItem (0,0,NULL);
    res = addPoly(a,b);
    assert ( res -> m_Mul == 2 );
    assert ( res -> m_Pow == 1 );
    assert ( res -> m_Next == NULL );
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
    a = createItem (0,0, NULL);
    b = createItem (0,0, NULL);
    res = addPoly(a,b);
    assert (res->m_Mul == 0);
    assert (res->m_Pow == 0);
    assert (res->m_Next == NULL);
    deleteList ( a );
    deleteList ( b );
    deleteList ( res );

    return 0;
}
#endif /* __PROGTEST__ */