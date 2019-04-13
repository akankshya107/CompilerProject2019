// GROUP 39
// AKANKSHYA MISHRA 2016A7PS0026P
// NARAPAREDDY BHAVANA 2016A7PS0034P
// KARABEE BATTA 2016A7PS0052P
// AASTHA KATARIA 2016A7PS0062P

#include "ASTDef.h"
#include "SymbolTableDef.h"
typedef int LABEL;
typedef int TEMP;
typedef struct IntermediateDef IntermediateDef;

typedef struct arg1
{
    int flag;
    union 
    {
        hash_ele* hElem;
        LABEL l;
        TEMP t;
        int num;
        float rnum;
    }u;
}arg1;

typedef struct arg2
{
    int flag;
    union 
    {
        hash_ele* hElem;
        LABEL l;
        TEMP t;
        int num;
        float rnum;
    }u;
}arg2;

typedef struct  op
{
    int flag;
    union
    {
        TAG tag;
        TOKEN tkname;
    }u;
}op;

typedef struct quadruple
{
   arg1* a1;
   arg2* a2;
   op* operand;
    int result;
    quadruple* next;  
}quadruple;
