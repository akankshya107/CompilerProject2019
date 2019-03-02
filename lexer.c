#include "lexerDef.h"
#define LEX_DEF_INCLUDED
#include "key.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
TRANSITION_TABLE_ELEM **transition_table;

//Normal return token function with retracting and without 
tokenInfo *return_str_token(char *lexeme, TOKEN tkname, int lineno, bool is_retract, int *input_buffer_pointer){
    tokenInfo *ti = (tokenInfo*)malloc(sizeof(tokenInfo));
    ti->line_no = lineno;
    ti->tokenName = tkname;
    ti->flag = 0;
    ti->u.lexeme = lexeme;
    if(!is_retract){
        if(*input_buffer_pointer!=0){
            input_buffer_pointer++;
        }
    }
    return ti;
}

//id and funid
tokenInfo *return_no_token(char *lexeme, TOKEN tkname, int lineno, bool is_retract, int *input_buffer_pointer){
    tokenInfo *ti = (tokenInfo*)malloc(sizeof(tokenInfo));
    ti->line_no = lineno;
    ti->tokenName = tkname;
    if(tkname==TK_INT) {
        ti->flag = 1;
        ti->u.value_of_int = atoi(lexeme);
    }
    if(tkname==TK_RNUM){
        ti->flag = 2;
        ti->u.value_of_real = atof(lexeme);
    }
    if(!is_retract){
        if(*input_buffer_pointer!=0){
            input_buffer_pointer++;
        }
    }
    return ti;
}

