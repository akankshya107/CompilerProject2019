#include "key.h"
#include <stdlib.h>
#include <string.h>
int hash(char *str){
	long unsigned int sum = 0;
	long unsigned int a = 32;
	for (int i=0; i<strlen(str); i++){
		sum=(sum*a+str[i])%43;
	}
	return sum;
}

hash_elem *create_hash_elem(){
    hash_elem *h = (hash_elem*)malloc(sizeof(hash_elem));
    h->str = (char*)malloc(sizeof(char)*11);
    h->tkname = -1;
}

hashTable populateKeyWordTable(){
    KeyWordTable = (hashTable)malloc(sizeof(hash_elem*)*NO_OF_KEYWORDS);

    int index;
    //populate this
    index = hash("with");
    KeyWordTable[index]=create_hash_elem();
    KeyWordTable[index]->tkname = TK_WITH;
    KeyWordTable[index]->str = "with";

    //see if any collisions
    return KeyWordTable;
}

hash_elem* lookup(char *str){
    if(strcmp(str, KeyWordTable[hash(str)]->str)){
        return KeyWordTable[hash(str)];
    }
    else {
        hash_elem *ret = create_hash_elem();
        return ret;
    }
}