#include <stdbool.h>
#include "lexerDef.h"
#define NO_OF_RULES 45
#define NO_OF_GRAMMAR_RULES 100

typedef struct node{
	TOKEN tokenName;
	struct node *next;
}node;    //used for first and follow

typedef struct{
	node **first;
	node **follow;
}FirstAndFollow;

FirstAndFollow *f;

typedef struct g_node{
	bool is_term;
	union{
		TOKEN terminal;
		NON_TERMINAL nonterminal;
	}elem;
	struct g_node *next;
}g_node;

g_node **grammar;

typedef struct f_node{
	void (*func_ptr)(void);
}f_node;

typedef f_node **table;

typedef struct{
	tokenInfo *leaf_symbol;
}leafNode;

typedef struct{
	g_node *children;
	g_node *nonterminal;
}nonLeafNode;

typedef union treeNode{
	leafNode *l;
	nonLeafNode *n;
}treeNode;
