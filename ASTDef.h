#include "parserDef.h"

typedef enum{ TAG_PROGRAM, TAG_FUN_LIST, TAG_MAIN, TAG_ARITHMETIC_EXPRESSION, TAG_BOOLEAN_EXPRESSION, 
TAG_OTHERSTMTS, TAG_RETURNSTMT, TAG_DECLARES, TAG_TYPEDEFS, TAG_TYPEDEF, TAG_FIELDDEF, TAG_DECLARE,
TAG_FUNCTION, TAG_INPUT_PARS, TAG_OUTPUT_PARS
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

