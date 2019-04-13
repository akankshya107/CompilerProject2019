// GROUP 39
// AKANKSHYA MISHRA 2016A7PS0026P
// NARAPAREDDY BHAVANA 2016A7PS0034P
// KARABEE BATTA 2016A7PS0052P
// AASTHA KATARIA 2016A7PS0062P
#include "IntermediateDef.h"
#include "SymbolTable.h"
quadruple* gen_arithematic(ASTNodeIt* root)
{
    ASTNodeIt* temp=root;
    ASTNodeIt* temp_post=temp->node->u.n->children;
    while(!temp_post->node->is_leaf)
    {
        temp_post=temp_post->node->u.n->children;
    }

    while(temp_post->next==NULL)
    {
        temp_post=temp_post->node->parent;
        temp_post->quad=(quadruple*) malloc(sizeof(quadruple));
        temp_post->quad->a1=(arg1*) malloc(sizeof(arg1));
        if(temp_post->node->u.n->children->node->is_leaf)
        {
            if(temp_post->node->u.n->children->node->u.l->leaf_symbol->flag==1)
            {
                temp_post->quad->a1->u.num=temp_post->node->u.n->children->node->u.l->leaf_symbol->u.value_of_int;
            }
            else if(temp_post->node->u.n->children->node->u.l->leaf_symbol->flag==2)
            {
                temp_post->quad->a1->u.num=temp_post->node->u.n->children->node->u.l->leaf_symbol->u.value_of_real;
            }
            else 
            {
                if(lookupEle(temp_post->node->u.n->children->node->u.l->leaf_symbol->u.lexeme,globalSymbolTable))
                temp_post->quad->a1->u.hElem=
            }

        }
        else
        {
            temp_post->quad->arg1.t=temp_post->node->u.n->children->quad->result.
        }
        

    }
}
quadraple* generateIntermediateCode(ASTNodeIt* root)
{
    ASTNodeIt* temp=root;
    while(1){
        if(temp->node->u.n->tag_info==TAG_ASSIGNMENT_STMT){
            ASTNodeIt* temp_post=temp->node->u.n->children;
            while(!temp_post->node->is_leaf)
            {
                temp_post=temp_post->node->u.n->children;
            }


        }
        else if(temp->node->u.n->tag_info==TAG_FUN_CALL_STMT){
            ASTNodeIt* f_out = temp->node->u.n->children->node->u.n->children;
            while(f_out!=NULL){
                for(int j=0; j<i; j++){
                    if(strcmp(f_out->node->u.l->leaf_symbol->u.lexeme, arr[j])==0){
                        flgs[j]=1;
                        end_flag=1;
                        break;
                    }
                }
            }
        }
        else if(temp->node->u.n->tag_info==TAG_READ){
            for(int j=0; j<i; j++){
                if(strcmp(temp->node->u.n->children->node->u.l->leaf_symbol->u.lexeme, arr[j])==0){
                    flgs[j]=1;
                    end_flag=1;
                    break;
                }
            }
        }
        else if(temp->node->u.n->tag_info==TAG_ITERATIVE_STMT){
            temp=temp->node->u.n->children->next;
            continue;
        }
        else if(temp->node->u.n->tag_info==TAG_COND_STMT){
            temp = temp->node->u.n->children->next->node->u.n->children;
            continue;
        }
        if(end_flag) break;
        while(temp->next==NULL){
            if(temp->node->parent==root) break;
            if(temp->node->parent->node->u.n->tag_info==TAG_ITERATIVE_STMT) temp=temp->node->parent;
            else if(temp->node->parent->node->u.n->tag_info==TAG_THEN) temp=temp->node->parent;
            else if(temp->node->parent->node->u.n->tag_info==TAG_COND_STMT) temp=temp->node->parent;
        }
        temp = temp->next;
    }
    if(!end_flag){
        printf("Lines %d: None of the variables participating in the iterations of the while loop gets updated\n", t->node->u.n->children->node->u.n->leaf_symbol->line_no);
    }
}





    



    
}