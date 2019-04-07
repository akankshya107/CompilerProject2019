// GROUP 39
// AKANKSHYA MISHRA 2016A7PS0026P
// NARAPAREDDY BHAVANA 2016A7PS0034P
// KARABEE BATTA 2016A7PS0052P
// AASTHA KATARIA 2016A7PS0062P
#include "ASTDef.h"

//High-level functions needed for abstract syntax tree generation:
ASTNodeIt* makeAbstractSyntaxTree(treeNodeIt *root);

//Auxiliary functions:
ASTNodeIt* newNonLeafNode (TAG taginf, tokenInfo *ti, ASTNodeIt* input1, ASTNodeIt* input2);
ASTNodeIt* ChildrenList (ASTNodeIt* input1, ASTNodeIt* input2);
ASTNodeIt* newLeafNode(tokenInfo *ti);
void freeChildren(treeNodeIt *temp);
//Nochestrell