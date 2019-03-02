#include <stdio.h>
#include "lexerDef.h"
FILE *getStream(FILE *fp);
tokenInfo* getNextToken();
void removeComments(char *testcaseFile, char *cleanFile); //char* refers to filename which is opened within the function
void populate_transition_table();
void unknown_symbol(char c);
void unknown_pattern(char* c);
tokenInfo* return_token(char* c);
float get_rnum(char*c);
int get_num(char* c);
tokenInfo* generate_token_info1(TOKEN tkname,int line_no,char* c);
tokenInfo* generate_token_info2(TOKEN tkname,int line_no,int num);
tokenInfo* generate_token_info3(TOKEN tkname,int line_no,float num);
