// GROUP 39
// AKANKSHYA MISHRA 2016A7PS0026P
// NARAPAREDDY BHAVANA 2016A7PS0034P
// KARABEE BATTA 2016A7PS0052P
// AASTHA KATARIA 2016A7PS0062P
#include "keyDef.h"
int hash(char *str);
void populateKeyWordTable();
void insertIntoHT(hash_elem *elem);
hash_elem *create_hash_elem(int tkname, char* str);
hash_elem* lookup(char *str);