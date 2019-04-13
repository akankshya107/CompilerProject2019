// GROUP 39
// AKANKSHYA MISHRA 2016A7PS0026P
// NARAPAREDDY BHAVANA 2016A7PS0034P
// KARABEE BATTA 2016A7PS0052P
// AASTHA KATARIA 2016A7PS0062P

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "lexer.h"
#include "key.h"
#include "parser.h"
#include "grammar.h"
#include "semantic.h"
extern parse_table T;
extern int semantic_correct;
// extern int parse_correct;
// extern int ParseNodes;
// extern int ASTNodes;
int main(int argc, char *argv[]){
	int option;
	printf("LEVEL 4: Symbol table/ AST/ Semantic Rules modules work.\n\n");
	populate_transition_table();
	populateKeyWordTable();
	populateGrammar();
	populateStrTable();
	ComputeFirstAndFollowSets();
	createParseTable();
	while(1){
		printf("Please enter the option:\n");
		scanf("%d", &option);
		if(option==0){
			break;
		}else if(option==1){
			//Invoke only lexer
			FILE *fp = fopen(argv[1], "r");
			tokenInfo *ti;
			do{
				ti = getNextToken(fp);
				if(ti->tokenName==TK_NUM) printf("Line %d: Token %s, Lexeme %d\n", ti->line_no, TerminalString(ti->tokenName), ti->u.value_of_int);
				else if(ti->tokenName==TK_RNUM) printf("Line %d: Token %s, Lexeme %.2f\n", ti->line_no, TerminalString(ti->tokenName), ti->u.value_of_real);
				else printf("Line %d: Token %s, Lexeme %s\n", ti->line_no, TerminalString(ti->tokenName), ti->u.lexeme);
				// free(ti);
			}while(ti->tokenName!=EOS);
			fclose(fp);
			printf("\n");
		}else if(option==2){
			treeNodeIt* t = parseInputSourceCode(argv[1]);
			printParseTree(t);
		}else if(option==3){
			printf("Traversal order of AST: Post-order\n");
			treeNodeIt* t = parseInputSourceCode(argv[1]);
			ASTNodeIt* ast = makeAbstractSyntaxTree(t);
			printAST(ast);
		}else if(option==4){
			treeNodeIt* t = parseInputSourceCode(argv[1]);
			size_t p = printParseTreeNodes(t);
			printf("Parse tree Number of nodes = %d\t\tAllocated Memory = %lu Bytes\n", ParseNodes, p);
			ASTNodeIt* ast = makeAbstractSyntaxTree(t);
			size_t a =  printASTNodes(ast);
			printf("AST Number of nodes = %d\t\tAllocated Memory =%lu Bytes\n", ASTNodes, a);
			printf("Compression percentage = %f\n", (((float)p-a)/(float)p)*100 );
		}
		else if(option==5 || option==6 || option==7 || option==8){
			treeNodeIt* t = parseInputSourceCode(argv[1]);
			ASTNodeIt* ast = makeAbstractSyntaxTree(t);
			ASTNodeIt * ch = ast->node->u.n->children->node->u.n->children;
			populateGlobalTable(ast);
    		SymbolTable = create_HTEle();
			while(ch!=NULL){
				populateSymbolTable(ch);
				ch=ch->next;
			}
			populateSymbolTable(ast->node->u.n->children->next);
			if(option==5){
				printSymbolTable();
			}else if(option==6){
				printGlobalvar();
			}else if(option==7){
				printMemActRec();
			}else{
				printGlobalTable_recDef();
			}
		}else if(option==9){

			clock_t start_time, end_time;

			double total_CPU_time, total_CPU_time_in_seconds;

			start_time = clock();

			treeNodeIt* t = parseInputSourceCode(argv[1]);
			if(parse_correct){
				ASTNodeIt *ast = semanticAnalyzer(t);
			}
			if(!semantic_correct){
				printf("Code compiles successfully...\n");
			}
			else printf("\n");
			end_time = clock();

			total_CPU_time  =  (double) (end_time - start_time);

			total_CPU_time_in_seconds =   total_CPU_time / CLOCKS_PER_SEC;

             // Print both total_CPU_time and total_CPU_time_in_seconds 

			printf("Total CPU time: %f\nTotal CPU time in seconds: %f\n", total_CPU_time, total_CPU_time_in_seconds);

		}else if(option==10){
			int i;
			printf("Please enter whether code is free of syntactic, semantic or type mismatch errors(0 for no, 1 for yes)\n");
			printf("To check, use option=9 first\n");
			scanf("%d\n", &i);
			if(i){
				treeNodeIt* t = parseInputSourceCode(argv[1]);
				ASTNodeIt *ast;
				if(parse_correct){
					ast = semanticAnalyzer(t);
				}
				if(!semantic_correct){
					printf("Code compiles successfully...\n");
				}
				else printf("\n");
				// constructASMcode(ast, argv[2]);
			}
		}
		else{
			printf("Enter correct option\n");
		}
	}
	return 0;
}