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
            if(lookupEle(ast->node->u.l->leaf_symbol->u.lexeme,globalSymbolTable)!=NULL)
            {
                return newArg(0, lookupEle(ast->node->u.l->leaf_symbol->u.lexeme,globalSymbolTable),0,0,0,0,0);
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

quadruple* newQuad(arg *a1, arg *a2, op* op, label* l, result *res){
    quadruple *q = (quadruple*)malloc(sizeof(quadruple));
    q->a1=a1;
    q->a2=a2;
    q->operand=op;
    q->l=l;
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
        n->quadhead=newQuad(NULL,NULL,NULL,temp,NULL);
        return temp;
    }
    else
    {
        if(n->quadhead->l=NULL)
        {
            temp=newLabel();
            n->quadhead->l->flag=0;
            n->quadhead->l->u.l=temp;
            return temp;
        }
        else
        {
            // if(n->quadhead->l->flag==0)
            {
                return n->quadhead->l->u.l;
            }
        }
    }
}

void preorder_labelpopulation(ASTNodeIt* root)
{
    // root->node->parent->next->quadhead=newQuad(NULL,NULL,NULL,newLabel(),NULL);
    // root->next->quadhead=newQuad(NULL,NULL,NULL,newLabel(),NULL);
    root->quadhead->a1->u.L=getLabel(root->node->parent->next);
    root->quadhead->a2->u.L=getLabel(root->next);

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
                
                temp->quadhead->a1->u.L=getLabel(temp->next);
                temp->next->quadhead->a1->u.L=temp->node->parent->quadhead->a1->u.L;
                temp->quadhead->a2->u.L=temp->node->parent->quadhead->a2->u.L;
                temp->next->quadhead->a2->u.L=temp->next->node->parent->quadhead->a2->u.L;

            }
            if(temp->node->parent->node->u.n->tag_info==TK_OR)
            {
                temp->quadhead->a2->u.L=getLabel(temp->next);
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
                LABEL temp1=temp->quadhead->a1->u.L;
                LABEL temp2=temp->quadhead->a2->u.L;
                temp->quadhead->a1=getArg(temp->node->u.n->children);
                temp->quadhead->a2=getArg (temp->node->u.n->children->next);
                temp->quadhead->operand=newOp(1,0,temp->node->u.n->leaf_symbol->tokenName);
                temp->quadhead->res->u.l=temp1;

                temp->quadtail=newQuad(NULL,NULL,newOp(2,0,0),NULL,temp2);
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
                    temp->quadhead=temp->node->u.n->children;
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
                    it->quadhead=newQuad(newArg(0, g->ele, 0, 0, 0, 0.0), NULL, newOp(0, TAG_DECLARE, 0), -1, NULL);
                }
                else if(s->ele!=NULL){
                    it->quadhead=newQuad(newArg(0, s->ele, 0, 0, 0, 0.0), NULL, newOp(0, TAG_DECLARE, 0), -1, NULL);
                }
                else print("Not possible\n");
                it=it->next;
            }
            it = temp->node->u.n->children;
            temp->quadhead=it->quadhead;
            it=it->next;
            quadruple *qptr=temp->quadhead;
            while(it!=NULL){
                qptr->next=it->quadhead;
                it=it->next;
                qptr=qptr->next;
            }
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
            return temp->quadhead;
        }
    }
}
