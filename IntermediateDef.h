// GROUP 39
// AKANKSHYA MISHRA 2016A7PS0026P
// NARAPAREDDY BHAVANA 2016A7PS0034P
// KARABEE BATTA 2016A7PS0052P
// AASTHA KATARIA 2016A7PS0062P

#include "SymbolTable.h"
typedef int LABEL;
typedef int TEMP;
typedef struct IntermediateDef IntermediateDef;

typedef struct arg{
    int flag;
    union{
        hash_ele* hElem;
        TEMP t;
        LABEL L; //TRUE is stored in arg1, FALSE in arg2
        int num;
        float rnum;
        int width;
    }u;
}arg;

typedef struct  op{
    int flag;
    union{
        TAG tag;
        TOKEN tkname;
    }u;
}op;

typedef struct{
    int flag;
    union{
        TEMP t; //temporary
        LABEL l;
    }u;
}result;

typedef struct label{
    int flag;
    union{
        LABEL l;
        char* dataDef;
    }u;
}label;

typedef struct quadruple{
    arg* a1;
    arg* a2;
    op* operand;
    result *res;
    label* l;
    struct quadruple* next;  
}quadruple;
