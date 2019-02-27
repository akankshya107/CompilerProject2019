#include <stdio.h>
#include "parser.h"
extern parse_table T;
int main(void){
	//menu outline
	//must call parser
	grammar = populateGrammar();
	f = ComputeFirstAndFollowSets(grammar);
	createParseTable(f, T);
	return 0;
}
