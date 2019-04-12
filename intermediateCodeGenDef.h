// GROUP 39
// AKANKSHYA MISHRA 2016A7PS0026P
// NARAPAREDDY BHAVANA 2016A7PS0034P
// KARABEE BATTA 2016A7PS0052P
// AASTHA KATARIA 2016A7PS0062P

#include "SymbolTableDef.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int LABEL;
typedef int TEMP;
typedef struct 
{
    
    union 
    {
        hash_ele* hElem;
        LABEL l;  
        TEMP t;
        int num;
        float rnum;
        int flag;
    }arg1;

    union 
    {
        hash_ele* hElem;
        LABEL l;  
        TEMP t;
        int num;
        float rnum;
        int flag;
    }arg2;

    union 
    {
        /* data */
    };
    

    
    
      
}quadruple;

