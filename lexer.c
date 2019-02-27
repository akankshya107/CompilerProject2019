#include "lexer.h"
#include <stdlib.h>
TRANSITION_TABLE_ELEM **transition_table;

void populate_transition_table(){
    TRANSITION_TABLE_ELEM **transition_table = (TRANSITION_TABLE_ELEM**)malloc(sizeof(TRANSITION_TABLE_ELEM*)*sizeof(NO_OF_STATES));
    for(int i=0; i<NO_OF_STATES; i++){
        transition_table[i]=(TRANSITION_TABLE_ELEM*)malloc(sizeof(TRANSITION_TABLE_ELEM)*(eps+1));
    }
}