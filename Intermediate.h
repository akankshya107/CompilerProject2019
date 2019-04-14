#include "IntermediateDef.h"
TEMP newTemp();
LABEL newLabel();
result *newResult(int flag, TEMP t, LABEL l);
arg* newArg(int flag, hash_ele* h, TEMP t, LABEL L, int num, float rnum, int width);
op* newOp(int flag, TAG tag, TOKEN tkname);
label* returnLabel(int flag, LABEL l, char* dataDef);
quadruple* newQuad(arg *a1, arg *a2, op* op, LABEL *l, result *res);
quadruple* generateIntermediateCode(ASTNodeIt* root);
