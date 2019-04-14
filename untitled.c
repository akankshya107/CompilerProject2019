//         else if(temp->node->u.n->tag_info==TAG_READ)
//         {
            
//         }

//         else if(temp->node->u.n->tag_info==TAG_ITERATIVE_STMT)
//         {
            
//         }

//         else if(temp->node->u.n->tag_info==TAG_COND_STMT)
//         {
            
//         }
        
// }

// while(temp!=NULL){
//         //Non-leaf node: contains some TAG and is associated with some semantic check

//         //The right hand side expression of an assignment statement must be of the same type as that of the left hand side identifier.
//         if(temp->node->u.n->tag_info==TAG_ASSIGNMENT_STMT){

//             temp = temp->node->u.n->children;
//             //find hash elem for children
//             //for children-next: arE, write function
//             temp = temp->node->parent;
//             while(temp->next==NULL){
//                 if(temp->node->parent->node->u.n->tag_info==TAG_ITERATIVE_STMT) temp=temp->node->parent;
//                 else if(temp->node->parent->node->u.n->tag_info==TAG_THEN) temp=temp->node->parent;
//                 else if(temp->node->parent->node->u.n->tag_info==TAG_COND_STMT) temp=temp->node->parent;
//                 else break;
//             }
//             temp = temp->next;
//         }
//         else if(temp->node->u.n->tag_info==TAG_ITERATIVE_STMT){
//             //While statement: one pass for checking if variables are being changed
//             ASTNodeIt *chk = temp->node->u.n->children;
//             //Quads
//             temp=temp->node->u.n->children->next;
//         }
//         else if(temp->node->u.n->tag_info==TAG_COND_STMT){
//             //if-then-else
//             ASTNodeIt *chk = temp->node->u.n->children;
//             temp = temp->node->u.n->children->next->node->u.n->children;
//         }
//         else if(temp->node->u.n->tag_info==TAG_FUN_CALL_STMT){
//             //lol

//             while(temp->next==NULL){
//                 if(temp->node->parent->node->u.n->tag_info==TAG_ITERATIVE_STMT) temp=temp->node->parent;
//                 else if(temp->node->parent->node->u.n->tag_info==TAG_THEN) temp=temp->node->parent;
//                 else if(temp->node->parent->node->u.n->tag_info==TAG_COND_STMT) temp=temp->node->parent;
//                 else break;
//             }
//             temp = temp->next;
//         }
//         else if(temp->node->u.n->tag_info==TAG_READ){
//             while(temp->next==NULL){
//                 if(temp->node->parent->node->u.n->tag_info==TAG_ITERATIVE_STMT) temp=temp->node->parent;
//                 else if(temp->node->parent->node->u.n->tag_info==TAG_THEN) temp=temp->node->parent;
//                 else if(temp->node->parent->node->u.n->tag_info==TAG_COND_STMT) temp=temp->node->parent;
//                 else break;
//             }
//             temp = temp->next;
//         }
//         else if(temp->node->u.n->tag_info==TAG_WRITE){
//             while(temp->next==NULL){
//                 if(temp->node->parent->node->u.n->tag_info==TAG_ITERATIVE_STMT) temp=temp->node->parent;
//                 else if(temp->node->parent->node->u.n->tag_info==TAG_THEN) temp=temp->node->parent;
//                 else if(temp->node->parent->node->u.n->tag_info==TAG_COND_STMT) temp=temp->node->parent;
//                 else break;
//             }
//             temp = temp->next;
//         }
//         else printf("Check AST structure\n");
//     }


