#include "keyDef.h"
int hash(char *str);
hashTable populateKeyWordTable();
void insertIntoHT(hash_elem *elem);
hash_elem *create_hash_elem(int tkname, char* str);
hash_elem* lookup(char *str);