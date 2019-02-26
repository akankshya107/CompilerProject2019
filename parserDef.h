#include "lexerDef.h"
#define NO_OF_RULES 45
#define NO_OF_GRAMMAR_RULES 100

typedef struct node{
	TOKEN tokenName;
	struct node *next;
}node;

struct g_node;

typedef struct{
	char* nonterminal;
	struct g_node *next;
}g_node_head;

typedef struct g_node{
	union{
		TOKEN terminal;
		g_node_head *nonterminal;
	};
	struct g_node *next;
}g_node;

g_node_head **grammar;
node **first;
node **follow;

typedef struct f_node{
	void (*func_ptr)(void);
}f_node;

typedef f_node **table;

typedef struct{
	tokenInfo *leaf_symbol;
}leafNode;

typedef struct{
	g_node *children;
	g_node_head *nonterminal;
}nonLeafNode;

typedef union treeNode{
	leafNode *l;
	nonLeafNode *n;
}treeNode;
