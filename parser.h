// GROUP 39
// AKANKSHYA MISHRA 2016A7PS0026P
// NARAPAREDDY BHAVANA 2016A7PS0034P
// KARABEE BATTA 2016A7PS0052P
// AASTHA KATARIA 2016A7PS0062P
#include <stdio.h>
#ifndef PARSE_INCLUDED
#include "parserDef.h"
#endif
void ComputeFirstAndFollowSets();
treeNodeIt* parseInputSourceCode(char *testcaseFile);
void printParseTree(treeNodeIt *root, char *outfile);
void createParseTable();
//Aux functions
treeNodeIt* returnIt(treeNode *t);
treeNode* returnTreeNode(bool is_leaf, int line_no);
treeNode* returnNonLeafNode(treeNode *t, NON_TERMINAL nt, int rule_no, treeNodeIt *children);
treeNode* returnLeafNode(treeNode *t, tokenInfo *ti);
treeNodeIt* makeTreeNodes(g_node_head *h, treeNodeIt *par, int line_no);
treeNodeIt* iterate(treeNodeIt *root);
void print_parse_table();
void print_leaf(FILE *fw, leafNode *l, NON_TERMINAL nt);
void print_nonleaf(FILE *fw, nonLeafNode *n, int line_no, NON_TERMINAL nt, bool flag);
void printParseTree(treeNodeIt *root, char *outfile);