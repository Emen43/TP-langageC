/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~QUEUES~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#include<stdio.h>
#include<stdlib.h>

typedef struct Node
{
    int data;
    struct Node* next;
}Node;

Node* first = NULL;
Node* last = NULL;

void enfiler(int value)
{
    Node* nd = (Node*)malloc(sizeof(Node));

    nd->data = value;
    nd->next = NULL;

    if(last == NULL)
     last = first = nd;
    last->next = nd;
    last = nd;
}

void defiler()
{
    if(first == NULL)
    {
        printf("Queue already empty!\n");
        return;
    }

    Node *ptr = first;
    first = first->next;
    free(ptr);

    if(first == NULL)
    last = NULL;
}

void displayFile()
{
    Node *ptr = first;
    if(first == NULL)
    {
        printf("Nothing to display!\n");
        return;
    }

    while(ptr != NULL)
    {
        printf("%d ",ptr->data);
        ptr = ptr->next;
    }
    printf("NULL\n");
}

void viderFile()
{
    Node *ptr = first;

    while(first != NULL)
    {
        ptr = first;
        first = first->next;
        free(ptr);
    }
    last = NULL;
    printf("La file a ete completement videe.\n");

}

int main()
{
    enfiler(10);
    enfiler(20);
    enfiler(30);

    displayFile();
    printf("\n");

    defiler();

    displayFile();
    printf("\n");

    enfiler(40);
    enfiler(50);
    displayFile();
    printf("\n");
    viderFile();
    return 0;
}