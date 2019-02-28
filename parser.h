#include "parserDef.h"
FirstAndFollow *ComputeFirstAndFollowSets(g_node **grammar);
void createParseTable(FirstAndFollow *f, parse_table T);
void parseInputSourceCode(char *testcaseFile, parse_table T);
// void printParseTree(treeNode *t, char *outfile);

//Aux functions
g_node_head** populateGrammar();
g_node_head* create_g_node_head(NON_TERMINAL nt);
g_node* create_g_node(bool is_term, int value);
node* create_node(TOKEN tkname, int rule_no);

//Error recovery functions
//Function pointer functions
