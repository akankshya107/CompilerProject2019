#include <stdio.h>
FILE *getStream(FILE *fp);
tokenInfo* getNextToken();
void removeComments(FILE *testcaseFile, FILE *cleanFile);
