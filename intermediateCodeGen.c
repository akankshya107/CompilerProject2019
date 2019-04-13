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

op* newOp(int flag, TAG tag, TOKEN tkname){
    op* o = (op*)malloc(sizeof(op));
    o->flag=flag;
    switch(flag){
        case 0:
            o->u.tag=tag;
            break;
        case 1:
            o->u.tkname=tkname;
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
    while(1){
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
                    temp_post_parent->quadhead->a1=getArg(temp_post);
                    temp_post_parent->quadhead->a2=getArg(temp_post->next);
                    //op* temp_post_parent-> = (op*)malloc(sizeof(op));
                    temp_post_parent->quadhead->operand->flag=1;
                    temp_post_parent->quadhead->operand=newOp(1,TAG_FUNCTION,temp_post_parent->node->u.n->leaf_symbol->tokenName);//can it be 
                    temp_post_parent->quadhead->res=new_temp();
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
            temp->quadhead->a1=getArg(left_leaf_child);
            temp->quadhead->a1=getArg(temp_post);
            temp->quadhead->operand->flag=0;
            temp->quadhead->operand=newOp(0,TAG_ASSIGNMENT_STMT,TK_GT); //check shouldnt it be a token of tknmae TK_ASSIGN_OP
            
            
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
                        temp_post_parent->quadhead->res=new_temp();
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
            temp->quadhead->a1=getArg(right_child);
            temp->quadhead->operand->flag=0;
            temp->quadhead->operand=newOp(0,TAG_ASSIGNMENT_STMT,TK_GT); //check shouldnt it be a token of tknmae TK_ASSIGN_OP
            
        }
        
            

//         else if(temp->node->u.n->tag_info==TAG_READ)
//         {
            
//         }

//         else if(temp->node->u.n->tag_info==TAG_ITERATIVE_STMT)
//         {
            
//         }

//         else if(temp->node->u.n->tag_info==TAG_COND_STMT)
//         {
            
//         }
        
// }

// while(temp!=NULL){
//         //Non-leaf node: contains some TAG and is associated with some semantic check

//         //The right hand side expression of an assignment statement must be of the same type as that of the left hand side identifier.
//         if(temp->node->u.n->tag_info==TAG_ASSIGNMENT_STMT){

//             temp = temp->node->u.n->children;
//             //find hash elem for children
//             //for children-next: arE, write function
//             temp = temp->node->parent;
//             while(temp->next==NULL){
//                 if(temp->node->parent->node->u.n->tag_info==TAG_ITERATIVE_STMT) temp=temp->node->parent;
//                 else if(temp->node->parent->node->u.n->tag_info==TAG_THEN) temp=temp->node->parent;
//                 else if(temp->node->parent->node->u.n->tag_info==TAG_COND_STMT) temp=temp->node->parent;
//                 else break;
//             }
//             temp = temp->next;
//         }
//         else if(temp->node->u.n->tag_info==TAG_ITERATIVE_STMT){
//             //While statement: one pass for checking if variables are being changed
//             ASTNodeIt *chk = temp->node->u.n->children;
//             //Quads
//             temp=temp->node->u.n->children->next;
//         }
//         else if(temp->node->u.n->tag_info==TAG_COND_STMT){
//             //if-then-else
//             ASTNodeIt *chk = temp->node->u.n->children;
//             temp = temp->node->u.n->children->next->node->u.n->children;
//         }
//         else if(temp->node->u.n->tag_info==TAG_FUN_CALL_STMT){
//             //lol

//             while(temp->next==NULL){
//                 if(temp->node->parent->node->u.n->tag_info==TAG_ITERATIVE_STMT) temp=temp->node->parent;
//                 else if(temp->node->parent->node->u.n->tag_info==TAG_THEN) temp=temp->node->parent;
//                 else if(temp->node->parent->node->u.n->tag_info==TAG_COND_STMT) temp=temp->node->parent;
//                 else break;
//             }
//             temp = temp->next;
//         }
//         else if(temp->node->u.n->tag_info==TAG_READ){
//             while(temp->next==NULL){
//                 if(temp->node->parent->node->u.n->tag_info==TAG_ITERATIVE_STMT) temp=temp->node->parent;
//                 else if(temp->node->parent->node->u.n->tag_info==TAG_THEN) temp=temp->node->parent;
//                 else if(temp->node->parent->node->u.n->tag_info==TAG_COND_STMT) temp=temp->node->parent;
//                 else break;
//             }
//             temp = temp->next;
//         }
//         else if(temp->node->u.n->tag_info==TAG_WRITE){
//             while(temp->next==NULL){
//                 if(temp->node->parent->node->u.n->tag_info==TAG_ITERATIVE_STMT) temp=temp->node->parent;
//                 else if(temp->node->parent->node->u.n->tag_info==TAG_THEN) temp=temp->node->parent;
//                 else if(temp->node->parent->node->u.n->tag_info==TAG_COND_STMT) temp=temp->node->parent;
//                 else break;
//             }
//             temp = temp->next;
//         }
//         else printf("Check AST structure\n");
//     }


