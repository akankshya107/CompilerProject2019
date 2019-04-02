#include "ASTDef.h"

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
void freeChildren(treeNodeIt *temp);
//Nochestrell