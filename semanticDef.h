// GROUP 39
// AKANKSHYA MISHRA 2016A7PS0026P
// NARAPAREDDY BHAVANA 2016A7PS0034P
// KARABEE BATTA 2016A7PS0052P
// AASTHA KATARIA 2016A7PS0062P
#include <stdbool.h>
typedef enum{ INT, REAL, RECORD }TYPE;

typedef struct Element Element;
typedef struct h{
    char *str;
    Element *ele;
    struct h *next;
} hash_elem;

typedef hash_elem **hashTable;

typedef struct symTableElem{
    TYPE type;
    int width;
    int offset;
    symTableElem *typeList; //Only exists for TYPE==RECORD
}symTableElem;

typedef struct Element{
    bool is_func;
    union{
        hashTable SymbolTable;
        symTableElem *s;
    }u;
}Element;