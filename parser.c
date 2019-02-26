#include <stdlib.h>
#include "parser.h"

FirstAndFollow *ComputeFirstAndFollowSets(g_node_head **grammar){
	FirstAndFollow *f = (FirstAndFollow*)malloc(sizeof(FirstAndFollow));
	f->first = (node**)malloc(sizeof(node*)*NO_OF_RULES);
	f->follow = (node**)malloc(sizeof(node*)*NO_OF_RULES);
	return f;
}

void createParseTable(FirstAndFollow *f, table T){
	
}

void parseInputSourceCode(char *testcaseFile, table T){
	g_node_head **grammar = populateGrammar();
	FirstAndFollow *f = ComputeFirstAndFollowSets(grammar);
	T = (f_node**)malloc(sizeof(f_node*)*NO_OF_RULES);
	for(int i=0; i<NO_OF_RULES; i++){
		T[i]=(f_node*)malloc(sizeof(f_node)*(eps+1));
	}
	createParseTable(f, T);
}

g_node_head** populateGrammar(){
	g_node_head **grammar = (g_node_head**)malloc(sizeof(g_node_head*)*NO_OF_GRAMMAR_RULES);
	//explicitly populate??
	return grammar;
}
