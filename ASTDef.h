// GROUP 39
// AKANKSHYA MISHRA 2016A7PS0026P
// NARAPAREDDY BHAVANA 2016A7PS0034P
// KARABEE BATTA 2016A7PS0052P
// AASTHA KATARIA 2016A7PS0062P
#ifndef PARSE_INCLUDED
#include "parserDef.h"
#endif

typedef enum{ TAG_PROGRAM, TAG_FUN_LIST, TAG_MAIN, TAG_ARITHMETIC_EXPRESSION, TAG_BOOLEAN_EXPRESSION, 
TAG_OTHERSTMTS, TAG_RETURNSTMT, TAG_DECLARES, TAG_TYPEDEFS, TAG_TYPEDEF, TAG_FIELDDEF, TAG_DECLARE,
TAG_FUNCTION, TAG_INPUT_PARS, TAG_OUTPUT_PARS, TAG_ASSIGNMENT_STMT, TAG_FUN_CALL_STMT, TAG_OUTPUT_ARGS,
TAG_INPUT_ARGS, TAG_ITERATIVE_STMT, TAG_COND_STMT, TAG_THEN, TAG_ELSE, TAG_READ, TAG_WRITE
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