void populate_transition_table(){
    TRANSITION_TABLE_ELEM **transition_table = (TRANSITION_TABLE_ELEM**)malloc(sizeof(TRANSITION_TABLE_ELEM*)*sizeof(NO_OF_STATES));
    for(int i=0; i<NO_OF_STATES; i++){
        transition_table[i]=(TRANSITION_TABLE_ELEM*)malloc(sizeof(TRANSITION_TABLE_ELEM)*(128));
    }
//     int j;
//     for(j=0;j<=127;j++)
//     {
//         switch(j)
//         {
//             case ',':{
//                 transition_table[0][j].u.state=1;
//                 transition_table[0][j].flag=0;
//                 break;
//             }
//             case ';':{
//                 transition_table[0][j].u.state=2;
//                 transition_table[0][j].flag=0;
//                 break;
//             }
//             case ':':{
//                 transition_table[0][j].u.state=3;
//                 transition_table[0][j].flag=0;
//                 break;
//             }
//             case '.':{
//                 transition_table[0][j].u.state=4;
//                 transition_table[0][j].flag=0;
//                 break;
//             }
//             case '(':{
//                 transition_table[0][j].u.state=5;
//                 transition_table[0][j].flag=0;
//                 break;
//             }
//             case ')':{
//                 transition_table[0][j].u.state=6;
//                 transition_table[0][j].flag=0;
//                 break;
//             }
//             case '=':{
//                 transition_table[0][j].u.state=7;
//                 transition_table[0][j].flag=0;
//                 break;
//             }
//             case '~':{
//                 transition_table[0][j].u.state=9;
//                 transition_table[0][j].flag=0;
//                 break;
//             }
//             case '<':{
//                 transition_table[0][j].u.state=10;
//                 transition_table[0][j].flag=0;
//                 break;
//             }
//             case '>':{
//                 transition_table[0][j].u.state=16;
//                 transition_table[0][j].flag=0;
//                 break;
//             }
//             case '!':{
//                 transition_table[0][j].u.state=19;
//                 transition_table[0][j].flag=0;
//                 break;
//             }
//             case '[':{
//                 transition_table[0][j].u.state=21;
//                 transition_table[0][j].flag=0;
//                 break;
//             }
//             case ']':{
//                 transition_table[0][j].u.state=22;
//                 transition_table[0][j].flag=0;
//                 break;
//             }
//             case '+':{
//                 transition_table[0][j].u.state=23;
//                 transition_table[0][j].flag=0;
//                 break;
//             }
//             case '-':{
//                 transition_table[0][j].u.state=24;
//                 transition_table[0][j].flag=0;
//                 break;
//             }
//             case '*':{
//                 transition_table[0][j].u.state=25;
//                 transition_table[0][j].flag=0;
//                 break;
//             }
//             case '/':{
//                 transition_table[0][j].u.state=26;
//                 transition_table[0][j].flag=0;
//                 break;
//             }
//             case '@':{
//                 transition_table[0][j].u.state=29;
//                 transition_table[0][j].flag=0;
//                 break;
//             }

//             case '&':{
//                 transition_table[0][j].u.state=32;
//                 transition_table[0][j].flag=0;
//                 break;
//             }
//             case '#':{
//                 transition_table[0][j].u.state=41;
//                 transition_table[0][j].flag=0;
//                 break;
//             }
//             case '_':{
//                 transition_table[0][j].u.state=44;
//                 transition_table[0][j].flag=0;
//                 break;
//             }
//             case '%':{
//                 transition_table[0][j].u.state=53;
//                 transition_table[0][j].flag=0;
//                 break;
//             }
            
//             default:
//             {
//                 if(j>='b'&&j<='d')
//                 {
//                     transition_table[0][j].u.state=35;
//                     transition_table[0][j].flag=0;
//                 }

//                 else if(j=='a'||(j>'d'&&j<='z'))
//                 {
//                     transition_table[0][j].u.state=39;
//                     transition_table[0][j].flag=0;
//                 }

//                 else if(j>='0'&&j<='9')
//                 {
//                     transition_table[0][j].u.state=48;
//                     transition_table[0][j].flag=0;
//                 }
//                 else if(j==9||j==10||j==13||j==32)
//                 {
//                     transition_table[0][j].u.state=27;
//                     transition_table[0][j].flag=0;
//                 }

//                 else
//                 {
//                     transition_table[0][j].u.error_function=&symbol_not_found;
//                     transition_table[0][j].flag=2;
//                 }
        
//             }
            

//         }
//     }

//     for(j=0;j<=127;j++)
//     {
//         transition_table[1][j].u.return_token_function=&return_token;
//         transition_table[1][j].flag=1;
//     }

//     for(j=0;j<=127;j++)
//     {
//         transition_table[2][j].u.return_token_function=&return_token;
//         transition_table[2][j].flag=1;
//     }

//     for(j=0;j<=127;j++)
//     {
//         transition_table[3][j].u.return_token_function=&return_token;
//         transition_table[3][j].flag=1;
//     }
//     for(j=0;j<=127;j++)
//     {
//         transition_table[4][j].u.return_token_function=&return_token;
//         transition_table[4][j].flag=1;
//     }
//     for(j=0;j<=127;j++)
//     {
//         transition_table[5][j].u.return_token_function=&return_token;
//         transition_table[5][j].flag=1;
//     }
//     for(j=0;j<=127;j++)
//     {
//         transition_table[6][j].u.return_token_function=&return_token;
//         transition_table[6][j].flag=1;
//     }
//     for(j=0;j<=127;j++)
//     {
//         if(j=='=')
//         {
//             transition_table[7][j].u.state=8;
//             transition_table[7][j].flag=0;
//         }
//         else
//         {
//             transition_table[7][j].u.error_function=&symbol_not_found;
//             transition_table[7][j].flag=2;
//         }

//     }
//     for(j=0;j<=127;j++)
//     {
//         transition_table[8][j].u.return_token_function=&return_token;
//         transition_table[8][j].flag=1;
//     }
//     for(j=0;j<=127;j++)
//     {
//         transition_table[9][j].u.return_token_function=&return_token;
//         transition_table[9][j].flag=1;
//     }
//     for(j=0;j<=127;j++)
//     {
//         if(j=='=')
//         {
//             transition_table[10][j].u.state=12;
//             transition_table[10][j].flag=0;
//         }

//         else if(j=='-'){
//         transition_table[10][j].u.state=13;
//         transition_table[10][j].flag=0;}
//         else
//         {
//             transition_table[10][j].u.state=11;
//             transition_table[10][j].flag=0;
//         }
        
//     }
//     for(j=0;j<=127;j++)
//     {
//         transition_table[11][j].u.return_token_function=&return_token;
//         transition_table[11][j].flag=1;
//     }
//     for(j=0;j<=127;j++)
//     {
//         transition_table[12][j].u.return_token_function=&return_token;
//         transition_table[12][j].flag=1;
//     }
//     for(j=0;j<=127;j++)
//     {
//         if(j=='-'){
//         transition_table[13][j].u.state=14;
//         transition_table[13][j].flag=0;}

//         else
//         {
//             transition_table[13][j].u.error_function=&symbol_not_found;
//             transition_table[13][j].flag=2;
//         }
//     }

//     for(j=0;j<=127;j++)
//     {
//         if(j=='-'){
//         transition_table[14][j].u.state=15;
//         transition_table[14][j].flag=0;}

//         else
//         {
//             transition_table[14][j].u.error_function=&symbol_not_found;
//             transition_table[14][j].flag=2;
//         }
//     }
//     for(j=0;j<=127;j++)
//     {
//         transition_table[15][j].u.return_token_function=&return_token;
//         transition_table[15][j].flag=1;
//     }
//     for(j=0;j<=127;j++)
//     {
//         if(j=='='){
//         transition_table[16][j].u.state=17;
//         transition_table[16][j].flag=0;}

//         else
//         {
//             transition_table[16][j].u.error_function=&symbol_not_found;
//             transition_table[16][j].flag=2;
//         }
//     }
//     for(j=0;j<=127;j++)
//     {
//         transition_table[17][j].u.return_token_function=&return_token;
//         transition_table[17][j].flag=1;
//     }

//     for(j=0;j<=127;j++)
//     {
//         transition_table[18][j].u.return_token_function=&return_token;
//         transition_table[18][j].flag=1;
//     }
//     for(j=0;j<=127;j++)
//     {
//         if(j=='='){
//         transition_table[19][j].u.state=20;
//         transition_table[19][j].flag=0;}

//         else
//         {
//             transition_table[19][j].u.error_function=&symbol_not_found;
//             transition_table[19][j].flag=2;
//         }
//     }
//     for(j=0;j<=127;j++)
//     {
//         transition_table[20][j].u.return_token_function=&return_token;
//         transition_table[20][j].flag=1;
//     }
//     for(j=0;j<=127;j++)
//     {
//         transition_table[21][j].u.return_token_function=&return_token;
//         transition_table[21][j].flag=1;
//     }
//     for(j=0;j<=127;j++)
//     {
//         transition_table[22][j].u.return_token_function=&return_token;
//         transition_table[22][j].flag=1;
//     }
//     for(j=0;j<=127;j++)
//     {
//         transition_table[23][j].u.return_token_function=&return_token;
//         transition_table[23][j].flag=1;
//     }
//     for(j=0;j<=127;j++)
//     {
//         transition_table[24][j].u.return_token_function=&return_token;
// transition_table[24][j].flag=1;
//     }
//     for(j=0;j<=127;j++)
//     {
//         transition_table[25][j].u.return_token_function=&return_token;
//         transition_table[25][j].flag=1;
//     }
//     for(j=0;j<=127;j++)
//     {
//         transition_table[26][j].u.return_token_function=&return_token;
//         transition_table[26][j].flag=1;
//     }
    

}

