#include <stdbool.h>
#ifndef LEX_DEF_INCLUDED
#include "lexerDef.h"
#endif
#define NO_OF_RULES 50
#define NO_OF_GRAMMAR_RULES 87
#define MAX_DIFF_RULES 10

typedef struct node{
	TOKEN tokenName;
	int rule_no_index;
	struct node *next;
}node;    //used for first and follow
typedef struct node_head_follow
{
	bool is_visited;
	node* head;
}node_head_follow;

typedef struct node_head_first
{
	bool has_eps;
	node* head;
}node_head_first;

typedef struct{
	node_head_first **first;
	node_head_follow **follow;
}FirstAndFollow;

FirstAndFollow *f;

struct g_node;

typedef struct {
	NON_TERMINAL non_terminal;
	int rule_no;
	struct g_node *next;
} g_node_head;

typedef struct g_node{
	bool is_term;
	union{
		TOKEN terminal;
		NON_TERMINAL nonterminal;
	}elem;
	struct g_node *next;
	struct g_node *prev; //doubly linked list
}g_node;

g_node_head **grammar;

typedef struct nonterminal_str{
	char *nonterminal;
	int *rules;
	int length;
}nonterminal_str;

nonterminal_str** nonTerminalStringTable;

typedef struct f_node{
	int is_error;
	union{
		int rule_no_index;
		void (*error) (void);
	}table_Entry;
}parse_table_elem;

typedef parse_table_elem** parse_table;
parse_table T;

// typedef struct{
// 	tokenInfo *leaf_symbol;
// }leafNode;

// typedef struct{
// 	NON_TERMINAL nonterminal;
// 	g_node *children;
// }nonLeafNode;

// typedef struct{
// 	bool is_leaf;
// 	union{
// 		leafNode *l;
// 		nonLeafNode *n;
// 	}treeNode_type;
// }treeNode;