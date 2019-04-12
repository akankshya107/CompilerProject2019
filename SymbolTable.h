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
<<<<<<< HEAD
hash_ele *create_hashEle(Element *ele, char *str);
Element* create_elem(bool flag);
ASTNodeIt* iterate_inorder(ASTNodeIt* temp);
// void* populateSymbolTable(ASTNodeIt* root);

//semantic analyzer functions
void populateSymbolTable(ASTNodeIt* root);
void extractTypes(ASTNodeIt* root);

=======

//semantic analyzer functions
ASTNodeIt* populateSymbolTable(ASTNodeIt* root);
void populateGlobalTable(ASTNodeIt *root); //two passes
void printSymbolTable();
void printGlobalTable(bool flg);
void printMemReqST();
>>>>>>> 1710f9d9377c283a8dfa2872115f3a01c987d24e
