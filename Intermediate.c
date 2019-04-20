// GROUP 39
// AKANKSHYA MISHRA 2016A7PS0026P
// NARAPAREDDY BHAVANA 2016A7PS0034P
// KARABEE BATTA 2016A7PS0052P
// AASTHA KATARIA 2016A7PS0062P
#include "IntermediateDef.h"
#include <string.h>
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

char* concat(const char *s1, const char *s2)
{
    char *result = malloc(strlen(s1) + strlen(s2) + 2);
    strcpy(result, s1);
    strcat(result, ".");
    strcat(result, s2);
    return result;
}

arg* getArg(ASTNodeIt* ast)
{
    int check_val;
    ast=ast->node->u.n->children;
    if(ast->next->node->is_leaf){
        check_val=1;
    }
    else check_val=0;
    if(!check_val)
    {
        if(ast->node->u.l->leaf_symbol->flag==is_lexeme)
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
        else if(ast->node->u.l->leaf_symbol->flag==is_int)
        {
            return newArg(3,0,0,0,ast->node->u.l->leaf_symbol->u.value_of_int,0,0);
        }
        else if(ast->node->u.l->leaf_symbol->flag==is_real)
        {
            return newArg(4,0,0,0,0,ast->node->u.l->leaf_symbol->u.value_of_real,0);
        }
    }
    else{
        hash_ele *g = lookupEle(ast->node->u.n->leaf_symbol->u.lexeme, globalSymbolTable);
        hash_ele *s = lookupEle(ast->node->u.n->leaf_symbol->u.lexeme, lookupEle("_main", SymbolTable)->ele->u.out_table->SymbolTable);
        if(g->ele!=NULL){
            ASTNodeIt *r = lookupEle(g->ele->u.g->u.t->u.rec_id, globalSymbolTable)->ele->u.g->u.rec_type_list->record_ptr;
            while(r!=NULL){
                if(strcmp(r->node->u.n->leaf_symbol->u.lexeme, ast->next->node->u.n->leaf_symbol->u.lexeme)==0) return newArg(2, 0, 0, returnLabel(1, 0, concat(ast->node->u.n->leaf_symbol->u.lexeme, ast->next->node->u.n->leaf_symbol->u.lexeme)), 0, 0.0, 0);
                r=r->next;
            }
        }
        else if(s->ele!=NULL){
            ASTNodeIt *r = lookupEle(s->ele->u.s->t->u.rec_id, globalSymbolTable)->ele->u.g->u.rec_type_list->record_ptr;
            while(r!=NULL){
                if(strcmp(r->node->u.n->leaf_symbol->u.lexeme, ast->next->node->u.n->leaf_symbol->u.lexeme)==0) return newArg(2, 0, 0, returnLabel(1, 0, concat(ast->node->u.n->leaf_symbol->u.lexeme, ast->next->node->u.n->leaf_symbol->u.lexeme)), 0, 0.0, 0);
                r=r->next;
            }
        }
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

LABEL getLabel(ASTNodeIt* n)
{
    int temp;
    if(n->quadhead==NULL)
    {
        temp=newLabel();
        // n->quadhead=newQuad(NULL,NULL,NULL,temp,NULL);
        return temp;
    }
    else
    {
        if(n->quadhead->L=NULL)
        {
            temp=newLabel();
            n->quadhead->L->flag=0;
            n->quadhead->L->u.l=temp;
            return temp;
        }
        else
        {
            // if(n->quadhead->L->flag==0)
            {
                return n->quadhead->L->u.l;
            }
        }
    }
}

void preorder_labelpopulation(ASTNodeIt* root)
{
    // root->node->parent->next->quadhead=newQuad(NULL,NULL,NULL,newLabel(),NULL);
    // root->next->quadhead=newQuad(NULL,NULL,NULL,newLabel(),NULL);
    root->quadhead->a1->u.L=returnLabel(0, getLabel(root->node->parent->next), NULL);
    root->quadhead->a2->u.L=returnLabel(0, getLabel(root->next), NULL);

    ASTNodeIt* temp=root;
    while(1)
    {
        while(!temp->node->is_leaf)
        {
            temp=temp->node->u.n->children;
            // temp->next->quadhead=newQuad(NULL,NULL,NULL,newLabel(),NULL);
            // temp->quadhead=newQuad(NULL,NULL,NULL,newLabel(),NULL);
            if(temp->quadhead==NULL)
                temp->quadhead=newQuad(NULL,NULL,NULL,NULL,NULL);
            if(temp->next->quadhead==NULL)
            temp->next->quadhead=newQuad(NULL,NULL,NULL,NULL,NULL);

            if(temp->node->parent->node->u.n->tag_info==TK_AND)
            {
                
                temp->quadhead->a1->u.L=returnLabel(0, getLabel(temp->next), NULL);
                temp->next->quadhead->a1->u.L=temp->node->parent->quadhead->a1->u.L;
                temp->quadhead->a2->u.L=temp->node->parent->quadhead->a2->u.L;
                temp->next->quadhead->a2->u.L=temp->next->node->parent->quadhead->a2->u.L;

            }
            if(temp->node->parent->node->u.n->tag_info==TK_OR)
            {
                temp->quadhead->a2->u.L=returnLabel(0, getLabel(temp->next), NULL);
                temp->next->quadhead->a1->u.L=temp->node->parent->quadhead->a2->u.L;
                temp->quadhead->a1->u.L=temp->node->parent->quadhead->a1->u.L;
                temp->next->quadhead->a1->u.L=temp->next->node->parent->quadhead->a1->u.L;
            }

            if(temp->node->parent->node->u.n->tag_info==TK_NOT)
            {
                temp->quadhead->a1->u.L=temp->node->parent->quadhead->a2->u.L;
                temp->quadhead->a2->u.L=temp->node->parent->quadhead->a1->u.L;
            }

        }
        if(temp->node->is_leaf)
        {
            if(temp->next!=NULL)
                temp=temp->next;
            else
            {
                while(temp->node->parent->next!=NULL)
                {
                    temp=temp->node->parent;
                    if(temp==root)
                    break;
                }
                temp=temp->next;
            }
        }
    }
}

quadruple* generateBoolean(ASTNodeIt* root)
{
    ASTNodeIt* temp=root;
    preorder_labelpopulation(root);
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
                label *temp1=temp->quadhead->a1->u.L;
                label *temp2=temp->quadhead->a2->u.L;
                temp->quadhead->a1=getArg(temp->node->u.n->children);
                temp->quadhead->a2=getArg (temp->node->u.n->children->next);
                temp->quadhead->operand=newOp(1,0,temp->node->u.n->leaf_symbol->tokenName);
                // temp->quadhead->res->u.l=temp1;

                // temp->quadtail=newQuad(NULL,NULL,newOp(2,0,0),NULL,temp2);
                temp->quadhead->next=temp->quadtail;
            }
            else if(
                temp->node->u.n->leaf_symbol->tokenName==TK_AND||
                temp->node->u.n->leaf_symbol->tokenName==TK_OR
            )
            {
                //figure out about arguments
                temp->quadhead=temp->node->u.n->children->quadhead;
                temp->node->u.n->children->quadtail=temp->node->u.n->children->next->quadhead;
                temp->quadtail=temp->node->u.n->children->next->quadtail;
            }

            else if(temp->node->u.n->leaf_symbol->tokenName==TK_NOT)
            {
                temp->quadhead=temp->node->u.n->children->quadhead;
                temp->quadtail=temp->node->u.n->children->quadtail;
            }

            // newQuad(,,,NULL,temp->node->u.n->children->)
			if(temp->node->parent->node->u.n->tag_info==TAG_ITERATIVE_STMT){
                if(temp->node->u.n->leaf_symbol->tokenName==TK_AND)
                {
                    temp->quadhead=temp->node->u.n->children->quadhead;
                    temp->node->u.n->children->quadtail=temp->node->u.n->children->next->quadhead;
                    temp->quadtail=temp->node->u.n->children->next->quadtail;
                    temp->quadtail->next=newQuad(NULL,NULL,NULL,NULL,NULL);
                    // temp->quadtail=temp->quadtail->next;

                    //b1,b2,label(b.true),stmts,goto l0
                }
                else if(temp->node->u.n->leaf_symbol->tokenName==TK_OR)
                {
                    temp->quadhead=temp->node->u.n->children->quadhead;
                    temp->quadhead->next=newQuad(NULL,NULL,NULL,NULL,NULL);
                    temp->quadhead->next->next=temp->node->u.n->children->next->quadhead;

                    //b1,label(b.true),stmts,goto l0,b2
                }
                else
                {
                    // temp->quadhead=temp->node->u.n->children;
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
    return NULL;
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
            int flag=0;
            while(1){
                if(temp->node->u.n->tag_info==TAG_ASSIGNMENT_STMT){       
                    ASTNodeIt* temp_post=temp;
                    quadruple* quadIt=NULL;
                    ASTNodeIt *left_child=temp->node->u.n->children;
                    temp_post=left_child->next;// because the left child will be a variable (x=arithmetic expression)
            
                    //travel to the leaf nodes
                    while(temp_post->node->is_leaf==0){
                        temp_post=temp_post->node->u.n->children;
                    }

                    //post order traversal
                    while(temp->next==NULL)
                    {
                        ASTNodeIt* temp_post_parent;
                        temp_post_parent=temp_post->node->parent;
                        if(temp_post_parent!=temp)
                        {
                            quadIt = newQuad(getArg(temp_post), getArg(temp_post->next), newOp(1,0,temp_post_parent->node->u.n->leaf_symbol->tokenName), NULL, newResult(0, newTemp(), 0));
                            
                            if(temp_post->quadhead!=NULL && temp_post->next->quadhead!=NULL){
                                temp_post_parent->quadhead=temp_post->quadhead;
                                temp_post->quadtail->next=temp_post->next->quadhead;
                                temp_post->next->quadtail->next=quadIt;
                                temp_post_parent->quadtail=quadIt;
                            }
                            else if(temp_post->quadhead!=NULL){
                                temp_post_parent->quadhead=temp_post->quadhead;
                                temp_post->quadtail->next=quadIt;
                                temp_post_parent->quadtail=quadIt;
                            }
                            else if(temp_post->next->quadhead!=NULL){
                                temp_post_parent->quadhead=temp_post->next->quadhead;
                                temp_post->next->quadtail->next=quadIt;
                                temp_post_parent->quadtail=quadIt;
                            }
                            else{
                                temp_post_parent->quadhead=quadIt;
                                temp_post_parent->quadtail=quadIt;
                            }

                            temp_post=temp_post_parent;
                        }
                        else //if rhs is also a leaf node or post order traversal has been completed , then generate a quad accordingly
                        {
                            //now lhs and rhs are ready
                            if(temp->quadhead!=NULL){
                                LABEL x = temp->quadhead->L->u.l;
                                quadIt=newQuad(getArg(left_child), getArg(temp_post), newOp(0, TAG_ASSIGNMENT_STMT, 0), returnLabel(0, x, NULL), NULL);
                            }else{
                                quadIt=newQuad(getArg(left_child), getArg(temp_post), newOp(0, TAG_ASSIGNMENT_STMT, 0), NULL, NULL);
                                
                            }
                            if(temp_post->quadhead!=NULL && temp_post->next->quadhead!=NULL){
                                temp->quadhead=temp_post->quadhead;
                                temp_post->quadtail->next=temp_post->next->quadhead;
                                temp_post->next->quadtail->next=quadIt;
                                temp->quadtail=quadIt;
                            }
                            else if(temp_post->quadhead!=NULL){
                                temp->quadhead=temp_post->quadhead;
                                temp_post->quadtail->next=quadIt;
                                temp->quadtail=quadIt;
                            }
                            else if(temp_post->next->quadhead!=NULL){
                                temp->quadhead=temp_post->next->quadhead;
                                temp_post->next->quadtail->next=quadIt;
                                temp->quadtail=quadIt;
                            }
                            else{
                                temp->quadhead=quadIt;
                                temp->quadtail=quadIt;
                            }
                            break;
                        }
                        temp=temp->next;
                    }
                }

                else if(temp->node->u.n->tag_info==TAG_ITERATIVE_STMT){
                    //While statement: one pass for checking if variables are being changed
                    //Boolean respective code
                    if(temp->node->u.n->leaf_symbol->tokenName==TK_AND)
                    {
                        temp->quadtail->next=temp->node->parent->quadhead;
                        temp->quadtail=temp->node->parent->quadtail;
                    }
                    else if(temp->node->u.n->leaf_symbol->tokenName==TK_OR)
                    {
                        quadruple* dummy=temp->quadtail->next->next;
                        temp->quadtail->next=temp->node->parent->node->u.n->children->next->quadhead;
                        // temp->quadtail=temp->node->parent->quadtail;
                        temp->quadtail->next=dummy;
                        quadruple* p=temp->quadtail->next;
                        while(p->next!=NULL)
                        {
                            p=p->next;
                        }
                        temp->quadtail=p;
                    }
                    else
                    {
                        
                    }
                    temp=temp->node->parent;

                    //attach inner code to dummy var
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
                    if(temp->node->u.l->leaf_symbol->flag!=is_lexeme){
                        if(temp->node->u.l->leaf_symbol->flag==is_int) temp->quadhead = newQuad(newArg(3, NULL, 0, NULL, temp->node->u.l->leaf_symbol->u.value_of_int, 0, 0), NULL, newOp(0, TAG_WRITE, 0), NULL, NULL);
                        if(temp->node->u.l->leaf_symbol->flag==is_real) temp->quadhead = newQuad(newArg(4, NULL, 0, NULL, 0, temp->node->u.l->leaf_symbol->u.value_of_real, 0), NULL, newOp(0, TAG_WRITE, 0), NULL, NULL);
                    }
                    else if(!check_val){
                        
                        hash_ele *g = lookupEle(temp->node->u.n->leaf_symbol->u.lexeme, globalSymbolTable);
                        hash_ele *s = lookupEle(temp->node->u.n->leaf_symbol->u.lexeme, funcTable);
                        if(g->ele!=NULL){
                            temp->quadhead = newQuad(newArg(2, 0, 0, returnLabel(1, 0, temp->node->u.n->leaf_symbol->u.lexeme), 0, 0.0, 0), NULL, newOp(0, TAG_WRITE, 0), NULL, NULL);
                        }
                        else if(s->ele!=NULL){
                            temp->quadhead = newQuad(newArg(2, 0, 0, returnLabel(1, 0, temp->node->u.n->leaf_symbol->u.lexeme), 0, 0.0, 0), NULL, newOp(0, TAG_WRITE, 0), NULL, NULL);
                        }
                    }
                    else{
                        hash_ele *g = lookupEle(temp->node->u.n->leaf_symbol->u.lexeme, globalSymbolTable);
                        hash_ele *s = lookupEle(temp->node->u.n->leaf_symbol->u.lexeme, funcTable);
                        if(g->ele!=NULL){
                            ASTNodeIt *r = lookupEle(g->ele->u.g->u.t->u.rec_id, globalSymbolTable)->ele->u.g->u.rec_type_list->record_ptr;
                            while(r!=NULL){
                                if(strcmp(r->node->u.n->leaf_symbol->u.lexeme, temp->next->node->u.n->leaf_symbol->u.lexeme)==0) temp->quadhead = newQuad(newArg(2, 0, 0, returnLabel(1, 0, concat(temp->node->u.n->leaf_symbol->u.lexeme, temp->next->node->u.n->leaf_symbol->u.lexeme)), 0, 0.0, 0), NULL, newOp(0, TAG_WRITE, 0), NULL, NULL);
                                r=r->next;
                            }
                        }
                        else if(s->ele!=NULL){
                            ASTNodeIt *r = lookupEle(s->ele->u.s->t->u.rec_id, globalSymbolTable)->ele->u.g->u.rec_type_list->record_ptr;
                            while(r!=NULL){
                                if(strcmp(r->node->u.n->leaf_symbol->u.lexeme, temp->next->node->u.n->leaf_symbol->u.lexeme)==0) temp->quadhead = newQuad(newArg(2, 0, 0, returnLabel(1, 0, concat(temp->node->u.n->leaf_symbol->u.lexeme, temp->next->node->u.n->leaf_symbol->u.lexeme)), 0, 0.0, 0), NULL, newOp(0, TAG_WRITE, 0), NULL, NULL);
                                r=r->next;
                            }
                        }
                    }
                }
                else printf("Check AST structure\n");
                
                while(temp->next==NULL){
                    if(temp->node->parent->node->u.n->tag_info==TAG_OTHERSTMTS){
                        //make LL and
                        ASTNodeIt *ch = temp->node->parent->node->u.n->children;
                        temp->node->parent->quadhead = ch->quadhead;
                        while(ch->next!=NULL){
                            ch->quadtail->next=ch->next->quadhead;
                            ch=ch->next;
                        }
                        temp->node->parent->quadtail=ch->quadtail;
                        flag=1;
                        break;
                    }
                    if(temp->node->parent->node->u.n->tag_info==TAG_ITERATIVE_STMT){
                        temp=temp->node->parent;
                        //attach inner code to dummy var
                    }
                    if(temp->node->parent->node->u.n->tag_info==TAG_THEN){
                        temp=temp->node->parent;
                        ASTNodeIt *ch = temp->node->parent->node->u.n->children;
                        temp->node->parent->quadhead = ch->quadhead;
                        while(ch->next!=NULL){
                            ch->quadtail->next=ch->next->quadhead;
                            ch=ch->next;
                        }
                        temp->node->parent->quadtail=ch->quadtail;
                    }
                    if(temp->node->parent->node->u.n->tag_info==TAG_ELSE){
                        temp=temp->node->parent;
                        ASTNodeIt *ch = temp->node->parent->node->u.n->children;
                        temp->node->parent->quadhead = ch->quadhead;
                        while(ch->next!=NULL){
                            ch->quadtail->next=ch->next->quadhead;
                            ch=ch->next;
                        }
                        temp->node->parent->quadtail=ch->quadtail;
                    }
                    if(temp->node->parent->node->u.n->tag_info==TAG_COND_STMT){
                        temp=temp->node->parent;
                        //attach inner code to dummy var
                    }
                    else temp=temp->node->parent;
                }
                if(flag) break;
                temp=temp->next;
            }
        }
        if(temp->next!=NULL) temp=temp->next;
        else{
            temp = root->node->u.n->children->next; 
            ASTNodeIt *ch = temp->node->u.n->children;
            temp->quadhead = ch->quadhead;
            while(ch->next!=NULL){
                if(ch->quadhead==NULL) break;
                ch->quadtail->next=ch->next->quadhead;
                ch=ch->next;
            }
            temp->quadtail=ch->quadtail;
            return temp->quadhead;
        }
    }
}