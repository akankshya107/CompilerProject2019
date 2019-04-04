#include "parserDef.h"

<<<<<<< HEAD
<<<<<<< HEAD
typedef struct ASTNodeIt ASTNodeIt;
typedef enum{}TAG;
typedef struct ASTNode{
=======
typedef enum{ X, y
}TAG;

typedef struct{
>>>>>>> 20294208f07d7ee65a22425bbb8ddcef9fd4f337
=======
typedef enum{ TAG_PROGRAM, TAG_FUN_LIST, TAG_MAIN, TAG_ARITHMETIC_EXPRESSION, TAG_BOOLEAN_EXPRESSION
}TAG;

typedef struct{
>>>>>>> 16b2ac9ea58cac25cd368cb4cc5cc73eb6440756
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
