// GROUP 39
// AKANKSHYA MISHRA 2016A7PS0026P
// NARAPAREDDY BHAVANA 2016A7PS0034P
// KARABEE BATTA 2016A7PS0052P
// AASTHA KATARIA 2016A7PS0062P
#include <stdbool.h>
#include "AST.h"
#define AST_INCLUDED
typedef enum{ INT, REAL, RECORD }TYPE;

typedef struct Element Element;
 

typedef struct hT{
    char *str;
    Element *ele;
    struct hT *next;
} hash_ele;

typedef hash_ele **hashTable;
hashTable globalSymbolTable;
hashTable SymbolTable;
typedef struct symTableElem{
    bool is_record;
    int width;
    int offset;
    union{
        TYPE pri_type;
        TYPE constr_type;
    }type;
    // symTableElem *typeList; //Only exists for TYPE==RECORD
}symTableElem;

typedef struct Element{
    bool is_func;
    union{
        hashTable SymbolTable;
        symTableElem *s;
    }u;
}Element;