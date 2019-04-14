// GROUP 39
// AKANKSHYA MISHRA 2016A7PS0026P
// NARAPAREDDY BHAVANA 2016A7PS0034P
// KARABEE BATTA 2016A7PS0052P
// AASTHA KATARIA 2016A7PS0062P
#include "IntermediateDef.h"

TEMP newTemp(){
    static int t=0;
    return t++;
}

LABEL newLabel(){
    static int l=0;
    return l++;
}

result *newResult(int flag, TEMP t, LABEL l){
    result *res = (result*)malloc(sizeof(result));
    switch(flag){
        case 0:
            res->u.t=t;
            break;
        case 1:
            res->u.l=l;
            break;
        default:
            return NULL;
    }
    return res;
}

arg* newArg(int flag, hash_ele* h, TEMP t, label *L, int num, float rnum, int width){
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
            break;
        default:
            return NULL;
    }
    return a;
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
        else if(ast->node->u.l->leaf_symbol->flag==1)
        {
            return newArg(3,0,0,0,ast->node->u.l->leaf_symbol->u.value_of_int,0,0);
        }
        else if(ast->node->u.l->leaf_symbol->flag==2)
        {
            return newArg(4,0,0,0,0,ast->node->u.l->leaf_symbol->u.value_of_real,0);
        }
    }
}

label* returnLabel(int flag, LABEL l, char* dataDef){
    label *L = (label*)malloc(sizeof(label));
    switch (flag)
    {
        case 0:
            L->u.l=l;
            break;
        case 1:
            L->u.dataDef=dataDef;
            break;
        default:
            return NULL;
    }
}

quadruple* newQuad(arg *a1, arg *a2, op* op, label *l, result *res){
    quadruple *q = (quadruple*)malloc(sizeof(quadruple));
    q->a1=a1;
    q->a2=a2;
    q->operand=op;
    q->L=l;
    q->res=res;
    q->next=NULL;
    return q;
}

char* concat(const char *s1, const char *s2)
{
    char *result = malloc(strlen(s1) + strlen(s2) + 2);
    strcpy(result, s1);
    strcat(result, ".");
    strcat(result, s2);
    return result;
}

quadruple* generateBoolean(ASTNodeIt* root)
{
    ASTNodeIt* temp=root;
    preorder_labelpopulation();
    while(1){
		while(temp->node->is_leaf==0){
			temp = temp->node->u.n->children;
		}
		//REACHED A LEAF
        //do nothing TK_LT, TK_LE, TK_EQ,TK_GT, TK_GE, TK_NE
		while(temp->next==NULL){
            temp = temp->node->parent;
            if(
                temp->node->u.n->leaf_symbol->tokenName==TK_GE||
                temp->node->u.n->leaf_symbol->tokenName==TK_LT||
                temp->node->u.n->leaf_symbol->tokenName==TK_LE||
                temp->node->u.n->leaf_symbol->tokenName==TK_EQ||
                temp->node->u.n->leaf_symbol->tokenName==TK_NE||
                temp->node->u.n->leaf_symbol->tokenName==TK_GT
            )
            {
                
                //If program node, ie root node is reached
                LABEL temp1=temp->quadhead->a1->u.L;
                LABEL temp2=temp->quadhead->a2->u.L;
                temp->quadhead->a1=getArg(temp->node->u.n->children);
                temp->quadhead->a2=getArg (temp->node->u.n->children->next);
                temp->quadhead->operand=temp->node->u.n->leaf_symbol->tokenName;
                temp->quadhead->res->u.l=temp1;

                temp->quadtail=newQuad(NULL,NULL,newOp(2,0,0),NULL,temp2);
                temp->quadhead->next=temp->quadtail;
            }
            else if(
                temp->node->u.n->leaf_symbol->tokenName==TK_AND||
                temp->node->u.n->leaf_symbol->tokenName==TK_OR||
                temp->node->u.n->leaf_symbol->tokenName==TK_NOT
            )
            {
                //figure out about arguments
                temp->quadhead=temp->node->u.n->children->quadhead;
                temp->node->u.n->children->quadtail=temp->node->u.n->children->next->quadhead;
                temp->quadtail=temp->node->u.n->children->next->quadtail;
            }

            // newQuad(,,,NULL,temp->node->u.n->children->)
			if(temp->node->parent->node->u.n->tag_info==TAG_ITERATIVE_STMT){
                if(temp->node->u.n->leaf_symbol->tokenName==TK_AND)
                {
                    //b1,b2,label(b.true),stmts,goto l0
                }
                else if(temp->node->u.n->leaf_symbol->tokenName==TK_AND)
                {
                    //b1,label(b.true),stmts,goto l0,b2
                }
                else
                {
                    //b,label(b.false),stmts,goto l0
                }
                
				break;	
			}
			
		}
        //iterate 
		temp = temp->next;
	}
}

