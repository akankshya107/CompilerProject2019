#include "parserDef.h"

typedef enum{}TAG;
typedef struct ASTNode{
    TAG tag;
    tokenInfo *leaf_symbol;
    ASTNodeIt *parent;
    ASTNodeIt *children;
}ASTNode;

typedef struct ASTNodeIt{
    ASTNode *node;
    ASTNodeIt *next;
}ASTNodeIt;
