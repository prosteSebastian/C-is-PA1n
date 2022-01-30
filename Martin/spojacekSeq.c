#ifndef __PROGTEST__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

typedef struct tnode {
    struct tnode *m_Next;
    int m_Val;
} Tnode;

Tnode *createItem(int i, Tnode *next) {
    Tnode *l = (Tnode *)malloc(sizeof(*l));
    l->m_Val = i;
    l->m_Next = next;
    return l;
}
void delList(Tnode *l) {
    while (l) {
        Tnode * tmp = l->m_Next;
        free(l);
        l = tmp;
    }
}
#endif /* __PROGTEST__ */
int validList (Tnode *l) {
    if (!l) return 0;
    int tmp = l->m_Val;
    l = l->m_Next;
    while (l) {
        if (tmp > l->m_Val) return 0;
        tmp = l->m_Val;
        l = l->m_Next;
    }
    return 1;
}
void printList (Tnode *a) {
    while (a) {
        printf("%d ->", a->m_Val);
        a = a->m_Next;
    }
    printf("\n");
}
Tnode * reverseList (Tnode *a) {
    Tnode * cur = a;
    Tnode * tmp;
    Tnode * p=NULL;
    while (cur){
        tmp = cur;
        cur = cur->m_Next;
        tmp->m_Next = p;
        p = tmp;
    }
    return tmp;
}
Tnode * mergeLists (Tnode *a, Tnode *b) {
    Tnode * res = NULL;
    while (a && b) {
        if (a->m_Val > b->m_Val) {
            res = createItem(b->m_Val, res);
            b = b->m_Next;
        } else {
            res = createItem(a->m_Val, res);
            a = a->m_Next;
        }
    }
    while (a) {
        res = createItem(a->m_Val, res);
        a = a->m_Next;
    }

    while (b) {
        res = createItem(b->m_Val, res);
        b = b->m_Next;
    }
    return reverseList(res);
}
Tnode * compareList (Tnode **a, int nr) {
    for (int i = 0; i < nr; i++) {
        if (!validList(a[i])) return NULL;
    }
    Tnode * res = a[0];
    for (int i = 1; i < nr; i++) {
        res = mergeLists(res, a[i]);
    }
    return res;
}

#ifndef __PROGTEST__
int main(int argc, char *argv[]) {
    Tnode *a[5];
    Tnode *res;

    a[0] = createItem(5, NULL);
    a[1] = createItem(1,
                      createItem(2,
                                 createItem(6,
                                            createItem(7,
                                                       createItem(8,
                                                                  createItem(9, NULL))))));
    res = compareList(a, 2);
    delList(res);
    for (int i = 0; i < 2; i++) {
        delList(a[i]);
    }
    a[0] = createItem(1,
                      createItem(7,
                                 createItem(24, NULL)));
    a[1] = createItem(3,
                      createItem(5,
                                 createItem(17, NULL)));
    a[2] = createItem(-3,
                      createItem(19, NULL));
    res = compareList(a, 3);
    delList(res);
    for (int i = 0; i < 3; i++) {
        delList(a[i]);
    }
    a[0] = createItem(15,
                      createItem(19,
                                 createItem(23,
                                            createItem(192, NULL))));
    a[1] = createItem(17,
                      createItem(18,
                                 createItem(18,
                                            createItem(21, NULL))));
    a[2] = createItem(-3,
                      createItem(19, NULL));
    res = compareList(a, 3);
    delList(res);
    for (int i = 0; i < 3; i++) {
        delList(a[i]);
    }
    a[0] = createItem(-4,
                      createItem(2,
                                 createItem(4,
                                            createItem(7, NULL))));
    a[1] = createItem(12,
                      createItem(18,
                                 createItem(20, NULL)));
    a[2] = createItem(-6,
                      createItem(3,
                                 createItem(4,
                                            createItem(11,
                                                       createItem(14,
                                                                  createItem(15,
                                                                             createItem(19, NULL)))))));
    res = compareList(a, 3);
    delList(res);
    for (int i = 0; i < 3; i++) {
        delList(a[i]);
    }
    a[0] = createItem(-4,
                      createItem(2,
                                 createItem(4,
                                            createItem(7, NULL))));
    a[1] = createItem(12,
                      createItem(18,
                                 createItem(20, NULL)));
    a[2] = createItem(-6,
                      createItem(3,
                                 createItem(4,
                                            createItem(11,
                                                       createItem(1,
                                                                  createItem(15,
                                                                             createItem(19, NULL)))))));
    res = compareList(a, 3);
    assert(res == NULL);
    delList(res);
    for (int i = 0; i < 3; i++) {
        delList(a[i]);
    }
    a[0] = createItem(-4,
                      createItem(2,
                                 createItem(4,
                                            createItem(7, NULL))));
    a[1] = createItem(12, NULL);
    a[2] = createItem(3, NULL);
    res = compareList(a, 3);
    delList(res);
    for (int i = 0; i < 3; i++) {
        delList(a[i]);
    }
    a[0] = createItem(15,
                      createItem(19,
                                 createItem(19,
                                            createItem(2, NULL))));
    a[1] = createItem(17,
                      createItem(18,
                                 createItem(18,
                                            createItem(21, NULL))));
    res = compareList(a, 2);
    assert(res == NULL);
    delList(res);
    for (int i = 0; i < 2; i++) {
        delList(a[i]);
    }
    a[0] = createItem(15,
                      createItem(19,
                                 createItem(19,
                                            createItem(2, NULL))));
    a[1] = NULL;
    a[2] = createItem(-2,
                      createItem(1,
                                 createItem(10,
                                            createItem(11, NULL))));
    res = compareList(a, 3);
    assert(res == NULL);
    delList(res);
    for (int i = 0; i < 3; i++) {
        delList(a[i]);
    }
    
    return 0;
}
#endif /* __PROGTEST__ */