quadruple* generateIntermediateCode(ASTNodeIt* root)
{
    //root=program
    ASTNodeIt *temp = root->node->u.n->children->next->node->u.n->children; //ignoring otherFunctions
    HashTable funcTable = lookupEle("_main", SymbolTable)->ele->u.out_table->SymbolTable;
    while(1){
        if(temp->node->u.n->tag_info==TAG_DECLARES){
            ASTNodeIt *it = temp->node->u.n->children;
            while(it!=NULL){
                hash_ele *g = lookupEle(it->node->u.n->leaf_symbol->u.lexeme, globalSymbolTable);
                hash_ele *s = lookupEle(it->node->u.n->leaf_symbol->u.lexeme, funcTable);
                if(g->ele!=NULL){
                    if(g->ele->u.g->u.t->is_record){
                        ASTNodeIt *r = lookupEle(g->ele->u.g->u.t->u.rec_id, globalSymbolTable)->ele->u.g->u.rec_type_list->record_ptr;
                        quadruple *ptr = newQuad(newArg(5, 0, 0, 0, 0, 0.0, (r->node->u.n->children->node->u.l->leaf_symbol->tokenName==TK_INT) ? 2 : 4), NULL, newOp(0, TAG_DECLARE, 0), returnLabel(1, 0, concat(it->node->u.n->leaf_symbol->u.lexeme, r->node->u.n->leaf_symbol->u.lexeme)), NULL);
                        it->quadhead = ptr;
                        r=r->next;
                        while(r!=NULL){
                            ptr->next = newQuad(newArg(5, 0, 0, 0, 0, 0.0, (r->node->u.n->children->node->u.l->leaf_symbol->tokenName==TK_INT) ? 2 : 4), NULL, newOp(0, TAG_DECLARE, 0), returnLabel(1, 0, concat(it->node->u.n->leaf_symbol->u.lexeme, r->node->u.n->leaf_symbol->u.lexeme)), NULL);
                            ptr=ptr->next;
                            r=r->next;
                        }
                    }
                    else{
                        it->quadhead=newQuad(newArg(5, NULL, 0, 0, 0, 0.0, (g->ele->u.g->u.t->u.pri_type==0) ? 2 : 4), NULL, newOp(0, TAG_DECLARE, 0), returnLabel(1, 0, it->node->u.n->leaf_symbol->u.lexeme), NULL);
                    }
                }
                else if(s->ele!=NULL){
                    if(s->ele->u.s->t->is_record){
                        ASTNodeIt *r = lookupEle(g->ele->u.g->u.t->u.rec_id, globalSymbolTable)->ele->u.g->u.rec_type_list->record_ptr;
                        quadruple *ptr = newQuad(newArg(5, 0, 0, 0, 0, 0.0, (r->node->u.n->children->node->u.l->leaf_symbol->tokenName==TK_INT) ? 2 : 4), NULL, newOp(0, TAG_DECLARE, 0), returnLabel(1, 0, concat(it->node->u.n->leaf_symbol->u.lexeme, r->node->u.n->leaf_symbol->u.lexeme)), NULL);
                        it->quadhead = ptr;
                        r=r->next;
                        while(r!=NULL){
                            ptr->next = newQuad(newArg(5, 0, 0, 0, 0, 0.0, (r->node->u.n->children->node->u.l->leaf_symbol->tokenName==TK_INT) ? 2 : 4), NULL, newOp(0, TAG_DECLARE, 0), returnLabel(1, 0, concat(it->node->u.n->leaf_symbol->u.lexeme, r->node->u.n->leaf_symbol->u.lexeme)), NULL);
                            ptr=ptr->next;
                            r=r->next;
                        }
                    }
                    else{
                        it->quadhead=newQuad(newArg(5, NULL, 0, 0, 0, 0.0, s->ele->u.s->width), NULL, newOp(0, TAG_DECLARE, 0), returnLabel(1, 0, it->node->u.n->leaf_symbol->u.lexeme), NULL);
                    }
                }
                else printf("Not possible\n");
                it=it->next;
            }
            it = temp->node->u.n->children;
            temp->quadhead=it->quadhead;
            it=it->next;
            quadruple *qptr=temp->quadtail;
            while(it!=NULL){
                qptr->next=it->quadhead;
                it=it->next;
                qptr=it->quadtail;
            }
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
                    int check_val;
                    temp=temp->node->u.n->children;
                    if(temp->next==NULL){
                        check_val=0;
                    }
                    else check_val=1;
                    if(!check_val){
                        hash_ele *g = lookupEle(temp->node->u.n->leaf_symbol->u.lexeme, globalSymbolTable);
                        hash_ele *s = lookupEle(temp->node->u.n->leaf_symbol->u.lexeme, funcTable);
                        if(g->ele!=NULL){
                            temp->quadhead = newQuad(newArg(2, 0, 0, returnLabel(1, 0, temp->node->u.n->leaf_symbol->u.lexeme), 0, 0.0, 0), NULL, newOp(0, TAG_READ, 0), NULL, NULL);
                        }
                        else if(s->ele!=NULL){
                            temp->quadhead = newQuad(newArg(2, 0, 0, returnLabel(1, 0, temp->node->u.n->leaf_symbol->u.lexeme), 0, 0.0, 0), NULL, newOp(0, TAG_READ, 0), NULL, NULL);
                        }
                    }
                    else{
                        hash_ele *g = lookupEle(temp->node->u.n->leaf_symbol->u.lexeme, globalSymbolTable);
                        hash_ele *s = lookupEle(temp->node->u.n->leaf_symbol->u.lexeme, funcTable);
                        if(g->ele!=NULL){
                            ASTNodeIt *r = lookupEle(g->ele->u.g->u.t->u.rec_id, globalSymbolTable)->ele->u.g->u.rec_type_list->record_ptr;
                            while(r!=NULL){
                                if(strcmp(r->node->u.n->leaf_symbol->u.lexeme, temp->next->node->u.n->leaf_symbol->u.lexeme)==0) temp->quadhead = newQuad(newArg(2, 0, 0, returnLabel(1, 0, concat(temp->node->u.n->leaf_symbol->u.lexeme, temp->next->node->u.n->leaf_symbol->u.lexeme)), 0, 0.0, 0), NULL, newOp(0, TAG_READ, 0), NULL, NULL);
                                r=r->next;
                            }
                        }
                        else if(s->ele!=NULL){
                            ASTNodeIt *r = lookupEle(s->ele->u.s->t->u.rec_id, globalSymbolTable)->ele->u.g->u.rec_type_list->record_ptr;
                            while(r!=NULL){
                                if(strcmp(r->node->u.n->leaf_symbol->u.lexeme, temp->next->node->u.n->leaf_symbol->u.lexeme)==0) temp->quadhead = newQuad(newArg(2, 0, 0, returnLabel(1, 0, concat(temp->node->u.n->leaf_symbol->u.lexeme, temp->next->node->u.n->leaf_symbol->u.lexeme)), 0, 0.0, 0), NULL, newOp(0, TAG_READ, 0), NULL, NULL);
                                r=r->next;
                            }
                        }
                    }
                }
                else if(temp->node->u.n->tag_info==TAG_WRITE){
                    int check_val;
                    temp=temp->node->u.n->children;
                    if(temp->next==NULL){
                        check_val=0;
                    }
                    else check_val=1;
                    if(!check_val){
                        hash_ele *g = lookupEle(temp->node->u.n->leaf_symbol->u.lexeme, globalSymbolTable);
                        hash_ele *s = lookupEle(temp->node->u.n->leaf_symbol->u.lexeme, funcTable);
                        if(g->ele!=NULL){
                            temp->quadhead = newQuad(newArg(2, 0, 0, returnLabel(1, 0, temp->node->u.n->leaf_symbol->u.lexeme), 0, 0.0, 0), NULL, newOp(0, TAG_READ, 0), NULL, NULL);
                        }
                        else if(s->ele!=NULL){
                            temp->quadhead = newQuad(newArg(2, 0, 0, returnLabel(1, 0, temp->node->u.n->leaf_symbol->u.lexeme), 0, 0.0, 0), NULL, newOp(0, TAG_READ, 0), NULL, NULL);
                        }
                    }
                    else{
                        hash_ele *g = lookupEle(temp->node->u.n->leaf_symbol->u.lexeme, globalSymbolTable);
                        hash_ele *s = lookupEle(temp->node->u.n->leaf_symbol->u.lexeme, funcTable);
                        if(g->ele!=NULL){
                            ASTNodeIt *r = lookupEle(g->ele->u.g->u.t->u.rec_id, globalSymbolTable)->ele->u.g->u.rec_type_list->record_ptr;
                            while(r!=NULL){
                                if(strcmp(r->node->u.n->leaf_symbol->u.lexeme, temp->next->node->u.n->leaf_symbol->u.lexeme)==0) temp->quadhead = newQuad(newArg(2, 0, 0, returnLabel(1, 0, concat(temp->node->u.n->leaf_symbol->u.lexeme, temp->next->node->u.n->leaf_symbol->u.lexeme)), 0, 0.0, 0), NULL, newOp(0, TAG_READ, 0), NULL, NULL);
                                r=r->next;
                            }
                        }
                        else if(s->ele!=NULL){
                            ASTNodeIt *r = lookupEle(s->ele->u.s->t->u.rec_id, globalSymbolTable)->ele->u.g->u.rec_type_list->record_ptr;
                            while(r!=NULL){
                                if(strcmp(r->node->u.n->leaf_symbol->u.lexeme, temp->next->node->u.n->leaf_symbol->u.lexeme)==0) temp->quadhead = newQuad(newArg(2, 0, 0, returnLabel(1, 0, concat(temp->node->u.n->leaf_symbol->u.lexeme, temp->next->node->u.n->leaf_symbol->u.lexeme)), 0, 0.0, 0), NULL, newOp(0, TAG_READ, 0), NULL, NULL);
                                r=r->next;
                            }
                        }
                    }
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
        if(temp->next!=NULL) temp=temp->next;
        else{
            temp = root->node->u.n->children->next; 
            //Construct LL here
            return temp->quadhead;
        }
    }
}