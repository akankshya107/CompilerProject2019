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
// #include "AST.h"
#include "semantic.h"
extern parse_table T;
int main(int argc, char *argv[]){
	// int option;
	// printf("(a) FIRST and FOLLOW set automated: YES\n(c) Both lexical and syntax analysis modules implemented: YES\n(f) Parse tree constructed: YES\n");
	populate_transition_table();
	populateKeyWordTable();
	// while(1){
	// 	scanf("%d", &option);
	// 	if(option==0){
	// 		break;
	// 	}else if(option==1){
	// 		removeComments(argv[1], "clean.txt");
	// 		FILE *pr = fopen("clean.txt", "r");
	// 		char * buf = (char*)malloc(sizeof(char)*513);
	// 		int s;
	// 		do{
	// 			s = fread(buf, sizeof(char), 512, pr);
	// 			for(int i=0; i<s; i++){
	// 				printf("%c", buf[i]);
	// 			}
	// 		}while(s==512);
	// 		fclose(pr);
	// 		printf("\n");
	// 	}else if(option==2){
	// 		//Invoke only lexer
	// 		FILE *fp = fopen(argv[1], "r");
	// 		tokenInfo *ti;
	// 		do{
	// 			ti = getNextToken(fp);
	// 			if(ti->tokenName==TK_NUM) printf("Line %d: Token %s, Lexeme %d\n", ti->line_no, TerminalString(ti->tokenName), ti->u.value_of_int);
	// 			else if(ti->tokenName==TK_RNUM) printf("Line %d: Token %s, Lexeme %.2f\n", ti->line_no, TerminalString(ti->tokenName), ti->u.value_of_real);
	// 			else printf("Line %d: Token %s, Lexeme %s\n", ti->line_no, TerminalString(ti->tokenName), ti->u.lexeme);
	// 			// free(ti);
	// 		}while(ti->tokenName!=EOS);
	// 		fclose(fp);
	// 		printf("\n");

	// 	}else if(option==3){
	// 		populateGrammar();
	// 		populateStrTable();
	// 		ComputeFirstAndFollowSets();
	// 		createParseTable();
	// 		treeNodeIt* t = parseInputSourceCode("testcase1.txt");
	// 		// printParseTree(t, argv[2]);
	// 		ASTNodeIt *plgiveerror = makeAbstractSyntaxTree(t);
	// 		// printAST(plgiveerror);
	// 		populateSymbolTable(plgiveerror);
			
	// 		printf("\n");
	// 	}else if(option==4){

	// 		clock_t start_time, end_time;

	// 		double total_CPU_time, total_CPU_time_in_seconds;

	// 		start_time = clock();

	// 		// FILE *fp = fopen("testcase1.txt", "r");
	// 		// tokenInfo *ti;
	// 		// do{
	// 		// 	ti = getNextToken(fp);
	// 		// }while(ti->tokenName!=EOS);

	// 		// fclose(fp);

	// 		populateGrammar();
	// 		populateStrTable();
	// 		ComputeFirstAndFollowSets();
	// 		createParseTable();
	// 		// free_first_follow();
	// 		treeNodeIt* t = parseInputSourceCode(argv[1]);
	// 		printParseTree(t, argv[2]);
	// 		printf("\n");

	// 		end_time = clock();

	// 		total_CPU_time  =  (double) (end_time - start_time);

	// 		total_CPU_time_in_seconds =   total_CPU_time / CLOCKS_PER_SEC;

    //          // Print both total_CPU_time and total_CPU_time_in_seconds 

	// 		printf("Total CPU time: %f\nTotal CPU time in seconds: %f\n", total_CPU_time, total_CPU_time_in_seconds);

	// 	}else{
	// 		printf("Enter correct option\n");
	// 	}
	// }
	populateGrammar();
	populateStrTable();
	ComputeFirstAndFollowSets();
	createParseTable();
	treeNodeIt* t = parseInputSourceCode("testcase3.txt");
	// printParseTree(t, argv[2]);
	ASTNodeIt *plgiveerror = makeAbstractSyntaxTree(t);
	// printAST(plgiveerror);
	populateSymbolTable(plgiveerror);
	printSymbolTable(plgiveerror);
	return 0;
}
