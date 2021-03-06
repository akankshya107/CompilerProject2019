// GROUP 39
// AKANKSHYA MISHRA 2016A7PS0026P
// NARAPAREDDY BHAVANA 2016A7PS0034P
// KARABEE BATTA 2016A7PS0052P
// AASTHA KATARIA 2016A7PS0062P
#ifndef GRAM_INCLUDED
#include "grammarDef.h"
#endif

void populateGrammar();
g_node_head* create_g_node_head(NON_TERMINAL nt);
g_node* create_g_node();
node* create_node();
g_node* first_gnode(g_node_head* h,int no,bool is_term);
g_node* dl_nodes(g_node* pnext,int no,bool is_term);
void print_gnode(g_node* ptr);
void print_grule(g_node_head* head);
void first_eps(node_head_follow* head,g_node* temp,g_node_head* g);
void first(NON_TERMINAL nt_index);
void follow(NON_TERMINAL nt_index);
node_head_follow* create_head_follow(NON_TERMINAL nt_index);
void add_ftof(node_head_follow* head,node* firstorfollow);
void add_nodetof(node_head_follow* head,TOKEN tk);
void clear_flags_follow();
void recurse_first(node_head_first* node_head,g_node* temp, int rule_no);
void add_list_to_first(node_head_first* head, node* list);
void add_node_to_first(node_head_first* head,TOKEN tk, int rule);
void print_follow(NON_TERMINAL nt);

void populateStrTable();
nonterminal_str* create_nt_str();
void print_strTable_row(NON_TERMINAL nt);
void print_strTable();
void print_first(NON_TERMINAL nt);
node_head_first* create_head_first(NON_TERMINAL nt_index);
node_head_follow* create_head_follow(NON_TERMINAL nt_index);
void free_first_follow();
void add_list_to_first_eps(node_head_first* head, node* list,int rule);
