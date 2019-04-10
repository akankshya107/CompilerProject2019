// GROUP 39
// AKANKSHYA MISHRA 2016A7PS0026P
// NARAPAREDDY BHAVANA 2016A7PS0034P
// KARABEE BATTA 2016A7PS0052P
// AASTHA KATARIA 2016A7PS0062P
#include "lexer.h"
#include "SymbolTable.h"

Ele* returnEle(ASTNodeIt *n){
    Ele *e = (Ele*)malloc(sizeof(Ele));
    e->node=n;
    e->next=NULL;
    return e;
}

ASTNodeIt *searchTag(ASTNodeIt *root, TAG tg){
    ASTNodeIt *temp = root;
    Stack *st = newStack();
    while(1){
        while((temp!=NULL)){        
            push(st, returnEle(temp));
            if(temp->node->is_leaf==0 && temp->node->u.n->tag_info==tg){
                return temp;
            }
            else if(temp->node->is_leaf==0){
                temp = temp->node->u.n->children; 
            }else{
                temp = temp->next;
            }
        }
        if(isEmpty(st)) break;
        temp = pop(st)->node;
        temp = temp->next;
    }
    return NULL;
}

void semanticRuleCheck(ASTNodeIt *chk, char *fun_id);
void semanticAnalyzer(treeNodeIt *t){
    ASTNodeIt *ast = makeAbstractSyntaxTree(t);
    printAST(ast);
    globalSymbolTable = populateGlobalTable(ast);
    ASTNodeIt *temp = searchTag(ast, TAG_FUN_LIST);
    ASTNodeIt *ch = temp->node->u.n->children;
    while(ch!=NULL){
        ASTNodeIt* stmts = populateSymbolTable(ch); //Populate Symbol Table for that function along with type extractor
        semanticRuleCheck(stmts, ch->node->u.n->leaf_symbol->u.lexeme);
        ch=ch->next;
    }
    temp = searchTag(ast, TAG_MAIN);
    ASTNodeIt* stmts = populateSymbolTable(temp); //Populate Symbol Table for that function along with type extractor
    semanticRuleCheck(stmts, temp->node->u.n->leaf_symbol->u.lexeme);
}


// void checkTypes(ASTNodeIt* root){
//     //Single pass through AST
//     ASTNodeIt *temp0 = searchTag(root, TAG_FUN_LIST);
//     ASTNodeIt *ch0 = temp0->node->u.n->children;
//     while(ch0!=NULL){
//         ASTNodeIt *temp = ch0;
//         Stack *st = newStack();
//         while(1){
//             while((temp!=NULL)){        
//                 push(st, returnEle(temp));
//                 if(temp->node->is_leaf==0 && temp->node->u.n->tag_info==TAG_ARITHMETIC_EXPRESSION){
//                     //check LHS and RHS
//                     // checkExpressionType(temp);
//                 }
//                 if(temp->node->is_leaf==0 && temp->node->u.n->tag_info==TAG_BOOLEAN_EXPRESSION){
//                     //check LHS and RHS
//                     // checkBExpressionType(temp);
//                 }
//                 if(temp->node->is_leaf==0 && temp->node->u.n->tag_info==TAG_FUN_CALL_STMT){
//                     //Formal and actual parameters being checked
//                     ASTNodeIt *out_args = temp->node->u.n->children->node->u.n->children;
//                     ASTNodeIt *in_args = temp->node->u.n->children->next->node->u.n->children;
//                     ASTNodeIt *f = searchTag(root, TAG_FUN_LIST);
//                     ASTNodeIt *ch = f->node->u.n->children;
//                     int flg =0;
//                     while(ch!=NULL){
//                         if(ch->node->u.n->leaf_symbol->u.lexeme==temp->node->u.n->leaf_symbol->u.lexeme){
//                             //input pars and input args
//                             flg=1;
//                             HashTable st = lookupEle(ch->node->u.n->leaf_symbol->u.lexeme, SymbolTable)->ele->u.symT.SymbolTable;
//                             ASTNodeIt *in_pars = ch->node->u.n->children->node->u.n->children;
//                             while(in_pars!=NULL){
//                                 if(lookupEle(in_args->node->u.l->leaf_symbol->u.lexeme, st)->ele->u.s->type =! in_pars->node->u.n->leaf_symbol->u.lexeme){
//                                     // printf("%s argument of type %s does not match with %s parameter of %s type\n");
//                                 }
//                                 in_pars=in_pars->next;
//                             }
//                             ASTNodeIt *out_pars = ch->node->u.n->children->next->node->u.n->children;
//                             while(out_pars!=NULL){
//                                 if(lookupEle(out_args->node->u.l->leaf_symbol->u.lexeme, st)->ele->u.s->type =! out_pars->node->u.n->leaf_symbol->u.lexeme){
//                                     // printf("%s argument of type %s does not match with %s parameter of %s type\n");
//                                 }
//                                 out_pars=out_pars->next;
//                             }
//                         }
//                         if(flg) break;
//                         ch = ch->next;
//                     }
                    
//                 }
//                 else if(temp->node->is_leaf==0){
//                     temp = temp->node->u.n->children; 
//                 }else{
//                     temp = temp->next;
//                 }
                
//             }
//             if(isEmpty(st)) break;
//             temp = pop(st)->node;
//             temp = temp->next;
//         }
//     }
//     ch0=ch0->next;
// }

void semanticRuleCheck(ASTNodeIt *chk, char *fun_id){
    //preorder traversal;
    ASTNodeIt *temp = chk;
    Stack *st = newStack();

    //Check for: The parameters being returned by a function must be assigned a value. If a parameter does not get a value assigned within the function definition, it should be reported as an error.
    bool ret_error=0;
    ASTNodeIt *ret = chk->next->node->u.n->children;
    SeqListPars *op = lookupEle(fun_id, SymbolTable)->ele->u.symT.out_pars;
    while(ret!=NULL && op!=NULL){
        op->u.out.tag=0;
        op->u.out.ret_par=ret->node->u.l->leaf_symbol->u.lexeme;
        op = op->next;
        ret = ret->next;
    }
    if(ret!=NULL) ret_error=1;
    if(op!=NULL) ret_error=1;
    
    while(1){
        while((temp!=NULL)){        
            push(st, returnEle(temp));
            if(temp->node->is_leaf==0){
                //Non-leaf node: contains some TAG and is associated with some semantic check

                //The right hand side expression of an assignment statement must be of the same type as that of the left hand side identifier.
                if(temp->node->u.n->tag_info==TAG_ASSIGNMENT_STMT){
                    type lhs_type;
                    if(temp->node->u.n->children->next==NULL){
                        
                    }
                }
                if(temp->node->u.n->tag_info==TAG_ITERATIVE_STMT){
                    
                }
                if(temp->node->u.n->tag_info==TAG_COND_STMT){
                    
                }
                if(temp->node->u.n->tag_info==TAG_FUN_CALL_STMT){
                    
                }
                temp = temp->node->u.n->children; 
            }else{
                temp = temp->next;
            }
        }
        if(isEmpty(st)) break;
        temp = pop(st)->node;
        temp = temp->next;
    }
}