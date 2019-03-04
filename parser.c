#include <stdlib.h>
#include "lexer.h"
#define LEX_DEF_INCLUDED
#include "grammar.h"
#define GRAM_INCLUDED
#include "parserDef.h"

void ComputeFirstAndFollowSets(){
	f = (FirstAndFollow*)malloc(sizeof(FirstAndFollow));
	// f->first = (node_head**)malloc(sizeof(node*)*NO_OF_RULES);
	f->first = (node_head_first**)malloc(sizeof(node_head_first*)*NO_OF_RULES);

	f->follow = (node_head_follow**)malloc(sizeof(node_head_follow*)*NO_OF_RULES);
//Do not merge these forloops into one
	for(int i=0; i<NO_OF_RULES; i++){
		f->first[i] = create_head_first(i);
	}
	for(int i=0; i<NO_OF_RULES; i++){
		if(f->first[i]->head==NULL)
		first(i);
	}
//Do not merge these for loops into one
	for(int i=0; i<NO_OF_RULES; i++){
		
		f->follow[i] = create_head_follow(i);
		
	}
	for(int i=0; i<NO_OF_RULES; i++){
		// f->first[i]->
		clear_flags_follow();
		follow(i);
	}
	return ;
}
