// GROUP 39
// AKANKSHYA MISHRA 2016A7PS0026P
// NARAPAREDDY BHAVANA 2016A7PS0034P
// KARABEE BATTA 2016A7PS0052P
// AASTHA KATARIA 2016A7PS0062P
#include "lexerDef.h"
#define LEX_DEF_INCLUDED
#include "key.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *TerminalString(int index){
    static char *terminalStringTable[EOS+1] =  { "TK_ASSIGNOP", "TK_COMMENT", "TK_FIELDID", "TK_ID", "TK_NUM", "TK_RNUM", "TK_FUNID", "TK_RECORDID", "TK_WITH", "TK_PARAMETERS", "TK_END", "TK_WHILE", "TK_TYPE", "TK_MAIN", "TK_GLOBAL", "TK_PARAMETER", "TK_LIST", "TK_SQL", "TK_SQR", "TK_INPUT", "TK_OUTPUT", "TK_INT", "TK_REAL", "TK_COMMA", "TK_SEM", "TK_COLON", "TK_DOT", "TK_ENDWHILE", "TK_OP", "TK_CL", "TK_IF", "TK_THEN", "TK_ENDIF", "TK_READ", "TK_WRITE", "TK_RETURN", "TK_PLUS", "TK_MINUS", "TK_MUL", "TK_DIV", "TK_CALL", "TK_RECORD", "TK_ENDRECORD", "TK_ELSE", "TK_AND", "TK_OR", "TK_NOT", "TK_LT", "TK_LE", "TK_EQ", "TK_GT", "TK_GE", "TK_NE", "eps", "EOS" };
    return terminalStringTable[index];
}

//Normal return token function with retracting and without 
tokenInfo *return_str_token(char *lexeme, TOKEN tkname, int lineno, bool is_retract, int *input_buffer_pointer){
    tokenInfo *ti = (tokenInfo*)malloc(sizeof(tokenInfo));
    ti->line_no = lineno;
    ti->tokenName = tkname;
    ti->flag = 0;
    ti->u.lexeme = lexeme;
    if(is_retract){
        if(*input_buffer_pointer!=0){
            *input_buffer_pointer=*input_buffer_pointer-1;
        }
    }
    return ti;
}

//id and funid
tokenInfo *return_no_token(char *lexeme, TOKEN tkname, int lineno, bool is_retract, int *input_buffer_pointer){
    tokenInfo *ti = (tokenInfo*)malloc(sizeof(tokenInfo));
    ti->line_no = lineno;
    ti->tokenName = tkname;
    if(tkname==TK_NUM) {
        ti->flag = 1;
        ti->u.value_of_int = atoi(lexeme);
    }
    if(tkname==TK_RNUM){
        ti->flag = 2;
        ti->u.value_of_real = atof(lexeme);
    }
    if(is_retract){
        if(*input_buffer_pointer!=0){
            *input_buffer_pointer=*input_buffer_pointer-1;
        }
    }
    return ti;
}

void length_error(int choice, int line_count){
    if(choice==0) {
       printf("Line %d: Identifier is longer than the prescribed length of 20 characters\n", line_count);
    }
    else if(choice==1) {
        printf("Line %d: Function identifier is longer than the prescribed length of 30 characters\n", line_count);
    }
    else {
        printf("Line %d: Variable is longer than the maximum length of 30 characters\n", line_count);
    }
}

void unknown_pattern(char *arr, int line_num, char ch, int *j, int *input_buffer_pointer){
    arr[*j+1]='\0';
    printf("Line %d: Unknown pattern %s \n",line_num, arr);
    *j=0;
}

void unknown_symbol(char *arr, int line_num, char ch, int *j, int *input_buffer_pointer){
    arr[*j]=ch;
    arr[*j+1]='\0';
    printf("Line %d: Unknown symbol %s \n",line_num, arr);
    *j=0;
    *input_buffer_pointer=*input_buffer_pointer+1;
}  

size_t getStream(FILE *fp){
    size_t no_of_bytes_read1 = fread(input_buffer, sizeof(char), BUF_LENGTH, fp);
    // printf("%d\n", no_of_bytes_read1);
    return no_of_bytes_read1;
}

