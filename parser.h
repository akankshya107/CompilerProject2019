#include "parserDef.h"
FirstAndFollow *ComputeFirstAndFollowSets(g_node_head **grammar);
void createParseTable(FirstAndFollow *f, table T);
void parseInputSourceCode(char *testcaseFile, table T);
void printParseTree(treeNode *t, char *outfile);

//Aux functions
g_node_head** populateGrammar();
g_node_head* create_g_node_head(char *nonterminal);
g_node* create_g_node();
node* create_node();

//Error recovery functions
//Function pointer functions
