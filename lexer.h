#include <stdio.h>
#include "lexerDef.h"
#define LEX_DEF_INCLUDED
void *getStream(FILE *fp);
tokenInfo* getNextToken(FILE *fp);
void removeComments(char *testcaseFile, char *cleanFile); //char* refers to filename which is opened within the function
void populate_transition_table();
