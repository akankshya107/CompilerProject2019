// GROUP 39
// AKANKSHYA MISHRA 2016A7PS0026P
// NARAPAREDDY BHAVANA 2016A7PS0034P
// KARABEE BATTA 2016A7PS0052P
// AASTHA KATARIA 2016A7PS0062P
#define everything
#include "SymbolTableDef.h"


//hashtable functions
int hashEle(char *str);
void insertIntoHTEle(hash_ele *elem, HashTable HT);
hash_ele *create_hashEle(Element *ele, char* str);
hash_ele* lookupEle(char *str, HashTable HT);
hash_ele *create_hashEle(Element *ele, char *str);
Element* create_elem(bool flag);
ASTNodeIt* iterate_inorder(ASTNodeIt* temp);
// void* populateSymbolTable(ASTNodeIt* root);

//semantic analyzer functions
void populateSymbolTable(ASTNodeIt* root);
void extractTypes(ASTNodeIt* root);

