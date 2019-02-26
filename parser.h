#include <stdio.h>
#include "parserDef.h"
void ComputeFirstAndFollowSets(g_node_head **grammar);
void createParseTable(node **first, node **follow, table T);
void parseInputSourceCode(FILE *testcaseFile, table T);
void printParseTree(treeNode *t, FILE *outfile);
//Error recovery functions
//Function pointer functions
