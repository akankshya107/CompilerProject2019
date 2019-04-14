// GROUP 39
// AKANKSHYA MISHRA 2016A7PS0026P
// NARAPAREDDY BHAVANA 2016A7PS0034P
// KARABEE BATTA 2016A7PS0052P
// AASTHA KATARIA 2016A7PS0062P

#include "intermediateCodeGenDef.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//(hash_ele*)find_hash_ele(char* str);
TEMP newTemp();
arg* newArg(int flag, hash_ele* h, TEMP t, LABEL L, int num, float rnum,int width);
arg* getArg(ASTNodeIt* ast);
op* newOp(int flag, TAG tag, TOKEN tkname);
quadruple* generateIntermediateCode(ASTNodeIt* root);

