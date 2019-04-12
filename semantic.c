// GROUP 39
// AKANKSHYA MISHRA 2016A7PS0026P
// NARAPAREDDY BHAVANA 2016A7PS0034P
// KARABEE BATTA 2016A7PS0052P
// AASTHA KATARIA 2016A7PS0062P
#include "lexer.h"
#include "SymbolTable.h"
#include <string.h>

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
ASTNodeIt *semanticAnalyzer(treeNodeIt *t){
    ASTNodeIt *ast = makeAbstractSyntaxTree(t);
    printAST(ast);
    populateGlobalTable(ast);
    ASTNodeIt *temp = ast->node->u.n->children;
    ASTNodeIt *ch = temp->node->u.n->children;
    while(ch!=NULL){
        ASTNodeIt* stmts = populateSymbolTable(ch); //Populate Symbol Table for that function along with type extractor
        if(stmts!=NULL) {
            semanticRuleCheck(stmts, ch->node->u.n->leaf_symbol->u.lexeme);
        }
        ch=ch->next;
    }
    temp = ast->node->u.n->children->next;
    ASTNodeIt* stmts = populateSymbolTable(temp); //Populate Symbol Table for that function along with type extractor
    if(stmts!=NULL){
        semanticRuleCheck(stmts, temp->node->u.n->leaf_symbol->u.lexeme);
    }
    return ast;
}

type* getType(ASTNodeIt *temp, HashTable funcSymbolTable){
    type *lhs_type = (type*)malloc(sizeof(type));
    bool check_val;
    if(temp->next==NULL){
        check_val=0;
    }else if(!temp->next->node->is_leaf){
        check_val=0;
    }else{
        if(temp->next->next==NULL){
            check_val=0; //Assignment operators with single RHS(i.e. no TAG_ARITHMETIC_EXPRESSION)
        }
        else{
            check_val=1;
        }
    }
    if(!check_val){ //LHS = TK_ID
        hash_ele *g = lookupEle(temp->node->u.l->leaf_symbol->u.lexeme, globalSymbolTable);
        hash_ele *s = lookupEle(temp->node->u.l->leaf_symbol->u.lexeme, funcSymbolTable);
        if(g->ele!=NULL){
            lhs_type = g->ele->u.g->u.t;
        }
        else if(s->ele!=NULL){
            lhs_type=s->ele->u.s->t;
        }
        else{
            printf("Line %d: Variable %s not declared\n", temp->node->u.l->leaf_symbol->line_no, temp->node->u.l->leaf_symbol->u.lexeme);
        }
    }else{ //LHS = TK_ID.TK_FIELDID
        hash_ele *g = lookupEle(temp->node->u.l->leaf_symbol->u.lexeme, globalSymbolTable);
        hash_ele *s = lookupEle(temp->node->u.l->leaf_symbol->u.lexeme, funcSymbolTable);
        if(g->ele!=NULL){
            if(g->ele->u.g->u.t->is_record==0){
                printf("Line %d: Variable %s not of record type\n", temp->node->u.l->leaf_symbol->line_no, temp->node->u.l->leaf_symbol->u.lexeme);
            }
            else{
                lhs_type->is_record=0;
                ASTNodeIt *rec_ptr = lookupEle(g->ele->u.g->u.t->u.rec_id, globalSymbolTable)->ele->u.g->u.rec_type_list->record_ptr;
                bool set_flag=0;
                while(rec_ptr!=NULL){
                    if(strcmp(rec_ptr->node->u.n->leaf_symbol->u.lexeme, temp->next->node->u.l->leaf_symbol->u.lexeme)==0){
                        lhs_type->u.pri_type = (rec_ptr->node->u.n->children->node->u.l->leaf_symbol->tokenName==TK_INT) ? 0 : 1;
                        set_flag=1;
                        break;
                    }
                    rec_ptr=rec_ptr->next;
                }
                if(!set_flag){
                    printf("Line %d: Variable %s not part of record definition\n", temp->node->u.l->leaf_symbol->line_no, temp->next->node->u.l->leaf_symbol->u.lexeme);
                }
            }
        }
        else if(s->ele!=NULL){
            if(s->ele->u.s->t->is_record==0){
                printf("Line %d: Variable %s not of record type\n", temp->node->u.l->leaf_symbol->line_no, temp->node->u.l->leaf_symbol->u.lexeme);
            }
            else{
                lhs_type->is_record=0;
                ASTNodeIt *rec_ptr = lookupEle(s->ele->u.s->t->u.rec_id, globalSymbolTable)->ele->u.g->u.rec_type_list->record_ptr;
                bool set_flag=0;
                while(rec_ptr!=NULL){
                    if(strcmp(rec_ptr->node->u.n->leaf_symbol->u.lexeme, temp->next->node->u.l->leaf_symbol->u.lexeme)==0){
                        lhs_type->u.pri_type = (rec_ptr->node->u.n->children->node->u.l->leaf_symbol->tokenName==TK_INT) ? 0 : 1;
                        set_flag=1;
                        break;
                    }
                    rec_ptr=rec_ptr->next;
                }
                if(!set_flag){
                    printf("Line %d: Variable %s not part of record definition\n", temp->node->u.l->leaf_symbol->line_no, temp->next->node->u.l->leaf_symbol->u.lexeme);
                }
            }
        }
        else{
            printf("Line %d: Variable %s not declared\n", temp->node->u.l->leaf_symbol->line_no, temp->node->u.l->leaf_symbol->u.lexeme);
        }
    }
    return lhs_type;
}

