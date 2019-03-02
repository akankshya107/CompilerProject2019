#include <stdbool.h>
#ifndef LEX_DEF_INCLUDED
#include "lexerDef.h"
<<<<<<< HEAD
#define NO_OF_RULES 45
#define NO_OF_GRAMMAR_RULES 88
=======
#endif


#define NO_OF_RULES 49
#define NO_OF_GRAMMAR_RULES 100
>>>>>>> 992a544f8f5c4d11c753a8c85247ec446de1a460

typedef struct node{
	TOKEN tokenName;
	int rule_no_index;
	struct node *next;
}node;    //used for first and follow

typedef struct{
	node **first;
	node **follow;
}FirstAndFollow;

FirstAndFollow *f;

struct g_node;

typedef struct {
	NON_TERMINAL non_terminal;
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

g_node **grammar;

typedef struct f_node{
	bool is_error;
	union{
		int rule_no_index;
		void (*error) (void);
	}table_Entry;
}parse_table_elem;

typedef parse_table_elem **parse_table;
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