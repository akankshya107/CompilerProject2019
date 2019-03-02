#ifndef LEX_DEF_INCLUDED
#include "lexerDef.h"
#endif
#define NO_OF_KEYWORDS 24
typedef struct {
    char *str;
    TOKEN tkname;
} hash_elem;

typedef hash_elem **hashTable;
hashTable KeyWordTable; 