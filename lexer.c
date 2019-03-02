#include "lexerDef.h"
#define LEX_DEF_INCLUDED
#include<stdio.h>
#include <stdlib.h>
TRANSITION_TABLE_ELEM **transition_table;


void symbol_not_found()
{
    printf("Symbol not Found");
}

tokenInfo* return_token(char* c){

}

void populate_transition_table(){
    TRANSITION_TABLE_ELEM **transition_table;
    transition_table = (TRANSITION_TABLE_ELEM**)malloc(sizeof(TRANSITION_TABLE_ELEM*)*sizeof(NO_OF_STATES));
    for(int i=0; i<NO_OF_STATES; i++){
        transition_table[i]=(TRANSITION_TABLE_ELEM*)malloc(sizeof(TRANSITION_TABLE_ELEM)*(128));
    }
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
                if(j>='b'&&j<='d')
                {
                    transition_table[0][j].u.state=35;
                    transition_table[0][j].flag=0;
                }

                else if(j=='a'||(j>'d'&&j<='z'))
                {
                    transition_table[0][j].u.state=39;
                    transition_table[0][j].flag=0;
                }

                else if(j>='0'&&j<='9')
                {
                    transition_table[0][j].u.state=48;
                    transition_table[0][j].flag=0;
                }
                else if(j==9||j==10||j==13||j==32)
                {
                    transition_table[0][j].u.state=27;
                    transition_table[0][j].flag=0;
                }

                else
                {
                    transition_table[0][j].u.error_function=&symbol_not_found;
                    transition_table[0][j].flag=2;
                }
        
            }
            

        }
    }

    for(j=0;j<=127;j++)
    {
        transition_table[1][j].u.return_token_function=&return_token;
        transition_table[1][j].flag=1;
    }

    for(j=0;j<=127;j++)
    {
        transition_table[2][j].u.return_token_function=&return_token;
        transition_table[2][j].flag=1;
    }

    for(j=0;j<=127;j++)
    {
        transition_table[3][j].u.return_token_function=&return_token;
        transition_table[3][j].flag=1;
    }
    for(j=0;j<=127;j++)
    {
        transition_table[4][j].u.return_token_function=&return_token;
        transition_table[4][j].flag=1;
    }
    for(j=0;j<=127;j++)
    {
        transition_table[5][j].u.return_token_function=&return_token;
        transition_table[5][j].flag=1;
    }
    for(j=0;j<=127;j++)
    {
        transition_table[6][j].u.return_token_function=&return_token;
        transition_table[6][j].flag=1;
    }
    for(j=0;j<=127;j++)
    {
        if(j=='=')
        {
            transition_table[7][j].u.state=8;
            transition_table[7][j].flag=0;
        }
        else
        {
            transition_table[7][j].u.error_function=&symbol_not_found;
            transition_table[7][j].flag=2;
        }

    }
    for(j=0;j<=127;j++)
    {
        transition_table[8][j].u.return_token_function=&return_token;
        transition_table[8][j].flag=1;
    }
    for(j=0;j<=127;j++)
    {
        transition_table[9][j].u.return_token_function=&return_token;
        transition_table[9][j].flag=1;
    }
    for(j=0;j<=127;j++)
    {
        if(j=='=')
        {
            transition_table[10][j].u.state=12;
            transition_table[10][j].flag=0;
        }

        else if(j=='-'){
        transition_table[10][j].u.state=13;
        transition_table[10][j].flag=0;}
        else
        {
            transition_table[10][j].u.state=11;
            transition_table[10][j].flag=0;
        }
        
    }
    for(j=0;j<=127;j++)
    {
        transition_table[11][j].u.return_token_function=&return_token;
        transition_table[11][j].flag=1;
    }
    for(j=0;j<=127;j++)
    {
        transition_table[12][j].u.return_token_function=&return_token;
        transition_table[12][j].flag=1;
    }
    for(j=0;j<=127;j++)
    {
        if(j=='-'){
        transition_table[13][j].u.state=14;
        transition_table[13][j].flag=0;}

        else
        {
            transition_table[13][j].u.error_function=&symbol_not_found;
            transition_table[13][j].flag=2;
        }
    }

    for(j=0;j<=127;j++)
    {
        if(j=='-'){
        transition_table[14][j].u.state=15;
        transition_table[14][j].flag=0;}

        else
        {
            transition_table[14][j].u.error_function=&symbol_not_found;
            transition_table[14][j].flag=2;
        }
    }
    for(j=0;j<=127;j++)
    {
        transition_table[15][j].u.return_token_function=&return_token;
        transition_table[15][j].flag=1;
    }
    for(j=0;j<=127;j++)
    {
        if(j=='='){
        transition_table[16][j].u.state=17;
        transition_table[16][j].flag=0;}

        else
        {
            transition_table[16][j].u.error_function=&symbol_not_found;
            transition_table[16][j].flag=2;
        }
    }
    for(j=0;j<=127;j++)
    {
        transition_table[17][j].u.return_token_function=&return_token;
        transition_table[17][j].flag=1;
    }

    for(j=0;j<=127;j++)
    {
        transition_table[18][j].u.return_token_function=&return_token;
        transition_table[18][j].flag=1;
    }
    for(j=0;j<=127;j++)
    {
        if(j=='='){
        transition_table[19][j].u.state=20;
        transition_table[19][j].flag=0;}

        else
        {
            transition_table[19][j].u.error_function=&symbol_not_found;
            transition_table[19][j].flag=2;
        }
    }
    for(j=0;j<=127;j++)
    {
        transition_table[20][j].u.return_token_function=&return_token;
        transition_table[20][j].flag=1;
    }
    for(j=0;j<=127;j++)
    {
        transition_table[21][j].u.return_token_function=&return_token;
        transition_table[21][j].flag=1;
    }
    for(j=0;j<=127;j++)
    {
        transition_table[22][j].u.return_token_function=&return_token;
        transition_table[22][j].flag=1;
    }
    for(j=0;j<=127;j++)
    {
        transition_table[23][j].u.return_token_function=&return_token;
        transition_table[23][j].flag=1;
    }
    for(j=0;j<=127;j++)
    {
        transition_table[24][j].u.return_token_function=&return_token;
        transition_table[24][j].flag=1;
    }
    for(j=0;j<=127;j++)
    {
        transition_table[25][j].u.return_token_function=&return_token;
        transition_table[25][j].flag=1;
    }
    for(j=0;j<=127;j++)
    {
        transition_table[26][j].u.return_token_function=&return_token;
        transition_table[26][j].flag=1;
    }
    

}

FILE *getStream(FILE *fp){
    size_t no_of_bytes_read = fread(input_buffer, sizeof(char), 512, fp);
    return fp;
}
