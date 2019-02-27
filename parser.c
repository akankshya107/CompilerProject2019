#include <stdlib.h>
#include "parser.h"

FirstAndFollow *ComputeFirstAndFollowSets(g_node **grammar){
	FirstAndFollow *f = (FirstAndFollow*)malloc(sizeof(FirstAndFollow));
	f->first = (node**)malloc(sizeof(node*)*NO_OF_RULES);
	f->follow = (node**)malloc(sizeof(node*)*NO_OF_RULES);
	//Automate the array filling
	return f;
}

void createParseTable(FirstAndFollow *f, table T){
	
}

void parseInputSourceCode(char *testcaseFile, table T){
	grammar = populateGrammar();
	f = ComputeFirstAndFollowSets(grammar);
	T = (f_node**)malloc(sizeof(f_node*)*NO_OF_RULES);
	for(int i=0; i<NO_OF_RULES; i++){
		T[i]=(f_node*)malloc(sizeof(f_node)*(eps+1));
	}
	createParseTable(f, T);
}

g_node** populateGrammar(){
	g_node **grammar = (g_node**)malloc(sizeof(g_node*)*NO_OF_GRAMMAR_RULES);
	//explicitly populate?
	return grammar;
}
