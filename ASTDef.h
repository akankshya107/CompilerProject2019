#include "parserDef.h"

typedef enum{ X, y
}TAG;

typedef struct{
    TAG tag_info;
    tokenInfo *leaf_symbol;
    ASTNodeIt *children;
}nonLeaf;

typedef struct{
    tokenInfo *leaf_symbol;
}Leaf;

typedef struct ASTNode{
    bool is_leaf;
    union{
        nonLeaf *n;
        Leaf *l;
    }u;
    ASTNodeIt *parent;
}ASTNode;

typedef struct ASTNodeIt{
    ASTNode *node;
    ASTNodeIt *next;
}ASTNodeIt;