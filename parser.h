#include "parserDef.h"
FirstAndFollow *ComputeFirstAndFollowSets(g_node **grammar);
void createParseTable(FirstAndFollow *f, parse_table T);
void parseInputSourceCode(char *testcaseFile, parse_table T);
// void printParseTree(treeNode *t, char *outfile);

//Aux functions
g_node** populateGrammar();
g_node* create_g_node_head(char *nonterminal);
g_node* create_g_node();
node* create_node();

//Error recovery functions
//Function pointer functions
