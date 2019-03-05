#ifndef PARSE_INCLUDED
#include "parserDef.h"
#endif
void ComputeFirstAndFollowSets();
treeNodeIt* parseInputSourceCode(char *testcaseFile);
void printParseTree(treeNodeIt *root, char *outfile);
void createParseTable();
//Aux functions