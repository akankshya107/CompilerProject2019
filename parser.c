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
	head->is_visited=false;
	head->head=NULL;
	return head;
}

node_head_first* create_head_first(NON_TERMINAL nt_index)
{
	node_head_first* head=(node_head_first*) malloc(sizeof(node_head_first));
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
char *TerminalString(int index){
    static char *terminalStringTable[EOS+1] =  { "TK_ASSIGNOP", "TK_COMMENT", "TK_FIELDID", "TK_ID", "TK_NUM", "TK_RNUM", "TK_FUNID", "TK_RECORDID", "TK_WITH", "TK_PARAMETERS", "TK_END", "TK_WHILE", "TK_TYPE", "TK_MAIN", "TK_GLOBAL", "TK_PARAMETER", "TK_LIST", "TK_SQL", "TK_SQR", "TK_INPUT", "TK_OUTPUT", "TK_INT", "TK_REAL", "TK_COMMA", "TK_SEM", "TK_COLON", "TK_DOT", "TK_ENDWHILE", "TK_OP", "TK_CL", "TK_IF", "TK_THEN", "TK_ENDIF", "TK_READ", "TK_WRITE", "TK_RETURN", "TK_PLUS", "TK_MINUS", "TK_MUL", "TK_DIV", "TK_CALL", "TK_RECORD", "TK_ENDRECORD", "TK_ELSE", "TK_AND", "TK_OR", "TK_NOT", "TK_LT", "TK_LE", "TK_EQ", "TK_GT", "TK_GE", "TK_NE", "eps", "EOS" };
    return terminalStringTable[index];
}
void print_gnode(g_node* ptr)
{
	if(ptr->is_term)
	{
		printf( " %s ",TerminalString( ptr->elem.terminal));
	}
	else
	printf("%s ", nonTerminalStringTable[ ptr->elem.nonterminal]->nonterminal);
}

void print_grule(g_node_head* head)
{
	printf("Rule %d:  %s -->",head->rule_no,nonTerminalStringTable [head->non_terminal]->nonterminal);
	g_node* temp=head->next;
	while(temp!=NULL){
		print_gnode(temp);
		temp=temp->next;
	}
	printf("\n");
	
}

void populateGrammar(){
	grammar = (g_node_head**)malloc(sizeof(g_node_head*)*NO_OF_GRAMMAR_RULES); //array of g_node_head pointers
	
	g_node *ptr, *pnext;
	//Rule 0
	ptr = NULL;
	grammar[0]=create_g_node_head(program);
	pnext=first_gnode(grammar[0],otherFunctions,0);
	pnext=dl_nodes(pnext,mainFunction,0);
	// print_gnode(pnext);
	//Rule 1
	grammar[1]=create_g_node_head(mainFunction);
	pnext=first_gnode(grammar[1],TK_MAIN,1);
	pnext=dl_nodes(pnext,stmts,0);
	pnext=dl_nodes(pnext,TK_END,1);
	//Rule 2
	grammar[2]=create_g_node_head(otherFunctions);
	pnext=first_gnode(grammar[2],function,0);
	pnext=dl_nodes(pnext,otherFunctions,0);
	//Rule 3(eps)
	grammar[3]=create_g_node_head(otherFunctions);
	pnext = first_gnode(grammar[3],eps,1);
	//Rule 4
	grammar[4]=create_g_node_head(function);
	pnext=first_gnode(grammar[4],TK_FUNID,1);
	pnext=dl_nodes(pnext,input_par,0);
	pnext=dl_nodes(pnext,output_par,0);
	pnext=dl_nodes(pnext,TK_SEM,1);
	pnext=dl_nodes(pnext,stmts,0);
	pnext=dl_nodes(pnext,TK_END,1);
	//Rule 5
	grammar[5]=create_g_node_head(input_par);
	pnext=first_gnode(grammar[5],TK_INPUT,1);
	pnext=dl_nodes(pnext,TK_PARAMETER,1);
	pnext=dl_nodes(pnext,TK_LIST,1);
	pnext=dl_nodes(pnext,TK_SQL,1);
	pnext=dl_nodes(pnext,parameter_list,0);
	pnext=dl_nodes(pnext,TK_SQR,1);
	//Rule 6
	grammar[6]=create_g_node_head(output_par);
	pnext=first_gnode(grammar[6], TK_OUTPUT, 1);
	pnext=dl_nodes(pnext, TK_PARAMETER, 1);
	pnext=dl_nodes(pnext, TK_LIST, 1);
	pnext=dl_nodes(pnext, TK_SQL, 1);
	pnext=dl_nodes(pnext, parameter_list, 0);
	pnext=dl_nodes(pnext, TK_SQR, 1);
	//Rule 7
	grammar[7]=create_g_node_head(output_par);
	pnext=first_gnode(grammar[7], eps, 1);
	//Rule 8
	grammar[8]=create_g_node_head(parameter_list);
	pnext=first_gnode(grammar[8],dataType,0);
	pnext=dl_nodes(pnext,TK_ID,1);
	pnext=dl_nodes(pnext,remaining_list,0);
	//Rule 9
	grammar[9]=create_g_node_head(dataType);
	pnext=first_gnode(grammar[9],primitiveDatatype,0);
	//Rule 10
	grammar[10]=create_g_node_head(dataType);
	pnext=first_gnode(grammar[10],constructedDatatype,0);
	//Rule 11
	grammar[11]=create_g_node_head(primitiveDatatype);
	pnext=first_gnode(grammar[11],TK_INT,1);
	//Rule 12
	grammar[12]=create_g_node_head(primitiveDatatype);
	pnext=first_gnode(grammar[12],TK_REAL,1);
	//Rule 13
	grammar[13]=create_g_node_head(constructedDatatype);
	pnext=first_gnode(grammar[13],TK_RECORD,1);
	pnext=dl_nodes(pnext,TK_RECORDID,1);
	//Rule 14
	grammar[14]=create_g_node_head(remaining_list);
	pnext=first_gnode(grammar[14],TK_COMMA,1);
	pnext=dl_nodes(pnext,parameter_list,0);
	//Rule 15(eps)
	grammar[15]=create_g_node_head(remaining_list);
	pnext=first_gnode(grammar[15],eps,1);
	//Rule 16
	grammar[16]=create_g_node_head(stmts);
	pnext=first_gnode(grammar[16],typeDefinitions,0);
	pnext=dl_nodes(pnext,declarations,0);
	pnext=dl_nodes(pnext,otherStmts,0);
	pnext=dl_nodes(pnext,returnStmt,0);
	//Rule 17
	grammar[17]=create_g_node_head(typeDefinitions);
	pnext=first_gnode(grammar[17],typeDefinition,0);
	pnext=dl_nodes(pnext,typeDefinitions,0);
	//Rule 18(eps)
	grammar[18]=create_g_node_head(typeDefinitions);
	pnext=first_gnode(grammar[18],eps,1);
	//Rule 19
	grammar[19]=create_g_node_head(typeDefinition);
	pnext=first_gnode(grammar[19],TK_RECORD,1);
	pnext=dl_nodes(pnext,TK_RECORDID,1);
	pnext=dl_nodes(pnext,fieldDefinitions,0);
	pnext=dl_nodes(pnext,TK_ENDRECORD,1);
	pnext=dl_nodes(pnext,TK_SEM,1);
	//Rule 20
	grammar[20]=create_g_node_head(fieldDefinitions);
	pnext=first_gnode(grammar[20],fieldDefinition,0);
	pnext=dl_nodes(pnext,fieldDefinition,0);
	pnext=dl_nodes(pnext,moreFields,0);
	//Rule 21
	grammar[21]=create_g_node_head(fieldDefinition);
	pnext=first_gnode(grammar[21],TK_TYPE,1);
	pnext=dl_nodes(pnext,primitiveDatatype,0);
	pnext=dl_nodes(pnext,TK_COLON,1);
	pnext=dl_nodes(pnext,TK_FIELDID,1);
	pnext=dl_nodes(pnext,TK_SEM,1);
	//Rule 22
	grammar[22]=create_g_node_head(moreFields);
	pnext=first_gnode(grammar[22],fieldDefinition,0);
	pnext=dl_nodes(pnext,moreFields,0);
	//Rule 23(eps)
	grammar[23]=create_g_node_head(moreFields);
	pnext=first_gnode(grammar[23],eps,1);
	//Rule 24
	grammar[24]=create_g_node_head(declarations);
	pnext=first_gnode(grammar[24],declaration,0);
	pnext=dl_nodes(pnext,declarations,0);
	//Rule 25(eps)
	grammar[25]=create_g_node_head(declarations);
	pnext=first_gnode(grammar[25],eps,1);
	//Rule 26
	grammar[26]=create_g_node_head(declaration);
	pnext=first_gnode(grammar[26],TK_TYPE,1);
	pnext=dl_nodes(pnext,dataType,0);
	pnext=dl_nodes(pnext,TK_COLON,1);
	pnext=dl_nodes(pnext,TK_ID,1);
	pnext=dl_nodes(pnext,global_or_not,0);
	pnext=dl_nodes(pnext,TK_SEM,1);
	//Rule 27
	grammar[27]=create_g_node_head(global_or_not);
	pnext=first_gnode(grammar[27],TK_COLON,1);
	pnext=dl_nodes(pnext,TK_GLOBAL,1);
	//Rule 28(eps)
	grammar[28]=create_g_node_head(global_or_not);
	pnext=first_gnode(grammar[28],eps,1);
	//Rule 29
	grammar[29]=create_g_node_head(otherStmts);
	pnext=first_gnode(grammar[29],stmt,0);
	pnext=dl_nodes(pnext,otherStmts,0);
	//Rule 30(eps)
	grammar[30]=create_g_node_head(otherStmts);
	pnext=first_gnode(grammar[30],eps,1);
	//Rule 31
	grammar[31]=create_g_node_head(stmt);
	pnext=first_gnode(grammar[31],assignmentStmt,0);
	//Rule 32
	grammar[32]=create_g_node_head(stmt);
	pnext=first_gnode(grammar[32],iterativeStmt,0);
	//Rule 33
	grammar[33]=create_g_node_head(stmt);
	pnext=first_gnode(grammar[33],conditionalStmt,0);
	//Rule 34
	grammar[34]=create_g_node_head(stmt);
	pnext=first_gnode(grammar[34],ioStmt,0);
	//Rule 35
	grammar[35]=create_g_node_head(stmt);
	pnext=first_gnode(grammar[35],funCallStmt,0);
	//Rule 36
	grammar[36]=create_g_node_head(assignmentStmt);
	pnext=first_gnode(grammar[36],singleOrRecId,0);
	pnext=dl_nodes(pnext,TK_ASSIGNOP,1);
	pnext=dl_nodes(pnext,arithmeticExpression,0);
	pnext=dl_nodes(pnext,TK_SEM,1);
	//Rule 37
	grammar[37]=create_g_node_head(singleOrRecId);
	pnext=first_gnode(grammar[37],TK_ID,1);
	pnext=dl_nodes(pnext,new_24,0);
	//Rule 38(eps)
	grammar[38]=create_g_node_head(new_24);
	pnext=first_gnode(grammar[38],eps,1);
	//Rule 39
	grammar[39]=create_g_node_head(new_24);
	pnext=first_gnode(grammar[39],TK_DOT,1);
	pnext=dl_nodes(pnext,TK_FIELDID,1);
	//Rule 40
	grammar[40]=create_g_node_head(funCallStmt);
	pnext=first_gnode(grammar[40],outputParameters,0);
	pnext=dl_nodes(pnext,TK_CALL,1);
	pnext=dl_nodes(pnext,TK_FUNID,1);
	pnext=dl_nodes(pnext,TK_WITH,1);
	pnext=dl_nodes(pnext,TK_PARAMETERS,1);
	pnext=dl_nodes(pnext,inputParameters,0);
	pnext=dl_nodes(pnext,TK_SEM,1);
	//Rule 41
	grammar[41]=create_g_node_head(outputParameters);
	pnext=first_gnode(grammar[41],TK_SQL,1);
	pnext=dl_nodes(pnext,idList,0);
	pnext=dl_nodes(pnext,TK_SQR,1);
	pnext=dl_nodes(pnext,TK_ASSIGNOP,1);
	//Rule 42(eps)
	grammar[42]=create_g_node_head(outputParameters);
	pnext=first_gnode(grammar[42],eps,1);
	//Rule 43
	grammar[43]=create_g_node_head(inputParameters);
	pnext=first_gnode(grammar[43],TK_SQL,1);
	pnext=dl_nodes(pnext,idList,0);
	pnext=dl_nodes(pnext,TK_SQR,1);
	//Rule 44
	grammar[44]=create_g_node_head(iterativeStmt);
	pnext=first_gnode(grammar[44],TK_WHILE,1);
	pnext=dl_nodes(pnext,TK_OP,1);
	pnext=dl_nodes(pnext,booleanExpression,0);
	pnext=dl_nodes(pnext,TK_CL,1);
	pnext=dl_nodes(pnext,stmt,0);
	pnext=dl_nodes(pnext,otherStmts,0);
	pnext=dl_nodes(pnext,TK_ENDWHILE,1);
	//Rule 45
	grammar[45]=create_g_node_head(conditionalStmt);
	pnext=first_gnode(grammar[45],TK_IF,1);
	pnext=dl_nodes(pnext,TK_OP,1);
	pnext=dl_nodes(pnext,booleanExpression,0);
	pnext=dl_nodes(pnext,TK_CL,1);
	pnext=dl_nodes(pnext,TK_THEN,1);
	pnext=dl_nodes(pnext,stmt,0);
	pnext=dl_nodes(pnext,otherStmts,0);
	pnext=dl_nodes(pnext,elsePart,0);
	//Rule 46
	grammar[46]=create_g_node_head(elsePart);
	pnext=first_gnode(grammar[46],TK_ELSE,1);
	pnext=dl_nodes(pnext,stmt,0);
	pnext=dl_nodes(pnext,otherStmts,0);
	pnext=dl_nodes(pnext,TK_ENDIF,1);
	//Rule 47
	grammar[47]=create_g_node_head(elsePart);
	pnext=first_gnode(grammar[47],TK_ENDIF,1);
	//Rule 48
	grammar[48]=create_g_node_head(ioStmt);
	pnext=first_gnode(grammar[48],TK_READ,1);
	pnext=dl_nodes(pnext,TK_OP,1);
	pnext=dl_nodes(pnext,singleOrRecId,0);
	pnext=dl_nodes(pnext,TK_CL,1);
	pnext=dl_nodes(pnext,TK_SEM,1);
	//Rule 49
	grammar[49]=create_g_node_head(ioStmt);
	pnext=first_gnode(grammar[49],TK_WRITE,1);
	pnext=dl_nodes(pnext,TK_OP,1);
	pnext=dl_nodes(pnext,allVar,0);
	pnext=dl_nodes(pnext,TK_CL,1);
	pnext=dl_nodes(pnext,TK_SEM,1);
	//Rule 50
	grammar[50]=create_g_node_head(allVar);
	pnext=first_gnode(grammar[50],TK_NUM,1);
	//Rule 51
	grammar[51]=create_g_node_head(allVar);
	pnext=first_gnode(grammar[51], TK_RNUM, 1);
	//Rule 52
	grammar[52]=create_g_node_head(allVar);
	pnext=first_gnode(grammar[52], TK_ID, 1);
	pnext=dl_nodes(pnext, temp, 0);
	//Rule 53
	grammar[53]=create_g_node_head(arithmeticExpression);
	pnext=first_gnode(grammar[53],term,0);
	pnext=dl_nodes(pnext,expPrime,0);
	//Rule 54
	grammar[54]=create_g_node_head(expPrime);
	pnext=first_gnode(grammar[54],lowPrecedenceOperators,0);
	pnext=dl_nodes(pnext,term,0);
	pnext=dl_nodes(pnext,expPrime,0);
	//Rule 55(eps)
	grammar[55]=create_g_node_head(expPrime);
	pnext=first_gnode(grammar[55],eps,1);
	//Rule 56
	grammar[56]=create_g_node_head(term);
	pnext=first_gnode(grammar[56],factor,0);
	pnext=dl_nodes(pnext,termPrime,0);
	//Rule 57
	grammar[57]=create_g_node_head(termPrime);
	pnext=first_gnode(grammar[57],highPrecedenceOperators,0);
	pnext=dl_nodes(pnext,factor,0);
	pnext=dl_nodes(pnext,termPrime,0);
	//Rule 58(eps)
	grammar[58]=create_g_node_head(termPrime);
	pnext=first_gnode(grammar[58],eps,1);
	//Rule 59
	grammar[59]=create_g_node_head(factor);
	pnext=first_gnode(grammar[59],TK_OP,1);
	pnext=dl_nodes(pnext,arithmeticExpression,0);
	pnext=dl_nodes(pnext,TK_CL,1);
	//Rule 60
	grammar[60]=create_g_node_head(factor);
	pnext=first_gnode(grammar[60],allVar,0);
	//Rule 61
	grammar[61]=create_g_node_head(highPrecedenceOperators);
	pnext=first_gnode(grammar[61],TK_MUL,1);
	//Rule 62
	grammar[62]=create_g_node_head(highPrecedenceOperators);
	pnext=first_gnode(grammar[62],TK_DIV,1);
	//Rule 63
	grammar[63]=create_g_node_head(lowPrecedenceOperators);
	pnext=first_gnode(grammar[63],TK_PLUS,1);
	//Rule 64
	grammar[64]=create_g_node_head(lowPrecedenceOperators);
	pnext=first_gnode(grammar[64],TK_MINUS,1);
	//Rule 65
	grammar[65]=create_g_node_head(temp);
	pnext=first_gnode(grammar[65],eps,1);
	//Rule 66
	grammar[66]=create_g_node_head(temp);
	pnext=first_gnode(grammar[66],TK_DOT,1);
	pnext=dl_nodes(pnext,TK_FIELDID,1);
	//Rule 67
	grammar[67]=create_g_node_head(booleanExpression);
	pnext=first_gnode(grammar[67],TK_OP,1);
	pnext=dl_nodes(pnext,booleanExpression,0);
	pnext=dl_nodes(pnext,TK_CL,1);
	pnext=dl_nodes(pnext,logicalOp,0);
	pnext=dl_nodes(pnext,TK_OP,1);
	pnext=dl_nodes(pnext,booleanExpression,0);
	pnext=dl_nodes(pnext,TK_CL,1);
	//Rule 68
	grammar[68]=create_g_node_head(booleanExpression);
	pnext=first_gnode(grammar[68],var,0);
	pnext=dl_nodes(pnext,relationalOp,0);
	pnext=dl_nodes(pnext,var,0);
	//Rule 69
	grammar[69]=create_g_node_head(booleanExpression);
	pnext=first_gnode(grammar[69],TK_NOT,1);
	pnext=dl_nodes(pnext, TK_OP, 1);
	pnext=dl_nodes(pnext,booleanExpression,0);
	pnext=dl_nodes(pnext, TK_CL, 1);
	//Rule 70
	grammar[70]=create_g_node_head(var);
	pnext=first_gnode(grammar[70],TK_ID,1);
	//Rule 71
	grammar[71]=create_g_node_head(var);
	pnext=first_gnode(grammar[71],TK_NUM,1);
	//Rule 72
	grammar[72]=create_g_node_head(var);
	pnext=first_gnode(grammar[72],TK_RNUM,1);
	//Rule 73
	grammar[73]=create_g_node_head(logicalOp);
	pnext=first_gnode(grammar[73],TK_AND,1);
	//Rule 74
	grammar[74]=create_g_node_head(logicalOp);
	pnext=first_gnode(grammar[74],TK_OR,1);
	//Rule 75
	grammar[75]=create_g_node_head(relationalOp);
	pnext=first_gnode(grammar[75],TK_LT,1);
	//Rule 76
	grammar[76]=create_g_node_head(relationalOp);
	pnext=first_gnode(grammar[76],TK_LE,1);
	//Rule 77
	grammar[77]=create_g_node_head(relationalOp);
	pnext=first_gnode(grammar[77],TK_EQ,1);
	//Rule 78
	grammar[78]=create_g_node_head(relationalOp);
	pnext=first_gnode(grammar[78],TK_GT,1);
	//Rule 79
	grammar[79]=create_g_node_head(relationalOp);
	pnext=first_gnode(grammar[79],TK_GE,1);
	//Rule 80
	grammar[80]=create_g_node_head(relationalOp);
	pnext=first_gnode(grammar[80],TK_NE,1);
	//Rule 81
	grammar[81]=create_g_node_head(returnStmt);
	pnext=first_gnode(grammar[81],TK_RETURN,1);
	pnext=dl_nodes(pnext,optionalReturn,0);
	pnext=dl_nodes(pnext,TK_SEM,1);
	//Rule 82
	grammar[82]=create_g_node_head(optionalReturn);
	pnext=first_gnode(grammar[82],TK_SQL,1);
	pnext=dl_nodes(pnext,idList,0);
	pnext=dl_nodes(pnext,TK_SQR,1);
	//Rule 83
	grammar[83]=create_g_node_head(optionalReturn);
	pnext=first_gnode(grammar[83],eps,1);
	//Rule 84
	grammar[84]=create_g_node_head(idList);
	pnext=first_gnode(grammar[84],TK_ID,1);
	pnext=dl_nodes(pnext,more_ids,0);
	//Rule 85
	grammar[85]=create_g_node_head(more_ids);
	pnext=first_gnode(grammar[85],TK_COMMA,1);
	pnext=dl_nodes(pnext,idList,0);
	//Rule 86
	grammar[86]=create_g_node_head(more_ids);
	pnext=first_gnode(grammar[86],eps,1);


	for(int i=0;i<NO_OF_GRAMMAR_RULES;i++)
	{
		grammar[i]->rule_no=i;
	}
	//so on

	return ;
}
void add_node_to_first(node_head_first* head,TOKEN tk, int rule)
{
	node* temp=create_node(tk,rule);
    temp->next=head->head;
    head->head=temp;
	
}

void add_list_to_first(node_head_first* head, node* list,int rule)
{
    node* curr;
    curr=list;
	node* temp;
    while(curr!=NULL)
    {
		temp=create_node(curr->tokenName,rule);
        temp->next=head->head;
        head->head=temp;
		curr=curr->next;
    }
}
void add_list_to_first_eps(node_head_first* head, node* list,int rule)
{
	node* curr;
    curr=list;
	node* temp;
    while(curr!=NULL)
    {
		if(curr->tokenName==eps)
		{
			curr=curr->next;
			continue;}
		temp=create_node(curr->tokenName,rule);
        temp->next=head->head;
        head->head=temp;
		curr=curr->next;
    }
}
void first (NON_TERMINAL nt);
void recurse_first(node_head_first* node_head,g_node* temp, int rule_no)
{
    if(temp==NULL)
	{
		add_node_to_first(node_head,eps,rule_no);		
	}

	else
	{
        if(!temp->is_term)
        {
            if(f->first[temp->elem.nonterminal]->head!=NULL)
            {
                if(!(f->first[temp->elem.nonterminal]->has_eps))
		        {
                    add_list_to_first(node_head,f->first[temp->elem.nonterminal]->head,rule_no);
                }
                else
                {
					add_list_to_first_eps(node_head,f->first[temp->elem.nonterminal]->head,rule_no);
                    recurse_first(node_head,temp->next, rule_no);
                }
            
            }
            else
            {
                first(temp->elem.nonterminal);
                if(!f->first[temp->elem.nonterminal]->has_eps)
                {
                    add_list_to_first(node_head,f->first[temp->elem.nonterminal]->head,rule_no);
                }
                else
                {
					add_list_to_first_eps(node_head,f->first[temp->elem.nonterminal]->head,rule_no);
                    recurse_first(node_head,temp->next,rule_no);
                }
                        
            }
        }
        else
        {
            add_node_to_first(node_head, temp->elem.terminal, rule_no);
        }
        	
	}
}

void first (NON_TERMINAL nt)
{
	// printf("%d\n ",nt);
    if(f->first[nt]->head!=NULL)
    {
        return;
    }
    else
    {
        int* rule= nonTerminalStringTable[nt]->rules;
        int length= nonTerminalStringTable[nt]->length;
        int i;
        g_node* iterator=NULL;
        node* temp=NULL;
        for(i=0;i<length;i++)
        {
            iterator =grammar[rule[i]]->next;
            // while(iterator!=NULL)
            {
                if(iterator->is_term)
                {
					// printf("hello\n");
                    if(iterator->elem.terminal==eps)
                    {
                        f->first[nt]->has_eps=true;
                    }
                    add_node_to_first(f->first[nt],iterator->elem.terminal,rule[i]);
                }
                else
                {
					// printf("hello bitch\n");
                    if(f->first[iterator->elem.nonterminal]->head!=NULL)
                    {
                        if(!(f->first[iterator->elem.nonterminal]->has_eps))
		                {
                            add_list_to_first(f->first[nt],f->first[iterator->elem.nonterminal]->head,rule[i]);
                        }
                        else
                        {
							add_list_to_first_eps(f->first[nt],f->first[iterator->elem.nonterminal]->head,rule[i]);
                            recurse_first(f->first[nt],iterator->next, rule[i]);
                        }
                    }

                    else
                    {
                        
                        first(iterator->elem.nonterminal);
                        if(!f->first[iterator->elem.nonterminal]->has_eps)
                        {
                            add_list_to_first(f->first[nt],f->first[iterator->elem.nonterminal]->head,rule[i]);
                        }
                        else
                        {
							add_list_to_first_eps(f->first[nt],f->first[iterator->elem.nonterminal]->head,rule[i]);
                            recurse_first(f->first[nt],iterator->next,rule[i]);
                        }
                    }
                    
                }
                // iterator=iterator->next;
            }           
        }
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

nonterminal_str* create_nt_str()
{
	nonterminal_str* temp=(nonterminal_str*) malloc(sizeof(nonterminal_str));
	temp->rules=(int*) malloc(sizeof(int)*MAX_DIFF_RULES);
	temp->nonterminal=(char*) malloc(sizeof(char)*MAX_NONTERMINAL);
	temp->length=0;
	return temp;
}


void populateStrTable()
{
	int i;
	nonTerminalStringTable=(nonterminal_str**) malloc(sizeof(nonterminal_str*)*NO_OF_RULES);
	for(i=0;i<NO_OF_RULES;i++)
	{
		nonTerminalStringTable[i]=create_nt_str();
		
	}

	for(i=0;i<NO_OF_GRAMMAR_RULES;i++)
	{
		int temp=grammar[i]->non_terminal;
		nonTerminalStringTable[temp]->rules[nonTerminalStringTable[temp]->length]=i;
		nonTerminalStringTable[temp]->length++;

	}

	FILE *f;
    char c;
    f=fopen("nt_string.txt","r");
	int j=0;
	i=0;
	int flag=0;
    while((c=fgetc(f))!=EOF){

        
        if((c>='a'&&c<='z')||(c>='A'&&c<='Z')||c=='_'||(c>='0'&&c<='9'))
		{
			if(flag==1)
			{
				i++;
				j=0;
				flag=0;
			}

			nonTerminalStringTable[i]->nonterminal[j++]=c;
            // printf("%c",c);
		}
		else
		{
			flag=1;
			nonTerminalStringTable[i]->nonterminal[j++]='\0';
			// i++;
            printf(" ");
            continue;
		}
    }  

    fclose(f);
    

	
}

void print_strTable_row(NON_TERMINAL nt)
{
	int temp=nonTerminalStringTable[nt]->length;
	printf("nt:%d--->len:%d  %s  ",nt,temp,nonTerminalStringTable[nt]->nonterminal);
	for(int i=0;i<temp;i++)
	{
		printf("%d ",nonTerminalStringTable[nt]->rules[i]);
	}
}

void print_strTable()
{
	for(int i=0;i<NO_OF_RULES;i++)
	{
		print_strTable_row(i);
		printf("\n");
	}
}

void print_first(NON_TERMINAL nt)
{
	// printf("hello\n");
	node* temp=f->first[nt]->head;
	while(temp!=NULL)
	{
		printf("token: %s(%d) , rule no:%d \n", TerminalString(temp->tokenName),temp->tokenName+1,temp->rule_no_index);
		temp=temp->next;
	}
}

void print_follow(NON_TERMINAL nt)
{
	node* temp=f->follow[nt]->head;
	while(temp!=NULL)
	{
		printf("token: %s(%d) , rule no:%d \n",TerminalString(temp->tokenName),temp->tokenName+1,temp->rule_no_index);
		temp=temp->next;
	}
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
						T[i][temp2->tokenName].table_Entry.rule_no_index=-2;
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


			// length=nonTerminalStringTable[i]->length;
			// for(r=0;r<length;r++)
			// {
			// 	gtemp=grammar[nonTerminalStringTable[i]->rules[r]]->next;
			// 	if(gtemp->is_term)
			// 	{
			// 		if(gtemp->elem.terminal==eps)
			// 		{
			// 			add_rule_to_Ttable()
			// 			//add current grammar rule to all the follows
			// 			break;
			// 		}
			// 	}
			// 	else
			// 	{
			// 		if(f->first[gtemp->elem.nonterminal]->has_eps)
			// 		{
			// 			//recurse to find if it derives eps or not;
			// 		}
			// 		else
			// 		{
			// 			continue;
			// 		}
					
			// 	}
				
				
			// }
		// }	
			
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

void parseInputSourceCode(char *testcaseFile, parse_table T){
	
}

// node* first(NON_TERMINAL nt_index){
	
// }