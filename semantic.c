// GROUP 39
// AKANKSHYA MISHRA 2016A7PS0026P
// NARAPAREDDY BHAVANA 2016A7PS0034P
// KARABEE BATTA 2016A7PS0052P
// AASTHA KATARIA 2016A7PS0062P
#include "lexer.h"
#include "SymbolTable.h"

Ele* returnEle(ASTNodeIt *n){
    Ele *e = (Ele*)malloc(sizeof(Ele));
    e->node=n;
    e->next=NULL;
    return e;
}

void printSymbolTable(ASTNodeIt *root);
void extractTypes(ASTNodeIt* root);
void checkTypes(ASTNodeIt* root);
void semanticAnalyzer(treeNodeIt *t){
    ASTNodeIt *ast = makeAbstractSyntaxTree(t);
    printAST(ast);
    populateSymbolTable(ast);
    // extractTypes(ast);
    // checkTypes(ast);
    //Single/Double pass AST
    printSymbolTable(ast);
}

ASTNodeIt *searchTag(ASTNodeIt *root, TAG tg){
    ASTNodeIt *temp = root;
    Stack *st = newStack();
    while(1){
        while((temp!=NULL)){        
            push(st, returnEle(temp));
            if(temp->node->is_leaf==0 && temp->node->u.n->tag_info==tg){
                return temp;
            }
            else if(temp->node->is_leaf==0){
                temp = temp->node->u.n->children; 
            }else{
                temp = temp->next;
            }
            
        }
        if(isEmpty(st)) break;
        temp = pop(st)->node;
        temp = temp->next;
    }
    return NULL;
}

void printSymbolTable(ASTNodeIt *root){
    ASTNodeIt *temp = searchTag(root, TAG_FUN_LIST);
    ASTNodeIt *ch = temp->node->u.n->children;
    printf("Lexeme\tType\tScope\tOffset\n");
    while(ch!=NULL){
        printf("%s\n", ch->node->u.n->leaf_symbol->u.lexeme);
        //print symbol table
        hashTable st = lookupEle(ch->node->u.n->leaf_symbol->u.lexeme, SymbolTable)->ele->u.SymbolTable;
        for(int i=0; i<LEN_HT; i++){
            hash_ele *e = st[i];
            while(e!=NULL){
                printf("%s\t%d\t%s\t%d\n", e->str, e->ele->u.s->type, ch->node->u.n->leaf_symbol->u.lexeme, e->ele->u.s->offset);
                e=e->next;
            }
        }
        ch=ch->next;
    }
    temp = searchTag(root, TAG_MAIN);
    printf("%s\n", TagString(temp->node->u.n->tag_info));
    for(int i=0; i<LEN_HT; i++){
        hash_ele *e = globalSymbolTable[i];
        while(e!=NULL){
            printf("%s\t%d\t%s\t%d\n", e->str, e->ele->u.s->type, ch->node->u.n->leaf_symbol->u.lexeme, e->ele->u.s->offset);
            e=e->next;
        }
    }
}