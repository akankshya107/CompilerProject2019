#include <stdio.h>
#include "lexerDef.h"
FILE *getStream(FILE *fp);
tokenInfo* getNextToken();
void removeComments(char *testcaseFile, char *cleanFile); //char* refers to filename which is opened within the function
void populate_transition_table();
void symbol_not_found();
void return_token(char* c);
