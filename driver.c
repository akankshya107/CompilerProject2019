#include <stdio.h>
#include "parser.h"
extern parse_table T;
int main(void){
	//menu outline
	//must call parser
	populateGrammar();
	// printf("%d",grammar[0]->next);
	int i;
	for(i=0;i<NO_OF_GRAMMAR_RULES;i++)
	print_grule(grammar[i]);

	populateStrTable();
	print_strTable();

	ComputeFirstAndFollowSets(grammar);
	for(i=0;i<NO_OF_RULES;i++)
	{
		printf("----------------Non terminal: %d-------------------\n",i);
		print_first(i);
	}
	// createParseTable(f, T);
	return 0;
}
