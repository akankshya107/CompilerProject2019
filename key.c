// GROUP 39
// AKANKSHYA MISHRA 2016A7PS0026P
// NARAPAREDDY BHAVANA 2016A7PS0034P
// KARABEE BATTA 2016A7PS0052P
// AASTHA KATARIA 2016A7PS0062P
#include "key.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int hash(char *str){
	long unsigned int sum = 0;
	long unsigned int a = 8;
	for (int i=0; i<strlen(str); i++){
		sum=(sum*a+str[i])%41;
	}
	return sum;
}

hash_elem *create_hash_elem(int tkname, char *str){
    hash_elem *h = (hash_elem*)malloc(sizeof(hash_elem));
    h->str = str;
    h->tkname = tkname;
    h->next=NULL;
    return h;
}

void insertIntoHT(hash_elem *elem){
    int index = hash(elem->str);
    if(KeyWordTable[index]->next==NULL){
        KeyWordTable[index]->next=elem;
    }
    else{
        hash_elem *ptr = KeyWordTable[index]->next;
        while(ptr->next!=NULL){
            ptr=ptr->next;
        }
        ptr->next=elem;
    }
}

void populateKeyWordTable(){
    KeyWordTable = (hTable)malloc(sizeof(hash_elem*)*43);
    for(int i=0; i<43; i++){
        KeyWordTable[i]=create_hash_elem(0, "none");
    }
    int index;
    //populate this
    //with
    insertIntoHT(create_hash_elem(TK_WITH, "with"));

    //parameters
    insertIntoHT(create_hash_elem(TK_PARAMETERS, "parameters"));

    //end
    insertIntoHT(create_hash_elem(TK_END, "end"));

    //while
    insertIntoHT(create_hash_elem(TK_WHILE, "while"));

    //type
    insertIntoHT(create_hash_elem(TK_TYPE, "type"));

    //main
    insertIntoHT(create_hash_elem(TK_MAIN, "_main"));

    //global
    insertIntoHT(create_hash_elem(TK_GLOBAL, "global"));

    //parameter
    insertIntoHT(create_hash_elem(TK_PARAMETER, "parameter"));

    //list
    insertIntoHT(create_hash_elem(TK_LIST, "list"));

    //input
    insertIntoHT(create_hash_elem(TK_INPUT, "input"));

    //output
    insertIntoHT(create_hash_elem(TK_OUTPUT, "output"));

    //int 
    insertIntoHT(create_hash_elem(TK_INT, "int"));

    //real
    insertIntoHT(create_hash_elem(TK_REAL, "real"));

    //endwhile
    insertIntoHT(create_hash_elem(TK_ENDWHILE, "endwhile"));

    //if
    insertIntoHT(create_hash_elem(TK_IF, "if"));

    //then
    insertIntoHT(create_hash_elem(TK_THEN, "then"));

    //endif
    insertIntoHT(create_hash_elem(TK_ENDIF, "endif"));

    //read
    insertIntoHT(create_hash_elem(TK_READ, "read"));

    //write 
    insertIntoHT(create_hash_elem(TK_WRITE, "write"));

    //return
    insertIntoHT(create_hash_elem(TK_RETURN, "return"));

    //call
    insertIntoHT(create_hash_elem(TK_CALL, "call"));

    //record
    insertIntoHT(create_hash_elem(TK_RECORD, "record"));

    //endrecord
    insertIntoHT(create_hash_elem(TK_ENDRECORD, "endrecord"));

    //else
    insertIntoHT(create_hash_elem(TK_ELSE, "else"));

}

hash_elem* lookup(char *str){
    int index = hash(str);
    hash_elem *temp =KeyWordTable[index]->next;
    while(temp!=NULL){
        if(strcmp(str, temp->str)==0){
            // printf("%s\n", str);
            return temp;
        }
        temp=temp->next;
    }
    return KeyWordTable[index];
}