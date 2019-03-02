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

FirstAndFollow *ComputeFirstAndFollowSets(g_node **grammar){
	FirstAndFollow *f = (FirstAndFollow*)malloc(sizeof(FirstAndFollow));
	f->first = (node**)malloc(sizeof(node*)*NO_OF_RULES);
	f->follow = (node**)malloc(sizeof(node*)*NO_OF_RULES);
	
	//First: recursive search til encounter a terminal
	// for(int i=0; i<NO_OF_RULES; i++){
	// 	f->first[i]->next = first(i);
	// }
	// for(int i=0; i<NO_OF_RULES; i++){
	// 	f->follow[i]->next = follow(i);
	// }
	return f;
}

void createParseTable(FirstAndFollow *f, parse_table T){
	T = (parse_table_elem**)malloc(sizeof(parse_table_elem*)*NO_OF_RULES);
	for(int i=0; i<NO_OF_RULES; i++){
		T[i]=(parse_table_elem*)malloc(sizeof(parse_table_elem)*(eps+1));
	}
}

void parseInputSourceCode(char *testcaseFile, parse_table T){
	
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
	pnext=dl_nodes(pnext,mainFunction,0);
	print_gnode(pnext);
	//Rule 1
	pnext=first_gnode(grammar[1],TK_MAIN,1);
	pnext=dl_nodes(pnext,stmts,0);
	pnext=dl_nodes(pnext,TK_END,1);
	//Rule 2
	pnext=first_gnode(grammar[2],function,0);
	pnext=dl_nodes(pnext,otherFunctions,0);
	//Rule 3(eps)
	pnext = first_gnode(grammar[3],eps,1);
	//Rule 4
	pnext=first_gnode(grammar[4],TK_FUNID,1);
	pnext=dl_nodes(pnext,input_par,0);
	pnext=dl_nodes(pnext,output_par,0);
	pnext=dl_nodes(pnext,TK_SEM,1);
	pnext=dl_nodes(pnext,stmts,0);
	pnext=dl_nodes(pnext,TK_END,1);
	//Rule 5
	pnext=first_gnode(grammar[5],TK_INPUT,1);
	pnext=dl_nodes(pnext,TK_PARAMETER,1);
	pnext=dl_nodes(pnext,TK_LIST,1);
	pnext=dl_nodes(pnext,TK_SQL,1);
	pnext=dl_nodes(pnext,parameter_list,0);
	pnext=dl_nodes(pnext,TK_SQR,1);
	//Rule 6
	pnext=first_gnode(grammar[6],dataType,0);
	pnext=dl_nodes(pnext,TK_ID,1);
	pnext=dl_nodes(pnext,remaining_list,0);
	//Rule 7
	pnext=first_gnode(grammar[7],primitiveDatatype,0);
	//Rule 8
	pnext=first_gnode(grammar[8],constructedDatatype,0);
	//Rule 9
	pnext=first_gnode(grammar[9],TK_INT,1);
	//Rule 10
	pnext=first_gnode(grammar[10],TK_REAL,1);
	//Rule 11
	pnext=first_gnode(grammar[11],TK_RECORD,1);
	pnext=dl_nodes(pnext,TK_RECORDID,1);
	//Rule 12
	pnext=first_gnode(grammar[12],TK_COMMA,1);
	pnext=dl_nodes(pnext,parameter_list,0);
	//Rule 13(eps)
	pnext=first_gnode(grammar[13],eps,1);
	//Rule 14
	pnext=first_gnode(grammar[14],typeDefinitions,0);
	pnext=dl_nodes(pnext,declarations,0);
	pnext=dl_nodes(pnext,otherStmts,0);
	pnext=dl_nodes(pnext,returnStmt,0);
	//Rule 15
	pnext=first_gnode(grammar[15],typeDefinition,0);
	pnext=dl_nodes(pnext,typeDefinitions,0);
	//Rule 16(eps)
	pnext=first_gnode(grammar[16],eps,1);
	//Rule 17
	pnext=first_gnode(grammar[17],TK_RECORD,1);
	pnext=dl_nodes(pnext,TK_RECORDID,1);
	pnext=dl_nodes(pnext,fieldDefinitions,0);
	pnext=dl_nodes(pnext,TK_ENDRECORD,1);
	pnext=dl_nodes(pnext,TK_SEM,1);
	//Rule 18
	pnext=first_gnode(grammar[18],fieldDefinition,0);
	pnext=dl_nodes(pnext,fieldDefinition,0);
	pnext=dl_nodes(pnext,moreFields,0);
	//Rule 19
	pnext=first_gnode(grammar[19],TK_TYPE,1);
	pnext=dl_nodes(pnext,primitiveDatatype,0);
	pnext=dl_nodes(pnext,TK_COLON,1);
	pnext=dl_nodes(pnext,TK_FIELDID,1);
	pnext=dl_nodes(pnext,TK_SEM,1);
	//Rule 20
	pnext=first_gnode(grammar[20],fieldDefinition,0);
	pnext=dl_nodes(pnext,moreFields,0);
	//Rule 21(eps)
	pnext=first_gnode(grammar[21],eps,1)
	//Rule 22
	pnext=first_gnode(grammar[22],declaration,0);
	pnext=dl_nodes(pnext,declarations,0);
	//Rule 23(eps)
	pnext=first_gnode(grammar[23],eps,1);
	//Rule 24
	pnext=first_gnode(grammar[24],TK_TYPE,1);
	pnext=dl_nodes(pnext,dataType,0);
	pnext=dl_nodes(pnext,TK_COLON,1);
	pnext=dl_nodes(pnext,TK_ID,1);
	pnext=dl_nodes(pnext,global_or_not,0);
	pnext=dl_nodes(pnext,TK_SEM,1);
	//Rule 25
	pnext=first_gnode(grammar[25],TK_COLON,1);
	pnext=dl_nodes(pnext,TK_GLOBAL,1);
	//Rule 26(eps)
	pnext=first_gnode(grammar[26],eps,1);
	//Rule 27
	pnext=first_gnode(grammar[27],stmt,0);
	pnext=dl_nodes(pnext,otherStmts,0);
	//Rule 28(eps)
	pnext=first_gnode(grammar[28],eps,1);
	//Rule 29
	pnext=first_gnode(grammar[29],assignmentStmt,0);
	//Rule 30
	pnext=first_gnode(grammar[30],iterativeStmt,0);
	//Rul 31
	pnext=first_gnode(grammar[31],conditionalStmt,0);
	//Rule 32
	pnext=first_gnode(grammar[32],ioStmt,0);
	//Rule 33
	pnext=first_gnode(grammar[33],funCallStmt,0);
	//Rule 34
	pnext=first_gnode(grammar[34],singleOrRecId,0);
	pnext=dl_nodes(pnext,TK_ASSIGNOP,1);
	pnext=dl_nodes(pnext,arithmeticExpression,0);
	pnext=dl_nodes(pnext,TK_SEM,1);
	//Rule 35
	pnext=first_gnode(grammar[35],TK_ID,1);
	pnext=dl_nodes(pnext,new_24,0);
	//Rule 36(eps)
	pnext=first_gnode(grammar[36],eps,1);
	//Rule 37
	pnext=first_gnode(grammar[37],TK_DOT,1);
	pnext=dl_nodes(pnext,TK_FIELDID,1);
	//Rule 38
	pnext=first_gnode(grammar[38],outputParameters,0);
	pnext=dl_nodes(pnext,TK_CALL,1);
	pnext=dl_nodes(pnext,TK_FUNID,1);
	pnext=dl_nodes(pnext,TK_WITH,1);
	pnext=dl_nodes(pnext,TK_PARAMETERS,1);
	pnext=dl_nodes(pnext,inputParameters,0);
	pnext=dl_nodes(pnext,TK_SEM,1);
	//Rule 39
	pnext=first_gnode(grammar[39],TK_SQL,1);
	pnext=dl_nodes(pnext,idList,0);
	pnext=dl_nodes(pnext,TK_SQR,1);
	pnext=dl_nodes(pnext,TK_ASSIGNOP,1);
	//Rule 40(eps)
	pnext=first_gnode(grammar[40],eps,1);
	//Rule 41
	pnext=first_gnode(grammar[41],TK_SQL,1);
	pnext=dl_nodes(pnext,idList,0);
	pnext=dl_nodes(pnext,TK_SQR,1);
	//Rule 42
	pnext=first_gnode(grammar[42],TK_WHILE,1);
	pnext=dl_nodes(pnext,TK_OP,1);
	pnext=dl_nodes(pnext,booleanExpression,0);
	pnext=dl_nodes(pnext,TK_CL,1);
	pnext=dl_nodes(pnext,stmt,0);
	pnext=dl_nodes(pnext,otherStmts,0);
	pnext=dl_nodes(pnext,TK_ENDWHILE,1);
	//Rule 43
	pnext=first_gnode(grammar[43],TK_IF,1);
	pnext=dl_nodes(pnext,TK_OP,1);
	pnext=dl_nodes(pnext,booleanExpression,0);
	pnext=dl_nodes(pnext,TK_CL,1);
	pnext=dl_nodes(pnext,TK_THEN,1);
	pnext=dl_nodes(pnext,stmt,0);
	pnext=dl_nodes(pnext,otherStmts,0);
	pnext=dl_nodes(pnext,elsePart,0);
	//Rule 44
	pnext=first_gnode(grammar[44],TK_ELSE,1);
	pnext=dl_nodes(pnext,stmt,0);
	pnext=dl_nodes(pnext,otherStmts,0);
	pnext=dl_nodes(pnext,TK_ENDIF,1);
	//Rule 45
	pnext=first_gnode(grammar[45],TK_ENDIF,1);
	//Rule 46
	pnext=first_gnode(grammar[46],TK_READ,1);
	pnext=dl_nodes(pnext,TK_OP,1);
	pnext=dl_nodes(pnext,singleOrRecId,0);
	pnext=dl_nodes(pnext,TK_CL,1);
	pnext=dl_nodes(pnext,TK_SEM,1);
	//Rule 47
	pnext=first_gnode(grammar[47],TK_WRITE,1);
	pnext=dl_nodes(pnext,TK_OP,1);
	pnext=dl_nodes(pnext,allVar,0);
	pnext=dl_nodes(pnext,TK_CL,1);
	pnext=dl_nodes(pnext,TK_SEM,1);
	//Rule 48
	pnext=first_gnode(grammar[48],var,0);
	//Rule 49
	pnext=first_gnode(grammar[49],TK_RECORDID,1);
	pnext=dl_nodes(pnext,TK_DOT,1);
	pnext=dl_nodes(pnext,TK_FIELDID,1);
	//Rule 50
	pnext=first_gnode(grammar[50],term,0);
	pnext=dl_nodes(pnext,expPrime,0);
	//Rule 51
	pnext=first_gnode(grammar[51],lowPrecedenceOperators,0);
	pnext=dl_nodes(pnext,term,0);
	pnext=dl_nodes(pnext,expPrime,0);
	//Rule 52(eps)
	pnext=first_gnode(grammar[52],eps,1);
	//Rule 53
	pnext=first_gnode(grammar[53],factor,0);
	pnext=dl_nodes(pnext,termPrime,0);
	//Rule 54
	pnext=first_gnode(grammar[54],highPrecedenceOperators,0);
	pnext=dl_nodes(pnext,factor,0);
	pnext=dl_nodes(pnext,termPrime,0);
	//Rule 55(eps)
	pnext=first_gnode(grammar[55],eps,1);
	//Rule 56
	pnext=first_gnode(grammar[56],TK_OP,1);
	pnext=dl_nodes(pnext,arithmeticExpression,0);
	pnext=dl_nodes(pnext,TK_CL,1);
	//Rule 57
	pnext=first_gnode(grammar[57],all,0);
	//Rule 58
	pnext=first_gnode(grammar[58],TK_MUL,1);
	//Rule 59
	pnext=first_gnode(grammar[59],TK_DIV,1);
	//Rule 60
	pnext=first_gnode(grammar[60],TK_PLUS,1);
	//Rule 61
	pnext=first_gnode(grammar[61],TK_MINUS,1);
	//Rule 62
	pnext=first_gnode(grammar[62],TK_ID,1);
	//Rule 63
	pnext=first_gnode(grammar[63],TK_NUM,1);
	//Rule 64
	pnext=first_gnode(grammar[64],TK_RNUM,1);
	//Rule 65
	pnext=first_gnode(grammar[65],TK_RECORDID,1);
	pnext=dl_nodes(pnext,temp,0);
	//Rule 66
	pnext=first_gnode(grammar[66],eps,1);
	//Rule 67
	pnext=first_gnode(grammar[67],TK_DOT,1);
	pnext=dl_nodes(pnext,TK_FIELDID,1);
	//Rule 68
	pnext=first_gnode(grammar[68],TK_OP,1);
	pnext=dl_nodes(pnext,booleanExpression.0);
	pnext=dl_nodes(pnext,TK_CL,1);
	pnext=dl_nodes(pnext,logicalOp,0);
	pnext=dl_nodes(pnext,TK_OP,1);
	pnext=dl_nodes(pnext,booleanExpression,0);
	pnext=dl_nodes(pnext,TK_CL,1);
	//Rule 69
	pnext=first_gnode(grammar[69],var,0);
	pnext=dl_nodes(pnext,relationalOp,0);
	pnext=dl_nodes(pnext,var,0);
	//Rule 70
	pnext=first_gnode(grammar[70],TK_NOT,1);
	pnext=dl_nodes(pnext,booleanExpression,0);
	//Rule 71
	pnext=first_gnode(grammar[71],TK_ID,1);
	//Rule 72
	pnext=first_gnode(grammar[72],TK_NUM,1);
	//Rule 73
	pnext=first_gnode(grammar[73],TK_RNUM,1);
	//Rule 74
	pnext=first_gnode(grammar[74],TK_AND,1);
	//Rule 75
	pnext=first_gnode(grammar[75],TK_OR,1);
	//Rule 76
	pnext=first_gnode(grammar[76],TK_LT,1);
	//Rule 77
	pnext=first_gnode(grammar[77],TK_LE,1);
	//Rule 78
	pnext=first_gnode(grammar[78],TK_EQ,1);
	//Rule 79
	pnext=first_gnode(grammar[79],TK_GT,1);
	//Rule 80
	pnext=first_gnode(grammar[80],TK_GE,1);
	//Rule 81
	pnext=first_gnode(grammar[81],TK_NE,1);
	//Rule 82
	pnext=first_gnode(grammar[82,TK_RETURN,1]);
	pnext=dl_nodes(pnext,optionalReturn,0);
	pnext=dl_nodes(pnext,TK_SEM,1);
	//Rule 83
	pnext=first_gnode(grammar[83],TK_SQL,1);
	pnext=dl_nodes(pnext,idList,0);
	pnext=dl_nodes(pnext,TK_SQR,1);
	//Rule 84
	pnext=first_gnode(grammar[84],eps,1);
	//Rule 85
	pnext=first_gnode(grammar[85],TK_ID,1);
	pnext=dl_nodes(pnext,more_ids,0);
	//Rule 86
	pnext=first_gnode(grammar[86],TK_COMMA,1);
	pnext=dl_nodes(pnext,idList,0);
	//Rule 87
	pnext=first_gnode(grammar[87],eps,1);


















	//so on

	return grammar;
}
g_node* first_gnode(g_node_head* h,int no,bool is_term)
{
	pnext = h->next = create_g_node(is_term, no);
	pnext->prev=NULL;
	pnext->next=NULL;
	return pnext;
}
g_node* dl_nodes(gnode* pnext,int no,bool is_term)
{
	ptr=pnext->next=create_g_node(is_term,no);
	ptr->prev=pnext;
	ptr->next=NULL;

	return ptr;
}

void print_gnode(gnode* ptr)
{
	if(ptr->is_term)
	{
		printf("%d\n", ptr->prev->elem.terminal);
	}
	else
	printf("%d\n", ptr->prev->elem.terminal);
}

// node* first(NON_TERMINAL nt_index){
	
// }