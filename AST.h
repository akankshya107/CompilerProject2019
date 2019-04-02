#include<parser.h>
#include "ASTDef.h"

ASTNode* makeAbstractSyntaxTree(treeNodeIt *root);

(ASTNode* ) newNode(TAG taginf,tokenInfo ti, ASTNode* input1,ASTNode* input2)
{
    input1->next=input2;
    ASTNode* final_node=(ASTNode*)malloc(sizeof(ASTNode));
    final_node->tag_info=taginf;
    final_node->token_info=ti;
    final_node->children=input1;
    input1->node->parent=final_node->parent;
    input2->node->parent=final_node->parent;
    return final_node;   

}