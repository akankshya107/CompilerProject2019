#include "Intermediate.h"

quadruple *writeDataDefs(quadruple *code, FILE *fp);
void writeCode(quadruple *code, FILE *fp);
void generateCode(ASTNodeIt *ast, char *filename);