type* verifyType(ASTNodeIt* tn, type *t, HashTable funcTable, TAG tag){
    //post-order traversal, should match type of t, check for declare, and for undefined record operations
    ASTNodeIt *temp = tn;
    ASTNodeIt *temp_child;
    bool typ_err=1;
    if(tag==TAG_ARITHMETIC_EXPRESSION){
        if(temp->node->is_leaf){
            if(temp->node->u.l->leaf_symbol->flag==is_int){
                temp->node->t = (type*)malloc(sizeof(type));
                temp->node->t->is_record=0;
                temp->node->t->u.pri_type=0;
            }else if(temp->node->u.l->leaf_symbol->flag==is_real){
                temp->node->t = (type*)malloc(sizeof(type));
                temp->node->t->is_record=0;
                temp->node->t->u.pri_type=1;
            }else if(temp->node->u.l->leaf_symbol->flag==is_lexeme){
                temp->node->t = getType(temp, funcTable);
            }
            return temp->node->t;
        }
        while(1){
            while(temp->node->is_leaf==0){
                temp=temp->node->u.n->children;
            }
            if(temp->node->is_leaf==1){
                if(temp->node->u.l->leaf_symbol->flag==is_int){
                    temp->node->t = (type*)malloc(sizeof(type));
                    temp->node->t->is_record=0;
                    temp->node->t->u.pri_type=0;
                }else if(temp->node->u.l->leaf_symbol->flag==is_real){
                    temp->node->t = (type*)malloc(sizeof(type));
                    temp->node->t->is_record=0;
                    temp->node->t->u.pri_type=1;
                }else if(temp->node->u.l->leaf_symbol->flag==is_lexeme){
                    temp->node->t = getType(temp, funcTable);
                }
            }
            while(temp->next==NULL){
                temp=temp->node->parent;
                if(temp==tn){
                    if(typ_err){
                        type *chk1 = temp->node->u.n->children->node->t;
                        type *chk2 = temp->node->u.n->children->next->node->t;
                        if(chk1->is_record!=chk2->is_record){
                            printf("Line %d: Type mismatch in arithmetic expression", temp->node->u.l->leaf_symbol->line_no);
                            typ_err=0;
                        }else if(chk1->is_record==0 && chk1->u.pri_type!=chk2->u.pri_type){
                            printf("Line %d: Type mismatch in arithmetic expression", temp->node->u.l->leaf_symbol->line_no);
                            typ_err=0;
                        }else if(chk1->is_record==1 && strcmp(chk1->u.rec_id, chk2->u.rec_id)){
                            printf("Line %d: Type mismatch in arithmetic expression", temp->node->u.l->leaf_symbol->line_no);
                            typ_err=0;
                        }else{
                            temp->node->t = (type*)malloc(sizeof(type));
                            temp->node->t->is_record = chk1->is_record;
                            if(chk1->is_record==0) temp->node->t->u.pri_type = chk1->u.pri_type;
                            if(chk1->is_record==1) temp->node->t->u.rec_id = chk1->u.rec_id;
                            return temp->node->t;
                        }
                    }
                    return NULL;
                }
                if(typ_err){
                    type *chk1 = temp->node->u.n->children->node->t;
                    type *chk2 = temp->node->u.n->children->next->node->t;
                    if(chk1->is_record!=chk2->is_record){
                        printf("Line %d: Type mismatch in arithmetic expression", temp->node->u.l->leaf_symbol->line_no);
                        typ_err=0;
                    }else if(chk1->is_record==0 && chk1->u.pri_type!=chk2->u.pri_type){
                        printf("Line %d: Type mismatch in arithmetic expression", temp->node->u.l->leaf_symbol->line_no);
                        typ_err=0;
                    }else if(chk1->is_record==1 && strcmp(chk1->u.rec_id, chk2->u.rec_id)){
                        printf("Line %d: Type mismatch in arithmetic expression", temp->node->u.l->leaf_symbol->line_no);
                        typ_err=0;
                    }else{
                        temp->node->t = (type*)malloc(sizeof(type));
                        temp->node->t->is_record = chk1->is_record;
                        if(chk1->is_record==0) temp->node->t->u.pri_type = chk1->u.pri_type;
                        if(chk1->is_record==1) temp->node->t->u.rec_id = chk1->u.rec_id;
                    }
                }
            }
            temp=temp->next;
        }
    }else if(tag==TAG_BOOLEAN_EXPRESSION){

    }else{
        printf("Code??\n");
    }
}

