// GROUP 39
// AKANKSHYA MISHRA 2016A7PS0026P
// NARAPAREDDY BHAVANA 2016A7PS0034P
// KARABEE BATTA 2016A7PS0052P
// AASTHA KATARIA 2016A7PS0062P
#include "intermediateCodeGen.h"
#include<stdio.h>
#include<stdlib.h>
//include "SymbolTableDef.h"
//#include "ASTDef.h"

TEMP newTemp(){
    static int t=0;
    // printf("%d\n",t);
    return t++;
}
// hash_ele* find_hash_ele(char* str)
// {
//     if(lookupEle(str,globalSymbolTable)==NULL)
//     {
//         return (lookupEle(str,SymbolTable)); //we need function id look into it
//     }
//     else
//     {
//         return (lookupEle(str,globalSymbolTable));/* code */
//     }
// }
arg* newArg(int flag, hash_ele* h, TEMP t, LABEL L, int num, float rnum,int width){
    arg* a = (arg*)malloc(sizeof(arg));
    a->flag=flag;
    switch (flag)
    {
        case 0:
            a->u.hElem=h;
            // printf("%s\n",h->str);
            break;
        case 1:
            a->u.t=t;
            // printf("%d\n",t);
            break;
        case 2:
            a->u.L=L;
            // printf("%d\n",L);
            break;
        case 3:
            a->u.num=num;
            // printf("%d\n",num);
            break;
        case 4:
            a->u.rnum=rnum;
            // printf("%f\n",rnum);
            break;
        case 5:
            a->u.width=width;
            // printf("%d\n",width);
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
            if(lookupEle(ast->node->u.l->leaf_symbol->u.lexeme,globalSymbolTable)!=NULL)
            {
                return newArg(0, lookupEle(ast->node->u.l->leaf_symbol->u.lexeme,globalSymbolTable),0,0,0,0,0);
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
            return newArg(4,0,0,0,0,ast->node->u.l->leaf_symbol->u.value_of_real,0);
        }
    }
}

op* newOp(int flag, TAG tag, TOKEN tkname){
    op* o = (op*)malloc(sizeof(op));
    o->flag=flag;
    switch(flag){
        case 0:
            o->u.tag=tag;
            // printf("%d\n",tag);
            break;
        case 1:
            o->u.tkname=tkname;
            // printf("%d\n",tkname);
            break;
        default:
            return NULL;
    }
    return o;
}



quadruple* generateIntermediateCode(ASTNodeIt* root)
{
    ASTNodeIt* temp=root;
    ASTNodeIt* left_child=NULL;
    ASTNodeIt* right_child=NULL;
    while(1)
    {
        if(temp->node->u.n->tag_info==TAG_ASSIGNMENT_STMT)
        {                
            ASTNodeIt* temp_post=temp;
            quadruple* quadIt=NULL;
            left_child=temp->node->u.n->children;
            temp_post=left_child->next;// because the left child will be a variable (x=arithmetic expression)
            
            //travel to the leaf nodes
            while(temp_post->node->is_leaf==0)
            {
                temp_post=temp_post->node->u.n->children;
            }

            //post order traversal
            while(temp_post->node->parent!=temp)
            {
                ASTNodeIt* temp_post_parent;
                temp_post_parent=temp_post->node->parent;
                if(temp_post_parent->node->u.n->tag_info=TAG_ARITHMETIC_EXPRESSION)
                {
                    //printf("QUADRUPLE generation for quad TAG_ARITHMETIC_EXPRESSION\n");
                    temp_post_parent->quadhead->a1=getArg(temp_post);
                    temp_post_parent->quadhead->a2=getArg(temp_post->next);
                    //op* temp_post_parent-> = (op*)malloc(sizeof(op));
                    temp_post_parent->quadhead->operand->flag=1;
                    temp_post_parent->quadhead->operand=newOp(1,TAG_FUNCTION,temp_post_parent->node->u.n->leaf_symbol->tokenName);//can it be 
                    temp_post_parent->quadhead->res->flag=0;
                    temp_post_parent->quadhead->res->u.t=newTemp();
                                        // printf("%d")
                    temp_post_parent->quadtail=quadIt;//here it will be null for a leaf node
                    quadIt=temp_post_parent->quadhead;
                    
                    temp_post=temp_post_parent;
                }
                else //if rhs is also a leaf node or post order traversal has been completed , then generate a quad accordingly
                {
                    break;                


                }
            }
            //now lhs and rhs are ready
            temp->quadhead->a1=getArg(left_child);
            temp->quadhead->a2=getArg(temp_post);
            temp->quadhead->operand->flag=0;
            temp->quadhead->operand=newOp(0,TAG_ASSIGNMENT_STMT,TK_AND); //check shouldnt it be a token of tknmae TK_ASSIGN_OP
            temp->quadhead->res=NULL;
            return temp->quadhead;
            
        }
        else if(temp->node->u.n->tag_info==TAG_ARITHMETIC_EXPRESSION)
        {
            ASTNodeIt* temp_post=temp;
            quadruple* quadIt=NULL;
            while(temp_post->node->is_leaf==0)
            {
                temp_post=temp_post->node->u.n->children;
            }
            while(1)
            {
                ASTNodeIt* temp_post_parent;
                temp_post_parent=temp_post->node->parent;
                if(temp_post_parent!=temp)
                {
                    if(temp_post_parent->node->u.n->tag_info=TAG_ARITHMETIC_EXPRESSION)
                    {
                        temp_post_parent->quadhead->a1=getArg(temp_post);
                        temp_post_parent->quadhead->a2=getArg(temp_post->next);
                        temp_post_parent->quadhead->operand->flag=1;
                        temp_post_parent->quadhead->operand=newOp(1,TAG_FUNCTION,temp_post_parent->node->u.n->leaf_symbol->tokenName);//can it be 
                        temp_post_parent->quadhead->res->flag=0;
                        temp_post_parent->quadhead->res->u.t=newTemp();
                        temp_post_parent->quadtail=quadIt;//here it will be null for a leaf node
                        quadIt=temp_post_parent->quadhead;
                        temp_post=temp_post_parent;
                    }
                    else
                    {
                        break;
                        //throw some error
                    }
                    
                }
                else
                {
                    if(temp_post->next!=NULL)
                    {
                        left_child=temp_post;
                        temp_post=temp_post->next;//repeating the process for the right child
                        //you need to go to the base leaf again
                        while(temp_post->node->is_leaf==0)
                        {
                            temp_post=temp_post->node->u.n->children;
                        }

                        continue;
                    }
                    else
                    {
                        right_child=temp_post;
                    }
                    // if((right_child!=NULL)&&(left_child!=NULL))
                    // {
                    //     break;
                    // }
                    break;
                    
                }
            }              
                
                
            temp->quadhead->a1=getArg(left_child);
            temp->quadhead->a2=getArg(right_child);
            temp->quadhead->operand->flag=0;
            temp->quadhead->operand=newOp(1,TAG_ASSIGNMENT_STMT,temp->node->u.n->leaf_symbol->tokenName); //check shouldnt it be a token of tknmae TK_ASSIGN_OP
            temp->quadhead->res->flag=0;
            temp->quadhead->res->u.t=newTemp();
            
        }
    }
    return temp->quadhead;
}
        
            

