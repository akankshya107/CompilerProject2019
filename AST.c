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
        if(temp->t->is_leaf==1 && (temp->t->treeNode_type.l->leaf_symbol->tokenName==SOMETHINGIWANNASAVE)){
            temp=temp->next;
            continue;
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
        case 0: {
            //program.node = new Node(TAG_PROGRAM, NULL, new Node(TAG_FUN_LIST, NULL, otherFunctions.node), mainFunction.node)
            treeNodeIt *temp = t->t->treeNode_type.n->children;
            ASTNodeIt* n = newNonLeafNode(TAG_PROGRAM, NULL, newNonLeafNode(TAG_FUN_LIST, NULL, temp->node, NULL, NULL), temp->next->node, NULL);
            freeChildren(temp);
            return n;
        }
        case 1:{
            //mainFunction.node=newNonLeafNode(TAG_MAIN, NULL, stmts.node)
            ASTNodeIt* n = newNonLeafNode(TAG_MAIN, NULL, t->t->treeNode_type.n->children->node, NULL, NULL);
            return n;
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