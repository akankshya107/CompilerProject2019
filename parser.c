#include <stdlib.h>
#include "lexer.h"
#define LEX_DEF_INCLUDED
#include "grammar.h"
#define GRAM_INCLUDED
#include "parserDef.h"
#define PARSE_INCLUDED
#include "stack.h"

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
	f->follow[0]->head=create_node(EOS,0);
	
	for(int i=1; i<NO_OF_RULES; i++){
		// f->first[i]->
		clear_flags_follow();
		follow(i);
	}
	return ;
}

void parseInputSourceCode(char *testcaseFile){
	FILE *fp = fopen(testcaseFile, "r");
	Stack *stack = newStack();
	push(stack, returnEle(1, EOS));
	push(stack, returnEle(0, program));
	tokenInfo *ti = getNextToken(fp);
	int e_flag=0;
	while(!isEmpty(stack)){
		gram_elem *e = top(stack);
		print_gram(e);
		if(e->is_term && e->elem.terminal==ti->tokenName){
			if(ti->tokenName==EOS){
				printf("Successfully parsed\n");
				break;
			}
			printf("Popped: %s\n", TerminalString(ti->tokenName));
			free(pop(stack));
			ti = getNextToken(fp);
		}
		else if(e->is_term){
			if(e->elem.terminal==EOS){
				e_flag=2;
				break;
			}
			if(ti->flag==0)
			{
				printf("Line %d: The token %s for lexeme %s does not match with expected token %s\n", ti->line_no, TerminalString(ti->tokenName), ti->u.lexeme, TerminalString(e->elem.terminal));
			}
			else if(ti->flag==1)
			{
				printf("Line %d: The token %s for lexeme %d does not match with expected token %s\n", ti->line_no, TerminalString(ti->tokenName), ti->u.value_of_int , TerminalString(e->elem.terminal));
			}
			else
			{
				printf("Line %d: The token %s for lexeme %f does not match with expected token %s\n", ti->line_no, TerminalString(ti->tokenName), ti->u.value_of_real, TerminalString(e->elem.terminal));
			}
			free(pop(stack));
		}
		else if(T[e->elem.nonterminal][ti->tokenName].is_error==1){
			e_flag=1;
			break;
			if(ti->tokenName==EOS){
				e_flag=1;
				break;
			}
			do{
				ti = getNextToken(fp);
				if((T[e->elem.nonterminal][ti->tokenName].is_error==0)){
					break;
				}
				if((T[e->elem.nonterminal][ti->tokenName].is_error==-1)){
					pop(stack);
					break;
				}
			}while(1);
		}
		else if(T[e->elem.nonterminal][ti->tokenName].is_error==-1){
			e_flag=1;
			break;
			free(pop(stack));
			break;
		}
		else if((T[e->elem.nonterminal][ti->tokenName].is_error)==0){
			free(pop(stack));
			printf("%d\n", T[e->elem.nonterminal][ti->tokenName].table_Entry.rule_no_index);
			if(T[e->elem.nonterminal][ti->tokenName].table_Entry.rule_no_index==-1){
				// printf("Top of stack: %s\n", TerminalString(top(stack)->elem.terminal));
				continue;
			}
			pushAll(stack, T[e->elem.nonterminal][ti->tokenName].table_Entry.rule_no_index);
			print_grule(grammar[T[e->elem.nonterminal][ti->tokenName].table_Entry.rule_no_index]);
		}else { printf("Error in parse code\n"); }
	}
	if(e_flag==1){
		while(!isEmpty(stack)){
			free(pop(stack));
		}
	}
	else if(e_flag==2){
		do{
			ti = getNextToken(fp);
		}while(ti->tokenName!=EOS);
	}
	printf("%d\n", e_flag);
}

void error_function()
{
	return;
}
void syn_error()
{
	return;
}

void createParseTable(){
	T = (parse_table_elem**)malloc(sizeof(parse_table_elem*)*NO_OF_RULES);
	for(int i=0; i<NO_OF_RULES; i++){
		T[i]=(parse_table_elem*)malloc(sizeof(parse_table_elem)*(EOS+1));
	}
	int i,j;
	node* temp,*temp2;
	int length;
	g_node* gtemp;

	for(i=0;i<NO_OF_RULES;i++)
	{
		for(j=0;j<EOS+1;j++)
		{
			T[i][j].is_error=1;
			T[i][j].table_Entry.error=&error_function;
		}
		if(!f->first[i]->has_eps)
		{
			temp=f->first[i]->head;
			while(temp!=NULL)
			{
				T[i][temp->tokenName].table_Entry.rule_no_index =temp->rule_no_index;
				T[i][temp->tokenName].is_error=0;
				temp=temp->next;
			}

			temp=f->follow[i]->head;
			while(temp!=NULL){
				// T[i][temp->tokenName].table_Entry.error=&syn_error;
				if(T[i][temp->tokenName].is_error==0){
					temp=temp->next;

				}
				else{
					T[i][temp->tokenName].is_error=-1;
					temp=temp->next;
				}
				// temp = temp->next;
			}
		}
		else
		{
			temp=f->first[i]->head;
			while(temp!=NULL)
			{
				if(temp->tokenName==eps)
				{
					temp2=f->follow[i]->head;
					while(temp2!=NULL){
						T[i][temp2->tokenName].table_Entry.rule_no_index=-1;
						T[i][temp2->tokenName].is_error=0;
						temp2=temp2->next;
						
					}
					temp=temp->next;
				}
				else
				{
					T[i][temp->tokenName].table_Entry.rule_no_index =temp->rule_no_index;
					T[i][temp->tokenName].is_error=0;
					temp=temp->next;
				}
				
				
			}

		}
	
	}
	free_first_follow();
}

void print_parse_table()
{
	int i,j;
	FILE* fp=fopen("table.csv","w");
	// for(j=0;j<EOS+1;j++)
	// fprintf(fp,"%d ",j+1);
	// fprintf(fp,"\n");
	for(i=0;i<NO_OF_RULES;i++)
	{
		// fprintf(fp,"%s: ",nonTerminalStringTable[i]->nonterminal);
		// fprintf(fp,"%d: ",i);
		for(j=0;j<EOS+1;j++)
		{
			if(T[i][j].is_error==0)
			{
				fprintf(fp,"%d,",T[i][j].table_Entry.rule_no_index);
			}
			else
			{
				if(T[i][j].is_error==-1)
				{
					fprintf(fp,"%c,",'S');
				}
				else
				{
					fprintf(fp,"%c,",'_');
				}
				

			}
				
		}
		fprintf(fp,"\n");
	}
	fclose(fp);

}