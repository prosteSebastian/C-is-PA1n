#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

typedef struct Tnode
{
    struct Tnode * m_Next;
    char m_Digit;
} TNODE;

/*!
 * Creates a linked list.
 * 
 * \param[in] digit represent HEX number.
 * \param[in] next pointer to the next linked list.
 *
 * \return pointer to linked list.
 */
TNODE * createNode ( char digit, TNODE * next  )
{
    TNODE * a = (TNODE*) malloc(sizeof(TNODE));
    a->m_Digit = digit;
    a->m_Next = next;
    return a;
}

/*!
 * Free all parametres (and pointer) in linked list.
 *
 * \param[in] a pointer to linked list.
 * \return nothing.
 */
void deleteList ( TNODE * a )
{
    if ( a == NULL )
    {
        return;
    }
    TNODE * tmp = a->m_Next;
    free(a);
    deleteList(tmp);
}

/*!
 * Converts char to int.
 *
 * \param[in] digit HEX number as char.
 *
 * \return converter char to int.
 */
int getNum ( char digit )
{
    int num = 0;
    if(digit == '0')
        num = 0;
      else if(digit == '1')
        num = 1;
      else if(digit == '2')
        num = 2;
      else if(digit == '3')
        num = 3;
      else if(digit == '4')
        num = 4;
      else if(digit == '5')
        num = 5;
      else if(digit == '6')
        num = 6;
      else if(digit == '7')
        num = 7;
      else if(digit == '8')
        num = 8;
      else if(digit == '9')
        num = 9;
      else if(digit == 'A' || digit == 'a')
        num = 10;
      else if(digit == 'B' || digit == 'b')
        num = 11;
      else if(digit == 'C' || digit == 'c')
        num = 12;
      else if(digit == 'D' || digit == 'd')
        num = 13;
      else if(digit == 'E' || digit == 'e')
        num = 14;
      else if(digit == 'F' || digit == 'f')
        num = 15;
      else{
        return -1;
      }
    return num;
}

/*!
 * Binary shift the value of linked list.
 *
 * \param[in] a pointer to linked list.
 * \param[in] shift number that binary shift our linked list.
 *
 * \return pointer to the new shifted linked list.
 */
TNODE * shiftLeft ( TNODE * a, unsigned int shift )
{
    if ( a == NULL )
    {
        return NULL;
    }
    int * array = (int*) malloc(100*sizeof(int));
    int j = 0, num = 0;
    while ( a )
    {
        num = getNum(a->m_Digit);
        // taking care of valid input
        if ( num == (-1) || 
        (num == 0 && j == 0 ) )
        {
            free(array);
            return NULL;
        }
        array[j] = num;
        j++;
        a=a->m_Next;
    }
    int hex = 1;
    num = 0;
    // conversion from Hex to Dec
    for (int i = 0; i < j; i++)
    {
        num += array[i] * hex;
        hex *= 16;
    }
    free(array);
    num = num << shift;
    TNODE * b = NULL;
    char * getHexa = (char*) malloc(10*sizeof(char));
    // "%x" convert int into Hex format, sprintf save output to 'getHexa'
    sprintf(getHexa, "%x", num);
    int len = strlen(getHexa);
    for (int z = 0; z < len; z++)
    {
        if ( z == 0 )
        {
            b = createNode( getHexa[z], NULL );
        }
        else
        {
            b = createNode( getHexa[z], b );
        }
    }

    free(getHexa);
    return b;
}

int main ( void )
{
    TNODE * a = NULL, * res = NULL;
    a = createNode ( '3',
          createNode ( '2',
            createNode ( '1', NULL )));
    res = shiftLeft ( a, 1 );
    assert ( res -> m_Digit == '6' );
    assert ( res -> m_Next -> m_Digit == '4' );
    assert ( res -> m_Next -> m_Next -> m_Digit == '2' );
    assert ( res -> m_Next -> m_Next -> m_Next == NULL );
    deleteList ( a );
    deleteList ( res );
    
    a = createNode ( 'f',
          createNode ( 'a',
            createNode ( '1', NULL )));
    res = shiftLeft ( a, 3 );
    assert ( res -> m_Digit == '8' );
    assert ( res -> m_Next -> m_Digit == '7' );
    assert ( res -> m_Next -> m_Next -> m_Digit == 'd' );
    assert ( res -> m_Next -> m_Next -> m_Next == NULL );
    deleteList ( a );
    deleteList ( res );
    
    a = createNode ( 'c',
          createNode ( '5',
            createNode ( '4',
              createNode ( 'd',
                createNode ( '1', NULL )))));
    res = shiftLeft ( a, 5 );
    assert ( res -> m_Digit == '0' );
    assert ( res -> m_Next -> m_Digit == '8' );
    assert ( res -> m_Next -> m_Next -> m_Digit == 'b' );
    assert ( res -> m_Next -> m_Next -> m_Next -> m_Digit == '8' );
    assert ( res -> m_Next -> m_Next -> m_Next -> m_Next -> m_Digit == 'a' );
    assert ( res -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Digit == '3' );
    assert ( res -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
    deleteList ( a );
    deleteList ( res );
    
    a = createNode ( 'a',
          createNode ( 'w',
            createNode ( '0', NULL )));
    res = shiftLeft ( a, 12 );
    assert ( res == NULL );
    deleteList ( a );
    
    a = createNode ( '0',
          createNode ( '1',
            createNode ( '0', NULL )));
    res = shiftLeft ( a, 1 );
    assert ( res == NULL );
    deleteList ( a );

    a = NULL;
    res = shiftLeft ( a, 1 );
    assert ( res == NULL );
    
    return 0;
}