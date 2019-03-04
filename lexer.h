#include <stdio.h>
#include "lexerDef.h"
#define LEX_DEF_INCLUDED

//Mandatory functions
size_t getStream(FILE *fp);
tokenInfo* getNextToken(FILE *fp);
void removeComments(char *testcaseFile, char *cleanFile); //char* refers to filename which is opened within the function

//Auxiliary functions
void populate_transition_table();
void populateNonTerminalStringTable();
char *TerminalString(int index);
void length_error(int choice, char *lex, int *state, int *input_buffer_pointer, int *j, bool *exceed_flag, int line_count);
void unknown_pattern(char *arr, int line_num, char ch, int *j, int *input_buffer_pointer);
void unknown_symbol(char *arr, int line_num, char ch, int *j, int *input_buffer_pointer);