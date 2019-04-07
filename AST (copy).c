// GROUP 39
// AKANKSHYA MISHRA 2016A7PS0026P
// NARAPAREDDY BHAVANA 2016A7PS0034P
// KARABEE BATTA 2016A7PS0052P
// AASTHA KATARIA 2016A7PS0062P
#include <stdio.h>
#include <stdlib.h>
#include "lexer.h"
#include "ASTDef.h"

char *TagString(int index){
    static char *tagTable[TAG_WRITE+1] = {"TAG_PROGRAM", "TAG_FUN_LIST", "TAG_MAIN", "TAG_ARITHMETIC_EXPRESSION", "TAG_BOOLEAN_EXPRESSION", 
"TAG_OTHERSTMTS", "TAG_RETURNSTMT", "TAG_DECLARES", "TAG_TYPEDEFS", "TAG_TYPEDEF", "TAG_FIELDDEF", "TAG_DECLARE",
"TAG_FUNCTION", "TAG_INPUT_PARS", "TAG_OUTPUT_PARS", "TAG_ASSIGNMENT_STMT", "TAG_FUN_CALL_STMT", "TAG_OUTPUT_ARGS",
"TAG_INPUT_ARGS", "TAG_ITERATIVE_STMT", "TAG_COND_STMT", "TAG_THEN", "TAG_ELSE", "TAG_READ", "TAG_WRITE"
};
    return tagTable[index];
}

ASTNodeIt* newNonLeafNode(TAG taginf, tokenInfo *ti, ASTNodeIt* input1, ASTNodeIt* input2, ASTNodeIt* input3){
    ASTNodeIt* k=input1;
    if(input1!=NULL){ 
        while(k->next!=NULL){
            k=k->next;
        }
        k->next=input2;
        // input2->next=NULL;
    }
    if(input2!=NULL){
        while(k->next!=NULL){
            k=k->next;
        }
        k->next=input3;
        // input3->next=NULL;
    }
    if(input3!=NULL){
        while(k->next!=NULL){
            k=k->next;
        }
        k->next=NULL;
    }
    ASTNodeIt* final_node=(ASTNodeIt*)malloc(sizeof(ASTNodeIt));
    final_node->node = (ASTNode*)malloc(sizeof(ASTNode));
    final_node->node->u.n=(nonLeaf*)malloc(sizeof(nonLeaf));
    final_node->node->u.n->tag_info=taginf;
    final_node->node->u.n->leaf_symbol=ti;
    final_node->node->u.n->children=input1;
    final_node->node->is_leaf=0;
    final_node->node->parent=NULL;
    final_node->next=NULL;
    ASTNodeIt* temp=input1;
    while(temp!=NULL){
        temp->node->parent = final_node;
        temp = temp->next;
    }
    return final_node;  
}

ASTNodeIt* ChildrenList(ASTNodeIt* input1, ASTNodeIt* input2){
    if(input1!=NULL) {
        input1->next=input2;
    }
    return input1;
}

