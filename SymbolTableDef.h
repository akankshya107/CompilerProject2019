// GROUP 39
// AKANKSHYA MISHRA 2016A7PS0026P
// NARAPAREDDY BHAVANA 2016A7PS0034P
// KARABEE BATTA 2016A7PS0052P
// AASTHA KATARIA 2016A7PS0062P
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "AST.h"
#define LEN_HT 41
typedef enum{ INT, REAL, RECORD }TYPE;

typedef struct Ele{
  ASTNodeIt *node;
  struct Ele *next;
}Ele;
#define ELEM
#include "stack.h"

typedef struct Element Element;
typedef struct hT{
    char *str;
    Element *ele;
    struct hT *next;
}hash_ele;

typedef hash_ele **HashTable;
HashTable globalSymbolTable;
HashTable SymbolTable;
typedef struct symTableElem symTableElem;
typedef struct symTableElem{
    // TYPE type;
    bool is_record;
    int width;
    int offset;
    symTableElem *typeList; //Only exists for TYPE==RECORD
    union{
        TYPE pri_type;
        TYPE constr_type;
    }type;
    // symTableElem *typeList; //Only exists for TYPE==RECORD
}symTableElem;

typedef struct Element{
    bool is_func;
    union{
        HashTable SymbolTable;
        symTableElem *s;
    }u;
}Element;