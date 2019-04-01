// GROUP 39
// AKANKSHYA MISHRA 2016A7PS0026P
// NARAPAREDDY BHAVANA 2016A7PS0034P
// KARABEE BATTA 2016A7PS0052P
// AASTHA KATARIA 2016A7PS0062P
#ifndef LEX_DEF_INCLUDED
#include "lexerDef.h"
#endif
#define NO_OF_KEYWORDS 24
typedef struct h{
    char *str;
    TOKEN tkname;
    struct h *next;
} hash_elem;

typedef hash_elem **hashTable;
hashTable KeyWordTable; 