ASTNodeIt* newLeafNode(tokenInfo *ti){
    ASTNodeIt* final_node = (ASTNodeIt*)malloc(sizeof(ASTNodeIt));
    final_node->node = (ASTNode*)malloc(sizeof(ASTNode));
    final_node->node->parent=NULL;
    final_node->node->is_leaf=1;
    final_node->node->u.l=(Leaf*)malloc(sizeof(Leaf));
    final_node->node->u.l->leaf_symbol=ti;
    final_node->next=NULL;
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
                    break;
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

        //MAIN
        //program.node = new Node(TAG_PROGRAM, NULL, new Node(TAG_FUN_LIST, NULL, otherFunctions.node), mainFunction.node)
        case 0: {
            treeNodeIt *temp = t->t->treeNode_type.n->children;
            ASTNodeIt* n = newNonLeafNode(TAG_PROGRAM, NULL, newNonLeafNode(TAG_FUN_LIST, NULL, temp->node, NULL, NULL), temp->next->node, NULL);
            freeChildren(temp);
            n->node->parent=NULL;
            return n;
        }
        //mainFunction.node=newNonLeafNode(TAG_MAIN, NULL, stmts.node) 
        case 1:{
            treeNodeIt *temp = t->t->treeNode_type.n->children;
            ASTNodeIt* n = newNonLeafNode(TAG_MAIN, NULL, temp->next->node, NULL, NULL);
            freeChildren(temp);
            return n;
        }
        //otherFunctions.node = ChildrenList( function.node, otherFunctions1.node)
        case 2:{
            treeNodeIt *temp = t->t->treeNode_type.n->children;
            ASTNodeIt* n = ChildrenList(temp->node, temp->next->node);
            freeChildren(temp);
            return n;
        }
        //otherFunctions.node=NULL
        case 3:{
            return NULL;
        }

        //FUNCTION
        //function.node=newNode(TAG_FUNCTION, LeafNode(TK_FUNID),new Node(TAG_INPUT_PARS, NULL, input_par.node),new Node(TAG_OUTPUT_PARS, NULL, output_par.node), stmts.node)
        case 4:{
            treeNodeIt *temp = t->t->treeNode_type.n->children;
            ASTNodeIt* n = newNonLeafNode(TAG_FUNCTION, temp->t->treeNode_type.l->leaf_symbol, 
                            newNonLeafNode(TAG_INPUT_PARS, NULL, temp->next->node, NULL, NULL), 
                            newNonLeafNode(TAG_OUTPUT_PARS, NULL, temp->next->next->node,NULL, NULL), 
                            temp->next->next->next->next->node);
            freeChildren(temp);
            return n;
        }
        //input_par.node=parameter_list.node
        case 5:{
            treeNodeIt *temp = t->t->treeNode_type.n->children;
            ASTNodeIt* n = temp->next->next->next->next->node;
            freeChildren(temp);
            return n;
        }
        //output_par.node=parameter_list.node
        case 6:{
            treeNodeIt *temp = t->t->treeNode_type.n->children;
            ASTNodeIt* n = temp->next->next->next->next->node;
            freeChildren(temp);
            return n;
        }
        //output_par.node = NULL
        case 7:{
            return NULL;
        }
        //parameter_list.node = ChildrenList(dataType.node, ChildrenList(LeafNode(TK_ID), remaining_list.node))
        case 8:{
            treeNodeIt *temp = t->t->treeNode_type.n->children;
            ASTNodeIt* n = ChildrenList(temp->node, ChildrenList(newLeafNode(temp->next->t->treeNode_type.l->leaf_symbol), temp->next->next->node));
            freeChildren(temp);
            return n;
        }
        //remaining_list.node = parameter_list.node
        case 14:{
            treeNodeIt *temp = t->t->treeNode_type.n->children;
            ASTNodeIt* n = temp->next->node;
            freeChildren(temp);
            return n;
        }
        //remaining_list.node = NULL
        case 15:{
            return NULL;
        }

        //DATATYPE
        //dataType.node = primitiveDatatype.node
        case 9:{
            treeNodeIt *temp = t->t->treeNode_type.n->children;
            ASTNodeIt *n = temp->node;
            freeChildren(temp);
            return n; 
        }
        //dataType.node = constructedDatatype.node
        case 10:{
            treeNodeIt *temp = t->t->treeNode_type.n->children;
            ASTNodeIt *n = temp->node;
            freeChildren(temp);
            return n;
        }
        //primitiveDatatype.node = Leafnode(TK_INT)
        case 11: return newLeafNode(t->t->treeNode_type.n->children->t->treeNode_type.l->leaf_symbol);
        //primitiveDatatype.node = Leafnode(TK_REAL)
        case 12: return newLeafNode(t->t->treeNode_type.n->children->t->treeNode_type.l->leaf_symbol);
        //constructedDatatype.node = LeafNode(TK_RECORDID)
        case 13: return newLeafNode(t->t->treeNode_type.n->children->next->t->treeNode_type.l->leaf_symbol);

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
            freeChildren(temp);
            return n3;
        }

        //TYPE DEFINITIONS
        // typeDefinitions.node = ChildrenList(typeDefinition.node,typeDefinitions​ 1​ .node)
        case 17:{
            treeNodeIt* temp=t->t->treeNode_type.n->children;
            ASTNodeIt* n=ChildrenList(temp->node,temp->next->node);
            freeChildren(temp);
            return n;
        }
        // typeDefinitions.node = NULL
        case 18:{
            // t->t->node=NULL;
            return NULL;
        }
        // typeDefinition.node = new Node(TAG_TYPEDEF,LeafNode(TK_RECORDID),fieldDefinitions.node)
        case 19:{
            treeNodeIt* temp=t->t->treeNode_type.n->children;
            ASTNodeIt* leaf=newLeafNode(temp->next->t->treeNode_type.l->leaf_symbol);
            ASTNodeIt* n=newNonLeafNode(TAG_TYPEDEF,leaf->node->u.l->leaf_symbol,temp->next->next->node,NULL,NULL);
            freeChildren(temp);
            return n;
        }
        // fieldDefinitions.node =ChildrenList(fieldDefinition.node,ChildrenList(fieldDefinition.node,moreFields.node))
        case 20:{
            treeNodeIt* temp=t->t->treeNode_type.n->children;
            ASTNodeIt* n1= ChildrenList(temp->next->node,temp->next->next->node);
            ASTNodeIt* n2= ChildrenList(temp->node, n1);
            freeChildren(temp);
            return n2;
        }
        // fieldDefinition.node = new Node(TAG_FIELDDEF,LeafNode(FIELDID),primitiveDataType.node)
        case 21:{
            treeNodeIt* temp=t->t->treeNode_type.n->children;
            ASTNodeIt* n= newNonLeafNode(TAG_FIELDDEF,temp->next->next->next->t->treeNode_type.l->leaf_symbol,temp->next->node,NULL,NULL);
            freeChildren(temp);
            return n;
        }
        // moreFields.node = ChildrenList(fieldDefinition.node,moreFields​ 1​ .node)
        case 22:{
            treeNodeIt* temp=t->t->treeNode_type.n->children;
            ASTNodeIt* n=ChildrenList(temp->node,temp->next->node);
            freeChildren(temp);
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
            freeChildren(temp);
            return n;
        }
        // declarations.node = NULL
        case 25:{
            return NULL;
        }
        // declaration.node=new Node(TAG_DECLARE, LeafNode(TK_ID),dataType.node, global_or_not.node)
        case 26:{
            treeNodeIt* temp=t->t->treeNode_type.n->children;
            ASTNodeIt* n=newNonLeafNode(TAG_DECLARE,temp->next->next->next->t->treeNode_type.l->leaf_symbol,temp->next->node,temp->next->next->next->next->node,NULL);
            freeChildren(temp);
            return n;
        }
        // global_or_not.node=LeafNode(TK_GLOBAL)
        case 27:{
            treeNodeIt* temp=t->t->treeNode_type.n->children;
            ASTNodeIt* leaf=newLeafNode(temp->next->t->treeNode_type.l->leaf_symbol);
            freeChildren(temp);
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
            freeChildren(temp);
            return n;
        }
        // otherStmts.node = NULL
        case 30:{
            return NULL;
        }
        
        //STMT
        //stmt -->assignmentStmt, stmt.node = assignmentStmt.node
        case 31 :{
            treeNodeIt *temp = t->t->treeNode_type.n->children;
            ASTNodeIt *n = temp->node;
            freeChildren(temp);
            return n;
        }
        // stmt -->iterativeStmt, stmt.node = iterativeStmt.node
        case 32:{
            treeNodeIt *temp = t->t->treeNode_type.n->children;
            ASTNodeIt *n = temp->node;
            freeChildren(temp);
            return n;   
        }
        //stmt -->conditionalStmt, stmt.node= conditionalStmt.node
        case 33 :
        {
            treeNodeIt *temp = t->t->treeNode_type.n->children;
            ASTNodeIt *n = temp->node;
            freeChildren(temp);
            return n;
        }
        //stmt -->ioStmt, stmt.node= ioStmt.node
        case 34 :
        {
            treeNodeIt *temp = t->t->treeNode_type.n->children;
            ASTNodeIt *n = temp->node;
            freeChildren(temp);
            return n;
        }
        // stmt -->funCallStmt, stmt.node = funCallStmt.node
        case 35 :
        {
            treeNodeIt *temp = t->t->treeNode_type.n->children;
            ASTNodeIt *n = temp->node;
            freeChildren(temp);
            return n;
        }
        // assignmentStmt -->singleOrRecId  TK_ASSIGNOP arithmeticExpression  TK_SEM 
        //Stmt.node = newNode( TAG_ASSIGNMENT_STMT, LeafNode(TK_ASSIGNOP), singleOrRecId.node, arithmeticExpression.node)
        case 36 :
        {
            treeNodeIt *temp = t->t->treeNode_type.n->children;
            ASTNodeIt* n = newNonLeafNode(TAG_ASSIGNMENT_STMT, temp->next->t->treeNode_type.l->leaf_symbol, temp->node, temp->next->next->node, NULL);
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
            treeNodeIt *temp = t->t->treeNode_type.n->children;
            ASTNodeIt *n = newLeafNode(temp->next->t->treeNode_type.l->leaf_symbol);
            freeChildren(temp);
            return n;
        }
        //funCallStmt -->outputParameters  TK_CALL  TK_FUNID  TK_WITH TK_PARAMETERS inputParameters  TK_SEM
        //funCallStmt.node = new Node( FUN_CALL_STMT, LeafNode(TK_FUNID), new Node(TAG_OUTPUT_ARGS, NULL, outputParameters.node), new Node( TAG_INPUT_ARGS, NULL, inputParameters.node))
        case 40 :
        {
            treeNodeIt *temp = t->t->treeNode_type.n->children;
            ASTNodeIt* n = newNonLeafNode(TAG_FUN_CALL_STMT, temp->next->next->t->treeNode_type.l->leaf_symbol, newNonLeafNode(TAG_OUTPUT_ARGS, NULL, temp->node, NULL, NULL), newNonLeafNode(TAG_INPUT_ARGS, NULL, temp->next->next->next->next->next->node, NULL, NULL), NULL);
            freeChildren(temp);
            return n;

        }
        // outputParameters --> TK_SQL idList  TK_SQR  TK_ASSIGNOP
        //outputParameters.node = idList.node
        case 41 :
        {
            treeNodeIt *temp = t->t->treeNode_type.n->children;
            ASTNodeIt *n = temp->next->node;
            freeChildren(temp);
            return n;
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
            freeChildren(temp);
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
            ASTNodeIt* n = newNonLeafNode(TAG_COND_STMT, NULL, temp->next->next->node, newNonLeafNode(TAG_THEN, NULL, temp->next->next->next->next->next->node,temp->next->next->next->next->next->next->node, NULL), temp->next->next->next->next->next->next->next->node);
            freeChildren(temp);
            return n;
        }
        // elsePart --> TK_ELSE stmt otherStmts  TK_ENDIF
        //elsePart.node=newNode(TAG_ELSE,NULL,stmt.node, otherStmts.node)
        case 46 :
        {
            treeNodeIt *temp = t->t->treeNode_type.n->children;
            ASTNodeIt* n = newNonLeafNode(TAG_ELSE, NULL, temp->next->node, temp->next->next->node, NULL);
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
            ASTNodeIt* n = newNonLeafNode(TAG_READ, NULL, temp->next->next->node, NULL, NULL);
            freeChildren(temp);
            return n;   
        }
        // ioStmt --> TK_WRITE  TK_OP allVar  TK_CL  TK_SEM
        //ioStmt.node = new Node(TAG_WRITE, NULL, allVar.node)
        case 49 :
        {
            treeNodeIt *temp = t->t->treeNode_type.n->children;
            ASTNodeIt* n = newNonLeafNode(TAG_WRITE, NULL, temp->next->next->node, NULL, NULL);
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
        // arithmeticExpression -->term expPrime
        // arithmeticExpression.node = expPrime.node
        case 53:{
            treeNodeIt *temp = t->t->treeNode_type.n->children;
            ASTNodeIt *n = temp->next->node;
            freeChildren(temp);
            return n;
        }
        // expPrime→ lowPrecedenceOperators term expPrime1
        // expPrime.node = new Node(TAG_ARITHMETIC_EXPRESSION, lowPrecedenceOperators.node, term.node, expPrime.node)
        case 54:{
            treeNodeIt *temp = t->t->treeNode_type.n->children;
            ASTNodeIt *n = newNonLeafNode(TAG_ARITHMETIC_EXPRESSION, temp->node->node->u.l->leaf_symbol, t->t->parent->t->treeNode_type.n->children->node, temp->next->next->node, NULL);
            freeChildren(temp);
            return n;
        }
        // expPrime --> eps
        // expPrime.node = NULL
        case 55:{
            return NULL;
        }
        // term -->factor termPrime
        case 56: {
            treeNodeIt *temp = t->t->treeNode_type.n->children;
            ASTNodeIt *n = temp->next->node;
            freeChildren(temp);
            return n;
        }
        // termPrime → highPrecedenceOperators factor termPrime1
        case 57: {
            treeNodeIt *temp = t->t->treeNode_type.n->children;
            ASTNodeIt *n = newNonLeafNode(TAG_ARITHMETIC_EXPRESSION, temp->node->node->u.l->leaf_symbol, t->t->parent->t->treeNode_type.n->children->node, temp->next->next->node, NULL);
            freeChildren(temp);
            return n;
        }
        // termPrime.node = NULL
        case 58: {
            return NULL;
        }
        // factor.node = arithmeticExpression.node
        case 59: {
            treeNodeIt *temp = t->t->treeNode_type.n->children;
            ASTNodeIt *n  = temp->next->node;
            freeChildren(temp);
            return n;
        }
        // factor.node = allVar.node
        case 60: {
            treeNodeIt *temp = t->t->treeNode_type.n->children;
            ASTNodeIt *n = temp->node;
            freeChildren(temp);
            return n;
        }
        // highPrecedenceOperators.node = LeafNode(TK_MUL)
        case 61: return newLeafNode(t->t->treeNode_type.n->children->t->treeNode_type.l->leaf_symbol);
        // highPrecedenceOperators.node = LeafNode(TK_DIV)
        case 62: return newLeafNode(t->t->treeNode_type.n->children->t->treeNode_type.l->leaf_symbol);
        // lowPrecedenceOperators.node = LeafNode(TK_PLUS)
        case 63: return newLeafNode(t->t->treeNode_type.n->children->t->treeNode_type.l->leaf_symbol);
        // lowPrecedenceOperators.node = LeafNode(TK_MINUS)
        case 64: return newLeafNode(t->t->treeNode_type.n->children->t->treeNode_type.l->leaf_symbol);
        // temp.node = NULL
        case 65: return NULL;
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
            ASTNodeIt *n = temp->next->node;
            freeChildren(temp);
            return n;
        }
        // optionalReturn.node=idList.node
        case 82:{
            treeNodeIt* temp=t->t->treeNode_type.n->children;
            ASTNodeIt *n = temp->next->node;
            freeChildren(temp);
            return n;
        }
        // optionalReturn.node = NULL
        case 83:{
            return NULL;
        }
        // idList.node = ChildrenList(LeafNode(TK_ID), more_ids.node)
        case 84:{
            treeNodeIt* temp=t->t->treeNode_type.n->children;
            ASTNodeIt* leaf=newLeafNode(temp->t->treeNode_type.l->leaf_symbol);
            ASTNodeIt* n=ChildrenList(leaf, temp->next->node);
            freeChildren(temp);
            return n;
        }
        // more_ids.node=idList.node
        case 85:{
            treeNodeIt* temp=t->t->treeNode_type.n->children;
            ASTNodeIt *n = temp->next->node;
            freeChildren(temp);
            return n;
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

void printAST(ASTNodeIt* root)
{
    ASTNodeIt *temp = root;
    ASTNodeIt* temp_child;
    while(1)
    {
        while(temp->node->is_leaf==0){
            temp_child=temp->node->u.n->children;
            if(temp_child==NULL)
            {
                printf("nonleaf with no children:  node tag: %s \n", TagString(temp->node->u.n->tag_info));
                
                if(temp->next==NULL)
                break;

                temp=temp->next;
            }
            else
            {
                temp=temp->node->u.n->children;
            }
            
            
        }
        // if (temp==NULL) break;
        if(temp->node->is_leaf==1)
            printf("leaf node:\t\t token: %s\n", TerminalString(temp->node->u.l->leaf_symbol->tokenName));
        while(temp->next==NULL){
            temp=temp->node->parent;
            if(temp==NULL){
                printf("root reached");
                return;
            }
            if(temp->node->u.n->leaf_symbol!=NULL)
                printf("nonleaf node:\t\t token: %s tag: %s \n",TerminalString(temp->node->u.n->leaf_symbol->tokenName), TagString(temp->node->u.n->tag_info));
            else
            {
                printf("nonleaf node:\t\t token: not stored tag: %s \n", TagString(temp->node->u.n->tag_info));
            }
            
        }
        temp=temp->next;
    }

}