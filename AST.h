#include<parser.h>
#include "ASTDef.h"

<<<<<<< HEAD
ASTNode* makeAbstractSyntaxTree(treeNodeIt *root);

(ASTNodeIt* ) newNode (TAG taginf,tokenInfo ti, ASTNodeIt* input1,ASTNodeIt* input2)
{
    input1->next=input2;
    ASTNodeIt* final_node;
    final_node=(ASTNodeIt*)malloc(sizeof(ASTNodeIt));
    final_node->tag_info=taginf;
    final_node->leaf_symbol=ti;
    final_node->children=input1;
    input1->node->parent=final_node;
    input2->node->parent=final_node;
    return final_node;  
}

(ASTNodeIt*) ChildrenList (ASTNodeIt* input1, ASTNodeIt* input2)
{
    input1->next=input2;
    ASTNodeIt* final_node;
    final_node=(ASTNodeIt*)malloc(sizeof(ASTNodeIt));
    input1->node->parent=final_node;
    input2->node->parent=final_node;
    return final_node;

}
=======
//High-level functions needed for abstract syntax tree generation:
ASTNodeIt* makeAbstractSyntaxTree(treeNodeIt *root);
ASTNodeIt* populateSymbolTable(ASTNodeIt* root);
ASTNodeIt* extractTypes(ASTNodeIt* root);
ASTNodeIt* checkTypes(ASTNodeIt* root);
ASTNodeIt* semanticAnalyzer(treeNodeIt *root);

//Auxiliary functions:
ASTNodeIt* newNonLeafNode (TAG taginf, tokenInfo *ti, ASTNodeIt* input1, ASTNodeIt* input2);
ASTNodeIt* ChildrenList (ASTNodeIt* input1, ASTNodeIt* input2);
ASTNodeIt* newLeafNode(tokenInfo *ti);
//Nochestrell
>>>>>>> 20294208f07d7ee65a22425bbb8ddcef9fd4f337
