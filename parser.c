// GROUP 39
// AKANKSHYA MISHRA 2016A7PS0026P
// NARAPAREDDY BHAVANA 2016A7PS0034P
// KARABEE BATTA 2016A7PS0052P
// AASTHA KATARIA 2016A7PS0062P
#include <stdlib.h>
#include "lexer.h"
#define LEX_DEF_INCLUDED
#include "grammar.h"
#define GRAM_INCLUDED
#include "parserDef.h"
#define PARSE_INCLUDED
#include "stack.h"
#include "string.h"

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

treeNodeIt* returnIt(treeNode *t){
	treeNodeIt *ti = (treeNodeIt*)malloc(sizeof(treeNodeIt));
	ti->next=NULL;
	ti->t=t;
	return ti;
}

treeNode* returnTreeNode(bool is_leaf, int line_no){
	treeNode *tn = (treeNode*)malloc(sizeof(treeNode));
	tn->is_leaf=is_leaf;
	tn->parent=NULL;
	tn->line_no=line_no;
	return tn;
}

treeNode* returnNonLeafNode(treeNode *t, NON_TERMINAL nt, int rule_no, treeNodeIt *children){
	nonLeafNode* nln = (nonLeafNode*)malloc(sizeof(nonLeafNode));
	nln->nonterminal=nt;
	nln->rule_no=rule_no;
	nln->children=children;
	t->treeNode_type.n = nln;
	return t;
}

treeNode* returnLeafNode(treeNode *t, tokenInfo *ti){
	leafNode* ln = (leafNode*)malloc(sizeof(leafNode));
	ln->leaf_symbol=ti;
	t->treeNode_type.l = ln;
	return t;
}

treeNodeIt* makeTreeNodes(g_node_head *h, treeNodeIt *par, int line_no){
	g_node *it=h->next;
	treeNodeIt *ch;
	if(it->is_term){
		ch= returnIt(returnLeafNode(returnTreeNode(1, line_no), NULL));
	}else{
		ch = returnIt(returnNonLeafNode(returnTreeNode(0, line_no), it->elem.nonterminal, h->rule_no, NULL));
	}
	ch->t->parent=par;
	treeNodeIt *head = ch;
	it = it->next;
	while(it!=NULL){
		if(it->is_term){
			ch->next= returnIt(returnLeafNode(returnTreeNode(1, line_no), NULL));
		}else{
			ch->next= returnIt(returnNonLeafNode(returnTreeNode(0, line_no), it->elem.nonterminal, h->rule_no, NULL));
		}
		ch->next->t->parent=par;
		it = it->next;
		ch = ch->next;
	}
	ch->next = NULL;

	return head;
}

treeNodeIt* iterate(treeNodeIt *root){
	while(root->next==NULL){
		root = root->t->parent;
		if(root->t->parent==NULL) return root;
	}
	root = root->next;
	return root;
}

