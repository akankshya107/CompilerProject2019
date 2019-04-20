// GROUP 39
// AKANKSHYA MISHRA 2016A7PS0026P
// NARAPAREDDY BHAVANA 2016A7PS0034P
// KARABEE BATTA 2016A7PS0052P
// AASTHA KATARIA 2016A7PS0062P
#include "SymbolTableDef.h"
#define SYM_INCLUDED
//hashtable functions
char *TypeString(int index);
int hashEle(char *str);
void insertIntoHTEle(hash_ele *elem, HashTable HT);
hash_ele *create_hashEle(Element *ele, char* str);
hash_ele* lookupEle(char *str, HashTable HT);
hash_ele *create_hashEle(Element *ele, char *str);
HashTable create_HTEle();
Element* create_elem(int flag);
ASTNodeIt* iterate_inorder(ASTNodeIt* temp);
ASTNodeIt* populateSymbolTable(ASTNodeIt* root);
ASTNodeIt* populateGlobalTable(ASTNodeIt* root);
void printSymbolTable();
void printGlobalTable_recDef();
void printGlobalvar();
void print_inpar_list();
void print_outpar_list();
void printMemActRec();
void extractTypes(ASTNodeIt* root);

