#include <stdbool.h>
#ifndef LEX_DEF_INCLUDED
#include "lexerDef.h"
#define LEX_DEF_INCLUDED
#endif
#ifndef GRAM_INCLUDED
#include "grammarDef.h"
#define GRAM_INCLUDED
#endif
typedef struct f_node{
	int is_error;
	int rule_no_index;
}parse_table_elem;

typedef parse_table_elem **parse_table;
parse_table T;

typedef struct{
	tokenInfo *leaf_symbol;
}leafNode;

typedef struct{
	NON_TERMINAL nonterminal;
	int rule_no;
	treeNodeIt *children;
}nonLeafNode;

typedef struct{
	bool is_leaf;
	union{
		leafNode *l;
		nonLeafNode *n;
	}treeNode_type;
	treeNodeIt *parent;
}treeNode;

typedef struct{
	treeNode *t;
	treeNodeIt *next;
}treeNodeIt;