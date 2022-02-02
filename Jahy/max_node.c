#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
 
typedef struct TItem
{
    struct TItem * m_Next;
    char           m_Digit;
} TITEM;
 
TITEM * createItem ( char digit, TITEM * next )
{
    TITEM * n = (TITEM *) malloc (sizeof ( *n ));
    n -> m_Digit = digit;
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

int toInt ( char x )
{
    int num = x - '0';
    return ( num < 0 || num > 9 ) ? -1 : num;
}

typedef struct max_node
{
    int num;
    int index;
} TNODE;

TITEM * maxOf (TITEM ** a, int nr )
{
    if ( nr == 0 ) { return a[0]; }

    TNODE * arr = (TNODE*) malloc( nr * sizeof(TNODE) );
    int rem = 10, max = 0, n = 0;
    TITEM * tmp;
    for (int i = 0; i < nr; i++)
    {
        if ( a[i] == NULL )
        {
            free(arr);
            return NULL;
        }
        tmp = a[i];
        n = 0;
        rem = 10;
        while ( tmp )
        {
            if ( toInt(tmp->m_Digit) == -1 )
            {
                free(arr);
                return NULL;
            }
            if ( n == 0 )
            {
                arr[i].num = toInt(tmp->m_Digit);
                //printf("a %d\n",arr[i].num);
                arr[i].index = i;
                n++;
            }
            else
            {
                arr[i].num += (toInt(tmp->m_Digit) * rem);
                //printf("b %d\n",arr[i].num);
                //printf("b %d\n", (toInt(tmp->m_Digit) * rem));
                rem *= 10;
                arr[i].index = i;
            }
            tmp = tmp->m_Next;
        }
        if ( i == 0 )
        {
            max = arr[0].num;
        }
        //printf("%d\n",arr[i].num);
    }
    rem = 0;
    for (int i = 1; i < nr; i++)
    {
        if ( max < arr[i].num )
        {
            max = arr[i].num;
            rem = i;
        }
    }
    free(arr);
    return a[rem];
}

/*
TITEM * maxOf (TITEM ** a, int nr )
{
    if ( a == NULL ) { return NULL; }
    if ( nr == 0 ) { return a[0]; }

    TITEM * res = a[0];
    TITEM * head_res = res;
    TITEM * tmp;
    TITEM * head_tmp;
    int res_num = 0, tmp_num = 0, max = 0, res_nul = 0, tmp_nul = 0;

    for (int i = 1; i < nr; i++)
    {
        tmp = a[i];
        head_tmp = a[i];
        res = head_res;
        while ( tmp != NULL )
        {
            res_num = toInt(res->m_Digit);
            tmp_num = toInt(tmp->m_Digit);
            if ( tmp->m_Next != NULL && res->m_Next == NULL )
            {
                head_res = head_tmp;
                break;
            }
            if ( tmp->m_Next == NULL && res->m_Next == NULL )
            {
                if ( max == 2 )
                {
                    head_res = head_tmp;
                }
                break;
            }
            if ( tmp->m_Next != NULL && res->m_Next != NULL )
            {
                if ( res_num > tmp_num )
                {
                    max = 1;
                }
                if ( tmp_num > res_num )
                {
                    max = 2;
                }
            }
            tmp = tmp->m_Next;
            res = res->m_Next;
        }
    }
    return head_res;
}
*/

int main (int argc, char * argv [])
{
    TITEM * a[5];
 
    a[0] = createItem ( '4',
            createItem ( '3',
             createItem ( '2',
              createItem ( '1', NULL ))));
    a[1] = createItem ( '2',
            createItem ( '3',
             createItem ( '4',
              createItem ( '5', NULL))));
    assert ( maxOf ( a, 2 ) == a[1] );
    deleteList( a[0] );
    deleteList( a[1] );
    //printf("_________\n");
    a[0] = createItem ( '0',
            createItem ( '0',
             createItem ( '0',
              createItem ( '1', NULL ))));
    a[1] = createItem ( '2',
            createItem ( '0',
             createItem ( '0',
              createItem ( '1', NULL ))));
    a[2] = createItem ( '1',
            createItem ( '0',
             createItem ( '0',
              createItem ( '1', NULL))));
    a[3] = createItem ( '2',
            createItem ( '0',
             createItem ( '0',
              createItem ( '1',
               createItem ( '0',
                createItem ( '0', NULL ))))));
    assert ( maxOf ( a, 4 ) == a[1] );
    deleteList ( a[0] );
    deleteList ( a[1] );
    deleteList ( a[2] );
    deleteList ( a[3] );

 
    a[0] = createItem ( '1',
            createItem ( '0',
             createItem ( '0',
              createItem ( '0',
               createItem ( '0',
                createItem ( '0', NULL ))))));
    a[1] = createItem ( '0',
            createItem ( '0',
             createItem ( '1', NULL )));
    a[2] = createItem ( '1',
            createItem ( '0',
             createItem ( '0',
              createItem ( '0',
               createItem ( '0',
                createItem ( '9', NULL ))))));
    a[3] = createItem ( '0',
            createItem ( '0',
             createItem ( '0',
              createItem ( '0',
               createItem ( '0',
                createItem ( '0',
                 createItem ( '0',
                  createItem ( '0',
                   createItem ( '0',
                    createItem ( '0',
                     createItem ( '0',
                      createItem ( '0',
                       createItem ( '0',
                        createItem ( '0',
                         createItem ( '0', NULL )))))))))))))));
    assert ( maxOf (a, 4) == a[2] );
    deleteList ( a[0] );
    deleteList ( a[1] );
    deleteList ( a[2] );
    deleteList ( a[3] );
 
    a[0] = createItem ( '0',
            createItem ( '0',
             createItem ( '0',
              createItem ( '0',
               createItem ( '0',
                createItem ( '0',
                 createItem ( '0',
                  createItem ( '0',
                   createItem ( '0',
                    createItem ( '0',
                     createItem ( '0',
                      createItem ( '0',
                       createItem ( '0',
                        createItem ( '0',
                         createItem ( '0',
                          createItem ( '0',
                           createItem ( '0',
                            createItem ( '0',
                             createItem ( '0',
                              createItem ( '0',
                               createItem ( '0',
                                createItem ( '1', NULL ))))))))))))))))))))));
    a[1] = createItem ( '1',
            createItem ( '0',
             createItem ( '0',
              createItem ( '0',
               createItem ( '0',
                createItem ( '0',
                 createItem ( '0',
                  createItem ( '0',
                   createItem ( '0',
                    createItem ( '0',
                     createItem ( '0',
                      createItem ( '0',
                       createItem ( '0',
                        createItem ( '0',
                         createItem ( '0',
                          createItem ( '0',
                           createItem ( '0',
                            createItem ( '0',
                             createItem ( '0',
                              createItem ( '0',
                               createItem ( '0',
                                createItem ( '1', NULL ))))))))))))))))))))));
    assert ( maxOf ( a, 2 ) == a[1] );
    deleteList ( a[0] );
    deleteList ( a[1] );
 
    a[0] = createItem ( '3',
            createItem ( '2',
             createItem ( '1', NULL )));
    a[1] = NULL;
    a[2] = createItem ( '9',
            createItem ( 'c',
             createItem ( 'b',
              createItem ( '9',
               createItem ( '9', NULL )))));
    assert ( maxOf ( a, 3 ) == NULL);
    deleteList ( a[0] );
    deleteList ( a[2] );

    a[0] = createItem ( '3',
            createItem ( '2',
             createItem ( '1', NULL )));
    a[1] = createItem ( '6',
            createItem ( '5',
             createItem ( '4', NULL )));
    a[2] = createItem ( '9',
            createItem ( 'c',
             createItem ( 'b',
              createItem ( '9',
               createItem ( '9', NULL )))));
    assert ( maxOf ( a, 3 ) == NULL);
    deleteList ( a[0] );
    deleteList ( a[1] );
    deleteList ( a[2] );
 
    return 0;
}