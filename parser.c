#include <stdlib.h>
#include "lexer.h"
#define LEX_DEF_INCLUDED
#include "parserDef.h"

FirstAndFollow *ComputeFirstAndFollowSets(g_node **grammar){
	FirstAndFollow *f = (FirstAndFollow*)malloc(sizeof(FirstAndFollow));
	f->first = (node**)malloc(sizeof(node*)*NO_OF_RULES);
	f->follow = (node**)malloc(sizeof(node*)*NO_OF_RULES);
	//Automate the array filling
	return f;
}

void createParseTable(FirstAndFollow *f, parse_table T){
	T = (parse_table_elem**)malloc(sizeof(parse_table_elem*)*NO_OF_RULES);
	for(int i=0; i<NO_OF_RULES; i++){
		T[i]=(parse_table_elem*)malloc(sizeof(parse_table_elem)*(eps+1));
	}
}

void parseInputSourceCode(char *testcaseFile, parse_table T){
	
}

g_node_head* create_g_node_head(NON_TERMINAL nt){
	g_node_head *head = (g_node_head*)malloc(sizeof(g_node_head));
	head->non_terminal = nt;
	head->next = NULL;
	return head;
}

g_node* create_g_node(bool is_term, int value){
	g_node *g = (g_node*)malloc(sizeof(g_node));
	g->is_term = is_term;
	if(is_term) g->elem.terminal = (TOKEN)value;
	else g->elem.nonterminal = (NON_TERMINAL)value;
	g->next = NULL;
	return g;
}

g_node_head** populateGrammar(){
	g_node_head **grammar = (g_node_head**)malloc(sizeof(g_node_head*)*NO_OF_GRAMMAR_RULES); //array of g_node_head pointers
	//explicitly populate?

	for(int i=0; i<NO_OF_GRAMMAR_RULES; i++){
		grammar[i] = create_g_node_head(i);
	}

	g_node *ptr;
	//Rule 0
	ptr = grammar[0]->next = create_g_node(0, otherFunctions);
	printf("%d\n", ptr->elem.nonterminal);
	ptr = ptr->next = create_g_node(0, mainFunction);

	//so on

	return grammar;
}
