#ifndef __PROGTEST__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

typedef struct TNode {
    struct TNode *m_Next;
    char m_Digit;
} TNODE;

TNODE *createNode(char digit, TNODE *next) {
    TNODE *n = (TNODE *)malloc(sizeof(*n));
    n->m_Digit = digit;
    n->m_Next = next;
    return n;
}

void deleteList(TNODE *l) {
    while (l) {
        TNODE *tmp = l->m_Next;
        free(l);
        l = tmp;
    }
}
#endif /* __PROGTEST__ */
void printList (TNODE *a) {
    while (a) {
        printf("%c->", a->m_Digit);
        a = a->m_Next;
    }
    printf("\n");
}
int validList (TNODE * a) {
    if (!a) return 0;
    int zeroCounter = 0, length = 0;
    while (a) {
        if (! ((a->m_Digit <= '9' && a->m_Digit >= '0') || (a->m_Digit >= 'a' && a->m_Digit <= 'f')) ) {
            return 0;
        }
        if (a->m_Digit == '0') {
            zeroCounter++;
        } else {
            zeroCounter = 0;
        }
        a = a->m_Next;
        length++;
    }
    if (zeroCounter && length !=1) {
        return 0;
    }
    return 1;
}
TNODE * reverseList (TNODE * a) {
    TNODE * cur = a;
    TNODE * tmp;
    TNODE * p = NULL;
    while (cur) {
        tmp = cur;
        cur = cur->m_Next;
        tmp->m_Next = p;
        p = tmp;
    }
    return tmp;
}
TNODE *  shiftList (TNODE * a) {
    TNODE * res = NULL;
    char remainder = 0;
    int digit;
    while (a) {
        if (a->m_Digit >= '0' && a->m_Digit <= '9') {
            digit = (a->m_Digit - '0')*2 + remainder; 
        }
        if (a->m_Digit >= 'a' && a->m_Digit <= 'f') {
            digit = (a->m_Digit - 'a' + 10)*2 + remainder;
        }
        remainder = 0;
        if (digit > 15) {
            digit -= 16;
            remainder = 1;
        }
        if (digit > 9) {
            res = createNode(digit + 'a' - 10, res);
        } else {
            res = createNode(digit + '0', res);
        }
        a = a->m_Next;
    }
    if (remainder) {
        res = createNode ('1', res);
    }
    res = reverseList(res);
    return res;
}
TNODE * shiftLeft ( TNODE * a, unsigned int shift) {
    if (!validList(a)) return NULL;
    int shifts = shift/4;
    int modShift = shift%4;
    for (int i = 0; i < shifts; i++) {
        a = createNode('0', a);
    }
    for (int i = 0; i < modShift; ++i) {
        TNODE *kek = a;
        a = shiftList(a);
        if(i) deleteList(kek);
    }
    printList(a);
    return a;
}
#ifndef __PROGTEST__
int main(int argc, char *argv[])
{
    TNODE *a = NULL, *res = NULL;
    a = createNode('3',
                   createNode('2',
                              createNode('1', NULL)));
    res = shiftLeft(a, 1);
    assert(res->m_Digit == '6');
    assert(res->m_Next->m_Digit == '4');
    assert(res->m_Next->m_Next->m_Digit == '2');
    assert(res->m_Next->m_Next->m_Next == NULL);

    deleteList(a);
    deleteList(res);

    a = createNode('a',
                   createNode('w',
                              createNode('0', NULL)));
    res = shiftLeft(a, 12);
    assert(res == NULL);
    deleteList(a);
    deleteList(res);
    a = NULL;
    res = shiftLeft(a, 1);
    assert(res == NULL);

    deleteList(a);
    deleteList(res);

    a = createNode('f',
                   createNode('a',
                              createNode('1', NULL)));
    res = shiftLeft(a, 3);
    assert(res->m_Digit == '8');
    assert(res->m_Next->m_Digit == '7');
    assert(res->m_Next->m_Next->m_Digit == 'd');
    assert(res->m_Next->m_Next->m_Next == NULL);
    deleteList(a);
    deleteList(res);

    a = createNode('c',
                   createNode('5',
                              createNode('4',
                                         createNode('d',
                                                    createNode('1', NULL)))));
    res = shiftLeft(a, 5);
    assert(res->m_Digit == '0');
    assert(res->m_Next->m_Digit == '8');
    assert(res->m_Next->m_Next->m_Digit == 'b');
    assert(res->m_Next->m_Next->m_Next->m_Digit == '8');
    assert(res->m_Next->m_Next->m_Next->m_Next->m_Digit == 'a');
    assert(res->m_Next->m_Next->m_Next->m_Next->m_Next->m_Digit == '3');
    assert(res->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next == NULL);
    deleteList(a);
    deleteList(res);
/*
    a = createNode('a', NULL);
    res = shiftLeft(a, 12);
    assert(res->m_Digit == '0');
    assert(res->m_Next->m_Digit == '0');
    assert(res->m_Next->m_Next->m_Digit == '0');
    assert(res->m_Next->m_Next->m_Next->m_Digit == 'a');
    assert(res->m_Next->m_Next->m_Next->m_Next == NULL);
    deleteList(a);
    deleteList(res);*/
    return 0;
}
#endif /* __PROGTEST__ */