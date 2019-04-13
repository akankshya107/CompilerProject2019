// GROUP 39
// AKANKSHYA MISHRA 2016A7PS0026P
// NARAPAREDDY BHAVANA 2016A7PS0034P
// KARABEE BATTA 2016A7PS0052P
// AASTHA KATARIA 2016A7PS0062P
#include "intermediateCodeGenDef.h"
#include<stdio.h>
#include<stdlib.h>
#include "SymbolTableDef.h"
#include "SymbolTable.h"
#include "ASTDef.h"
hash_ele* find_hash_ele(char* str)
{
    if(lookupEle(str,globalSymbolTable)==NULL)
    {
        return (lookupEle(str,SymbolTable)); //we need function id look into it
    }
    else
    {
        return (lookupEle(str,globalSymbolTable));/* code */
    }
}
arg* newArg(int flag, hash_ele* h, TEMP t, LABEL L, int num, float rnum,int width){
    arg* a = (arg*)malloc(sizeof(arg));
    a->flag=flag;
    switch (flag)
    {
        case 0:
            a->u.hElem=h;
            break;
        case 1:
            a->u.t=t;
            break;
        case 2:
            a->u.L=L;
            break;
        case 3:
            a->u.num=num;
            break;
        case 4:
            a->u.rnum=rnum;
            break;
        case 5:
            a->u.width=width;
        default:
            return NULL;
    }
    return a;
}
arg* getArg(ASTNodeIt* ast)
{
    if(ast->node->is_leaf)
    {
        if(ast->node->u.l->leaf_symbol->flag==0)
        {
            if(lookup(ast->node->u.l->leaf_symbol->u.lexeme,globalSymbolTable)!=NULL)
            {
                return newArg(0, lookup(ast->node->u.l->leaf_symbol->u.lexeme,globalSymbolTable),0,0,0,0,0);
            }
            else
            {
                return newArg(0,lookupEle(ast->node->u.l->leaf_symbol->u.lexeme, lookupEle("_main",SymbolTable)->ele->u.out_table->SymbolTable),0,0,0,0,0);
            }
            
        }
        if(ast->node->u.l->leaf_symbol->flag==1)
        {
            return newArg(3,0,0,0,ast->node->u.l->leaf_symbol->u.value_of_int,0,0);
        }
        if(ast->node->u.l->leaf_symbol->flag==2)
        {
            return newArg(4,0,0,0,ast->node->u.l->leaf_symbol->u.value_of_real,0,0);
        }
    }
}



quadruple* generateIntermediateCode(ASTNodeIt* root)
{
    ASTNodeIt* temp=root;
    while(1){
        if(temp->node->u.n->tag_info==TAG_ASSIGNMENT_STMT)
        {
            //implement a post order
            ASTNodeIt* temp_post=temp;
            temp_post=temp_post->next; // because the left child will be a variable (x=arithmetic expression)
            while(temp_post->node->is_leaf==0)
            {
                temp_post=temp_post->node->u.n->children;
            }
            while(temp_post!=temp)
            {
                ASTNodeIt* temp_post_parent;
                //temp_post_parent=temp_post->node->parent;
                if(temp_post->node->parent->node->u.n->tag_info==TAG_ARITHMETIC_EXPRESSION);
                {
                    //lookup for child
                    hash_ele* h=find_hash_ele(temp_post->node->u.l->leaf_symbol->u.lexeme);             
                    
                }
                
                //temp_post_parent->quad->a1->flag=0;
                temp_post_parent->quadhead->a1=getArg(temp_post);//take bahvanan;s code
                //temp_post_parent->quad->a2->flag=0;
                temp_post_parent->quadhead->a2=getArg(temp_post->next);
                //temp_post_parent->quad->operand->flag=0;
                temp_post_parent->quadhead->operand->u.tkname=temp_post_parent->node->u.n->leaf_symbol;
                temp_post_parent->quadhead->res=new_temp(); //insert function
                temp_post_parent->quadtail=temp_post->quadhead;


            }
            
            
        }
        else if(temp->node->u.n->tag_info==TAG_ASSIGNMENT_STMT)
        {

        }

        else if(temp->node->u.n->tag_info==TAG_READ)
        {
            
        }

        else if(temp->node->u.n->tag_info==TAG_ITERATIVE_STMT)
        {
            
        }

        else if(temp->node->u.n->tag_info==TAG_COND_STMT)
        {
            
        }
        
}

while(temp!=NULL){
        //Non-leaf node: contains some TAG and is associated with some semantic check

        //The right hand side expression of an assignment statement must be of the same type as that of the left hand side identifier.
        if(temp->node->u.n->tag_info==TAG_ASSIGNMENT_STMT){

            temp = temp->node->u.n->children;
            //find hash elem for children
            //for children-next: arE, write function
            temp = temp->node->parent;
            while(temp->next==NULL){
                if(temp->node->parent->node->u.n->tag_info==TAG_ITERATIVE_STMT) temp=temp->node->parent;
                else if(temp->node->parent->node->u.n->tag_info==TAG_THEN) temp=temp->node->parent;
                else if(temp->node->parent->node->u.n->tag_info==TAG_COND_STMT) temp=temp->node->parent;
                else break;
            }
            temp = temp->next;
        }
        else if(temp->node->u.n->tag_info==TAG_ITERATIVE_STMT){
            //While statement: one pass for checking if variables are being changed
            ASTNodeIt *chk = temp->node->u.n->children;
            //Quads
            temp=temp->node->u.n->children->next;
        }
        else if(temp->node->u.n->tag_info==TAG_COND_STMT){
            //if-then-else
            ASTNodeIt *chk = temp->node->u.n->children;
            temp = temp->node->u.n->children->next->node->u.n->children;
        }
        else if(temp->node->u.n->tag_info==TAG_FUN_CALL_STMT){
            //lol

            while(temp->next==NULL){
                if(temp->node->parent->node->u.n->tag_info==TAG_ITERATIVE_STMT) temp=temp->node->parent;
                else if(temp->node->parent->node->u.n->tag_info==TAG_THEN) temp=temp->node->parent;
                else if(temp->node->parent->node->u.n->tag_info==TAG_COND_STMT) temp=temp->node->parent;
                else break;
            }
            temp = temp->next;
        }
        else if(temp->node->u.n->tag_info==TAG_READ){
            while(temp->next==NULL){
                if(temp->node->parent->node->u.n->tag_info==TAG_ITERATIVE_STMT) temp=temp->node->parent;
                else if(temp->node->parent->node->u.n->tag_info==TAG_THEN) temp=temp->node->parent;
                else if(temp->node->parent->node->u.n->tag_info==TAG_COND_STMT) temp=temp->node->parent;
                else break;
            }
            temp = temp->next;
        }
        else if(temp->node->u.n->tag_info==TAG_WRITE){
            while(temp->next==NULL){
                if(temp->node->parent->node->u.n->tag_info==TAG_ITERATIVE_STMT) temp=temp->node->parent;
                else if(temp->node->parent->node->u.n->tag_info==TAG_THEN) temp=temp->node->parent;
                else if(temp->node->parent->node->u.n->tag_info==TAG_COND_STMT) temp=temp->node->parent;
                else break;
            }
            temp = temp->next;
        }
        else printf("Check AST structure\n");
    }


