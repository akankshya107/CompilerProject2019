// GROUP 39
// AKANKSHYA MISHRA 2016A7PS0026P
// NARAPAREDDY BHAVANA 2016A7PS0034P
// KARABEE BATTA 2016A7PS0052P
// AASTHA KATARIA 2016A7PS0062P

#include "SymbolTableDef.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LEN_HT 41
int hashEle(char *str){
	long unsigned int sum = 0;
	long unsigned int a = 8;
    int len;
    if(str!=NULL)
        len=strlen(str);
    else 
        len=0;
	for (int i=0; i<len; i++){
		sum=(sum*a+str[i])%LEN_HT;
	}
	return sum;
}


hash_ele *create_hashEle(Element *ele, char *str){
    hash_ele *h = (hash_ele*)malloc(sizeof(hash_ele));
    h->str = str;
    h->ele = ele;
    h->next=NULL;
    return h;
}

HashTable create_HTEle()
{
    int i;
    hash_ele** HT=(hash_ele**) malloc(sizeof(hash_ele*)*LEN_HT);
    for(i=0;i<LEN_HT;i++)
    {
        HT[i]=create_hashEle(NULL,NULL);
    }
    return HT;
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

void insertIntoHTEle(hash_ele *elem, HashTable HT){
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

hash_ele* lookupEle(char *str, HashTable HT){
    int index = hashEle(str);
    hash_ele *temp =HT[index]->next;
    while(temp!=NULL){
        if(strcmp(str, temp->str)==0){
            // printf("%s\n", str);
            return temp;
        }
        temp=temp->next;
    }
    return HT[index];
}

ASTNodeIt* iterate_inorder(ASTNodeIt* temp)
{
    // int flag=0;
    if(temp==NULL)
        return temp;
    if(temp->next!=NULL)
        temp=temp->next;
    else
    {
        //iterate_next_outside_function_subtree()
        while(temp!=NULL)
        {
            temp=temp->node->parent;
            if(temp==NULL)//root reached
            {
                // flag=1;//declare flag, may reach root node
                //in this case should also break from outer while(1)
                // think of how this can be done if iterate is written as a seperate function
                return temp;
            }
            if(temp->next!=NULL)
            {
                return temp->next;
                
            }               
        }   
    }
    return temp;
}

void* populateSymbolTable(ASTNodeIt* root)
{
    globalSymbolTable=create_HTEle();
    SymbolTable=create_HTEle();

    ASTNodeIt* temp=root;
    while(1)
    {
        int outer_sym_table;
        if(!temp->node->is_leaf)
        {
            if(temp->node->u.n->tag_info==TAG_FUNCTION||temp->node->u.n->tag_info==TAG_MAIN)
            {
                outer_sym_table = temp->node->u.n->leaf_symbol->tokenName;
                Element* func_elem = create_elem(true);
                hash_ele* hashEle_func_elem=create_hashEle(func_elem,temp->node->u.n->leaf_symbol->u.lexeme);
                insertIntoHTEle(hashEle_func_elem,SymbolTable);
                Element* identifier_elem;
                hash_ele* hashEle_identifier;
                temp=temp->node->u.n->children;
                while(1)
                {
                    if(temp==NULL)//root reached
                        break;
                    if(!temp->node->is_leaf)
                    {
                        if(temp->node->u.n->tag_info==TAG_FUNCTION||temp->node->u.n->tag_info==TAG_MAIN)
                            break;
                        
                        if(temp->node->u.n->tag_info==TAG_ID)
                        {
                            identifier_elem=create_elem(false);
                            hashEle_identifier=create_hashEle(identifier_elem,temp->node->u.n->leaf_symbol->u.lexeme);
                            insertIntoHTEle(hashEle_identifier,func_elem->u.SymbolTable);
                            identifier_elem->u.s->width=-1;
                            identifier_elem->u.s->offset=0;
                            identifier_elem->u.s->is_record=false;
                            identifier_elem->u.s->type.pri_type=-1;
                            
                        }
                        // else if(temp->node->u.n->tag_info==TAG_TYPEDEF)
                        // {
                        //     //global HT se karna hai

                        // }
                        else if(temp->node->u.n->tag_info==TAG_DECLARE)
                        {
                            identifier_elem=create_elem(false);
                            hashEle_identifier=create_hashEle(identifier_elem,temp->node->u.n->leaf_symbol->u.lexeme);
                            if(temp->node->u.n->children->next==NULL)
                                insertIntoHTEle(hashEle_identifier,func_elem->u.SymbolTable);
                            // else
                                //insert into global symbol table
                            identifier_elem->u.s->width=-1;
                            identifier_elem->u.s->offset=0;
                            identifier_elem->u.s->is_record=false;
                            identifier_elem->u.s->type.pri_type=-1;      
                        }
                        else
                        {
                            
                            if(temp->node->u.n->children==NULL)
                            {
                                // temp=temp->next;
                                temp=iterate_inorder(temp);//if function reached, move to next function
                                
                                //may reach root nnode
                                //in this case should also break from outer while(1)
                                // think of how this can be done if iterate is written as a seperate function
                            }
                            else
                            temp=temp->node->u.n->children;
                            
                        }
                    }
                    // else
                    {
                        temp=iterate_inorder(temp);
                    }
                    
                }
            }
            
            else
            {
                if(temp->node->u.n->children==NULL)
                {
                    // temp=temp->next;
                    temp=iterate_inorder(temp);//if function reached, move to next function
                    
                    //may reach root nnode
                    //in this case should also break from outer while(1)
                    // think of how this can be done if iterate is written as a seperate function
                }
                else
                temp=temp->node->u.n->children;
            } 

            if(temp==NULL)//root reached
            break;   
        }
    
        else
        {
            temp=iterate_inorder(temp);
        }
    }        
}







