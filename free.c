#include<stdio.h>
#include<stdlib.h>
    struct node {
    int data;
    struct node* next;};

struct node* buildList()
{
    struct node* head = NULL;
    struct node* second = NULL;
    struct node* third = NULL;

    head = malloc(sizeof(struct node));
    second = malloc(sizeof(struct node));
    third = malloc(sizeof(struct node));

    head->data = 1;
    head->next = second;

    second->data = 2;
    second->next = third;

    third->data = 3;
    third->next = NULL;

    return head;
}
void freeList(struct node* head)
{
   struct node* tmp;

   while (head != NULL)
    {
       tmp = head;
       head = head->next;
       free(tmp);
    }

}  
int main()
{
    struct node* temp=buildList();
    freeList(temp);
    printf("%d",temp->next->data);

}