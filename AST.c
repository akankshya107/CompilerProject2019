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

        //STMT
        //stmt -->assignmentStmt, stmt.node = assignmentStmt.node
        case 31 :
        {
         treeNodeIt *temp = t->t->treeNode_type.n->children;
         ASTNodeIt *n = temp->node;
         return n;
        }
        // stmt -->iterativeStmt, stmt.node = iterativeStmt.node
        case 32 :
        {
         treeNodeIt *temp = t->t->treeNode_type.n->children;
         ASTNodeIt *n = temp->node;
         return n;   
        }
        //stmt -->conditionalStmt, stmt.node= conditionalStmt.node
        case 33 :
        {
         treeNodeIt *temp = t->t->treeNode_type.n->children;
         ASTNodeIt *n = temp->node;
         return n;
        }
        //stmt -->ioStmt, stmt.node= ioStmt.node
        case 34 :
        {
         treeNodeIt *temp = t->t->treeNode_type.n->children;
         ASTNodeIt *n = temp->node;
         return n;
        }
        // stmt -->funCallStmt, stmt.node = funCallStmt.node
        case 35 :
        {
         treeNodeIt *temp = t->t->treeNode_type.n->children;
         ASTNodeIt *n = temp->node;
         return n;
        }
        // assignmentStmt -->singleOrRecId  TK_ASSIGNOP arithmeticExpression  TK_SEM 
        //Stmt.node = newNode( TAG_ASSIGNMENT_STMT, LeafNode(TK_ASSIGNOP), singleOrRecId.node, arithmeticExpression.node)
        case 36 :
        {
            treeNodeIt *temp = t->t->treeNode_type.n->children;
            ASTNodeIt* n = newNonLeafNode(TAG_ASSIGNMENT_STMT, temp->t->treeNode_type.l->leaf_symbol, temp->node, temp->next->next->node, NULL);
            freeChildren(temp);
            return n;
        }
        //singleOrRecId --> TK_ID new_24, singleOrRecId.node = ChildrenList( LeafNode(TK_ID), new_24.node)
        case 37 :
        {
            treeNodeIt *temp = t->t->treeNode_type.n->children;
            ASTNodeIt *n = ChildrenList(newLeafNode(temp->t->treeNode_type.l->leaf_symbol), temp->next->node);
            freeChildren(temp);
            return n;        

        }
        //new_24.node = NULL
        case 38 :
        {
            return NULL;
        }
        //new_24.node = LeafNode(TK_FIELDID)
        case 39 :
        {
            return newLeafNode(t->t->treeNode_type.n->children->t->treeNode_type.l->leaf_symbol);
        }
        //funCallStmt -->outputParameters  TK_CALL  TK_FUNID  TK_WITH TK_PARAMETERS inputParameters  TK_SEM
        //funCallStmt.node = new Node( FUN_CALL_STMT, LeafNode(TK_FUNID), new Node(TAG_OUTPUT_ARGS, NULL, outputParameters.node), new Node( TAG_INPUT_ARGS, NULL, inputParameters.node))
        case 40 :
        {
            treeNodeIt *temp = t->t->treeNode_type.n->children;
            ASTNodeIt* n = newNonLeafNode(TAG_FUN_CALL_STMT, temp->t->treeNode_type.l->leaf_symbol, newNonLeafNode(TAG_OUTPUT_ARGS,NULL,temp->node,NULL,NULL), newNonLeafNode(TAG_INPUT_ARGS, NULL,temp->next->next->next->next->next->node,NULL,NULL), NULL);
            freeChildren(temp);
            return n;

        }
        // outputParameters --> TK_SQL idList  TK_SQR  TK_ASSIGNOP
        //outputParameters.node = idList.node
        case 41 :
        {
            treeNodeIt *temp = t->t->treeNode_type.n->children;
            ASTNodeIt *n = temp->next->node;
        }
        //outputParameters --> eps
        //outputParameters.node=NULL
        case 42 :
        {
            return NULL;
        }
        //inputParameters --> TK_SQL idList  TK_SQR
        //inputParameters.node = idList.node
        case 43 :
        {
            treeNodeIt *temp = t->t->treeNode_type.n->children;
            ASTNodeIt *n = temp->next->node;
            return n;
        }
        //iterativeStmt --> TK_WHILE  TK_OP booleanExpression  TK_CL stmt otherStmts  TK_ENDWHILE
        //iterativeStmt.node = new Node( TAG_ITERATIVE_STMT, NULL, booleanExpression.node, stmt.node, otherStmts.node
        case 44 :
        {
            treeNodeIt *temp = t->t->treeNode_type.n->children;
            ASTNodeIt* n = newNonLeafNode(TAG_ITERATIVE_STMT, NULL, temp->next->next->node, temp->next->next->next->next->node,temp->next->next->next->next->next->node );
            freeChildren(temp);
            return n;
        }
        //conditionalStmt --> TK_IF  TK_OP booleanExpression  TK_CL  TK_THEN stmt otherStmts elsePart
        //conditionalStmt.node = newNode(TAG_COND_STMT, NULL, booleanExpression.node, newNode(TAG_THEN,NULL,stmt.node, otherStmts.node), elsePart.node)
        case 45 :
        {
            treeNodeIt *temp = t->t->treeNode_type.n->children;
            ASTNodeIt* n = newNonLeafNode(TAG_COND_STMT, NULL, temp->next->next->node, newNonLeafNode(TAG_THEN,NULL,temp->next->next->next->next->next->node,temp->next->next->next->next->next->next->node,NULL),temp->next->next->next->next->next->next->next->node );
            freeChildren(temp);
            return n;
        }
        // elsePart --> TK_ELSE stmt otherStmts  TK_ENDIF
        //elsePart.node=newNode(TAG_ELSE,NULL,stmt.node, otherStmts.node)
        case 46 :
        {
            treeNodeIt *temp = t->t->treeNode_type.n->children;
            ASTNodeIt* n = newNonLeafNode(TAG_ELSE, NULL, temp->next->node,temp->next->next->node,NULL);
            freeChildren(temp);
            return n;
        }
        //elsePart --> TK_ENDIF
        //elsePart.node = NULL
        case 47 :
        {
            return NULL;
        }
        // ioStmt --> TK_READ  TK_OP singleOrRecId  TK_CL  TK_SEM
        //ioStmt.node = new Node(TAG_READ, NULL, singleOrRecId.node)
        case 48 :
        {
            treeNodeIt *temp = t->t->treeNode_type.n->children;
            ASTNodeIt* n = newNonLeafNode(TAG_READ, NULL, temp->next->next->node,NULL,NULL);
            freeChildren(temp);
            return n;   
        }
        // ioStmt --> TK_WRITE  TK_OP allVar  TK_CL  TK_SEM
        //ioStmt.node = new Node(TAG_WRITE, NULL, allVar.node)
        case 49 :
        {
            treeNodeIt *temp = t->t->treeNode_type.n->children;
            ASTNodeIt* n = newNonLeafNode(TAG_WRITE, NULL, temp->next->next->node,NULL,NULL);
            freeChildren(temp);
            return n; 
        }
       




        // ARITHMETIC EXPRESSION
        //allVar.node = LeafNode(TK_NUM)
        case 50: return newLeafNode(t->t->treeNode_type.n->children->t->treeNode_type.l->leaf_symbol);
        //allVar.node = LeafNode(TK_RNUM)
        case 51: return newLeafNode(t->t->treeNode_type.n->children->t->treeNode_type.l->leaf_symbol);
        //allVar.node = ChildrenList( LeafNode(TK_ID), temp.node)
        case 52:{
            treeNodeIt *temp = t->t->treeNode_type.n->children;
            ASTNodeIt *n = ChildrenList(newLeafNode(temp->t->treeNode_type.l->leaf_symbol), temp->next->node);
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
        }
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