tokenInfo* getNextToken(FILE *fp){
    //Rough: some implementation left
    //static ints
    static int line_count = 1;
    static int input_buffer_pointer=0;
    static bool global_flag = 0;
    static int flag = 0;
    static size_t no_of_bytes;
    static char temp;

    if(!global_flag){
        input_buffer=(char*)malloc(sizeof(char)*BUF_LENGTH);
        no_of_bytes=getStream(fp);
        global_flag = 1;
    }

    bool exceed_length=0;
    int j=0, state=0;   
    int ch;
    char* lex = (char*)malloc(sizeof(char)*MAX_LENGTH);
    while(1){
        if(input_buffer_pointer==no_of_bytes) {
            if(no_of_bytes==BUF_LENGTH){
                no_of_bytes=getStream(fp);
                input_buffer_pointer=0;
            }else{
                if(state==0 || state==27 || state==28 || state==53 || state==54){
                    // printf("EOF\n");
                }
                else if(transition_table[state][0].flag==1){
                    if(transition_table[state][ch].u.func.is_retract) {
                        if(lex[j-1]=='\n') line_count--;
                        lex[j-1]='\0';
                    }
                    if(transition_table[state][ch].u.func.func_flag==0){
                        if(strlen(lex)>20 && transition_table[state][ch].u.func.tkname==TK_ID) {
                            length_error(0, line_count);
                        }
                        if(exceed_length){
                            length_error(2, line_count);
                        }
                        return return_str_token(lex, transition_table[state][ch].u.func.tkname, line_count, transition_table[state][ch].u.func.is_retract, &input_buffer_pointer);
                    }else if(transition_table[state][ch].u.func.func_flag==1){ //for TK_FIELDID and TK_FUNID
                        hash_elem *k = lookup(lex);
                        if(k->tkname>0){
                            return return_str_token(k->str, k->tkname, line_count, 1, &input_buffer_pointer);
                        }
                        else{
                            if(exceed_length && transition_table[state][ch].u.func.tkname==TK_FUNID) {
                                length_error(1, line_count);
                            }
                            if(exceed_length){
                                length_error(2, line_count);
                            }
                            return return_str_token(lex, transition_table[state][ch].u.func.tkname, line_count, transition_table[state][ch].u.func.is_retract, &input_buffer_pointer);
                        }
                    }else if(transition_table[state][ch].u.func.func_flag==2){
                        if(exceed_length){
                            length_error(2, line_count);
                        }
                        return return_no_token(lex, transition_table[state][ch].u.func.tkname, line_count, transition_table[state][ch].u.func.is_retract, &input_buffer_pointer);
                    }else if(transition_table[state][ch].u.func.func_flag==3){
                        state=0;
                    }
                    else{
                        printf("Error in transition table");
                    }
                }
                else{
                    lex[j]='\0';
                    unknown_pattern(lex, line_count, ch, &j, &input_buffer_pointer);
                }
                free(input_buffer);
                int to_pass = line_count;
                global_flag = 0;
                line_count = 1;
                input_buffer_pointer=0;
                return return_str_token("EOS", EOS, to_pass, 0, &input_buffer_pointer);
            
            }
        }
        ch = input_buffer[input_buffer_pointer];
        if(flag){
            ch=temp;
        }
        if(transition_table[state][ch].flag==0){
            state = transition_table[state][ch].u.state;
            if(exceed_length==0){
                lex[j++]=ch;
            }
            if(flag) flag=0;
            else input_buffer_pointer++;
            if(j==MAX_LENGTH+1) exceed_length=1;
            
            if(ch=='\n') line_count++;
        }else if(transition_table[state][ch].flag==1){
            if(transition_table[state][ch].u.func.is_retract) {
                if(input_buffer_pointer==0){
                    flag=1;
                    temp=lex[j-1];
                }
                if(transition_table[state][ch].u.func.func_flag!=3){
                    if(lex[j-1]=='\n') line_count--;
                    lex[j-1]='\0';
                }
            }
            else lex[j]='\0';
            if(transition_table[state][ch].u.func.func_flag==0){
                if(strlen(lex)>20 && transition_table[state][ch].u.func.tkname==TK_ID) {
                    tokenInfo *t = return_str_token(lex, transition_table[state][ch].u.func.tkname, line_count, transition_table[state][ch].u.func.is_retract, &input_buffer_pointer);
                    length_error(0, line_count);
                    return t;
                }
                if(exceed_length){
                    length_error(2, line_count);
                }
                return return_str_token(lex, transition_table[state][ch].u.func.tkname, line_count, transition_table[state][ch].u.func.is_retract, &input_buffer_pointer);
            }else if(transition_table[state][ch].u.func.func_flag==1){ //for TK_FIELDID and TK_FUNID
                hash_elem *k = lookup(lex);
                if(k->tkname!=0){
                    return return_str_token(k->str, k->tkname, line_count, 1, &input_buffer_pointer);
                }
                else{
                    if(exceed_length && transition_table[state][ch].u.func.tkname==TK_FUNID) {
                        tokenInfo *t = return_str_token(lex, transition_table[state][ch].u.func.tkname, line_count, transition_table[state][ch].u.func.is_retract, &input_buffer_pointer);
                        length_error(1, line_count);
                        return t;
                    }
                    if(exceed_length){
                        length_error(2, line_count);
                    }
                    return return_str_token(lex, transition_table[state][ch].u.func.tkname, line_count, transition_table[state][ch].u.func.is_retract, &input_buffer_pointer);
                }
            }else if(transition_table[state][ch].u.func.func_flag==2){
                if(exceed_length){
                    length_error(2, line_count);
                    continue;
                }
                return return_no_token(lex, transition_table[state][ch].u.func.tkname, line_count, transition_table[state][ch].u.func.is_retract, &input_buffer_pointer);
            }else if(transition_table[state][ch].u.func.func_flag==3){
                // if(ch=='\n') line_count--;
                if(transition_table[state][ch].u.func.is_retract==1) {
                    if(input_buffer_pointer==0){
                        flag=1;
                        temp=lex[j-1];
                    }
                    else input_buffer_pointer--;
                }
                memset(lex, 0, sizeof(char)*MAX_LENGTH);
                j=0;
                state=0;
                exceed_length=0;
            }
            else{
                printf("Error in transition table");
            }
        }else{
            transition_table[state][ch].u.error_function(lex, line_count, ch, &j, &input_buffer_pointer);
            memset(lex, 0, sizeof(char)*MAX_LENGTH);
            state = 0;
            exceed_length=0;
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
