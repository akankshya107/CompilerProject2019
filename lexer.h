// GROUP 39
// AKANKSHYA MISHRA 2016A7PS0026P
// NARAPAREDDY BHAVANA 2016A7PS0034P
// KARABEE BATTA 2016A7PS0052P
// AASTHA KATARIA 2016A7PS0062P
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
void length_error(int choice, int line_count);
void unknown_pattern(char *arr, int line_num, char ch, int *j, int *input_buffer_pointer);
void unknown_symbol(char *arr, int line_num, char ch, int *j, int *input_buffer_pointer);
tokenInfo *return_str_token(char *lexeme, TOKEN tkname, int lineno, bool is_retract, int *input_buffer_pointer);
tokenInfo *return_no_token(char *lexeme, TOKEN tkname, int lineno, bool is_retract, int *input_buffer_pointer);