treeNodeIt* parseInputSourceCode(char *testcaseFile){
	FILE *fp = fopen(testcaseFile, "r");
	fseek(fp, 0, SEEK_SET);
	Stack *stack = newStack();
	push(stack, returnEle(1, EOS));
	push(stack, returnEle(0, program));
	tokenInfo *ti = getNextToken(fp);

	treeNodeIt *root = returnIt(returnNonLeafNode(returnTreeNode(0, ti->line_no), program, 0, NULL));
	treeNodeIt *store = root, *par;

	int e_flag=0;
	bool panic_mode = 0;
	while(!isEmpty(stack)){
		gram_elem *e = top(stack);
		// print_gram(e);
		if(e->is_term && e->elem.terminal==ti->tokenName){
			if(ti->tokenName==EOS){
				if(panic_mode==0) printf("Input source code is syntactically correct...........\n");
				break;
			}
			// printf("Popped: %s\n", TerminalString(ti->tokenName));
			root->t->treeNode_type.l->leaf_symbol = ti;
			root = iterate(root);

			free(pop(stack));
			ti = getNextToken(fp);
		}
		else if(e->is_term){
			// if(e->elem.terminal==TK_SEM){
			// 	printf("Line %d: Semicolon is missing\n", ti->line_no);
			// 	free(pop(stack));
			// 	continue;
			// }
			panic_mode=1;
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
				printf("Line %d: The token %s for lexeme %.2f does not match with expected token %s\n", ti->line_no, TerminalString(ti->tokenName), ti->u.value_of_real, TerminalString(e->elem.terminal));
			}
			free(pop(stack));
			root = iterate(root);
		}
		else if(T[e->elem.nonterminal][ti->tokenName].is_error==1){
			panic_mode=1;
			if(ti->tokenName==EOS){
				e_flag=1;
				break;
			}
			if(ti->flag==0)
			{
				printf("Line %d: The token %s for lexeme %s does not match with expected token %s\n", ti->line_no, TerminalString(ti->tokenName), ti->u.lexeme, nonTerminalStringTable[e->elem.nonterminal]->nonterminal);
			}
			else if(ti->flag==1)
			{
				printf("Line %d: The token %s for lexeme %d does not match with expected token %s\n", ti->line_no, TerminalString(ti->tokenName), ti->u.value_of_int , nonTerminalStringTable[e->elem.nonterminal]->nonterminal);
			}
			else
			{
				printf("Line %d: The token %s for lexeme %.2f does not match with expected token %s\n", ti->line_no, TerminalString(ti->tokenName), ti->u.value_of_real, nonTerminalStringTable[e->elem.nonterminal]->nonterminal);
			}
			do{
				ti = getNextToken(fp);
				// printf("%s\n", TerminalString(ti->tokenName));
				if((T[e->elem.nonterminal][ti->tokenName].is_error==0)){
					break;
				}
				if((T[e->elem.nonterminal][ti->tokenName].is_error==-1)){
					free(pop(stack));
					root = iterate(root);
					break;
				}
			}while(1);
		}
		else if(T[e->elem.nonterminal][ti->tokenName].is_error==-1){
			free(pop(stack));
			root = iterate(root);
			
		}
		else if((T[e->elem.nonterminal][ti->tokenName].is_error)==0){
			free(pop(stack));
			// printf("%d\n", T[e->elem.nonterminal][ti->tokenName].rule_no_index);
			if(T[e->elem.nonterminal][ti->tokenName].rule_no_index==-1){
				// printf("Top of stack: %s\n", TerminalString(top(stack)->elem.terminal));
				tokenInfo *ti_eps = (tokenInfo*)malloc(sizeof(tokenInfo));
				ti_eps->flag=0;
				ti_eps->line_no=ti->line_no;
				ti_eps->tokenName=eps;
				ti_eps->u.lexeme="eps";
				// ti->u.lexeme="eps";
				root->t->treeNode_type.n->children = returnIt(returnLeafNode(returnTreeNode(1, ti->line_no), ti_eps));
				root->t->treeNode_type.n->children->t->parent=root;	
				root = iterate(root);
				continue;
			}
			pushAll(stack, T[e->elem.nonterminal][ti->tokenName].rule_no_index);

			par = root;
			root->t->treeNode_type.n->children=makeTreeNodes(grammar[T[e->elem.nonterminal][ti->tokenName].rule_no_index], par, ti->line_no);
			root = root->t->treeNode_type.n->children;

			// print_grule(grammar[T[e->elem.nonterminal][ti->tokenName].rule_no_index]);
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
	// printf("%d\n", e_flag);
	fclose(fp);
	return store;
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
		}
		if(!f->first[i]->has_eps)
		{
			temp=f->first[i]->head;
			while(temp!=NULL)
			{
				T[i][temp->tokenName].rule_no_index =temp->rule_no_index;
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
						T[i][temp2->tokenName].rule_no_index=-1;
						T[i][temp2->tokenName].is_error=0;
						temp2=temp2->next;
					}
					temp=temp->next;
				}
				else
				{
					T[i][temp->tokenName].rule_no_index =temp->rule_no_index;
					T[i][temp->tokenName].is_error=0;
					temp=temp->next;
				}
				
				
			}

		}
	
	}
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
				fprintf(fp,"%d,",T[i][j].rule_no_index);
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

