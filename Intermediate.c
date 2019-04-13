// GROUP 39
// AKANKSHYA MISHRA 2016A7PS0026P
// NARAPAREDDY BHAVANA 2016A7PS0034P
// KARABEE BATTA 2016A7PS0052P
// AASTHA KATARIA 2016A7PS0062P
#include "IntermediateDef.h"
// quadruple* gen_arithematic(ASTNodeIt* root)
// {
//     ASTNodeIt* temp=root;
//     ASTNodeIt* temp_post=temp->node->u.n->children;
//     while(!temp_post->node->is_leaf)
//     {
//         temp_post=temp_post->node->u.n->children;
//     }

//     while(temp_post->next==NULL)
//     {
//         temp_post=temp_post->node->parent;
//         temp_post->quad=(quadruple*) malloc(sizeof(quadruple));
//         temp_post->quad->a1=(arg1*) malloc(sizeof(arg1));
//         if(temp_post->node->u.n->children->node->is_leaf)
//         {
//             if(temp_post->node->u.n->children->node->u.l->leaf_symbol->flag==1)
//             {
//                 temp_post->quad->a1->u.num=temp_post->node->u.n->children->node->u.l->leaf_symbol->u.value_of_int;
//             }
//             else if(temp_post->node->u.n->children->node->u.l->leaf_symbol->flag==2)
//             {
//                 temp_post->quad->a1->u.num=temp_post->node->u.n->children->node->u.l->leaf_symbol->u.value_of_real;
//             }
//             else 
//             {
//                 if(lookupEle(temp_post->node->u.n->children->node->u.l->leaf_symbol->u.lexeme,globalSymbolTable))
//                 temp_post->quad->a1->u.hElem=
//             }

//         }
//         else
//         {
//             temp_post->quad->arg1.t=temp_post->node->u.n->children->quad->result.
//         }
        

//     }
// }
quadruple* generateIntermediateCode(ASTNodeIt* root)
{
    //root=program
    ASTNodeIt *temp = root->node->u.n->children->next->node->u.n->children; //ignoring otherFunctions
    while(1){
        if(temp->node->u.n->tag_info==TAG_DECLARES){

        }
        else if(temp->node->u.n->tag_info==TAG_TYPEDEFS){

        }
        else if(temp->node->u.n->tag_info==TAG_OTHERSTMTS){
            temp=temp->node->u.n->children;
            while(1){
                if(temp->node->u.n->tag_info==TAG_ASSIGNMENT_STMT){
                    //Traverse RHS: get RHS code-ARITHMETIC EXPRESSION
                }
                else if(temp->node->u.n->tag_info==TAG_ITERATIVE_STMT){
                    //While statement: one pass for checking if variables are being changed
                    //Boolean respective code
                    temp=temp->node->u.n->children->next;
                }
                else if(temp->node->u.n->tag_info==TAG_COND_STMT){
                    //if-then-else
                    //Boolean repective code
                    temp = temp->node->u.n->children->next->node->u.n->children;
                }
                else if(temp->node->u.n->tag_info==TAG_ELSE){
                    temp=temp->node->u.n->children;
                }
                else if(temp->node->u.n->tag_info==TAG_FUN_CALL_STMT){
                    //Skip: not to be implemented
                }
                else if(temp->node->u.n->tag_info==TAG_READ){
                }
                else if(temp->node->u.n->tag_info==TAG_WRITE){
                }
                else printf("Check AST structure\n");
                
                while(temp->next==NULL){
                    if(temp->node->parent->node->u.n->tag_info==TAG_OTHERSTMTS){
                        //make LL and
                        break;
                    }
                    if(temp->node->parent->node->u.n->tag_info==TAG_ITERATIVE_STMT){
                        temp=temp->node->parent;
                        //attach inner code to dummy var
                    }
                    if(temp->node->parent->node->u.n->tag_info==TAG_THEN){
                        temp=temp->node->parent;
                        //attach inner code to dummy var
                    }
                    if(temp->node->parent->node->u.n->tag_info==TAG_ELSE){
                        temp=temp->node->parent;
                        //attach inner code to dummy var
                    }
                    if(temp->node->parent->node->u.n->tag_info==TAG_COND_STMT){
                        temp=temp->node->parent;
                        //attach inner code to dummy var
                    }
                    else temp=temp->node->parent;
                }
                temp=temp->next;
            }
        }
        else{
            //RETURN STMTS: main has no o/p parameters
        }
        if(temp->next!=NULL) temp=temp->next;
        else{
            //make LL
            return temp->quad;
        }
    }
}