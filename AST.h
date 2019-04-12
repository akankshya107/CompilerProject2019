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
void printAST(ASTNodeIt* root);
char *TagString(int index);
size_t printASTNodes(ASTNodeIt *root);
<<<<<<< HEAD
=======
//Nochestrell
>>>>>>> 1710f9d9377c283a8dfa2872115f3a01c987d24e
