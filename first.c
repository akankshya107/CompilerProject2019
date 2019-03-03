#include<parser.h>
#include<parserdef.h>

(struct first_head*) first ( int index)
{
    /*typedef struct 
    {
        bool eps;
        struct node* head;
    }first_head;*/
    
    //check grammar array name (of gnodes)
    //discrepancy between first_head->next/head
    //check arr_first_head ka original name

    int k;
    for(k=0;k<NO_OF_GRAMMAR_RULES;k++)
    {
        if(g_node_head[k]->non_terminal==g_node_head[i]->non_terminal)
        {
            if(arr_first_head[i]->next==NULL)
            {
                if (g_node_head[i]->next.is_term==1)
                {
                    struct node* ft_node= (struct node*)malloc(sizeof(struct node));
                    arr_first_head[i]->next=ft_node; //confirm if this would be erased as we keep on calling it again and again //or is it better to statically allcate memory for lined k=list
                    ft_node->token=tok;
                    ft_node->rule_no_index=i;
                    ft_node->next=NULL;
                }              

                if (arr_first_head[i]->next[i].is_term!=1)
                {
                    if(has_eps(arr_first_head[i]->next)==1)    //check first head
                    {
                        int j;
                        j=reverse_lookup(arr_first_head[i]->next->non_terminal);
                        arr_first_head[i]=first(j); //figure out how
                        temp=arr_first_head[i];
                        while(temp->next!=NULL)
                        {
                            temp=temp->next; //to get the last node in the list
                        }
                    }
                
                    else
                    {
                        int j;
                        j=reverse_lookup(arr_first_head[i]->next->non_terminal);
                        arr_first_head[i]=first(j);
                        temp=arr_first_head[i];
                        while(temp->next!=NULL)
                        {
                            temp=temp->next; //to get the last node in the list
                        }
                    }
                }
            }

            else
            {
                /* code */
                if (temp->next.is_term==1)// confirm notation of g_node_head ka array
                {
                    if(check_redundancy(temp->next->next.token, arr_first_head[i])==1)
                    {
                        temp=add_node(temp, arr_first_head[i]->next.token,i);   //returns opinter of last ode added         
                    }

                }
                else
                {
                    /* code */
                    if(has_eps(temp->next)==1)    //check first head
                    {
                        int j;
                        j=reverse_lookup(temp->next);
                        temp->next=first(j); //figure out how
                        temp=arr_first_head[i];
                        while(temp->next!=NULL)
                        {
                            temp=temp->next; //to get the last node in the list
                        }
                    }       
                    else
                    {
                        temp->next=first(temp->next);
                        temp=arr_first_head[i];
                        while(temp->next!=NULL)
                        {
                            temp=temp->next; //to get the last node in the list
                        }
                    }
                }
            }
        }             
    }  
    struct first_head* fh=arr_first_head[i]
    return fh;
}

int has_eps (struct node*)
{
    struct node* temp;
    if(temp->token!=TK_EPS)
    {
        temp=temp->next;    
    }
    else
    {
        return 1;
    }
    return 0;
}

int check_redundancy (enum TOKEN tok, struct first_head*)
{
    struct node* temp;
    temp=first_head->next;
    while(temp->next!=NULL)
    {
        if(tok!=temp->token)
        {
            temp=temp->next;
        }
        else
        {
            return 0;
        }
        return 1;        
    }
}

(struct node*) add_node( struct node* temp, enum TOKEN tok, int i)
{
    struct node* temp2= (struct node*)malloc(sizeof(struct node));
    temp->next=temp2; //confirm if this would be erased as we keep on calling it again and again //or is it better to statically allcate memory for lined k=list
    temp->token=tok;
    temp->rule_no_index=i;
    temp->next=temp2;
    return temp2;
}

(int) reverse_lookup (struct node*)
{
    //check what the array of grammanrnode heads is called
    int i;
    for(i=0;i<NO_OF_GRAMMAR_RULES;i++)
    {
        if (g[i]->elem.non_terminal==node)          //check grammar array name
        {
            return i;
        }
    }
}