#include "lexerDef.h"
#define LEX_DEF_INCLUDED
#include "key.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
TRANSITION_TABLE_ELEM **transition_table;

char *TerminalString(int index){
    static char *terminalStringTable[EOS+1] =  { "TK_ASSIGNOP", "TK_COMMENT", "TK_FIELDID", "TK_ID", "TK_NUM", "TK_RNUM", "TK_FUNID", "TK_RECORDID", "TK_WITH", "TK_PARAMETERS", "TK_END", "TK_WHILE", "TK_TYPE", "TK_MAIN", "TK_GLOBAL", "TK_PARAMETER", "TK_LIST", "TK_SQL", "TK_SQR", "TK_INPUT", "TK_OUTPUT", "TK_INT", "TK_REAL", "TK_COMMA", "TK_SEM", "TK_COLON", "TK_DOT", "TK_ENDWHILE", "TK_OP", "TK_CL", "TK_IF", "TK_THEN", "TK_ENDIF", "TK_READ", "TK_WRITE", "TK_RETURN", "TK_PLUS", "TK_MINUS", "TK_MUL", "TK_DIV", "TK_CALL", "TK_RECORD", "TK_ENDRECORD", "TK_ELSE", "TK_AND", "TK_OR", "TK_NOT", "TK_LT", "TK_LE", "TK_EQ", "TK_GT", "TK_GE", "TK_NE", "eps", "EOS" };
    return terminalStringTable[index];
}

