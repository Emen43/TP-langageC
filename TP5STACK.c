/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~STACK~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

#include<stdio.h>
#include<stdlib.h>

typedef struct Node{
    int data;
    struct Node* next;
}Node;

void push(Node** top,int valeur)
{
    Node* nd = (Node*)malloc(sizeof(Node));

    nd->data=valeur;
    nd->next=*top;
    *top=nd;
}

void pop(Node** top)
{
    Node* tmp = (*top);

    if( (*top)==NULL )
     printf("Stack already empty , nothing to pop!\n");
    else
    {
        tmp = (*top);
        (*top)=(*top)->next;
        free(tmp);
    }
}

void peek(Node* top)
{
    Node* ptr = top;

    if( top!=NULL )
     printf("Peek : %d\n",top->data);
    else
     printf("No peek , stack empty!\n");
}

void displayPile(Node* top)
{
    Node* ptr = top;

    if(top==NULL)
     printf("Nothing to display , empty stack!\n");

    while(ptr!=NULL)
    {
        printf("%d ",ptr->data);
        ptr = ptr->next;
    }
    printf("NULL");
}

int taille(Node* top)
{
    int counter = 0;
    Node* ptr = top;

    while(top!=NULL)
    {
        counter++;
        ptr=ptr->next;
    }

    return counter;
}

int main()
{
    Node* top = NULL;

    push(&top,10);
    push(&top,20);
    push(&top,30);

    displayPile(top);

    peek(top);

    int size = taille(top);

    pop(&top);
    pop(&top);
    displayPile(top);

    return 0;
}