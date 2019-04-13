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
void xyz(ASTNodeIt* root)
{
    ASTNodeIt* temp;
    temp=root;    
    ASTNodeIt* temp_post;
    temp_post=temp;
    quadruple* quadIt=NULL;
    if(temp->node->u.n->tag_info==TAG_ARITHMETIC_EXPRESSION)
    {
        while(temp_post->node->is_leaf==0)
            {
                temp_post=temp_post->node->u.n->children;
            }
        while(temp_post!=temp)
        {
            ASTNodeIt* temp_post_parent;
            temp_post_parent=temp_post->node->parent;
            //generate quadruple with arguments as temp_post and temp_post->next
            temp_post_parent->quadhead->a1=getArg(temp_post);
            temp_post_parent->quadhead->a2=getArg(temp_post->next);
            temp_post_parent->quadhead->operand=temp_post_parent->quadhead->operand=newOp(1,TAG_FUNCTION,temp_post_parent->node->u.n->leaf_symbol->tokenName);
            temp_post_parent->quadhead->res=new_temp();
            temp_post_parent->quadtail=quadIt;//here it will be null for a leaf node
            quadIt=temp_post_parent->quadhead;
            temp_post=temp_post_parent;           
        
        }
        
        
    }
        
            