void *getStream(FILE *fp){
    size_t no_of_bytes_read1 = fread(input_buffer, sizeof(char), BUF_LENGTH, fp);
    return fp;
}

tokenInfo* getNextToken(FILE *fp){
    //Rough: some implementation left
    //static ints
    static int line_count = 0;
    static int input_buffer_pointer=0;
    static bool global_flag = 0;

    if(!global_flag){
        getStream(fp);
        global_flag = 1;
    }

    int j=0, state=0;   
    int ch;
    char* lex = (char*)malloc(sizeof(char)*MAX_LENGTH);
    while(1){
        if(input_buffer_pointer==BUF_LENGTH) {
            getStream(fp);
            input_buffer_pointer=0;
        }
        ch = input_buffer[input_buffer_pointer];
        if(ch=='\n') line_count++;
        if(transition_table[state][ch].flag==0){
            state = transition_table[state][ch].u.state;
            lex[j++]=ch;
            input_buffer_pointer++;
        }else if(transition_table[state][ch].flag==1){
            if(transition_table[state][ch].u.func.func_flag==0){
                lex[j]='\0';
                return return_str_token(lex, transition_table[state][ch].u.func.tkname, line_count, transition_table[state][ch].u.func.is_retract, &input_buffer_pointer);
            }else if(transition_table[state][ch].u.func.func_flag==1){ //for TK_FIELDID and TK_FUNID
                hash_elem *k = lookup(lex);
                if(k->tkname>0){
                    return return_str_token(k->str, k->tkname, line_count, 1, &input_buffer_pointer);
                }
                else{
                    return return_str_token(lex, transition_table[state][ch].u.func.tkname, line_count, transition_table[state][ch].u.func.is_retract, &input_buffer_pointer);
                }
            }else if(transition_table[state][ch].u.func.func_flag==2){
                return return_no_token(lex, transition_table[state][ch].u.func.tkname, line_count, transition_table[state][ch].u.func.is_retract, &input_buffer_pointer);
            }else{
                printf("Error in transition table");
            }
        }else{
            transition_table[state][ch].u.error_function(lex, line_count);
            memset(lex, 0, sizeof(char)*MAX_LENGTH);
            j=0;
            state = 0;
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
