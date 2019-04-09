// GROUP 39
// AKANKSHYA MISHRA 2016A7PS0026P
// NARAPAREDDY BHAVANA 2016A7PS0034P
// KARABEE BATTA 2016A7PS0052P
// AASTHA KATARIA 2016A7PS0062P

#include "SymbolTableDef.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int hashEle(char *str){
	long unsigned int sum = 0;
	long unsigned int a = 8;
	for (int i=0; i<strlen(str); i++){
		sum=(sum*a+str[i])%LEN_HT;
	}
	return sum;
}

hash_ele *create_hashEle(Element *ele, char *str);
hashTable create_HTEle()
{
    int i;
    hash_ele** HT=(hash_ele**) malloc(sizeof(hash_ele*)*LEN_HT);
    for(i=0;i<LEN_HT;i++)
    {
        HT[i]=create_hashEle(NULL,NULL);
    }
    return HT;
}


hash_ele *create_hashEle(Element *ele, char *str){
    hash_ele *h = (hash_ele*)malloc(sizeof(hash_ele));
    h->str = str;
    h->ele = ele;
    h->next=NULL;
    return h;
}

Element* create_elem(bool flag)// flag=true if in global table
                            // flag=false if in func symbol table ie 2ndlevel HT
{
    Element* ele=(Element*) malloc(sizeof(Element));
    if(flag)
    {
        ele->is_func=true;
        ele->u.SymbolTable=create_HTEle();
    }
    else
    {
        ele->is_func=false;
        ele->u.s=(symTableElem*) malloc(sizeof(symTableElem));
    }   
}

void insertIntoHTEle(hash_ele *elem, hashTable HT){
    int index = hashEle(elem->str);
    if(HT[index]->next==NULL){
        HT[index]->next=elem;
    }
    else{
        hash_ele *ptr = HT[index]->next;
        while(ptr->next!=NULL){
            ptr=ptr->next;
        }
        ptr->next=elem;
    }
}

hash_ele* lookupEle(char *str, hashTable HT){
    int index = hashEle(str);
    hash_ele *temp = HT[index]->next;
    while(temp!=NULL){
        if(strcmp(str, temp->str)==0){
            // printf("%s\n", str);
            return temp;
        }
        temp=temp->next;
    }
    return HT[index];
}

void populateSymbolTable(ASTNodeIt* root)
{
    
    
}