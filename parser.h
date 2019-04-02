// GROUP 39
// AKANKSHYA MISHRA 2016A7PS0026P
// NARAPAREDDY BHAVANA 2016A7PS0034P
// KARABEE BATTA 2016A7PS0052P
// AASTHA KATARIA 2016A7PS0062P
#include <stdio.h>
#ifndef PARSE_INCLUDED
#include "parserDef.h"
<<<<<<< HEAD
void ComputeFirstAndFollowSets();

void parseInputSourceCode(char *testcaseFile, parse_table T);
// void printParseTree(treeNode *t, char *outfile);

//Aux functions
void populateGrammar();
g_node_head* create_g_node_head(NON_TERMINAL nt);
g_node* create_g_node();
node* create_node();
g_node* first_gnode(g_node_head* h,int no,bool is_term);
g_node* dl_nodes(g_node* pnext,int no,bool is_term);
void print_gnode(g_node* ptr);
void print_grule(g_node_head* head);
node* first_eps(node_head_follow* head,g_node* temp,g_node_head* g);
void first(NON_TERMINAL nt_index);
void follow(NON_TERMINAL nt_index);
node_head_follow* create_head_follow(NON_TERMINAL nt_index);
void add_ftof(node_head_follow* head,node* firstorfollow);
void add_nodetof(node_head_follow* head,TOKEN tk);
void clear_flags_follow();
void recurse_first(node_head_first* node_head,g_node* temp, int rule_no);
void add_list_to_first(node_head_first* head, node* list);
void add_node_to_first(node_head_first* head,TOKEN tk, int rule);
void add_list_to_first_eps(node_head_first* head, node* list);
void print_follow(NON_TERMINAL nt);
char *TerminalString(int index);
void first_eps_stmt(node_head_follow* node_head,g_node* temp,g_node_head* g);
void populateStrTable();
nonterminal_str* create_nt_str();
void print_strTable_row(NON_TERMINAL nt);
void print_strTable();
void print_first(NON_TERMINAL nt);

//Transition Table
void createParseTable( );
void error_function();
void syn_error();
void print_parse_table();
void free_first_follow();



//Error recovery functions
//Function pointer functions
=======
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
>>>>>>> 822a511e5ac2b3b3685296573d69ef557a776d65
