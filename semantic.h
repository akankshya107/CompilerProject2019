// GROUP 39
// AKANKSHYA MISHRA 2016A7PS0026P
// NARAPAREDDY BHAVANA 2016A7PS0034P
// KARABEE BATTA 2016A7PS0052P
// AASTHA KATARIA 2016A7PS0062P
#include "semanticDef.h"
#include "ASTDef.h"
//hashtable functions
int hash(char *str);
void insertIntoHT(hash_elem *elem, hashTable HT);
hash_elem *create_hash_elem(Element *ele, char* str);
hash_elem* lookup(char *str, hashTable HT);

//semantic analyzer functions
ASTNodeIt* populateSymbolTable(ASTNodeIt* root);
ASTNodeIt* extractTypes(ASTNodeIt* root);
ASTNodeIt* checkTypes(ASTNodeIt* root);
<<<<<<< HEAD
ASTNodeIt* semanticAnalyzer(treeNodeIt *root);
=======
ASTNodeIt* semanticAnalyzer(treeNodeIt *root);
>>>>>>> cf0333a6a161c288d0bd26767ef5b9ce907ab4fa
