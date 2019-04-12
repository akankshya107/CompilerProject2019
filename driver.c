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
// extern int parse_correct;
// extern int ParseNodes;
// extern int ASTNodes;
int main(int argc, char *argv[]){
<<<<<<< HEAD
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
=======
	int option;
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
			ASTNodeIt * ch = searchTag(ast, TAG_FUN_LIST)->node->u.n->children;
			populateGlobalTable(ast);
			while(ch!=NULL){
				populateSymbolTable(ch);
			}
			// if(option==5){
			// 	printSymbolTable();
			// }else if(option==6){
			// 	printGlobalTable(0); //print global variables
			// }else if(option==7){
			// 	printMemReqST();
			// }else{
			// 	printGlobalTable(1); //print record defs
			// }
		}else if(option==9){
>>>>>>> 1710f9d9377c283a8dfa2872115f3a01c987d24e

	// 		clock_t start_time, end_time;

	// 		double total_CPU_time, total_CPU_time_in_seconds;

	// 		start_time = clock();

<<<<<<< HEAD
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
=======
			treeNodeIt* t = parseInputSourceCode(argv[1]);
			if(parse_correct){
				ASTNodeIt *ast = semanticAnalyzer(t);
			}
			printf("\n");
			end_time = clock();
>>>>>>> 1710f9d9377c283a8dfa2872115f3a01c987d24e

	// 		total_CPU_time  =  (double) (end_time - start_time);

	// 		total_CPU_time_in_seconds =   total_CPU_time / CLOCKS_PER_SEC;

    //          // Print both total_CPU_time and total_CPU_time_in_seconds 

	// 		printf("Total CPU time: %f\nTotal CPU time in seconds: %f\n", total_CPU_time, total_CPU_time_in_seconds);

<<<<<<< HEAD
	// 	}else{
	// 		printf("Enter correct option\n");
	// 	}
	// }
	populateGrammar();
	populateStrTable();
	ComputeFirstAndFollowSets();
	createParseTable();
	treeNodeIt* t = parseInputSourceCode("testcase1.txt");
	// printParseTree(t, argv[2]);
	ASTNodeIt *plgiveerror = makeAbstractSyntaxTree(t);
	// printAST(plgiveerror);
	populateSymbolTable(plgiveerror);
	printSymbolTable(plgiveerror);
=======
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
				// constructASMcode(ast, argv[2]);
			}
		}
		else{
			printf("Enter correct option\n");
		}
	}
>>>>>>> 1710f9d9377c283a8dfa2872115f3a01c987d24e
	return 0;
}
