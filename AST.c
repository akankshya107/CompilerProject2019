#include <stdio.h>
#include "ASTDef.h"
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
			if(temp->t->parent==NULL){
				temp->node = semanticRuleExecute(temp, 0);
				return;	
			}
			//REACHED A NON-LEAF
            //Get ASTNode and free the subsequent nodes
            temp->node = semanticRuleExecute(temp, temp->t->treeNode_type.n->rule_no);
		}
		temp = temp->next;
	}
}

ASTNodeIt* semanticRuleExecute(treeNodeIt *t, int rule_no){
    switch(rule_no){
        case 0:
        case 1:
        default:
    }
}