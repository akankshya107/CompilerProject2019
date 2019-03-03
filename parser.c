#include <stdlib.h>
#include "lexer.h"
#define LEX_DEF_INCLUDED
#include "parserDef.h"


g_node_head* create_g_node_head(NON_TERMINAL nt){
	g_node_head *head = (g_node_head*)malloc(sizeof(g_node_head));
	head->non_terminal = nt;
	head->next = NULL;
	return head;
}
node_head_follow* create_head_follow(NON_TERMINAL nt_index)
{
	node_head_follow* head=(node_head_follow*) malloc(sizeof(node_head_follow));
	head->nt=nt_index;
	head->is_visited=false;
	head->head=NULL;
	return head;
}

node_head_first* create_head_first(NON_TERMINAL nt_index)
{
	node_head_first* head=(node_head_first*) malloc(sizeof(node_head_first));
	head->nt=nt_index;
	head->has_eps=false;
	head->head=NULL;
	return head;
}

g_node* create_g_node(bool is_term, int value){
	g_node *g = (g_node*)malloc(sizeof(g_node));
	g->is_term = is_term;
	if(is_term) g->elem.terminal = (TOKEN)value;
	else g->elem.nonterminal = (NON_TERMINAL)value;
	g->next = NULL;
	g->prev = NULL;
	return g;
}

node* create_node(TOKEN tkname, int rule_no){
	node *n = (node*)malloc(sizeof(node));
	n->tokenName = tkname;
	n->rule_no_index = rule_no;
	n->next = NULL;
	return n;
}

void createParseTable(FirstAndFollow *f, parse_table T){
	T = (parse_table_elem**)malloc(sizeof(parse_table_elem*)*NO_OF_RULES);
	for(int i=0; i<NO_OF_RULES; i++){
		T[i]=(parse_table_elem*)malloc(sizeof(parse_table_elem)*(eps+1));
	}
}

void parseInputSourceCode(char *testcaseFile, parse_table T){
	
}


g_node* first_gnode(g_node_head* h,int no,bool is_term)
{
	g_node* pnext;
	pnext = h->next = create_g_node(is_term, no);
	pnext->prev=NULL;
	pnext->next=NULL;
	return pnext;
}
g_node* dl_nodes(g_node* pnext,int no,bool is_term)
{
	g_node* ptr;
	ptr=pnext->next=create_g_node(is_term,no);
	ptr->prev=pnext;
	ptr->next=NULL;

	return ptr;
}

void print_gnode(g_node* ptr)
{
	if(ptr->is_term)
	{
		printf("%d\n", ptr->prev->elem.terminal);
	}
	else
	printf("%d\n", ptr->prev->elem.terminal);
}

g_node_head** populateGrammar(){
	g_node_head **grammar = (g_node_head**)malloc(sizeof(g_node_head*)*NO_OF_GRAMMAR_RULES); //array of g_node_head pointers
	//explicitly populate?

	for(int i=0; i<NO_OF_GRAMMAR_RULES; i++){
		grammar[i] = create_g_node_head(i);
	}

	g_node *ptr, *pnext;
	//Rule 0
	ptr = NULL;
	pnext=first_gnode(grammar[0],otherFunctions,0);
	pnext=dl_nodes(pnext,0,mainFunction);
	print_gnode(pnext);
	//Rule 1
	pnext=first_gnode(grammar[1],TK_MAIN,1);
	pnext=dl_nodes(pnext,stmts,0);
	pnext=dl_nodes(pnext,TK_END,1);


	//so on

	return grammar;
}
void first(NON_TERMINAL nt_index)
{
	node* head=NULL;
	return head;
	if(f->first[nt_index]->head!=NULL)
	{
		return;
	}

	else
	{
		int* rules=nonterminal_str[nt_index]->;

	}
	



}
void add_nodetof(node_head_follow* head,TOKEN tk)
{
	if(tk==eps)
		return;
	
	node* temp=head->head;
	int flag=0;
	node* temp_node;
	while(temp!=NULL)
	{
		if(temp->tokenName==tk)
		{
			flag=1;
			break;
		}
		else
		{
			temp=temp->next;
		}
		
	}
	if(flag==0)
	{
		temp_node=create_node(tk,0);
		temp_node->next=head->head;
		head->head=temp_node;
	}
}
void add_ftof(node_head_follow* head,node* firstorfollow)
{
	node* temp=firstorfollow;
	while(temp!=NULL)
	{
		add_nodetof(head,temp->tokenName);
		temp=temp->next;
	}
}


void first_eps(node_head_follow* node_head,g_node* temp,g_node_head* g)
{
	if(temp==NULL)
	{
		// if(f->follow[g->non_terminal].is_visited)
		// return NULL;
		// else
		add_ftof(node_head,f->follow[g->non_terminal]->head);
		
	}

	else
	{
		if(!f->first[temp->elem.nonterminal]->has_eps)
		add_ftof(node_head,f->first[temp->elem.nonterminal]->head);
		 

		else
		{
			//add firsts - eps
			add_ftof(node_head,f->first[temp->elem.nonterminal]->head);
			first_eps(node_head,temp->next,g);	
			// return first(temp);first
		}
		
	}
	
}

void clear_flags_follow()
{
	for(int i=0; i<NO_OF_RULES; i++)
	{
		f->follow[i]->is_visited=false;
	}
}
void follow(NON_TERMINAL nt_index)
{
	
	if(f->follow[nt_index]->head!=NULL)
	{
		f->follow[nt_index]->is_visited=true;
		// return f->follow[nt_index]->head;
		return;
	}
	else
	{
		if(f->follow[nt_index]->is_visited)
		// return f->follow[nt_index]->head;
		return;
		else
		{
			f->follow[nt_index]->is_visited=true;
			g_node* temp;
			// f->follow[nt_index]->nt=nt_index;
			for(int i=0; i<NO_OF_GRAMMAR_RULES; i++)
			{
				temp=grammar[i]->next;
				while(temp!=NULL)
				{
					if(!temp->is_term)
					{
						if(temp->elem.nonterminal==nt_index)
						{
							if(temp->next==NULL)
							{
								// add follow of grammar[i]->non_terminal to 
								//current follow
								add_ftof(f->follow[nt_index],f->follow[grammar[i]->non_terminal]->head);
							}
							else
							{
								if(temp->next->is_term)
								{
									add_nodetof(f->follow[nt_index],temp->next->elem.terminal);
								}

								else
								{
									
									if(!f->first[temp->next->elem.nonterminal]->has_eps)
									{
										//add first of temp->next->elem.nonterminal to the 
										//current follow
										add_ftof(f->follow[nt_index],f->first[temp->next->elem.nonterminal]->head);
									}

									else
									{
										first_eps(f->follow[nt_index],temp->next,grammar[i]);
									}
									
								}
							}
						}
						
					}
					temp=temp->next;
				}
			}
		}
	}
}

FirstAndFollow *ComputeFirstAndFollowSets(g_node **grammar){
	FirstAndFollow *f = (FirstAndFollow*)malloc(sizeof(FirstAndFollow));
	// f->first = (node_head**)malloc(sizeof(node*)*NO_OF_RULES);
	f->first = (node_head_first**)malloc(sizeof(node_head_first*)*NO_OF_RULES);

	f->follow = (node_head_follow**)malloc(sizeof(node_head_follow*)*NO_OF_RULES);
//Do not merge these forloops into one
	for(int i=0; i<NO_OF_RULES; i++){
		f->first[i] = create_head_first(i);
	}
	for(int i=0; i<NO_OF_RULES; i++){
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
	return f;
}

// node* first(NON_TERMINAL nt_index){
	
// }