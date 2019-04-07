// GROUP 39
// AKANKSHYA MISHRA 2016A7PS0026P
// NARAPAREDDY BHAVANA 2016A7PS0034P
// KARABEE BATTA 2016A7PS0052P
// AASTHA KATARIA 2016A7PS0062P

#include "semanticDef.h"
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

hash_elem *create_hash_elem(Element *ele, char *str){
    hash_elem *h = (hash_elem*)malloc(sizeof(hash_elem));
    h->str = str;
    h->ele = ele;
    h->next=NULL;
    return h;
}

void insertIntoHT(hash_elem *elem, hashTable HT){
    int index = hash(elem->str);
    if(HT[index]->next==NULL){
        HT[index]->next=elem;
    }
    else{
        hash_elem *ptr = HT[index]->next;
        while(ptr->next!=NULL){
            ptr=ptr->next;
        }
        ptr->next=elem;
    }
}

hash_elem* lookup(char *str, hashTable HT){
    int index = hash(str);
    hash_elem *temp =HT[index]->next;
    while(temp!=NULL){
        if(strcmp(str, temp->str)==0){
            // printf("%s\n", str);
            return temp;
        }
        temp=temp->next;
    }
    return HT[index];
}

ASTNodeIt* extractTypes(ASTNodeIt* root)
{
    temp=root;
    while()
}