void semanticRuleCheck(ASTNodeIt *chk, char *fun_id){
    //preorder traversal;
    ASTNodeIt *temp = chk;
    Stack *st = newStack();

    //Inner symbol table(storing for function variables)
    HashTable funcSymbolTable = lookupEle(fun_id, SymbolTable)->ele->u.out_table->SymbolTable;

    //Check for: The parameters being returned by a function must be assigned a value. If a parameter does not get a value assigned within the function definition, it should be reported as an error.
    bool ret_no_error=0, ret_type_error=0, ret_declare_error=0;
    type *ret_t;
    ASTNodeIt *ret = chk->next->node->u.n->children; //Return statement id list access
    SeqListPars *op = lookupEle(fun_id, SymbolTable)->ele->u.out_table->out_pars;
    while(ret!=NULL && op!=NULL){
        op->out_check->tag=0;
        op->out_check->ret_par=ret->node->u.l->leaf_symbol->u.lexeme;
        if(lookupEle(ret->node->u.l->leaf_symbol->u.lexeme, globalSymbolTable)->ele!=NULL){
            ret_t = lookupEle(ret->node->u.l->leaf_symbol->u.lexeme, globalSymbolTable)->ele->u.g->u.t;
        }else if(lookupEle(ret->node->u.l->leaf_symbol->u.lexeme, funcSymbolTable)->ele!=NULL){
            ret_t = lookupEle(ret->node->u.l->leaf_symbol->u.lexeme, funcSymbolTable)->ele->u.s->t;
        }else{
            ret_declare_error=1;
        }
        if(!((op->t->is_record==ret_t->is_record) && (op->t->u.pri_type==ret_t->u.pri_type || strcmp(op->t->u.rec_id, ret_t->u.rec_id)==0))){
            ret_type_error=1;
        }
        op = op->next;
        ret = ret->next;
    }
    if(ret!=NULL) ret_no_error=1;
    if(op!=NULL) ret_no_error=1;

    while(1){
        while(temp!=NULL){        
            push(st, returnEle(temp));
            if(temp->node->is_leaf==0){
                //Non-leaf node: contains some TAG and is associated with some semantic check

                //The right hand side expression of an assignment statement must be of the same type as that of the left hand side identifier.
                if(temp->node->u.n->tag_info==TAG_ASSIGNMENT_STMT){
                    temp = temp->node->u.n->children;
                    type *lhs_type = getType(temp, funcSymbolTable);
                    int ln = temp->node->u.l->leaf_symbol->line_no;
                    while(temp->next!=NULL){
                        temp=temp->next;
                    }
                    type *rhs_type = verifyType(temp, lhs_type, funcSymbolTable, TAG_ARITHMETIC_EXPRESSION);
                    if(rhs_type==NULL){
                        printf("Line %d: Assignment to type mismatched arithmetic expression\n", ln);
                    }else{
                        if(lhs_type->is_record!=rhs_type->is_record){
                            printf("Line %d: Type mismatch in assignment statement", ln);
                        }else if(lhs_type->is_record==0 && lhs_type->u.pri_type!=rhs_type->u.pri_type){
                            printf("Line %d: Type mismatch in assignment statement", ln);
                        }else if(lhs_type->is_record==1 && strcmp(lhs_type->u.rec_id, rhs_type->u.rec_id)){
                            printf("Line %d: Type mismatch in assignment statement", ln);
                        }
                    }
                }
                if(temp->node->u.n->tag_info==TAG_ITERATIVE_STMT){
                    //While statement: one pass for checking if variables are being changed
                    ASTNodeIt *chk = temp->node->u.n->children;
                }
                if(temp->node->u.n->tag_info==TAG_COND_STMT){
                    //type-check for boolean
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

    if(ret_no_error){
        printf("Line %d: The number of parameters in return statement of function %s is incorrect\n", chk->next->node->u.n->children->node->u.l->leaf_symbol->line_no, fun_id);
    }
    if(ret_type_error || ret_declare_error){
        ret = chk->next->node->u.n->children;
        op = lookupEle(fun_id, SymbolTable)->ele->u.out_table->out_pars;
        while(ret!=NULL && op!=NULL){
            if(lookupEle(ret->node->u.l->leaf_symbol->u.lexeme, globalSymbolTable)->ele!=NULL){
                ret_t = lookupEle(ret->node->u.l->leaf_symbol->u.lexeme, globalSymbolTable)->ele->u.g->u.t;
            }else if(lookupEle(ret->node->u.l->leaf_symbol->u.lexeme, funcSymbolTable)->ele!=NULL){
                ret_t = lookupEle(ret->node->u.l->leaf_symbol->u.lexeme, funcSymbolTable)->ele->u.s->t;
            }else{
                printf("Line %d: Variable %s not declared\n", ret->node->u.l->leaf_symbol->line_no, ret->node->u.l->leaf_symbol->u.lexeme);
            }
            if(!((op->t->is_record==ret_t->is_record) && (op->t->u.pri_type==ret_t->u.pri_type || strcmp(op->t->u.rec_id, ret_t->u.rec_id)==0))){
                ret_type_error=1;
            }
            op = op->next;
            ret = ret->next;
        }
        if(ret_type_error) printf("Line %d: The types of parameters in return statement of function %s is incorrect\n", chk->next->node->u.n->children->node->u.l->leaf_symbol->line_no, fun_id);
    }
    op = lookupEle(fun_id, SymbolTable)->ele->u.out_table->out_pars;
    while(op!=NULL){
        if(op->out_check->tag==0){
            printf("Line %d: Parameters in return statement of function must have a value assigned to them\n", chk->next->node->u.n->children->node->u.l->leaf_symbol->line_no);
            break;
        }
    }
}