#include "ASTDef.h"

//High-level functions needed for abstract syntax tree generation:
ASTNodeIt* makeAbstractSyntaxTree(treeNodeIt *root);
ASTNodeIt* populateSymbolTable(ASTNodeIt* root);
ASTNodeIt* extractTypes(ASTNodeIt* root);
ASTNodeIt* checkTypes(ASTNodeIt* root);
ASTNodeIt* semanticAnalyzer(treeNodeIt *root);

//Auxiliary functions:
ASTNodeIt* returnASTNodeIt();
ASTNode* returnASTNode();
//Nochestrell