#include "lexerDef.h"
#define LEX_DEF_INCLUDED
#include <stdio.h>
#include <stdlib.h>
TRANSITION_TABLE_ELEM **transition_table;
bool global_flag = 0;
int line_count = 0; //Still a doubt

void populate_transition_table(){
    TRANSITION_TABLE_ELEM **transition_table = (TRANSITION_TABLE_ELEM**)malloc(sizeof(TRANSITION_TABLE_ELEM*)*sizeof(NO_OF_STATES));
    for(int i=0; i<NO_OF_STATES; i++){
        transition_table[i]=(TRANSITION_TABLE_ELEM*)malloc(sizeof(TRANSITION_TABLE_ELEM)*(127));
    }
}

FILE *getStream(FILE *fp){
    if(!global_flag) {
        size_t no_of_bytes_read = fread(input_buffer, sizeof(char), BUF_LENGTH, fp);
        global_flag = 1;
        return fp;
    }
    input_buffer = input_buffer_twin;
    size_t twin_bytes = fread(input_buffer_twin, sizeof(char), BUF_LENGTH, fp);
    return fp;
}

tokenInfo* getNextToken(){
    //Rough: some implementation left
    int i=0, j=0, state=0;
    bool flag = 1;
    int ch;
    char* lex = (char*)malloc(sizeof(char)*MAX_LENGTH); //efficiently do this
    while(1){
        if (flag) ch = input_buffer[i];
        else ch = input_buffer_twin[i];
        if(transition_table[state][ch].flag==0){
            state = transition_table[state][ch].u.state;
            lex[j++]=ch;
            i++;
            if(i==BUF_LENGTH) {
                flag=0;
                i=0;
            }
        }else if(transition_table[state][ch].flag==1){
            return transition_table[state][ch].u.return_token_function(lex);
        }else{
            return transition_table[state][ch].u.error_function(lex);
        }
    }
}

void removeComments(char *testcaseFile, char *cleanFile){
    char* inp_buffer = (char*)malloc(sizeof(char)*BUF_LENGTH);
    char* write_buffer = (char*)malloc(sizeof(char)*BUF_LENGTH);
    FILE *f_test = fopen(testcaseFile, "r");
    FILE *f_clean = fopen(cleanFile, "w");
    size_t n = BUF_LENGTH;
    int flag = 1;
    int j = 0;
    int wr = BUF_LENGTH;
    while(1){
        if(j==wr){
            fwrite(write_buffer, sizeof(char), j, f_clean);
            j=0;
        }
        if(n<BUF_LENGTH) break;
        n = fread(inp_buffer, sizeof(char), BUF_LENGTH, f_test);
        wr = n;
        for(int i=0; i<n; i++){
            if(inp_buffer[i]=='%'){
                flag = 0;
            }
            if(flag) write_buffer[j++] = inp_buffer[i];
            else{
                if(inp_buffer[i]=='\n') flag=1;
                wr--;
            }
        }
    }
    fclose(f_clean);
    fclose(f_test);
}