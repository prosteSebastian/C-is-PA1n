

#ifndef __PROGTEST__
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
 
typedef struct TItem {
    struct TItem * m_Next;
    char m_Digit;
} TITEM;
 
TITEM * createItem(char digit, TITEM * next) {
    TITEM *n = (TITEM *) malloc(sizeof(*n));
    n->m_Digit = digit;
    n->m_Next = next;
    return n;
}
 
void deleteList(TITEM * l) {
    while (l) {
        TITEM *tmp = l->m_Next;
        free(l);
        l = tmp;
    }
}
 
#endif /* __PROGTEST__ */
int validLinkedList (TITEM * list) {
    if (!list) return 0; 
    int lastZero = 0;
    int length = 0;
    while (list) {
        if (!isdigit(list->m_Digit)) return 0;
        if (list->m_Digit == '0') {
            lastZero = 1;
        } else {
            lastZero = 0;
        }
        length++; 
        list = list->m_Next;
    }
    if (lastZero && length != 1) {
        return 0;
    }
    
    return 1;
}
TITEM * reverseList (TITEM *a) {
    TITEM * cur = a;
    TITEM * tmp;
    TITEM * p = NULL;
    while (cur) {
        tmp = cur;
        cur = cur->m_Next;
        tmp->m_Next = p;
        p = tmp;
    }
    return tmp;
}
TITEM * addList ( TITEM * a, TITEM * b ) {
    if (!validLinkedList(a)  || !validLinkedList(b) ) {
        return NULL;
    }
    TITEM * res = NULL;
    char remainder = 0;
    while (a && b) {
        if (a->m_Digit + b->m_Digit + remainder - '0' > '9') {
            res = createItem(a->m_Digit + b->m_Digit + remainder - '0' - 10, res);
            remainder = 1;
        } else {
            res = createItem(a->m_Digit + b->m_Digit + remainder - '0', res);
            remainder = 0;
        }
        a = a->m_Next;
        b = b->m_Next;
    }
    while (a) {
        if (a->m_Digit + remainder > '9') {
            res = createItem(a->m_Digit + remainder - 10, res);
            remainder = 1;
        } else {
            res = createItem(a->m_Digit + remainder, res);
            remainder = 0;
        }
        a = a->m_Next;
    }
    while (b) {
        if (b->m_Digit + remainder > '9') {
            res = createItem(b->m_Digit + remainder - 10, res);
            remainder = 1;
        } else {
            res = createItem(b->m_Digit + remainder, res);
            remainder = 0;
        }
        b = b->m_Next;
    }
    if (remainder) {
        res = createItem('1', res);
    }
    res = reverseList(res);
    return res;
}
 
#ifndef __PROGTEST__
 
int main(int argc, char *argv[]) {
    
    TITEM * a, * b, * res;
 
    a = createItem('9',
          createItem('9',
           createItem('9', NULL)));
    b = createItem('1', NULL);

    res = addList(a, b);
    assert(res->m_Digit == '0');
    assert(res->m_Next->m_Digit == '0');
    assert(res->m_Next->m_Next->m_Digit == '0');
    assert(res->m_Next->m_Next->m_Next->m_Digit == '1');
    assert(res->m_Next->m_Next->m_Next->m_Next == NULL);
    deleteList(res);
    deleteList(a);
    deleteList(b);

    a = createItem('9',
          createItem('0',
           createItem('9', NULL)));
    b = createItem('1', 
          createItem('9', NULL));

    res = addList(a, b);
    assert(res->m_Digit == '0');
    assert(res->m_Next->m_Digit == '0');
    assert(res->m_Next->m_Next->m_Digit == '0');
    assert(res->m_Next->m_Next->m_Next->m_Digit == '1');
    assert(res->m_Next->m_Next->m_Next->m_Next == NULL);
    deleteList(res);
    deleteList(a);
    deleteList(b);

    a = createItem('x', NULL);
    b = createItem('3', NULL);
    res = addList(a, b);
    assert (res == NULL);
    deleteList(a);
    deleteList(b);
 
    a = createItem('5',
         createItem('0',
          createItem('0', NULL)));
    b = createItem('3', NULL);
    res = addList(a, b);
    assert (res == NULL);
    deleteList(a);
    deleteList(b);
 
    a = createItem('3',
         createItem('4',
          createItem('5', NULL)));
    b = createItem('0', NULL);
    res = addList(a, b);
    assert (res->m_Digit == '3');
    assert (res->m_Next->m_Digit == '4');
    assert (res->m_Next->m_Next->m_Digit == '5');
    assert (res->m_Next->m_Next->m_Next == NULL);
    deleteList(res);
    deleteList(a);
    deleteList(b);
    return 0;
}
 
#endif /* __PROGTEST__ */

