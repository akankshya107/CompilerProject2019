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
    populateGlobalTable(ast);
    ASTNodeIt *temp = ast->node->u.n->children;
    ASTNodeIt *ch = temp->node->u.n->children;
    SymbolTable = create_HTEle();
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

type* getType(ASTNodeIt *temp, HashTable funcSymbolTable, bool idlist){
    type *lhs_type = (type*)malloc(sizeof(type));
    bool check_val;
    if(idlist){
        check_val=0;
    }
    else if(temp->next==NULL){
        check_val=0;
    }
    else if(!temp->next->node->is_leaf){
        check_val=0;
    }
    else{
        if(temp->next->next==NULL){
            check_val=0; //Assignment operators with single RHS(i.e. no TAG_ARITHMETIC_EXPRESSION) and for Boolean operators
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
            return NULL;
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
            return NULL;
        }
    }
    return lhs_type;
}

type* verifyType(ASTNodeIt* tn, HashTable funcTable, TAG tag){
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
                temp->node->t = getType(temp, funcTable, 0);
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
                    temp->node->t = getType(temp, funcTable, 0);
                }
            }
            while(temp->next==NULL){
                temp=temp->node->parent;
                if(temp==tn){
                    if(typ_err){
                        type *chk1 = temp->node->u.n->children->node->t;
                        type *chk2 = temp->node->u.n->children->next->node->t;
                        if(chk1!=NULL && chk2!=NULL){
                            if((chk1->is_record==1 || chk2->is_record==1) && (temp->node->u.n->leaf_symbol->tokenName==TK_MUL || temp->node->u.n->leaf_symbol->tokenName==TK_DIV)){
                                if(chk1->is_record==1 && chk2->is_record!=1){
                                    temp->node->t = (type*)malloc(sizeof(type));
                                    temp->node->t->is_record = chk1->is_record;
                                    temp->node->t->u.rec_id = chk1->u.rec_id;
                                    return temp->node->t;
                                }else if(chk1->is_record!=1 && chk2->is_record==1){
                                    temp->node->t = (type*)malloc(sizeof(type));
                                    temp->node->t->is_record = chk2->is_record;
                                    temp->node->t->u.rec_id = chk2->u.rec_id;
                                    return temp->node->t;
                                }else{
                                    printf("Line %d: Type mismatch in arithmetic expression\n", temp->node->u.n->leaf_symbol->line_no);
                                }
                            }else if(chk1->is_record!=chk2->is_record){
                                printf("Line %d: Type mismatch in arithmetic expression\n", temp->node->u.n->leaf_symbol->line_no);
                            }else if(chk1->is_record==0 && chk1->u.pri_type!=chk2->u.pri_type){
                                printf("Line %d: Type mismatch in arithmetic expression\n", temp->node->u.n->leaf_symbol->line_no);
                            }else if(chk1->is_record==1 && strcmp(chk1->u.rec_id, chk2->u.rec_id)){
                                printf("Line %d: Type mismatch in arithmetic expression\n", temp->node->u.n->leaf_symbol->line_no);
                            }else{
                                temp->node->t = (type*)malloc(sizeof(type));
                                temp->node->t->is_record = chk1->is_record;
                                if(chk1->is_record==0) temp->node->t->u.pri_type = chk1->u.pri_type;
                                if(chk1->is_record==1) temp->node->t->u.rec_id = chk1->u.rec_id;
                                return temp->node->t;
                            }
                        }
                    }
                    return NULL;
                }
                if(typ_err){
                    type *chk1 = temp->node->u.n->children->node->t;
                    type *chk2 = temp->node->u.n->children->next->node->t;
                    if(chk1!=NULL && chk2!=NULL){
                        if((chk1->is_record==1 || chk2->is_record==1) && (temp->node->u.n->leaf_symbol->tokenName==TK_MUL || temp->node->u.n->leaf_symbol->tokenName==TK_DIV)){
                            if(chk1->is_record==1 && chk2->is_record!=1){
                                temp->node->t = (type*)malloc(sizeof(type));
                                temp->node->t->is_record = chk1->is_record;
                                temp->node->t->u.rec_id = chk1->u.rec_id;
                            }else if(chk1->is_record!=1 && chk2->is_record==1){
                                temp->node->t = (type*)malloc(sizeof(type));
                                temp->node->t->is_record = chk2->is_record;
                                temp->node->t->u.rec_id = chk2->u.rec_id;
                            }else{
                                printf("Line %d: Type mismatch in arithmetic expression\n", temp->node->u.n->leaf_symbol->line_no);
                                typ_err=0;
                            }
                        }else if(chk1->is_record!=chk2->is_record){
                            printf("Line %d: Type mismatch in arithmetic expression\n", temp->node->u.n->leaf_symbol->line_no);
                            typ_err=0;
                        }else if(chk1->is_record==0 && chk1->u.pri_type!=chk2->u.pri_type){
                            printf("Line %d: Type mismatch in arithmetic expression\n", temp->node->u.n->leaf_symbol->line_no);
                            typ_err=0;
                        }else if(chk1->is_record==1 && strcmp(chk1->u.rec_id, chk2->u.rec_id)){
                            printf("Line %d: Type mismatch in arithmetic expression\n", temp->node->u.n->leaf_symbol->line_no);
                            typ_err=0;
                        }else{
                            temp->node->t = (type*)malloc(sizeof(type));
                            temp->node->t->is_record = chk1->is_record;
                            if(chk1->is_record==0) temp->node->t->u.pri_type = chk1->u.pri_type;
                            if(chk1->is_record==1) temp->node->t->u.rec_id = chk1->u.rec_id;
                        }
                    }else typ_err=0;
                }
            }
            temp=temp->next;
        }
    }else if(tag==TAG_BOOLEAN_EXPRESSION){
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
                    temp->node->t = getType(temp, funcTable, 0);
                }
            }
            while(temp->next==NULL){
                temp=temp->node->parent;
                if(temp==tn){
                    if(typ_err){
                        type *chk1 = temp->node->u.n->children->node->t;
                        type *chk2 = temp->node->u.n->children->next->node->t;
                        if(chk1->is_record==1 || chk2->is_record==1){
                            printf("Line %d: No record variables can be used in boolean expression\n", temp->node->u.l->leaf_symbol->line_no);
                        }
                        else if(temp->node->u.n->leaf_symbol->tokenName==TK_AND || temp->node->u.n->leaf_symbol->tokenName==TK_OR){
                            temp->node->t = (type*)malloc(sizeof(type));
                            temp->node->t->is_record = 0;
                            temp->node->t->u.pri_type = t_bool;
                            return temp->node->t;
                        }
                        else if(temp->node->u.n->leaf_symbol->tokenName==TK_NOT){
                            temp->node->t = (type*)malloc(sizeof(type));
                            temp->node->t->is_record = 0;
                            temp->node->t->u.pri_type = t_bool;
                            return temp->node->t;
                        }
                        else{
                            if(chk1->u.pri_type!=chk2->u.pri_type){
                                printf("Line %d: Type %s of %s does not match with type %s of %s in boolean expression\n", temp->node->u.l->leaf_symbol->line_no, TypeString(chk1->u.pri_type), temp->node->u.n->children->node->u.l->leaf_symbol->u.lexeme, TypeString(chk2->u.pri_type), temp->node->u.n->children->next->node->u.l->leaf_symbol->u.lexeme);
                            }
                            else{
                                temp->node->t = (type*)malloc(sizeof(type));
                                temp->node->t->is_record = 0;
                                temp->node->t->u.pri_type = t_bool;
                                return temp->node->t;
                            }
                        }
                    }
                    return NULL;
                }
                if(typ_err){
                    type *chk1 = temp->node->u.n->children->node->t;
                    type *chk2 = temp->node->u.n->children->next->node->t;
                    if(chk1->is_record==1 || chk2->is_record==1){
                        printf("Line %d: No record variables can be used in boolean expression\n", temp->node->u.l->leaf_symbol->line_no);
                        typ_err=0;
                    }
                    else if(temp->node->u.n->leaf_symbol->tokenName==TK_AND || temp->node->u.n->leaf_symbol->tokenName==TK_OR){
                        temp->node->t = (type*)malloc(sizeof(type));
                        temp->node->t->is_record = 0;
                        temp->node->t->u.pri_type = t_bool;
                    }
                    else if(temp->node->u.n->leaf_symbol->tokenName==TK_NOT){
                        temp->node->t = (type*)malloc(sizeof(type));
                        temp->node->t->is_record = 0;
                        temp->node->t->u.pri_type = t_bool;
                    }
                    else{
                        if(chk1->u.pri_type!=chk2->u.pri_type){
                            printf("Line %d: Type %s of %s does not match with type %s of %s in boolean expression\n", temp->node->u.l->leaf_symbol->line_no, TypeString(chk1->u.pri_type), temp->node->u.n->children->node->u.l->leaf_symbol->u.lexeme, TypeString(chk2->u.pri_type), temp->node->u.n->children->next->node->u.l->leaf_symbol->u.lexeme);
                            typ_err=0;
                        }
                        else{
                            temp->node->t = (type*)malloc(sizeof(type));
                            temp->node->t->is_record = 0;
                            temp->node->t->u.pri_type = t_bool;
                        }
                    }
                }
            }
            temp=temp->next;
        }
    }else{
        printf("Code??\n");
    }
}

