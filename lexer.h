#include <stdio.h>
#include "lexerDef.h"
#define LEX_DEF_INCLUDED

//Mandatory functions
void *getStream(FILE *fp);
tokenInfo* getNextToken(FILE *fp);
void removeComments(char *testcaseFile, char *cleanFile); //char* refers to filename which is opened within the function

//Auxiliary functions
void populate_transition_table();
void symbol_not_found();
void return_token(char* c);
