#ifndef PARSE_INCLUDED
#include "parserDef.h"
#endif
void ComputeFirstAndFollowSets();
// void createParseTable(FirstAndFollow *f, parse_table T);
void parseInputSourceCode(char *testcaseFile);
void printParseTree(treeNode *root, char *outfile);
void createParseTable();
//Aux functions