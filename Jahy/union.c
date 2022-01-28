#include <stdlib.h>
#include <stdio.h>

typedef struct TNode {
  struct TNode * m_L, * m_R;
  int m_Val;
} TNODE;

int printTree(TNODE * root, int d, int i){
    if (root == NULL) return 0;
    d+=1; // počet teček
    i += printTree(root->m_L, d, i);
    printf("%2d: ", i + 1);
    i++;
    for (int i = 0; i < d; i++) printf(".");
    printf("%2d\n", root->m_Val);
    i += printTree(root->m_R, d, i);
    d-=1;
    return i;
}

TNODE * treeOne ( )
{
    TNODE * add = (TNODE*) malloc (sizeof(TNODE));
    add->m_Val = 5;

    add->m_L = (TNODE*) malloc (sizeof(TNODE));
    add->m_L->m_Val = 3;
    add->m_L->m_L = NULL;
    add->m_L->m_R = NULL;

    add->m_R = (TNODE*) malloc (sizeof(TNODE));
    add->m_R->m_Val = 1;
    add->m_R->m_L = NULL;
    add->m_R->m_R = (TNODE*) malloc (sizeof(TNODE));

    add->m_R->m_R->m_Val = -2;
    add->m_R->m_R->m_L = NULL;
    add->m_R->m_R->m_R = (TNODE*) malloc (sizeof(TNODE));

    add->m_R->m_R->m_R->m_Val = 8;
    add->m_R->m_R->m_R->m_L = NULL;
    add->m_R->m_R->m_R->m_R = NULL;
    
    return add;
}

TNODE * treeTwo ( )
{
    TNODE * add = (TNODE*) malloc (sizeof(TNODE));
    add->m_Val = 8;

    add->m_R = (TNODE*) malloc (sizeof(TNODE));
    add->m_R->m_Val = 4;
    add->m_R->m_L = NULL;
    add->m_R->m_R = NULL;

    add->m_L = (TNODE*) malloc (sizeof(TNODE));
    add->m_L->m_Val = 9;
    add->m_L->m_R = NULL;
    add->m_L->m_L = (TNODE*) malloc (sizeof(TNODE));

    add->m_L->m_L->m_Val = -7;
    add->m_L->m_L->m_R = NULL;
    add->m_L->m_L->m_L = (TNODE*) malloc (sizeof(TNODE));

    add->m_L->m_L->m_L->m_Val = 5;
    add->m_L->m_L->m_L->m_L = NULL;
    add->m_L->m_L->m_L->m_R = NULL;
    
    return add;
}

//side: 1=left, 2=right, 3=both
TNODE * addBranch (TNODE * tree ,int side, int value){
    if ( tree == NULL )
    {
        TNODE * c = (TNODE*)malloc(sizeof(TNODE));
        c->m_L = NULL;
        c->m_R = NULL;
        c->m_Val = value;
        return c;
    }
    else{
        if ( side == 1 )
        {
            tree->m_L = addBranch(tree->m_L,0,value);
        }
        else if (side == 2)
        {
            tree->m_R = addBranch(tree->m_R,0,value);
        }
        return tree;
    }
}

TNODE * unionTree ( TNODE * a, TNODE * b ){
    TNODE * c = NULL;
    if ( a!=NULL && b!=NULL )
    {
        c = (TNODE*)malloc(sizeof(TNODE));
        c->m_Val = a->m_Val+b->m_Val;
        c->m_L = unionTree(a->m_L,b->m_L);
        c->m_R = unionTree(a->m_R,b->m_R);
    }
    else if ( a!=NULL )
    {
        c = (TNODE*)malloc(sizeof(TNODE));
        c->m_Val = a->m_Val;
        c->m_L = unionTree(a->m_L,NULL);
        c->m_R = unionTree(a->m_R,NULL);
    }
    else if (b!=NULL)
    {
        c = (TNODE*)malloc(sizeof(TNODE));
        c->m_Val = b->m_Val;
        c->m_L = unionTree(NULL,b->m_L);
        c->m_R = unionTree(NULL,b->m_R);
    }
    return c;
}

void freeTree ( TNODE * tree ){
    if ( tree == NULL )
    {
        return;
    }
    freeTree(tree->m_L);
    freeTree(tree->m_R);
    free( tree );
}

int main(int argc, char const *argv[])
{
    TNODE * tree1 = NULL;
    TNODE * tree2 = NULL;

    printf("Tree1:\n");
    //tree1 = treeOne();
    tree1 = addBranch(tree1,0,5);
    tree1 = addBranch(tree1,1,3);
    tree1 = addBranch(tree1,2,1);
    printTree(tree1,0,0);

    printf("Tree2:\n");
    //tree2 = treeTwo();
    tree2 = addBranch(tree2,0,8);
    tree2 = addBranch(tree2,1,9);
    tree2 = addBranch(tree2,2,4);
    printTree(tree2,0,0);
    
    printf("Tree:\n");
    TNODE * tree = unionTree(tree1,tree2);
    printTree(tree,0,0);
    
    freeTree(tree1);
    freeTree(tree2);
    freeTree(tree);
    return 1;
}