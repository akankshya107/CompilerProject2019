#include <stdio.h>
#include "parser.h"
extern parse_table T;
int main(void){
	//menu outline
	//must call parser
	populateGrammar();
	populateStrTable();
	// printf("%d",grammar[0]->next);
	int i;
	for(i=0;i<NO_OF_GRAMMAR_RULES;i++)
	print_grule(grammar[i]);

	
	// print_strTable();

	ComputeFirstAndFollowSets(grammar);
	createParseTable();
	// print_parse_table();
	for(i=0;i<NO_OF_RULES;i++)
	{
		printf("----------------Non terminal: %s-------------------\n",nonTerminalStringTable[i]->nonterminal);
		printf("FIRST:\n");
		// printf("-------------\n");
		print_first(i);
		printf("FOLLOW\n");
		// printf("-------------\n");
		print_follow(i);

	}
	// printf("==================================================================================\n");
	// for(i=0;i<NO_OF_RULES;i++)
	// {
	// 	printf("----------------Non terminal: %s-------------------\n",nonTerminalStringTable[i]->nonterminal);
	// 	print_follow(i);
	// }

	// createParseTable(f, T);
	return 0;
}