void populateNonTerminalStringTable(){
    nonTerminalStringTable = (nonterminal_str**)malloc(sizeof(nonterminal_str*)*NO_OF_RULES);
    for(int i=0; i<NO_OF_RULES; i++){
        nonTerminalStringTable[i]=(nonterminal_str*)malloc(sizeof(nonterminal_str));
    }
    //populate
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

void unknown_pattern(char *arr, int line_num){
    printf("Line %d: Unknown pattern %s \n",line_num, arr);
    
}

void unknown_symbol(char *arr, int line_num){
    printf("Line %d: Unknown symbol %s \n",line_num, arr);
    
}

void populate_transition_table(){
    transition_table = (TRANSITION_TABLE_ELEM**)malloc(sizeof(TRANSITION_TABLE_ELEM*)*NO_OF_STATES);
    // printf("lol");
    for(int i=0; i<NO_OF_STATES; i++){
        transition_table[i]=(TRANSITION_TABLE_ELEM*)malloc(sizeof(TRANSITION_TABLE_ELEM)*(128));
        // printf("%p\n", transition_table[i]);
    }
    // printf("L");
    int j;
    for(j=0;j<=127;j++)
    {
        switch(j)
        {
            case ',':{
                transition_table[0][j].u.state=1;
                transition_table[0][j].flag=0;
                break;
            }
            case ';':{
                transition_table[0][j].u.state=2;
                transition_table[0][j].flag=0;
                break;
            }
            case ':':{
                transition_table[0][j].u.state=3;
                transition_table[0][j].flag=0;
                break;
            }
            case '.':{
                transition_table[0][j].u.state=4;
                transition_table[0][j].flag=0;
                break;
            }
            case '(':{
                transition_table[0][j].u.state=5;
                transition_table[0][j].flag=0;
                break;
            }
            case ')':{
                transition_table[0][j].u.state=6;
                transition_table[0][j].flag=0;
                break;
            }
            case '=':{
                transition_table[0][j].u.state=7;
                transition_table[0][j].flag=0;
                break;
            }
            case '~':{
                transition_table[0][j].u.state=9;
                transition_table[0][j].flag=0;
                break;
            }
            case '<':{
                transition_table[0][j].u.state=10;
                transition_table[0][j].flag=0;
                break;
            }
            case '>':{
                transition_table[0][j].u.state=16;
                transition_table[0][j].flag=0;
                break;
            }
            case '!':{
                transition_table[0][j].u.state=19;
                transition_table[0][j].flag=0;
                break;
            }
            case '[':{
                transition_table[0][j].u.state=21;
                transition_table[0][j].flag=0;
                break;
            }
            case ']':{
                transition_table[0][j].u.state=22;
                transition_table[0][j].flag=0;
                break;
            }
            case '+':{
                transition_table[0][j].u.state=23;
                transition_table[0][j].flag=0;
                break;
            }
            case '-':{
                transition_table[0][j].u.state=24;
                transition_table[0][j].flag=0;
                break;
            }
            case '*':{
                transition_table[0][j].u.state=25;
                transition_table[0][j].flag=0;
                break;
            }
            case '/':{
                transition_table[0][j].u.state=26;
                transition_table[0][j].flag=0;
                break;
            }
            case '@':{
                transition_table[0][j].u.state=29;
                transition_table[0][j].flag=0;
                break;
            }

            case '&':{
                transition_table[0][j].u.state=32;
                transition_table[0][j].flag=0;
                break;
            }
            case '#':{
                transition_table[0][j].u.state=41;
                transition_table[0][j].flag=0;
                break;
            }
            case '_':{
                transition_table[0][j].u.state=44;
                transition_table[0][j].flag=0;
                break;
            }
            case '%':{
                transition_table[0][j].u.state=53;
                transition_table[0][j].flag=0;
                break;
            }
            
            default:
            {
                // printf("%d\n", j);
                if((j>='b') && (j<='d'))
                {
                    transition_table[0][j].u.state=35;
                    transition_table[0][j].flag=0;
                }

                else if((j=='a')||(j>'d'&&j<='z'))
                {
                    transition_table[0][j].u.state=39;
                    transition_table[0][j].flag=0;
                }

                else if((j>='0')&&(j<='9'))
                {
                    transition_table[0][j].u.state=48;
                    transition_table[0][j].flag=0;
                }
                else if ((j==' ')||(j=='\t')||(j=='\n'))
                {
                    transition_table[0][j].flag=0;
                    transition_table[0][j].u.state=27;
                }
                else
                {
                    transition_table[0][j].u.error_function=&unknown_symbol;
                    transition_table[0][j].flag=2;
                }
            }
        }
    // // }

    // // for(j=0;j<=127;j++)
    // // {
        transition_table[1][j].u.func.func_flag=0;
        transition_table[1][j].u.func.is_retract=0;
        transition_table[1][j].u.func.tkname=TK_COMMA;
        transition_table[1][j].flag=1;
    // // }
    // // for(j=0;j<=127;j++)
    // // {
        transition_table[2][j].u.func.func_flag=0;
        transition_table[2][j].u.func.is_retract=0;
        transition_table[2][j].u.func.tkname=TK_SEM;
        transition_table[2][j].flag=1;
    // // }
    // // for(j=0;j<=127;j++)
    // // {
        transition_table[3][j].u.func.func_flag=0;
        transition_table[3][j].u.func.is_retract=0;
        transition_table[3][j].u.func.tkname=TK_COLON;
        transition_table[3][j].flag=1;
    // // }
    // // for(j=0;j<=127;j++)
    // // {
        transition_table[4][j].u.func.func_flag=0;
        transition_table[4][j].u.func.is_retract=0;
        transition_table[4][j].u.func.tkname=TK_DOT;
        transition_table[4][j].flag=1;
    // // }
    // // for(j=0;j<=127;j++)
    // // {
        transition_table[5][j].u.func.func_flag=0;
        transition_table[5][j].u.func.is_retract=0;
        transition_table[5][j].u.func.tkname=TK_OP;
        transition_table[5][j].flag=1;
    // // }
    // // for(j=0;j<=127;j++)
    // // {
        transition_table[6][j].u.func.func_flag=0;
        transition_table[6][j].u.func.is_retract=0;
        transition_table[6][j].u.func.tkname=TK_CL;
        transition_table[6][j].flag=1;
    // // }
    // // for(j=0;j<=127;j++)
    // // {
        if(j=='=')
        {
            transition_table[7][j].u.state=8;
            transition_table[7][j].flag=0;
        }
        else
        {
            transition_table[7][j].u.error_function=&unknown_pattern;
            transition_table[7][j].flag=2;
        }

    // // }
    // // for(j=0;j<=127;j++)
    // // {
        transition_table[8][j].u.func.func_flag=0;
        transition_table[8][j].u.func.is_retract=0;
        transition_table[8][j].u.func.tkname=TK_EQ;
        transition_table[8][j].flag=1;
    // // }
    // // for(j=0;j<=127;j++)
    // // {
        transition_table[9][j].u.func.func_flag=0;
        transition_table[9][j].u.func.is_retract=0;
        transition_table[9][j].u.func.tkname=TK_NOT;
        transition_table[9][j].flag=1;
    // // }
    // // for(j=0;j<=127;j++)
    // // {
        if(j=='=')
        {
            transition_table[10][j].u.state=12;
            transition_table[10][j].flag=0;
        }
        else if(j=='-')
        {
            transition_table[10][j].u.state=13;
            transition_table[10][j].flag=0;
        }
        else
        {
            transition_table[10][j].u.state=11;
            transition_table[10][j].flag=0;
        }
        
    // // }
    // // for(j=0;j<=127;j++)
    // // {
        transition_table[11][j].u.func.func_flag=0;
        transition_table[11][j].u.func.is_retract=1;
        transition_table[11][j].u.func.tkname=TK_LT;
        transition_table[11][j].flag=1;
    // // }
    // // for(j=0;j<=127;j++)
    // // {
        transition_table[12][j].u.func.func_flag=0;
        transition_table[12][j].u.func.is_retract=0;
        transition_table[12][j].u.func.tkname=TK_LE;
        transition_table[12][j].flag=1;
    // // }
    // // for(j=0;j<=127;j++)
    // // {
        if(j=='-'){
            transition_table[13][j].u.state=14;
            transition_table[13][j].flag=0;
        }
        else
        {
            transition_table[13][j].u.error_function=&unknown_pattern;
            transition_table[13][j].flag=2;
        }
    // // }

    // // for(j=0;j<=127;j++)
    // // {
        if(j=='-'){
            transition_table[14][j].u.state=15;
            transition_table[14][j].flag=0;}

        else
        {
            transition_table[14][j].u.error_function=&unknown_pattern;
            transition_table[14][j].flag=2;
        }
    // // }
    // // for(j=0;j<=127;j++)
    // // {
        transition_table[15][j].u.func.func_flag=0;
        transition_table[15][j].u.func.is_retract=0;
        transition_table[15][j].u.func.tkname=TK_ASSIGNOP;
        transition_table[15][j].flag=1;
    // // }
    // // for(j=0;j<=127;j++)
    // // {
        if(j=='='){
            transition_table[16][j].u.state=17;
            transition_table[16][j].flag=0;}

        else
        {
            transition_table[16][j].u.state=18;
            transition_table[16][j].flag=0;
        }
    // // }
    // // for(j=0;j<=127;j++)
    // // {
        transition_table[17][j].u.func.func_flag=0;
        transition_table[17][j].u.func.is_retract=0;
        transition_table[17][j].u.func.tkname=TK_GE;
        transition_table[17][j].flag=1;
    // // }

    // // for(j=0;j<=127;j++)
    // // {
        transition_table[18][j].u.func.func_flag=0;
        transition_table[18][j].u.func.is_retract=1;
        transition_table[18][j].u.func.tkname=TK_GT;
        transition_table[18][j].flag=1;
    // // }
    // // for(j=0;j<=127;j++)
    // // {
        if(j=='='){
            transition_table[19][j].u.state=20;
            transition_table[19][j].flag=0;
        }
        else{
            transition_table[19][j].u.error_function=&unknown_pattern;
            transition_table[19][j].flag=2;
        }
    // // }
    // // for(j=0;j<=127;j++)
    // // {
        transition_table[20][j].u.func.func_flag=0;
        transition_table[20][j].u.func.is_retract=0;
        transition_table[20][j].u.func.tkname=TK_NE;
        transition_table[20][j].flag=1;
    // // }
    // // for(j=0;j<=127;j++)
    // // {
        transition_table[21][j].u.func.func_flag=0;
        transition_table[21][j].u.func.is_retract=0;
        transition_table[21][j].u.func.tkname=TK_SQL;
        transition_table[21][j].flag=1;
    // // }
    // // for(j=0;j<=127;j++)
    // // {
        transition_table[22][j].u.func.func_flag=0;
        transition_table[22][j].u.func.is_retract=0;
        transition_table[22][j].u.func.tkname=TK_SQR;
        transition_table[22][j].flag=1;
    // // }
    // // for(j=0;j<=127;j++)
    // // {
        transition_table[23][j].u.func.func_flag=0;
        transition_table[23][j].u.func.is_retract=0;
        transition_table[23][j].u.func.tkname=TK_PLUS;
        transition_table[23][j].flag=1;
    // // }
    // // for(j=0;j<=127;j++)
    // // {
        transition_table[24][j].u.func.func_flag=0;
        transition_table[24][j].u.func.is_retract=0;
        transition_table[24][j].u.func.tkname=TK_MINUS;
        transition_table[24][j].flag=1;
    // // }
    // // for(j=0;j<=127;j++)
    // // {
        transition_table[25][j].u.func.func_flag=0;
        transition_table[25][j].u.func.is_retract=0;
        transition_table[25][j].u.func.tkname=TK_MUL;
        transition_table[25][j].flag=1;
    // // }
    // // for(j=0;j<=127;j++)
    // // {
        transition_table[26][j].u.func.func_flag=0;
        transition_table[26][j].u.func.is_retract=0;
        transition_table[26][j].u.func.tkname=TK_DIV;
        transition_table[26][j].flag=1;
    // // }
    // // for(j=0; j<=127; j++){
        if ((j==' ')||(j=='\t')||(j=='\n'))
        {
            transition_table[27][j].flag=0;
            transition_table[27][j].u.state=27;
        }
        else{
            transition_table[27][j].flag=0;
            transition_table[27][j].u.state=28;
        }
    // // }
    // // for(j=0; j<=127; j++){
        transition_table[28][j].flag=1;
        transition_table[28][j].u.func.func_flag=3;
        transition_table[28][j].u.func.is_retract=1;
        transition_table[28][j].u.func.tkname=eps;
    // // }
    // // for(j=0;j<=127;j++)
    // // {
        if(j=='@')
        {
            transition_table[29][j].flag=0;
            transition_table[29][j].u.state=30;
        }
        else
        {
            transition_table[29][j].flag=2;
            transition_table[29][j].u.error_function=&unknown_pattern;
        }
    // // }
    // // for(j=0;j<=127;j++)
    // // {
        if(j=='@')
        {
            transition_table[30][j].flag=0;
            transition_table[30][j].u.state=31;
        }
        else
        {
            transition_table[30][j].flag=2;
            transition_table[30][j].u.error_function=&unknown_pattern;
        }           
    // // }
    // // for(j=0;j<=127;j++)
    // // {
        transition_table[31][j].flag=1;
        transition_table[31][j].u.func.func_flag=0;
        transition_table[31][j].u.func.is_retract=0;
        transition_table[31][j].u.func.tkname=TK_OR;
    // // }
    // // for(j=0;j<=127;j++)
    // // {
        if(j=='&')
        {
            transition_table[32][j].flag=0;
            transition_table[32][j].u.state=33;
        }
        else
        {
            transition_table[32][j].flag=2;
            transition_table[32][j].u.error_function=&unknown_pattern;
        }           
    // // }
    // // for(j=0;j<=127;j++)
    // {
        if(j=='&')
        {
            transition_table[33][j].flag=0;
            transition_table[33][j].u.state=34;
        }
        else
        {
            transition_table[33][j].flag=2;
            transition_table[33][j].u.error_function=&unknown_pattern;

        }           
    // // }
    // // for(j=0;j<=127;j++)
    // // {
        transition_table[34][j].flag=1;
        transition_table[34][j].u.func.func_flag=0;
        transition_table[34][j].u.func.is_retract=0;
        transition_table[34][j].u.func.tkname=TK_AND;
    // // }
    // // for(j=0;j<=127;j++)
    // // {
        if((j<='7')&&(j>='2'))
        {
            transition_table[35][j].flag=0;
            transition_table[35][j].u.state=36;
        }
        else if ((j>='a')&&(j<='z'))
        {
            transition_table[35][j].flag=0;
            transition_table[35][j].u.state=39;
        } 
        else
        {
            transition_table[35][j].flag=0;
            transition_table[35][j].u.state=40;
        }
    // // }
    // // for(j=0;j<=127;j++)
    // // {
        if((j<='7')&&(j>='2'))
        {
            transition_table[36][j].flag=0;
            transition_table[36][j].u.state=37;
        }
        else if ((j>='b')&&(j<='d'))
        {
            transition_table[36][j].flag=0;
            transition_table[36][j].u.state=36;
        }
        else 
        {
            transition_table[36][j].flag=0;
            transition_table[36][j].u.state=38; 
        }          
    // // }
    // // for(j=0;j<=127;j++)
    // // {
        if((j<='7')&&(j>='2'))
        {
            transition_table[37][j].flag=0;
            transition_table[37][j].u.state=37;
        }
        else 
        {
            transition_table[37][j].flag=0;
            transition_table[37][j].u.state=38; 
        }          
    // // }
    // // for(j=0;j<=127;j++)
    // // {
        transition_table[38][j].flag=1;
        transition_table[38][j].u.func.func_flag=0;
        transition_table[38][j].u.func.is_retract=1;
        transition_table[38][j].u.func.tkname=TK_ID;
    // // }
    // // for(j=0;j<=127;j++)
    // // {
        if((j<='z')&&(j>='a'))
        {
            transition_table[39][j].flag=0;
            transition_table[39][j].u.state=39;
        }
        else
        {
            transition_table[39][j].flag=0;
            transition_table[39][j].u.state=40;
        }
    // // }
    // // for (j=0;j<=127;j++)
    // // {
        transition_table[40][j].flag=1;
        transition_table[40][j].u.func.func_flag=1;
        transition_table[40][j].u.func.is_retract=1;
        transition_table[40][j].u.func.tkname=TK_FIELDID;
    // // }
    // // for(j=0;j<=127;j++)
    // // {
        if((j<='z')&&(j>='a'))
        {
            transition_table[41][j].flag=0;
            transition_table[41][j].u.state=42;
        }
        else
        {
            transition_table[41][j].flag=2;
            transition_table[41][j].u.error_function=&unknown_pattern;
        }
    // // }
    // // for(j=0;j<=127;j++)
    // // {
        if((j<='z')&&(j>='a'))
        {
            transition_table[42][j].flag=0;
            transition_table[42][j].u.state=42;
        }
        else
        {
            transition_table[42][j].flag=0;
            transition_table[42][j].u.state=43;
        }
    // // }
    // // for (j=0;j<=127;j++)
    // // {
        transition_table[43][j].flag=1;
        transition_table[43][j].u.func.func_flag=0;
        transition_table[43][j].u.func.is_retract=1;
        transition_table[43][j].u.func.tkname=TK_RECORDID;
    // // }
    // // for(j=0;j<=127;j++)
    // //     {
        if(((j<='z')&&(j>='a'))||((j>='A')&&(j<='Z')))
        {
            transition_table[44][j].flag=0;
            transition_table[44][j].u.state=45;
        }
        else
        {
            transition_table[44][j].flag=2;
            transition_table[44][j].u.error_function=&unknown_pattern;
        }
    // //     }
    // // for(j=0;j<=127;j++)
    // // {
        if(((j<='z')&&(j>='a'))||((j>='A')&&(j<='Z')))
        {
            transition_table[45][j].flag=0;
            transition_table[45][j].u.state=45;
        }
        else if ((j>='0')&&(j<='9'))
        {
            transition_table[45][j].flag=0;
            transition_table[45][j].u.state=46;
        }
        else
        {
            transition_table[45][j].flag=0;
            transition_table[45][j].u.state=47;
        }
    // // }
    // // for(j=0;j<=127;j++)
    // // {
        if ((j>='0')&&(j<='9'))
        {
            transition_table[46][j].flag=0;
            transition_table[46][j].u.state=46;
        }
        else
        {
            transition_table[46][j].flag=0;
            transition_table[46][j].u.state=47;
        }
    // // }
    // // for (j=0;j<=127;j++)
    // // {
        transition_table[47][j].flag=1;
        transition_table[47][j].u.func.func_flag=1;
        transition_table[47][j].u.func.is_retract=1;
        transition_table[47][j].u.func.tkname=TK_FUNID;
    // // }
    // // for(j=0;j<=127;j++)
    // // {
        if ((j>='0')&&(j<='9'))
        {
            transition_table[48][j].flag=0;
            transition_table[48][j].u.state=48;
        }
        else if (j=='.')
        {
            transition_table[48][j].flag=0;
            transition_table[48][j].u.state=50;
        }
        else
        {
            transition_table[48][j].flag=0;
            transition_table[48][j].u.state=49;
        }
    // // }
    // // for (j=0;j<=127;j++)
    // // {
        transition_table[49][j].flag=1;
        transition_table[49][j].u.func.func_flag=2;
        transition_table[49][j].u.func.is_retract=1;
        transition_table[49][j].u.func.tkname=TK_NUM;
    // // }
    // // for(j=0;j<=127;j++)
    // // {
        if ((j>='0')&&(j<='9'))
        {
            transition_table[50][j].flag=0;
            transition_table[50][j].u.state=51;
        }
        else
        {
            transition_table[50][j].flag=2;
            transition_table[50][j].u.error_function=&unknown_pattern;
        }
    // // }
    // // for(j=0;j<=127;j++)
    // // {
        if ((j>='0')&&(j<='9'))
        {
            transition_table[51][j].flag=0;
            transition_table[51][j].u.state=52;
        }
        else
        {
            transition_table[51][j].flag=2;
            transition_table[51][j].u.error_function=&unknown_pattern;
        }
    // // }
    // // for (j=0;j<=127;j++)
    // // {
        transition_table[52][j].flag=1;
        transition_table[52][j].u.func.func_flag=2;
        transition_table[52][j].u.func.is_retract=0;
        transition_table[52][j].u.func.tkname=TK_RNUM;
    // // }
    // // for(j=0;j<=127;j++)
    // // {
        if ((j=='\n')||(j==' '))
        {
            transition_table[53][j].flag=0;
            transition_table[53][j].u.state=54;
        }

        else
        {
            transition_table[53][j].flag=0;
            transition_table[53][j].u.state=53;
        }
    // // }
    // // for (j=0;j<=127;j++)
    // // {
        transition_table[54][j].flag=0;
        transition_table[54][j].u.state=0;
    }
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
    static size_t no_of_bytes;

    if(!global_flag){
        input_buffer=(char*)malloc(sizeof(char)*BUF_LENGTH);
        no_of_bytes=getStream(fp);
        global_flag = 1;
    }

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
                    lex[j]='\0';
                    if(transition_table[state][ch].u.func.func_flag==0){
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
                    }else if(transition_table[state][ch].u.func.func_flag==3){
                        state=0;
                    }
                    else{
                        printf("Error in transition table");
                    }
                }
                else{
                    lex[j]='\0';
                    unknown_pattern(lex, line_count);
                }
                return return_str_token("EOS", EOS, line_count, 0, &input_buffer_pointer);
            
            }
        }
        ch = input_buffer[input_buffer_pointer];
        if(transition_table[state][ch].flag==0){
            state = transition_table[state][ch].u.state;
            lex[j++]=ch;
            input_buffer_pointer++;
            if(ch=='\n') line_count++;
        }else if(transition_table[state][ch].flag==1){
            if(transition_table[state][ch].u.func.is_retract) {
                if(lex[j-1]=='\n') line_count--;
                lex[j-1]='\0';
            }
            else lex[j]='\0';
            if(transition_table[state][ch].u.func.func_flag==0){
                return return_str_token(lex, transition_table[state][ch].u.func.tkname, line_count, transition_table[state][ch].u.func.is_retract, &input_buffer_pointer);
            }else if(transition_table[state][ch].u.func.func_flag==1){ //for TK_FIELDID and TK_FUNID
                hash_elem *k = lookup(lex);
                if(k->tkname!=0){
                    return return_str_token(k->str, k->tkname, line_count, 1, &input_buffer_pointer);
                }
                else{
                    return return_str_token(lex, transition_table[state][ch].u.func.tkname, line_count, transition_table[state][ch].u.func.is_retract, &input_buffer_pointer);
                }
            }else if(transition_table[state][ch].u.func.func_flag==2){
                return return_no_token(lex, transition_table[state][ch].u.func.tkname, line_count, transition_table[state][ch].u.func.is_retract, &input_buffer_pointer);
            }else if(transition_table[state][ch].u.func.func_flag==3){
                state=0;
                memset(lex, 0, sizeof(char)*MAX_LENGTH);
                j=0;
                input_buffer_pointer--;
            }
            else{
                printf("Error in transition table");
            }
        }else{
            lex[j-1]='\0';
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
