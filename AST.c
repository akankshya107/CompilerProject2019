#include <stdio.h>
#include <stdlib.h>
#include "ASTDef.h"

ASTNodeIt* newNonLeafNode(TAG taginf, tokenInfo *ti, ASTNodeIt* input1, ASTNodeIt* input2, ASTNodeIt* input3){
    input1->next=input2;
    input2->next=input3;
    ASTNodeIt* final_node=(ASTNodeIt*)malloc(sizeof(ASTNodeIt));
    final_node->node->is_leaf=0;
    final_node->node->u.n->tag_info=taginf;
    final_node->node->u.n->leaf_symbol=ti;
    final_node->node->u.n->children=input1;
    ASTNodeIt* temp=input1;
    while(temp!=NULL){
        temp->node->parent = final_node;
        temp = temp->next;
    }
    return final_node;  
}

ASTNodeIt* ChildrenList(ASTNodeIt* input1, ASTNodeIt* input2){
    input1->next=input2;
    return input1;
}

ASTNodeIt* newLeafNode(tokenInfo *ti){
    ASTNodeIt* final_node = (ASTNodeIt*)malloc(sizeof(ASTNodeIt));
    final_node->node->is_leaf=1;
    final_node->node->u.l->leaf_symbol=ti;
    return final_node;
}

void freeChildren(treeNodeIt *temp){
    static int arr[23]= {TK_FUNID, TK_ID, TK_INT, TK_REAL, TK_RECORDID, TK_FIELDID, TK_GLOBAL, TK_ASSIGNOP, TK_NUM, TK_RNUM, TK_MUL, TK_DIV, TK_MINUS, TK_PLUS, TK_NOT, TK_AND, TK_OR, TK_LT, TK_LE, TK_GT, TK_GE,  TK_EQ,  TK_NE};
    treeNodeIt *freetemp;
    while(temp!=NULL){
        int flag=0;
        if(temp->t->is_leaf==1){
            for(int i=0; i<24; i++){
                if(temp->t->treeNode_type.l->leaf_symbol->tokenName==arr[i]){
                    temp=temp->next;
                    flag=1;
                }
            }
            if(flag==1){
                continue;
            }
        }
        if(temp->t->is_leaf==1){
            
            free(temp->t->treeNode_type.l->leaf_symbol);
            free(temp->t->treeNode_type.l);
        }else{
            free(temp->t->treeNode_type.n);
        }
        free(temp->t);
        freetemp=temp;
        temp=temp->next;
        free(freetemp);
    }
}

