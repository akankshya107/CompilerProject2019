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
	int option;
	// printf("(a) FIRST and FOLLOW set automated: YES\n(c) Both lexical and syntax analysis modules implemented: YES\n(f) Parse tree constructed: YES\n");
	populate_transition_table();
	populateKeyWordTable();
	populateGrammar();
	populateStrTable();
	ComputeFirstAndFollowSets();
	createParseTable();
	treeNodeIt* t = parseInputSourceCode("semAn/testcase1.txt");
	// printParseTree(t, argv[2]);
	ASTNodeIt *plgiveerror = makeAbstractSyntaxTree(t);
	// printAST(plgiveerror);
	populateGlobalTable(plgiveerror);
	populateSymbolTable(plgiveerror);
	printGlobalTable_recDef();
	printGlobalvar();
	printSymbolTable();
	print_inpar_list();
	print_outpar_list();
	printf("hie\n");
	printMemActRec();
	return 0;
}
