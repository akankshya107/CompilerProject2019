// GROUP 39
// AKANKSHYA MISHRA 2016A7PS0026P
// NARAPAREDDY BHAVANA 2016A7PS0034P
// KARABEE BATTA 2016A7PS0052P
// AASTHA KATARIA 2016A7PS0062P
#include "IntermediateDef.h"
quadraple* generateIntermediateCode()
{
    while(1)
    {
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