ASTNodeIt* semanticRuleExecute(treeNodeIt *t, int rule_no){
    switch(rule_no){
        //program.node = new Node(TAG_PROGRAM, NULL, new Node(TAG_FUN_LIST, NULL, otherFunctions.node), mainFunction.node)
        case 0: {
            treeNodeIt *temp = t->t->treeNode_type.n->children;
            ASTNodeIt* n = newNonLeafNode(TAG_PROGRAM, NULL, newNonLeafNode(TAG_FUN_LIST, NULL, temp->node, NULL, NULL), temp->next->node, NULL);
            freeChildren(temp);
            return n;
        }
        //mainFunction.node=newNonLeafNode(TAG_MAIN, NULL, stmts.node) 
        case 1:{
            ASTNodeIt* n = newNonLeafNode(TAG_MAIN, NULL, t->t->treeNode_type.n->children->node, NULL, NULL);
            return n;
        }
        //STMTS
        // stmts.node=new ChildrenList(newNode(TAG_TYPEDEFS, NULL,typeDefinitions.node),
        // new Node(TAG_DECLARES, NULL,declarations.node),
        // new Node(TAG_OTHERSTMTS,NULL, otherStmts.node),
        // new Node(TAG_RETURNSTMT,NULL, returnStmt.node))
        case 16:{
            treeNodeIt* temp=t->t->treeNode_type.n->children;
            ASTNodeIt* n1= ChildrenList(newNonLeafNode(TAG_OTHERSTMTS, NULL, temp->next->next->node,NULL,NULL),
                                        newNonLeafNode(TAG_RETURNSTMT, NULL, temp->next->next->next->node,NULL,NULL));
            ASTNodeIt* n2=ChildrenList(newNonLeafNode(TAG_DECLARES, NULL, temp->next->node,NULL,NULL),n1);
            ASTNodeIt* n3=ChildrenList(newNonLeafNode(TAG_TYPEDEFS, NULL, temp->node,NULL,NULL),n2);
            return n3;
        }

        //TYPE DEFINITIONS
        // typeDefinitions.node = ChildrenList(typeDefinition.node,typeDefinitions​ 1​ .node)
        case 17:{
            treeNodeIt* temp=t->t->treeNode_type.n->children;
            ASTNodeIt* n=ChildrenList(temp->node,temp->next->node);
            return n;
        }
        // typeDefinitions.node = NULL
        case 18:{
            // t->t->node=NULL;
            return (ASTNodeIt*)NULL;
        }
        // typeDefinition.node = new Node(TAG_TYPEDEF,LeafNode(TK_RECORDID),fieldDefinitions.node)
        case 19:{
            treeNodeIt* temp=t->t->treeNode_type.n->children;
            ASTNodeIt* leaf=newLeafNode(t->t->treeNode_type.n->children->next->t->treeNode_type.l->leaf_symbol);
            ASTNodeIt* n=newNonLeafNode(TAG_TYPEDEF,leaf->node->u.l->leaf_symbol,temp->next->next->node,NULL,NULL);
            return n;
        }
        // fieldDefinitions.node =ChildrenList(fieldDefinition.node,ChildrenList(fieldDefinition.node,moreFields.node))
        case 20:{
            treeNodeIt* temp=t->t->treeNode_type.n->children;
            ASTNodeIt* n1= ChildrenList(temp->next->node,temp->next->next->node);
            ASTNodeIt n2= ChildrenList(temp->node,n1);
            return n2;
        }
        // fieldDefinition.node = new Node(TAG_FIELDDEF,LeafNode(FIELDID),primitiveDataType.node)
        case 21:{
            treeNodeIt* temp=t->t->treeNode_type.n->children;
            ASTNodeIt* leaf=newLeafNode(temp->next->next->next->t->treeNode_type.l->leaf_symbol);
            ASTNodeIt* n= newNonLeafNode(TAG_FIELDDEF,leaf->node->u.l->leaf_symbol,temp->next->node,NULL,NULL );
            return n;
        }
        // moreFields.node = ChildrenList(fieldDefinition.node,moreFields​ 1​ .node)
        case 22:{
            treeNodeIt* temp=t->t->treeNode_type.n->children;
            ASTNodeIt* n=ChildrenList(temp->node,temp->next->node);
            return n;    
        }
        // moreFields.node=NULL
        case 23:{
            return NULL;
        }

        // DECLARATIONS
        // declarations.node = ChildrenList(declaration.node, declarations​ 1​ .node)
        case 24:{
            treeNodeIt* temp=t->t->treeNode_type.n->children;
            ASTNodeIt* n=ChildrenList(temp->node,temp->next->node);
            return n;
        }
        // declarations.node = NULL
        case 25:{
            return NULL;
        }
        // declaration.node=new Node(TAG_DECLARE, LeafNode(TK_ID),dataType.node, global_or_not.node)
        case 26:{
            treeNodeIt* temp=t->t->treeNode_type.n->children;
            ASTNodeIt* leaf=newLeafNode(temp->next->next->next->t->treeNode_type.l->leaf_symbol);
            ASTNodeIt* n=newNonLeafNode(TAG_DECLARE,leaf->node->u.l->leaf_symbol,temp->next->node,temp->next->next->next->next->node,NULL);
            return n;
        }
        // global_or_not.node=LeafNode(TK_GLOBAL)
        case 27:{
            treeNodeIt* temp=t->t->treeNode_type.n->children;
            ASTNodeIt* leaf=newLeafNode(temp->next->t->treeNode_type.l->leaf_symbol);
            return leaf;
        }
        // global_or_not.node = NULL
        case 28:{
            return NULL;
        }

        //OTHER STMTS
        // otherStmts.node =ChildrenList(stmt.node,otherStmts​ 1​ .node)
        case 29:{
            treeNodeIt* temp=t->t->treeNode_type.n->children;
            ASTNodeIt* n=ChildrenList(temp->node,temp->next->node);
            return n;
        }
        // otherStmts.node = NULL
        case 30:{
            return NULL;
        }

        // ARITHMETIC EXPRESSION
        //allVar.node = LeafNode(TK_NUM)
        case 50: return newLeafNode(t->t->treeNode_type.n->children->t->treeNode_type.l->leaf_symbol);
        //allVar.node = LeafNode(TK_RNUM)
        case 51: return newLeafNode(t->t->treeNode_type.n->children->t->treeNode_type.l->leaf_symbol);
        //allVar.node = ChildrenList( LeafNode(TK_ID), temp.node)
        case 52:{
            treeNodeIt *temp = t->t->treeNode_type.n->children;
            ASTNodeIt *n = ChildrenList(newLeafNode(temp->t->treeNode_type.l->leaf_symbo), temp->next->node);
            freeChildren(temp);
            return n;
        }
        //arithmeticExpression.node = expPrime.node
        //expPrime.inh = term.node
        case 53:{
            treeNodeIt *temp = t->t->treeNode_type.n->children;
            ASTNodeIt *n = temp->next->node;
            return n;
        }
        //expPrime1.inh = new Node(TAG_ARITHMETIC_EXPRESSION, lowPrecedenceOperators.node, expPrime.inh, term.node)
        //expPrime.node = expPrime1.node
        case 54:{
            treeNodeIt *temp = t->t->treeNode_type.n->children;
            ASTNodeIt *n = temp->next->node;
            return n;
        }
        //expPrime.node = expPrime.inh
        case 55:{
            if(t->t->treeNode_type.n->rule_no==53){
                t->inh=t->t->parent->t->treeNode_type.n->children->node;
            }
            else if(t->t->treeNode_type.n->rule_no==54){
                treeNodeIt *temp = t->t->parent->t->treeNode_type.n->children;
                t->inh=newNonLeafNode(TAG_ARITHMETIC_EXPRESSION, temp->node->node->u.l->leaf_symbol, temp->next->inh, temp->next->next->node, NULL);
            }
            return t->inh;
        // term.node = termPrime.node
        // termPrime.inh = factor.node
        case 56:
        // termPrime1.inh = new Node( TAG_ARITHMETIC_EXPRESSION, highPrecedenceOperators.node, termPrime.inh, factor.node)
        // termPrime.node = termPrime1.node
        case 57:
        // termPrime.nd = termPrime.inh
        case 58:
        // factor.node = arithmeticExpression.node
        case 59: return t->t->treeNode_type.n->children->next->node;
        // factor.node = allVar.node
        case 60: return t->t->treeNode_type.n->children->node;
        // highPrecedenceOperators.node = LeafNode(TK_MUL)
        case 61: return newLeafNode(t->t->treeNode_type.n->children->t->treeNode_type.l->leaf_symbol);
        // highPrecedenceOperators.node = LeafNode(TK_DIV)
        case 62: return newLeafNode(t->t->treeNode_type.n->children->t->treeNode_type.l->leaf_symbol);
        // lowPrecedenceOperators.node = LeafNode(TK_PLUS)
        case 63: return newLeafNode(t->t->treeNode_type.n->children->t->treeNode_type.l->leaf_symbol);
        // lowPrecedenceOperators.node = LeafNode(TK_MINUS)
        case 64: return newLeafNode(t->t->treeNode_type.n->children->t->treeNode_type.l->leaf_symbol);
        // temp.node = NULL
        case 65: return (ASTNodeIt*)NULL;
        // temp.node = LeafNode(TK_FIELDID)
        case 66: {
            treeNodeIt *temp = t->t->treeNode_type.n->children;
            ASTNodeIt* n = newLeafNode(temp->next->t->treeNode_type.l->leaf_symbol);
            freeChildren(temp);
            return n;
        }

        // BOOLEAN EXPRESSION
        // booleanExpression.node = new Node( TAG_BOOLEAN_EXPRESSION, logicalOp.node, booleanExpression1.node, booleanExpression2.node)
        case 67: {
            treeNodeIt *temp = t->t->treeNode_type.n->children;
            ASTNodeIt* n = newNonLeafNode(TAG_BOOLEAN_EXPRESSION, temp->next->next->next->node->node->u.l->leaf_symbol, temp->next->node, temp->next->next->next->next->next->node, NULL);
            freeChildren(temp);
            return n;
        }
        // booleanExpression.node = new Node( TAG_BOOLEAN_EXPRESSION, relationalOp.node, var1.node, var2.node)
        case 68: {
            treeNodeIt *temp = t->t->treeNode_type.n->children;
            ASTNodeIt* n = newNonLeafNode(TAG_BOOLEAN_EXPRESSION, temp->next->node->node->u.l->leaf_symbol, temp->node, temp->next->next->node, NULL);
            freeChildren(temp);
            return n;
        }
        // booleanExpression.node = new Node( TAG_BOOLEAN_EXPRESSION, leafNode(TK_NOT), booleanExpression1.node)
        case 69: {
            treeNodeIt *temp = t->t->treeNode_type.n->children;
            ASTNodeIt* n = newNonLeafNode(TAG_BOOLEAN_EXPRESSION, temp->t->treeNode_type.l->leaf_symbol, temp->next->next->node, NULL, NULL);
            freeChildren(temp);
            return n;
        }
        // var.node = LeafNode(TK_ID)
        case 70: return newLeafNode(t->t->treeNode_type.n->children->t->treeNode_type.l->leaf_symbol);
        // var.node = LeafNode(TK_NUM)
        case 71: return newLeafNode(t->t->treeNode_type.n->children->t->treeNode_type.l->leaf_symbol);
        // var.node = LeafNode(TK_RNUM)
        case 72: return newLeafNode(t->t->treeNode_type.n->children->t->treeNode_type.l->leaf_symbol);
        // logicalOp.node = LeafNode(TK_AND)
        case 73: return newLeafNode(t->t->treeNode_type.n->children->t->treeNode_type.l->leaf_symbol);
        // logicalOp.node = LeafNode(TK_OR)
        case 74: return newLeafNode(t->t->treeNode_type.n->children->t->treeNode_type.l->leaf_symbol);
        // relationalOp.node = LeafNode(TK_LT)
        case 75: return newLeafNode(t->t->treeNode_type.n->children->t->treeNode_type.l->leaf_symbol);
        // relationalOp.node = LeafNode(TK_LE)
        case 76: return newLeafNode(t->t->treeNode_type.n->children->t->treeNode_type.l->leaf_symbol);
        // relationalOp.node = LeafNode(TK_EQ)
        case 77: return newLeafNode(t->t->treeNode_type.n->children->t->treeNode_type.l->leaf_symbol);
        // relationalOp.node = LeafNode(TK_GT)
        case 78: return newLeafNode(t->t->treeNode_type.n->children->t->treeNode_type.l->leaf_symbol);
        // relationalOp.node = LeafNode(TK_GE)
        case 79: return newLeafNode(t->t->treeNode_type.n->children->t->treeNode_type.l->leaf_symbol);
        // relationalOp.node = LeafNode(TK_NE)
        case 80: return newLeafNode(t->t->treeNode_type.n->children->t->treeNode_type.l->leaf_symbol);

        //RETURN STMT  
        // returnStmt.node=optionalReturn.node
        case 81:{
            treeNodeIt* temp=t->t->treeNode_type.n->children;
            return temp->next->node;    
        }
        // optionalReturn.node=idList.node
        case 82:{
            treeNodeIt* temp=t->t->treeNode_type.n->children;
            return temp->next->node; 
        }
        // optionalReturn.node = NULL
        case 83:{
            return NULL;
        }
        // idList.node = ChildrenList(LeafNode(TK_ID), more_ids.node)
        case 84:{
            treeNodeIt* temp=t->t->treeNode_type.n->children;
            ASTNodeIt* leaf=newLeafNode(temp->t->treeNode_type.l->leaf_symbol);
            ASTNodeIt* n=ChildrenList(leaf->node->u.l->leaf_symbol,temp->next->node);
            return n;
        }
        // more_ids.node=idList.node
        case 85:{
            treeNodeIt* temp=t->t->treeNode_type.n->children;
            return temp->next->node;
        }
        // more_ids.node =NULL
        case 86:{
            return NULL;
        }

    }
}

ASTNodeIt* makeAbstractSyntaxTree(treeNodeIt *root){
    treeNodeIt *temp = root;
	while(1){
		while(temp->t->is_leaf==0){
			temp = temp->t->treeNode_type.n->children;
			if (temp==NULL) break;
		}
		if (temp==NULL) break;
		//REACHED A LEAF
        //do nothing
		while(temp->next==NULL){
			temp = temp->t->parent;
            //If program node, ie root node is reached
			if(temp->t->parent==NULL){
				temp->node = semanticRuleExecute(temp, 0);
				return temp->node;	
			}
			//REACHED A NON-LEAF
            //Get ASTNode and free the subsequent nodes
            if(temp->t->treeNode_type.n->children->t->is_leaf==0){
                temp->node = semanticRuleExecute(temp, temp->t->treeNode_type.n->children->t->treeNode_type.n->rule_no);
            }else{
                temp->node = semanticRuleExecute(temp, temp->t->treeNode_type.n->children->t->treeNode_type.l->rule_no);
            }
		}
        //iterate 
		temp = temp->next;
	}
}