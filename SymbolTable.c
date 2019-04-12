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

Element* create_elem(int flag)// flag=true if in global table
                            // flag=false if in func symbol table ie 2ndlevel HT
{
    Element* ele=(Element*) malloc(sizeof(Element));
    ele->flag=flag;
    if(flag==0)
    {
        ele->u.out_table=(symT*)malloc(sizeof(symT));
        ele->u.out_table->in_pars=NULL;
        ele->u.out_table->out_pars=NULL;
        // ele->u.out_table->
        ele->u.out_table->SymbolTable=create_HTEle();
        // ele->u.SymbolTable=create_HTEle();
    }
    else if(flag==1)
    {
        ele->u.s=(symTableElem*) malloc(sizeof(symTableElem));
    }  
    else if(flag==2)
    {
        ele->u.g=(globalTableElem*) malloc(sizeof(globalTableElem));
    }
    return ele; 
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

int get_width(type* t)
{
    if(!t->is_record)
    {
        if(!t->u.pri_type)//false if int
        {
            return INT_WIDTH;
        }
        else if(t->u.pri_type)
        {
            return REAL_WIDTH;
        }
    }
    else 
    {
        return lookupEle(t->u.rec_id,globalSymbolTable)->ele->u.g->u.rec_type_list->width;
    }
}

void populate_type(hash_ele* hashEle_identifier,ASTNodeIt* temp)
{
    if(hashEle_identifier->ele->flag==1)
    {
        if(temp->node->u.n->children->node->u.l->leaf_symbol->tokenName==TK_INT)
        {
            hashEle_identifier->ele->u.s->t->is_record=0;
            hashEle_identifier->ele->u.s->t->u.pri_type=false;
        }
        else if(temp->node->u.n->children->node->u.l->leaf_symbol->tokenName==TK_REAL)
        {
            hashEle_identifier->ele->u.s->t->is_record=0;
            hashEle_identifier->ele->u.s->t->u.pri_type=true;
        }
        else
        {
            hashEle_identifier->ele->u.s->t->is_record=1;
            hashEle_identifier->ele->u.s->t->u.rec_id=temp->node->u.n->children->node->u.l->leaf_symbol->u.lexeme;
        }
    }
    else if(hashEle_identifier->ele->flag==2)
    {
        if(temp->node->u.n->children->node->u.l->leaf_symbol->tokenName==TK_INT)
        {
            hashEle_identifier->ele->u.g->u.t->is_record=0;
            hashEle_identifier->ele->u.g->u.t->u.pri_type=false;
        }
        else if(temp->node->u.n->children->node->u.l->leaf_symbol->tokenName==TK_REAL)
        {
            hashEle_identifier->ele->u.g->u.t->is_record=0;
            hashEle_identifier->ele->u.g->u.t->u.pri_type=false;
        }
        else
        {
            hashEle_identifier->ele->u.g->u.t->is_record=1;
            hashEle_identifier->ele->u.g->u.t->u.rec_id=temp->node->u.n->children->node->u.l->leaf_symbol->u.lexeme;
        }
    }
}

SeqListPars* make_inpars_node(type *t)
{
    SeqListPars* n=(SeqListPars*) malloc(sizeof(SeqListPars));
    n->out_flg=false;
    n->t=t;
    n->out_check=NULL;
    n->next=NULL;
    return n;
}

SeqListPars* make_outpars_node(type* t)
{
    SeqListPars* n=(SeqListPars*) malloc(sizeof(SeqListPars));
    n->out_flg=true;
    n->t=t;
    n->out_check=(out*) malloc(sizeof(out));
    n->out_check->tag=false;
    n->out_check->ret_par=NULL;
    n->next=NULL;
    return n;
}

void* populateSymbolTable(ASTNodeIt* root)
{
    SymbolTable=create_HTEle();
    ASTNodeIt* temp=root;
    while(1)
    {
        if(!temp->node->is_leaf)
        {
            if(temp->node->u.n->tag_info==TAG_FUNCTION||temp->node->u.n->tag_info==TAG_MAIN)
            {
                Element* func_elem;
                hash_ele* hashEle_func_elem;
                
                if(lookupEle(temp->node->u.n->leaf_symbol->u.lexeme,SymbolTable)->ele==NULL)
                {
                    func_elem = create_elem(0);
                    hashEle_func_elem=create_hashEle(func_elem,temp->node->u.n->leaf_symbol->u.lexeme);           
                    insertIntoHTEle(hashEle_func_elem,SymbolTable);
                }
                else
                {
                    printf("Line no: %d Redeclaration of function %s\n",temp->node->u.n->leaf_symbol->line_no,temp->node->u.n->leaf_symbol->u.lexeme);
                    if(temp->next!=NULL)
                        temp=temp->next;
                    else
                    {
                        temp=iterate_inorder(temp);
                        if(temp==NULL)
                            break;
                    }
                    
                    continue;
                }
                
                int global_offset=0;

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
                            //check if not previously created
                            if(lookupEle(temp->node->u.n->leaf_symbol->u.lexeme,func_elem->u.out_table->SymbolTable)->ele==NULL)
                            {
                                identifier_elem=create_elem(1);
                                hashEle_identifier=create_hashEle(identifier_elem,temp->node->u.n->leaf_symbol->u.lexeme);
                                insertIntoHTEle(hashEle_identifier,func_elem->u.out_table->SymbolTable);
                                hashEle_identifier->ele->u.s->t=(type*) malloc(sizeof(type));
                                //type population
                                populate_type(hashEle_identifier,temp);
                                //width population
                                identifier_elem->u.s->width=get_width(hashEle_identifier->ele->u.s->t);
                                identifier_elem->u.s->offset=global_offset;
                                global_offset+=identifier_elem->u.s->width; 
                            }
                            else
                            {
                                printf("Line no: %d Redeclaration of variable %s\n",temp->node->u.n->leaf_symbol->line_no,temp->node->u.n->leaf_symbol->u.lexeme);

                            }

                        }

                        else if(temp->node->u.n->tag_info==TAG_DECLARE)
                        {
                            if(lookupEle(temp->node->u.n->leaf_symbol->u.lexeme,func_elem->u.out_table->SymbolTable)->ele==NULL)
                            {
                                identifier_elem=create_elem(1);
                                hashEle_identifier=create_hashEle(identifier_elem,temp->node->u.n->leaf_symbol->u.lexeme);
                                insertIntoHTEle(hashEle_identifier,func_elem->u.out_table->SymbolTable);
                                hashEle_identifier->ele->u.s->t=(type*) malloc(sizeof(type));
                                if(temp->node->u.n->leaf_symbol->tokenName!=TK_RECORDID)
                                {
                                    hashEle_func_elem->ele->u.g->is_record=false;
                                    
                                }
                                else
                                {
                                    hashEle_func_elem->ele->u.g->is_record=true;    
                                }
                                //type population
                                populate_type(hashEle_identifier,temp);
                                //width population
                                identifier_elem->u.s->width=get_width(hashEle_identifier->ele->u.s->t);
                                identifier_elem->u.s->offset=global_offset;
                                global_offset+=identifier_elem->u.s->width; 
                            }
                            else
                            {
                                printf("Line no: %d Redeclaration of variable %s\n",temp->node->u.n->leaf_symbol->line_no,temp->node->u.n->leaf_symbol->u.lexeme);

                            }
                                  
                        }
                        else if(temp->node->u.n->tag_info==TAG_OUTPUT_PARS)
                        {
                            ASTNodeIt* temp_ast=temp->node->parent->node->u.n->children->node->u.n->children;
                            func_elem->u.out_table->in_pars=make_inpars_node(lookupEle(temp_ast->node->u.n->leaf_symbol->u.lexeme,func_elem->u.out_table->SymbolTable)->ele->u.s->t);
                            SeqListPars* temp_seq=func_elem->u.out_table->in_pars;
                            temp_ast=temp_ast->next;
                            while(temp_ast!=NULL)
                            {
                                temp_seq->next=make_inpars_node(lookupEle(temp_ast->node->u.n->leaf_symbol->u.lexeme,func_elem->u.out_table->SymbolTable)->ele->u.s->t);
                                temp_ast=temp_ast->next;
                                temp_seq=temp_seq->next;
                            }
                        }

                        else if( temp->node->u.n->tag_info==TAG_TYPEDEFS)
                        {
                            if(temp->node->parent->node->u.n->tag_info!=TAG_MAIN)
                            {
                                ASTNodeIt* temp_ast=temp->node->parent->node->u.n->children->next->node->u.n->children;
                                func_elem->u.out_table->out_pars=make_outpars_node(lookupEle(temp_ast->node->u.n->leaf_symbol->u.lexeme,func_elem->u.out_table->SymbolTable)->ele->u.s->t);
                                // func_elem->u.out_table->out_pars->out_check->ret_par=temp_ast->node->u.n->leaf_symbol->u.lexeme;
                                SeqListPars* temp_seq=func_elem->u.out_table->out_pars;
                                temp_ast=temp_ast->next;
                                while(temp_ast!=NULL)
                                {
                                    temp_seq->next=make_outpars_node(lookupEle(temp_ast->node->u.n->leaf_symbol->u.lexeme,func_elem->u.out_table->SymbolTable)->ele->u.s->t);
                                    // func_elem->u.out_table->out_pars->out_check->ret_par=temp_ast->node->u.n->leaf_symbol->u.lexeme;
                                    temp_ast=temp_ast->next;
                                    temp_seq=temp_seq->next;
                                }
                            }

                        }
                        else if(temp->node->u.n->tag_info==TAG_RETURNSTMT)
                        {}

                        if(temp->node->u.n->children==NULL)
                        {
                            // temp=temp->next;
                            temp=iterate_inorder(temp);//if function reached, move to next function
                        }
                        else
                        temp=temp->node->u.n->children;
                    }
                    else
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

int get_width_record(ASTNodeIt* n){
    ASTNodeIt* temp=n;
    int width=0;
    while(n!=NULL)
    {
        if(n->node->u.n->children->node->u.l->leaf_symbol->tokenName==TK_INT)
            width+=INT_WIDTH;
        else
            width+=REAL_WIDTH;
        n=n->next;
    }
    return width;
}

void populateGlobalTable(ASTNodeIt* root)
{
    globalSymbolTable=create_HTEle();
    ASTNodeIt* temp=root;
    while(1)
    {
        if(temp==NULL)
            break;
        if(!temp->node->is_leaf)
        {
            if(temp->node->u.n->tag_info==TAG_TYPEDEF)
            {
                Element* func_elem;
                hash_ele* hashEle_func_elem;
                
                if(lookupEle(temp->node->u.n->leaf_symbol->u.lexeme,globalSymbolTable)->ele==NULL)
                {
                    func_elem = create_elem(2);
                    hashEle_func_elem=create_hashEle(func_elem,temp->node->u.n->leaf_symbol->u.lexeme);           
                    insertIntoHTEle(hashEle_func_elem,globalSymbolTable);
                    hashEle_func_elem->ele->u.g->is_record=true;
                    hashEle_func_elem->ele->u.g->u.rec_type_list=(rec*) malloc(sizeof(rec));
                    hashEle_func_elem->ele->u.g->u.rec_type_list->rec_id=temp->node->u.n->leaf_symbol->u.lexeme;
                    hashEle_func_elem->ele->u.g->u.rec_type_list->record_ptr=temp->node->u.n->children;
                    hashEle_func_elem->ele->u.g->u.rec_type_list->width=get_width_record(temp->node->u.n->children);    
                }
                else
                {
                    printf("Line no: %d Redeclaration of function %s\n",temp->node->u.n->leaf_symbol->line_no,temp->node->u.n->leaf_symbol->u.lexeme);
                }
                 
            }

            if(temp->node->u.n->children==NULL)
                {
                    // temp=temp->next;
                    temp=iterate_inorder(temp);//if function reached, move to next function
                }
                else
                temp=temp->node->u.n->children;

            }
            else
            {
                temp=iterate_inorder(temp);
            }

            if(temp==NULL)//root reached
            break;
    }

    temp=root;
    ASTNodeIt* temp_children;
    int offset=0;

    while(1)
    {
        if(!temp->node->is_leaf)
        {
            if(temp->node->u.n->tag_info==TAG_DECLARE)
            {
                Element* func_elem;
                hash_ele* hashEle_func_elem;

                temp_children=temp->node->u.n->children;
                if(temp_children->next!=NULL)
                {
                    if(lookupEle(temp->node->u.n->leaf_symbol->u.lexeme,globalSymbolTable)->ele==NULL)
                    {
                        func_elem = create_elem(2);
                        hashEle_func_elem=create_hashEle(func_elem,temp->node->u.n->leaf_symbol->u.lexeme);           
                        insertIntoHTEle(hashEle_func_elem,globalSymbolTable);
                        hashEle_func_elem->ele->u.g->u.t=(type*) malloc(sizeof(type));
                        if(temp->node->u.n->leaf_symbol->tokenName!=TK_RECORDID)
                        {
                            hashEle_func_elem->ele->u.g->is_record=false;
                            
                        }
                        else
                        {
                            hashEle_func_elem->ele->u.g->is_record=true;    
                        }
                        //populate type
                        populate_type(hashEle_func_elem,temp);
                        

                        //populate offset
                        hashEle_func_elem->ele->u.g->offset=offset;
                        offset+=get_width(hashEle_func_elem->ele->u.g->u.t);

                    }
                    else
                    {
                        printf("Line no: %d Redeclaration of function %s\n",temp->node->u.n->leaf_symbol->line_no,temp->node->u.n->leaf_symbol->u.lexeme);
                    }
                }
            }
            if(temp->node->u.n->children==NULL)
            {
                // temp=temp->next;
                temp=iterate_inorder(temp);//if function reached, move to next function
            }
            else
            temp=temp->node->u.n->children;

             
        } 
        
        else
        {
            temp=iterate_inorder(temp);
        }

        if(temp==NULL)//root reached
            break;
    }              

}



void printSymbolTable(){
    int i,j;
    hash_ele* temp1,*temp2;
    printf("Lexeme\tType\tScope\tOffset\n");
    for(i=0;i<LEN_HT;i++)
    {
        temp1=SymbolTable[i]->next;
        while(temp1!=NULL)
        {
            for(j=0;j<LEN_HT;j++)
            {
                temp2=temp1->ele->u.out_table->SymbolTable[j]->next;
                while(temp2!=NULL)
                {
                    if(temp2->ele->u.s->t->is_record==0)
                    {
                        printf("%s\t%d\t%s\t%d\n", temp2->str, temp2->ele->u.s->t->u.pri_type, temp1->str, temp2->ele->u.s->offset);
                    }
                    else if (temp2->ele->u.s->t->is_record==1)
                    {
                    printf("%s\t%s\t%s\t%d\n", temp2->str, temp2->ele->u.s->t->u.rec_id, temp1->str, temp2->ele->u.s->offset); 
                    }
                    temp2=temp2->next;
                }
                
            }        
            temp1=temp1->next;
        }
    }
}

void printGlobalTable_recDef()
{
    int i;
    hash_ele* temp;
    ASTNodeIt* temp_ast;

    for(i=0;i<LEN_HT;i++)
    {
        temp=globalSymbolTable[i]->next;
        while(temp!=NULL)
        {
            if(temp->ele->u.g->is_record)
            {
                temp_ast=temp->ele->u.g->u.rec_type_list->record_ptr;
                printf("%s\t",temp->str);
                while(temp_ast!=NULL)
                {
                    printf("%s,",temp_ast->node->u.n->children->node->u.l->leaf_symbol->u.lexeme);
                    temp_ast=temp_ast->next;
                }
                printf("\t");

                printf("%d\n",temp->ele->u.g->u.rec_type_list->width);

            }
            temp=temp->next;
        }
        
    }
}

void printGlobalvar()
{
    int i;
    hash_ele* temp;

    for(i=0;i<LEN_HT;i++)
    {
        temp=globalSymbolTable[i]->next;
        while(temp!=NULL)
        {
            if(!temp->ele->u.g->is_record)
            {
                
                if(temp->ele->u.g->u.t->is_record==0)
                {
                    printf("%s\t%d\t--\t%d\n", temp->str, temp->ele->u.g->u.t->u.pri_type, temp->ele->u.g->offset);
                }
                else if (temp->ele->u.g->u.t->is_record==1)
                {
                printf("%s\t%s\t--\t%d\n", temp->str, temp->ele->u.g->u.t->u.rec_id, temp->ele->u.g->offset); 
                }
                
            }
            temp=temp->next;
        }
    }
}

void print_inpar_list()
{
    int i;
    hash_ele* temp;
    SeqListPars* temp_seq;
    for(i=0;i<LEN_HT;i++)
    {
        temp=SymbolTable[i]->next;

        while(temp!=NULL)
        {
            temp_seq=temp->ele->u.out_table->in_pars;
            while(temp_seq!=NULL)
            {
                if(!temp_seq->t->is_record)
                printf("%d  ",temp_seq->t->u.pri_type);
                else
                {
                    printf("%s  ",temp_seq->t->u.rec_id);
                }
                temp_seq=temp_seq->next;
            }
            temp=temp->next;
            if(temp==NULL)
            printf("\n");
        }
        // printf("\n");
    }
}

void print_outpar_list()
{
    int i;
    hash_ele* temp;
    SeqListPars* temp_seq;
    for(i=0;i<LEN_HT;i++)
    {
        temp=SymbolTable[i]->next;

        while(temp!=NULL)
        {
            temp_seq=temp->ele->u.out_table->out_pars;
            while(temp_seq!=NULL)
            {
                if(!temp_seq->t->is_record)
                printf("%d  ",temp_seq->t->u.pri_type);
                else
                {
                    printf("%s  ",temp_seq->t->u.rec_id);
                }
                temp_seq=temp_seq->next;
            }
            temp=temp->next;
            if(temp==NULL)
            printf("\n");
        }
        
        
    }
}






