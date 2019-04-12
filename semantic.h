// GROUP 39
// AKANKSHYA MISHRA 2016A7PS0026P
// NARAPAREDDY BHAVANA 2016A7PS0034P
// KARABEE BATTA 2016A7PS0052P
// AASTHA KATARIA 2016A7PS0062P
#include "SymbolTable.h"
Ele* returnEle(ASTNodeIt *n);
ASTNodeIt *searchTag(ASTNodeIt *root, TAG tg);
ASTNodeIt *semanticAnalyzer(treeNodeIt *t);
void checkTypes(ASTNodeIt* root);
<<<<<<< HEAD
void semanticAnalyzer(treeNodeIt *root);
void printSymbolTable(ASTNodeIt *root);
=======
void semanticRuleCheck(ASTNodeIt *chk, char* fun_id);
type getType(ASTNodeIt *t);
>>>>>>> 1710f9d9377c283a8dfa2872115f3a01c987d24e