void print_leaf(FILE *fw, leafNode *l, NON_TERMINAL nt){
	if(l->leaf_symbol==NULL){
		printf("\n");
		return;
	}
	char *s = "--------------   ";
	if(l->leaf_symbol->flag==0){
		if(strlen(l->leaf_symbol->u.lexeme)>6) fprintf(fw, "%-20s", l->leaf_symbol->u.lexeme);
		else fprintf(fw, "%-20s", l->leaf_symbol->u.lexeme);
	}else{
		fprintf(fw, "%-20s", s);
	}

	fprintf(fw, "%-10d", l->leaf_symbol->line_no);

	if(strlen(TerminalString(l->leaf_symbol->tokenName))>=8){
		fprintf(fw, "%-20s", TerminalString(l->leaf_symbol->tokenName));
	}else{
		fprintf(fw, "%-20s", TerminalString(l->leaf_symbol->tokenName));
	}

	if(l->leaf_symbol->flag==1){
		fprintf(fw, "%-20d", l->leaf_symbol->u.value_of_int);
	}else if(l->leaf_symbol->flag==1){
		fprintf(fw, "%-20.2f", l->leaf_symbol->u.value_of_real);
	}
	else{
		fprintf(fw, "%-20s", s);
	}

	if(strlen(nonTerminalStringTable[nt]->nonterminal)<=7){
		fprintf(fw, "%-30s", nonTerminalStringTable[nt]->nonterminal);
	}
	else if(strlen(nonTerminalStringTable[nt]->nonterminal)<=15) {
		fprintf(fw, "%-30s", nonTerminalStringTable[nt]->nonterminal);
	}else fprintf(fw, "%-30s", nonTerminalStringTable[nt]->nonterminal);

	fprintf(fw, "Yes");

	fprintf(fw, "%30s", s);
	fprintf(fw, "\n");
}

void print_nonleaf(FILE *fw, nonLeafNode *n, int line_no, NON_TERMINAL nt, bool flag){
	char *s = "--------------   ";
	fprintf(fw, "%-20s", s);

	fprintf(fw, "%-10d", line_no);

	fprintf(fw, "%s", s);

	fprintf(fw, "%-23s", s);

	if(!flag){
		if(strlen(nonTerminalStringTable[nt]->nonterminal)<=7){
			fprintf(fw, "%-30s", nonTerminalStringTable[nt]->nonterminal);
		}
		else if(strlen(nonTerminalStringTable[nt]->nonterminal)<=15) {
			fprintf(fw, "%-30s", nonTerminalStringTable[nt]->nonterminal);
		}else fprintf(fw, "%-30s", nonTerminalStringTable[nt]->nonterminal);
	}else{
		fprintf(fw, "Root node\t\t\t\t\t\t\t\t\t\t");
	}

	fprintf(fw, "No\t");

	fprintf(fw, "%30s\n", nonTerminalStringTable[n->nonterminal]->nonterminal);
}

void printParseTree(treeNodeIt *root, char *outfile){
	FILE *fw = fopen(outfile, "w");
	treeNodeIt *temp = root;
	while(1){
		while(temp->t->is_leaf==0){
			temp = temp->t->treeNode_type.n->children;
			if (temp==NULL) break;
		}
		if (temp==NULL) break;
		print_leaf(fw, temp->t->treeNode_type.l, temp->t->parent->t->treeNode_type.n->nonterminal);
		while(temp->next==NULL){
			temp = temp->t->parent;
			if(temp->t->parent==NULL){
				print_nonleaf(fw, temp->t->treeNode_type.n, temp->t->line_no , 0, 1);
				return;	
			}
			print_nonleaf(fw, temp->t->treeNode_type.n, temp->t->line_no , temp->t->parent->t->treeNode_type.n->nonterminal, 0);
		}
		temp = temp->next;
	}
	fclose(fw);
}