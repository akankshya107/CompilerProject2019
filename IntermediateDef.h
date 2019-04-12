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
typedef struct quadraple
{
   union 
    {
       int flag;
       hash_ele* hElem;
       LABEL l;
       TEMP t;
       int num;
       float rnum;
    }arg1;

    union 
    {
        int flag;
        hash_ele* hElem;
        LABEL l;
        TEMP t;
        int num;
        float rnum;
    }arg2;

    union
    {
        int flag;
        TAG tag;
        TOKEN tkname;
    }op;

    union 
    {
        int flag;
        int result;
        hash_ele* Hresult;
    }result; 
    quadraple* next;  
}quadraple;
