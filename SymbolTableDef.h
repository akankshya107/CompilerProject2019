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
#define INT_WIDTH 2
#define REAL_WIDTH 4

typedef struct Ele{
  ASTNodeIt *node;
  struct Ele *next;
}Ele;
#define ELEM
#include "stack.h"

typedef struct Element Element;
typedef struct hT hash_ele;
typedef struct hT{
    char *str;
    Element *ele;
    hash_ele *next;
}hash_ele;

typedef hash_ele **HashTable;
HashTable globalSymbolTable;
HashTable SymbolTable;

typedef struct symTableElem{
    type* t;
    int width;
    int offset;
}symTableElem;

typedef struct{
    bool tag;
    char *ret_par;
}out; //Should be made NULL for in_pars

typedef struct SeqListPars{
    bool out_flg;
    type *t;
    out *out_check;
    struct SeqListPars *next;
}SeqListPars;

typedef struct rec{
    char *rec_id;
    ASTNodeIt *record_ptr;
    int width;
}rec;

typedef struct globalTableElem{
    bool is_record;
    union{
        type* t;
        rec* rec_type_list;    
    }u;
    int offset;
}globalTableElem;

typedef struct symT{
    SeqListPars *in_pars;
    SeqListPars *out_pars;
    HashTable SymbolTable;
}symT;

typedef struct Element{
    int flag; 
//0 for FUN_ID hashtable, 1 for Symbol Table for a function, 2 for global hashtable(containing global variables and record definitions)
    union{
        symT* out_table;
        symTableElem *s;
        globalTableElem *g;
    }u;
}Element;