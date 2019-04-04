#include "parserDef.h"

<<<<<<< HEAD
typedef struct ASTNodeIt ASTNodeIt;
typedef enum{}TAG;
typedef struct ASTNode{
=======
typedef enum{ X, y
}TAG;

typedef struct{
>>>>>>> 20294208f07d7ee65a22425bbb8ddcef9fd4f337
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
