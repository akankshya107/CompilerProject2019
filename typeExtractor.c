#include<symbolTable.h>

ASTNodeIt* extractTypes(ASTNodeIt* root)
{
    ASTNodeIt* temp=root;
    ASTNodeIt* result;
    while(1)
    {
        while(temp->node->is_leaf==0)
        {
            if(temp->node->u.n->tag_info==FUN_ID)
            {
                //start an pre-order traversal
                char* function_id=temp->node->u.n->leaf_symbol->u.lexeme;
                populate_level_2(function_id, temp);
            }break;
            else if(temp->node->next->is_leaf==1)
            {
                temp=temp->node->next; //keep checking its siblings till you find a FUN_ID
            }    
            
        }
        temp=temp->node->u.n->children; //then traverse its children since we havent found a FUN_ID tag
        
    }
    return result;
}

void populate_level_2 (char* function_id,ASTNodeIt* root)
{
    //start a pre-order traversal
    ASTNodeIt* temp=root->node->u.n->children; //what is is
    while(temp->node!=NULL)
    {
        pre_order_populate(children,function_id); //confirm root or funid
        temp=temp->next; //traverse siblings till you reach the end
    }
   
}

void pre_order_populate(ASTNodeIt* child, char* function_id)
{
    char* lex, temp;
    if(child->node->u.n->tag_info==INPUT_PARS)
    {
        
        //ASTNodeIt* param=temp->next->next->next->next->node; //is the parameter list node
        ASTNodeIt* param=child->node->u.n->children;
        while(param->next!=NULL)// traverse the sibling list
        {   if(param->node->u.n->tag_info==TAG_ID)
            {
            
                lex=param->node->u.l->leaf_symbol->u.lexeme; //"a" in int a
                type=param->node->u.n->children->node->u.l->leaf_symbol->u.lexeme; //"int" in int a
                populate_symbol_table(lex,type,function_id)
            }
            param=param->next;
        }
        
    }
    if(child->node->u.n->tag_info==OUTPUT_PARS)
    {
        
        //ASTNodeIt* param=temp->next->next->next->next->node; //is the parameter list node
        ASTNodeIt* param=child->node->u.n->children;
        while(param->next!=NULL)// traverse the sibling list
        {   if(param->node->u.n->tag_info==TAG_ID)
            {
            
                lex=param->node->u.l->leaf_symbol->u.lexeme; //"a" in int a
                type=param->node->u.n->children->node->u.l->leaf_symbol->u.lexeme; //"int" in int a
                populate_sym_tab(lex,type,function_id) //doubt?
            }
            param=param->next;
        }
        
    }
    else
    {
        child=child->node->u.n->children;
        if(child->node->u.n->tag_info==TYPEDEFS)
        {
            
            //ASTNodeIt* param=temp->next->next->next->next->node; //is the parameter list node
            ASTNodeIt* param=child->node->u.n->children;
            while(param->next!=NULL)// traverse the sibling list
            {   if(param->node->u.n->tag_info==TAG_ID)
                {
                
                    lex=param->node->u.l->leaf_symbol->u.lexeme; //"a" in int a
                    type=param->node->u.n->children->node->u.l->leaf_symbol->u.lexeme; //"int" in int a
                    populate_sym_tab(lex,type,function_id)
                }
                param=param->next;
            }
            
        }
        else if(child->node->u.n->tag_info==INPUT_PARS)
        {
            
            //ASTNodeIt* param=temp->next->next->next->next->node; //is the parameter list node
            ASTNodeIt* param=child->node->u.n->children;
            while(param->next!=NULL)// traverse the sibling list
            {   if(param->node->u.n->tag_info==TAG_ID)
                {
                
                    lex=param->node->u.l->leaf_symbol->u.lexeme; //"a" in int a
                    type=param->node->u.n->children->node->u.l->leaf_symbol->u.lexeme; //"int" in int a
                    populate_sym_tab(lex,type,function_id)
                }
                param=param->next;
            }
            
        }     
    }
    


}
