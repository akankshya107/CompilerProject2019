#include <stdio.h>
#include <stdlib.h>
#include "ASTDef.h"

ASTNodeIt* newNonLeafNode(TAG taginf, tokenInfo *ti, ASTNodeIt* input1, ASTNodeIt* input2){
    input1->next=input2;
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
        //otherFunctions.node = ChildrenList( function.node, otherFunctions1.node)
        case 2:{
            treeNodeIt *temp = t->t->treeNode_type.n->children;
            ASTNodeIt* n = ChildrenList(temp->node,NULL,NULL,temp->next->node,NULL);
            freeChildren(temp);
            return n;
        }
        //otherFunctions.node=NULL
        case 3:{
            ASTNodeIt* n = NULL;
            return n;
        }
        //function.node=newNode(TAG_FUNCTION, LeafNode(TK_FUNID),new Node(TAG_INPUT_PARS, NULL, input_par.node),new Node(TAG_OUTPUT_PARS, NULL, output_par.node), stmts.node)
        case 4:{
            treeNodeIt *temp = t->t->treeNode_type.n->children;
            ASTNodeIt* n = newLeafNode(TAG_FUNCTION,newLeafNode(TK_FUNID),newLeafNode(TAG_INPUT_PARS,NULL,temp->node,NULL,NULL)newLeafNode(TAG_OUTPUT_PARS,NULL,temp->next->node,NULL));
            freeChildren(temp);
        }
        //input_par.node=parameter_list.node
        case 5:{
            treeNodeIt *temp = t->t->treeNode_type.n->children;
            ASTNodeIt* n = temp->next->node;
            return n;
        }
        //output_par.node=parameter_list.node
        case 6:{
            treeNodeIt *temp = t->t->treeNode_type.n->children;
            ASTNodeIt* n = temp->next->node;
            return n;
        }
        //output_par.node = NULL
        case 7:{
            ASTNodeIt* n = NULL;
            return n;
        }
        //parameter_list.node = ChildrenList(dataType.node, ChildrenList(LeafNode(TK_ID), remaining_list.node))
        case 8:{
            treeNodeIt *temp = t->t->treeNode_type.n->children;
            ASTNodeIt* n = ChildrenList(temp->node,NULL,NULL,ChildrenList(newLeafNode(TK_ID),temp->next->node,NULL));
            return n;
        }
        //remaining_list.node = parameter_list.node
        case 9:{
            treeNodeIt *temp = t->t->treeNode_type.n->children;
            ASTNodeIt* n = temp->next->node;
            return n;
        }
        //remaining_list.node = NULL
        case 10:{
            ASTNodeIt* n = NULL;
            return n;
        }
        //dataType.node = primitiveDatatype.node
        case 11:{
            treeNodeIt *temp = t->t->treeNode_type.n->children;
            ASTNodeIt *n = temp->next->node;
            return n; 
        }
        //dataType.node = constructedDatatype.node
        case 12:{
            treeNodeIt *temp = t->t->treeNode_type.n->children;
            ASTNodeIt *n = temp->next->node;
            return n;
        }
        //primitiveDatatype.node = Leafnode(TK_INT)
        case 13: return newLeafNode(t->t->treeNode_type.n->children->t->treeNode_type.l->leaf_symbol);
        //primitiveDatatype.node = Leafnode(TK_REAL)
        case 14: return newLeafNode(t->t->treeNode_type.n->children->t->treeNode_type.l->leaf_symbol);
        //constructedDatatype.node = LeafNode(TK_RECORDID)
        case 15: return newLeafNode(t->t->treeNode_type.n->children->t->treeNode_type.l->leaf_symbol);





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
            temp->node = semanticRuleExecute(temp, temp->t->treeNode_type.n->rule_no);
		}
        //iterate 
		temp = temp->next;
	}
}
