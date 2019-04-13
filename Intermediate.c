// GROUP 39
// AKANKSHYA MISHRA 2016A7PS0026P
// NARAPAREDDY BHAVANA 2016A7PS0034P
// KARABEE BATTA 2016A7PS0052P
// AASTHA KATARIA 2016A7PS0062P
#include "IntermediateDef.h"

int newTemp(){
    static int t=0;
    return t++;
}

int newLabel(){
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

arg* newArg(int flag, hash_ele* h, TEMP t, LABEL L, int num, float rnum){
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

quadruple* newQuad(arg *a1, arg *a2, op* op, LABEL l, result *res){
    quadruple *q = (quadruple*)malloc(sizeof(quadruple));
    q->a1=a1;
    q->a2=a2;
    q->operand=op;
    q->l=l;
    q->res=res;
    q->next=NULL;
    return q;
}

quadruple* generateIntermediateCode(ASTNodeIt* root)
{
    //root=program
    ASTNodeIt *temp = root->node->u.n->children->next->node->u.n->children; //ignoring otherFunctions
    while(1){
        if(temp->node->u.n->tag_info==TAG_DECLARES){
            ASTNodeIt *it = temp->node->u.n->children;
            while(it!=NULL){
                it=it->next;
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