int noOfTerms(ASTNodeIt *b){
    ASTNodeIt *temp =b;
    int count=0;
    while(1){
        while(temp->node->is_leaf==0){
            temp=temp->node->u.n->children;
        }
        if(temp->node->is_leaf==1 && temp->node->u.l->leaf_symbol->flag==is_lexeme){
            count++;
        }
        while(temp->next==NULL){
            temp=temp->node->parent;
            if(temp==b){
                return count;
            }
        }
        temp=temp->next;
    }
}

void checkChange(ASTNodeIt *t){
    //For ITERATIVE_STATEMENT
    ASTNodeIt *temp = t->node->u.n->children;
    int size = noOfTerms(temp);
    char **arr = (char**)malloc(sizeof(char*)*size);
    for(int i=0; i<size; i++){
        arr[i]=NULL;
    }
    int i=0;
    int br_flag=0;
    while(1){
        while(temp->node->is_leaf==0){
            temp=temp->node->u.n->children;
        }
        if(temp->node->is_leaf==1 && temp->node->u.l->leaf_symbol->flag==is_lexeme){
            int flg=0;
            for(int j=0; j<i; j++){
                if(strcmp(arr[j], temp->node->u.l->leaf_symbol->u.lexeme)==0){
                    flg=1; break;
                }
            }
            if(!flg) arr[i++] = temp->node->u.l->leaf_symbol->u.lexeme;
        }
        while(temp->next==NULL){
            temp=temp->node->parent;
            if(temp==t->node->u.n->children){
                br_flag=1;
                break;
            }
        }
        if(br_flag) break;
        temp=temp->next;
    }
    //Check if assignment statement, fun_call_statement, io_stmt
    int flgs[i];
    temp = t->node->u.n->children->next;
    int end_flag=0;
    br_flag=0;
    while(1){
        if(temp->node->u.n->tag_info==TAG_ASSIGNMENT_STMT){
            for(int j=0; j<i; j++){
                if(strcmp(temp->node->u.n->children->node->u.l->leaf_symbol->u.lexeme, arr[j])==0){
                    flgs[j]=1;
                    end_flag=1;
                    break;
                }
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
                f_out = f_out->next;
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
            if(temp->node->parent==t) {
                br_flag=1;
                break;
            }
            if(temp->node->parent->node->u.n->tag_info==TAG_ITERATIVE_STMT) temp=temp->node->parent;
            else if(temp->node->parent->node->u.n->tag_info==TAG_THEN) temp=temp->node->parent;
            else if(temp->node->parent->node->u.n->tag_info==TAG_COND_STMT) temp=temp->node->parent;
        }
        if(br_flag) break;
        temp = temp->next;
    }
    if(!end_flag){
        printf("Line %d: None of the variables participating in the iterations of the while loop gets updated\n", t->node->u.n->children->node->u.n->leaf_symbol->line_no);
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
        if(ret_t->is_record!=op->t->is_record){
            ret_type_error=1;
        }else if(ret_t->is_record==0 && ret_t->u.pri_type!=op->t->u.pri_type){
            ret_type_error=1;
        }else if(ret_t->is_record==1 && strcmp(ret_t->u.rec_id, op->t->u.rec_id)){
            ret_type_error=1;
        }
        op = op->next;
        ret = ret->next;
    }
    if(ret!=NULL) ret_no_error=1;
    if(op!=NULL) ret_no_error=1;

    temp=chk->node->u.n->children;
    while(temp!=NULL){
        //Non-leaf node: contains some TAG and is associated with some semantic check

        //The right hand side expression of an assignment statement must be of the same type as that of the left hand side identifier.
        if(temp->node->u.n->tag_info==TAG_ASSIGNMENT_STMT){

            if(!ret_no_error){
                op = lookupEle(fun_id, SymbolTable)->ele->u.out_table->out_pars;
                while(op!=NULL){
                    if(strcmp(op->out_check->ret_par, temp->node->u.n->children->node->u.l->leaf_symbol->u.lexeme)==0){
                        op->out_check->tag=1;
                        break;
                    }
                    op=op->next;
                }
            }

            temp = temp->node->u.n->children;
            type *lhs_type = getType(temp, funcSymbolTable, 0);
            int ln = temp->node->u.l->leaf_symbol->line_no;
            while(temp->next!=NULL){
                temp=temp->next;
            }
            type *rhs_type = verifyType(temp, funcSymbolTable, TAG_ARITHMETIC_EXPRESSION);
            if(lhs_type!=NULL){
                if(rhs_type==NULL){
                    printf("Line %d: Assignment to type mismatched arithmetic expression\n", ln);
                }else{
                    if(lhs_type->is_record!=rhs_type->is_record){
                        printf("Line %d: The type %s of LHS in assignment statement does not match with type %s of arithmetic expression\n", ln, lhs_type->is_record ? lhs_type->u.rec_id : TypeString(lhs_type->u.pri_type), rhs_type->is_record ? rhs_type->u.rec_id : TypeString(rhs_type->u.pri_type));
                    }else if(lhs_type->is_record==0 && lhs_type->u.pri_type!=rhs_type->u.pri_type){
                        printf("Line %d: The type %s of LHS in assignment statement does not match with type %s of arithmetic expression\n", ln, TypeString(lhs_type->u.pri_type), TypeString(lhs_type->u.pri_type));
                    }else if(lhs_type->is_record==1 && strcmp(lhs_type->u.rec_id, rhs_type->u.rec_id)){
                        printf("Line %d: The type %s of LHS in assignment statement does not match with type %s of arithmetic expression\n", ln, lhs_type->u.rec_id, rhs_type->u.rec_id);
                    }
                }
            }

            temp = temp->node->parent;
            while(temp->next==NULL){
                if(temp->node->parent->node->u.n->tag_info==TAG_ITERATIVE_STMT) temp=temp->node->parent;
                else if(temp->node->parent->node->u.n->tag_info==TAG_THEN) temp=temp->node->parent;
                else if(temp->node->parent->node->u.n->tag_info==TAG_ELSE) temp=temp->node->parent;
                else if(temp->node->parent->node->u.n->tag_info==TAG_COND_STMT) temp=temp->node->parent;
                else break;
            }
            temp = temp->next;
        }
        else if(temp->node->u.n->tag_info==TAG_ITERATIVE_STMT){
            //While statement: one pass for checking if variables are being changed
            ASTNodeIt *chk = temp->node->u.n->children;
            type *cond = verifyType(chk, funcSymbolTable, TAG_BOOLEAN_EXPRESSION);
            if(cond!=NULL){
                checkChange(temp);
            }
            temp=temp->node->u.n->children->next;
        }
        else if(temp->node->u.n->tag_info==TAG_COND_STMT){
            //if-then-else
            ASTNodeIt *chk = temp->node->u.n->children;
            type *cond = verifyType(chk, funcSymbolTable, TAG_BOOLEAN_EXPRESSION);
            temp = temp->node->u.n->children->next->node->u.n->children;
        }
        else if(temp->node->u.n->tag_info==TAG_FUN_CALL_STMT){
            ASTNodeIt *out_args = temp->node->u.n->children->node->u.n->children;
            if(!ret_no_error){
                while(out_args!=NULL){
                    op = lookupEle(fun_id, SymbolTable)->ele->u.out_table->out_pars;
                    while(op!=NULL){
                        if(strcmp(op->out_check->ret_par, out_args->node->u.l->leaf_symbol->u.lexeme)==0){
                            op->out_check->tag=1;
                            break;
                        }
                        op=op->next;
                    }
                    out_args=out_args->next;
                }
            }

            hash_ele *f = lookupEle(temp->node->u.n->leaf_symbol->u.lexeme, SymbolTable);
            int ln = temp->node->u.n->leaf_symbol->line_no;
            if(f->ele==NULL){
                printf("Line %d: Function %s used without being declared before the %s function\n", ln, temp->node->u.n->leaf_symbol->u.lexeme, fun_id);
            }
            else if(strcmp(temp->node->u.n->leaf_symbol->u.lexeme, fun_id)==0){
                printf("Line %d: Function %s being invoked recursively\n", ln, fun_id);
            }
            else{
                ASTNodeIt *out_args = temp->node->u.n->children->node->u.n->children;
                ASTNodeIt *in_args = temp->node->u.n->children->next->node->u.n->children;
                SeqListPars *f_in_pars = f->ele->u.out_table->in_pars;
                SeqListPars *f_out_pars = f->ele->u.out_table->out_pars;
                type *chk1, *chk2;

                while(out_args!=NULL && f_out_pars!=NULL){
                    chk1 = getType(out_args, funcSymbolTable, 1);
                    chk2 = f_out_pars->t;
                    if(chk1!=NULL){
                        if(chk1->is_record!=chk2->is_record){
                            printf("Line %d: The type %s of variable %s does not match with the type %s of the formal output parameter\n", ln, chk1->is_record ? chk1->u.rec_id : TypeString(chk1->u.pri_type), out_args->node->u.l->leaf_symbol->u.lexeme, chk2->is_record ? chk2->u.rec_id : TypeString(chk2->u.pri_type));
                        }else if(chk1->is_record==0 && chk1->u.pri_type!=chk2->u.pri_type){
                            printf("Line %d: The type %s of variable %s does not match with the type %s of the formal output parameter\n", ln, TypeString(chk1->u.pri_type), out_args->node->u.l->leaf_symbol->u.lexeme, TypeString(chk2->u.pri_type));
                        }else if(chk1->is_record==1 && strcmp(chk1->u.rec_id, chk2->u.rec_id)){
                            printf("Line %d: The type %s of variable %s does not match with the type %s of the formal output parameter\n", ln, chk1->u.rec_id, out_args->node->u.l->leaf_symbol->u.lexeme, chk2->u.rec_id);
                        }
                    }
                    out_args = out_args->next;
                    f_out_pars = f_out_pars->next;
                }
                if(out_args!=NULL)  printf("Line %d: The number of output parameters at function call %s is incorrect\n", ln, temp->node->u.n->leaf_symbol->u.lexeme);
                if(f_out_pars!=NULL) printf("Line %d: The number of output parameters at function call %s is incorrect\n", ln, temp->node->u.n->leaf_symbol->u.lexeme);

                while(in_args!=NULL && f_in_pars!=NULL){
                    chk1 = getType(in_args, funcSymbolTable, 1);
                    chk2 = f_in_pars->t;
                    if(chk1!=NULL){
                        if(chk1->is_record!=chk2->is_record){
                            printf("Line %d: The type %s of variable %s does not match with the type %s of the formal input parameter\n", ln, chk1->is_record ? chk1->u.rec_id : TypeString(chk1->u.pri_type), in_args->node->u.l->leaf_symbol->u.lexeme, chk2->is_record ? chk2->u.rec_id : TypeString(chk2->u.pri_type));
                        }else if(chk1->is_record==0 && chk1->u.pri_type!=chk2->u.pri_type){
                            printf("Line %d: The type %s of variable %s does not match with the type %s of the formal input parameter\n", ln, TypeString(chk1->u.pri_type), in_args->node->u.l->leaf_symbol->u.lexeme, TypeString(chk2->u.pri_type));
                        }else if(chk1->is_record==1 && strcmp(chk1->u.rec_id, chk2->u.rec_id)){
                            printf("Line %d: The type %s of variable %s does not match with the type %s of the formal input parameter\n", ln, chk1->u.rec_id, in_args->node->u.l->leaf_symbol->u.lexeme, chk2->u.rec_id);
                        }
                    }
                    in_args = in_args->next;
                    f_in_pars = f_in_pars->next;
                }
                if(in_args!=NULL)  printf("Line %d: The number of input parameters at function call %s is incorrect\n", ln, temp->node->u.n->leaf_symbol->u.lexeme);
                if(f_in_pars!=NULL) printf("Line %d: The number of input parameters at function call %s is incorrect\n", ln, temp->node->u.n->leaf_symbol->u.lexeme);

            }

            while(temp->next==NULL){
                if(temp->node->parent->node->u.n->tag_info==TAG_ITERATIVE_STMT) temp=temp->node->parent;
                else if(temp->node->parent->node->u.n->tag_info==TAG_THEN) temp=temp->node->parent;
                else if(temp->node->parent->node->u.n->tag_info==TAG_ELSE) temp=temp->node->parent;
                else if(temp->node->parent->node->u.n->tag_info==TAG_COND_STMT) temp=temp->node->parent;
                else break;
            }
            temp = temp->next;
        }
        else if(temp->node->u.n->tag_info==TAG_READ){

            if(!ret_no_error){
                op = lookupEle(fun_id, SymbolTable)->ele->u.out_table->out_pars;
                while(op!=NULL){
                    if(strcmp(op->out_check->ret_par, temp->node->u.n->children->node->u.l->leaf_symbol->u.lexeme)==0){
                        op->out_check->tag=1;
                        break;
                    }
                    op=op->next;
                }
            }

            getType(temp->node->u.n->children, funcSymbolTable, 0);
            while(temp->next==NULL){
                if(temp->node->parent->node->u.n->tag_info==TAG_ITERATIVE_STMT) temp=temp->node->parent;
                else if(temp->node->parent->node->u.n->tag_info==TAG_THEN) temp=temp->node->parent;
                else if(temp->node->parent->node->u.n->tag_info==TAG_ELSE) temp=temp->node->parent;
                else if(temp->node->parent->node->u.n->tag_info==TAG_COND_STMT) temp=temp->node->parent;
                else break;
            }
            temp = temp->next;
        }
        else if(temp->node->u.n->tag_info==TAG_WRITE){
            if(temp->node->u.n->children->node->u.l->leaf_symbol->flag==is_lexeme) getType(temp->node->u.n->children, funcSymbolTable, 0);
            while(temp->next==NULL){
                if(temp->node->parent->node->u.n->tag_info==TAG_ITERATIVE_STMT) temp=temp->node->parent;
                else if(temp->node->parent->node->u.n->tag_info==TAG_THEN) temp=temp->node->parent;
                else if(temp->node->parent->node->u.n->tag_info==TAG_ELSE) temp=temp->node->parent;
                else if(temp->node->parent->node->u.n->tag_info==TAG_COND_STMT) temp=temp->node->parent;
                else break;
            }
            temp = temp->next;
        }
        else temp = temp->node->u.n->children;
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
            if(ret_t->is_record!=op->t->is_record){
                ret_type_error=1;
            }else if(ret_t->is_record==0 && ret_t->u.pri_type!=op->t->u.pri_type){
                ret_type_error=1;
            }else if(ret_t->is_record==1 && strcmp(ret_t->u.rec_id, op->t->u.rec_id)){
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
        op=op->next;
    }
}