#include "parserDef.h"
void ComputeFirstAndFollowSets();
void createParseTable(FirstAndFollow *f, parse_table T);
void parseInputSourceCode(char *testcaseFile, parse_table T);
// void printParseTree(treeNode *t, char *outfile);

//Aux functions
//Error recovery functions
//Function pointer functions