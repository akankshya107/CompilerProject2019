#include <stdio.h>
#include "lexer.h"
#include "key.h"
#include "parser.h"
extern parse_table T;
int main(int argc, char *argv[]){
	int option;
	while(1){
		scanf("%d", &option);
		if(option==0){
			break;
		}else if(option==1){
			removeComments(argv[1], "clean.txt");
		}else if(option==2){
			// //Invoke only lexer
			// printf("lyf");
			FILE *fp = fopen("testcase4.txt", "r");
			populate_transition_table();
			// printTT();
			populateKeyWordTable();
			// printf("lyf");
			// // populateTerminalStringTable();
			// // populateNonTerminalStringTable()
			tokenInfo *ti;
			do{
				ti = getNextToken(fp);
				if(ti->tokenName==TK_NUM) printf("Line %d: Token %s, Lexeme %d\n", ti->line_no, TerminalString(ti->tokenName), ti->u.value_of_int);
				else if(ti->tokenName==TK_RNUM) printf("Line %d: Token %s, Lexeme %.2f\n", ti->line_no, TerminalString(ti->tokenName), ti->u.value_of_real);
				else printf("Line %d: Token %s, Lexeme %s\n", ti->line_no, TerminalString(ti->tokenName), ti->u.lexeme);
			}while(ti->tokenName!=EOS);
			
		}else if(option==3){

		}else if(option==4){

		}else{
			printf("Enter correct option\n");
		}
	}
	return 0;
}
