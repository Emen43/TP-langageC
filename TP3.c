#include<stdio.h>
#include<stdlib.h>

typedef struct Noeud{
    int data;
    struct Noeud* suivant;
    struct Noeud* precedent;
}Noeud;

Noeud* cree(int valeur)
{
    Noeud* node = (Noeud*)malloc(sizeof(Noeud));
    if(node==NULL)
    { printf("Allocation Error!\a\n"); exit(1);/*No need to verify nowadays XD*/ }
    node->data = valeur;
    node->suivant = NULL;
    node->precedent = NULL;
    return node;
}

void affiche(Noeud* debut)
{
    Noeud* ptr = debut;
    if(ptr == NULL)
    { printf("Nothing to display! Empty List!\n"); }
    else
    {
        while(ptr!=NULL)
        {
            printf("%d -> ",ptr->data);
            ptr=ptr->suivant;
        }
        printf("NULL\n");
    }
}

void afficheInverse(Noeud* debut)
{
    Noeud* ptr = debut;
    Noeud* last = NULL;
    if(ptr == NULL)
    { printf("Nothing to display! Empty List!\n"); }
    else
    {
        while(ptr->suivant!=NULL)
        {
            ptr=ptr->suivant;
        }
        last = ptr;

        while(last!=NULL)
        {
            printf("%d -> ",last->data);
            last=last->precedent;
        }
        printf("NULL\n");
    }
}

Noeud* ajouterD(Noeud* debut,int valeur)
{
    Noeud* node = cree(valeur);
    if(debut == NULL)
     return node;
    else
    {
        node->suivant = debut;
        if(debut!=NULL)
        debut->precedent = node;
        debut = node; /*or return node; without that 'return debut'*/
    }
    return debut;
}

Noeud* ajouterF(Noeud* debut,int valeur)
{
    Noeud* node = cree(valeur);
    Noeud* ptr = debut;

    if(debut == NULL)
     return node;
    else
    {
        while(ptr->suivant!=NULL)
         ptr=ptr->suivant;
        node->precedent = ptr;
        ptr->suivant = node;
    }
    return debut;
}

int taille(Noeud* debut)
{
    int counter=0;
    Noeud* ptr = debut;
    while(ptr!=NULL)
    {
        ptr=ptr->suivant;
        counter++;
    }
    return counter;
}

Noeud* insertion(Noeud* debut,int pos,int valeur)
{
    if(pos<0 || pos>taille(debut))
     printf("Invalid Position!\n");
    else if(pos==0)
    {
        //to process an empty list
        Noeud* node = cree(valeur);
        node->suivant=debut;
        if(debut != NULL)
        { debut->precedent=node; }
        debut = node;
        return debut;
    }
    else
    {
        Noeud* parkour = debut;
        int i;

        for(i=1;i<pos;i++)//for(i=0;i<pos-1;i++)
         parkour=parkour->suivant;
        Noeud * node = cree(valeur);
        if(node!=NULL)
        {
            node->suivant=parkour->suivant;
            node->precedent=parkour;
            if(parkour->suivant!=NULL)
             parkour->suivant->precedent=node;
            parkour->suivant=node;
        }
    }
    return debut;
}

Noeud* rechercher(Noeud* debut,int valeur)
{
    Noeud* ptr = debut;

    if(ptr==NULL)
    { printf("Nothing to find! Empty List!\n"); return NULL; }
    else
    {
        while(ptr != NULL)
        {
            if(ptr->data == valeur)
             return ptr;
            ptr=ptr->suivant;
        }
        return NULL;
    }
}

Noeud* suppressionD(Noeud* debut)
{
    Noeud* ptr = debut;
    if(debut == NULL)
    { printf("Nothing to delete , list already empty!\n"); return NULL; }
    else
    {
        debut=debut->suivant;
        free(ptr);
        debut->precedent=NULL;
    }
    return debut;
}

Noeud* suppressionF(Noeud* debut)
{
    Noeud* ptr = debut;
    Noeud* tmp = NULL;
    if(debut == NULL)
    { printf("Nothing to delete , list already empty!\n"); return NULL; }
    else
    {
        while(ptr->suivant!=NULL)
         ptr=ptr->suivant;
        if(ptr->precedent!=NULL)
        { 
            tmp = ptr;
            ptr = ptr->precedent;
            ptr->suivant = NULL;
            free(tmp);
        }
    }
    return debut;
}

Noeud* suppressionP(Noeud* debut,int pos)
{
    if(pos<=0 || pos>taille(debut))
    { printf("Invalid position!\n"); return debut; }

    if(debut==NULL)
    { printf("Nothing to delete , Empty List!\n"); return NULL; }
    else if(pos==1)
    { debut = suppressionD(debut); }
    else if(pos==taille(debut))
    { debut = suppressionF(debut); }
    else
    {
        Noeud* ptr = debut;
        for(int i=1 ; i<pos ; i++)
         ptr=ptr->suivant;
        Noeud* tmp = ptr;
        ptr->precedent->suivant = ptr->suivant;
        free(tmp);
    }
    return debut;
}

Noeud* modifierD(Noeud* debut,int valeur)
{
    if(debut == NULL)
    { printf("Nothing to modifiy , empty list!\n"); return NULL; }
    else
     debut->data = valeur;
    return debut;
}

Noeud* modifierF(Noeud* debut,int valeur)
{
    Noeud* ptr = debut;

    if(debut == NULL)
    { printf("Nothing to modifiy , empty list!\n"); return NULL; }
    else
    {
        while(ptr->suivant!=NULL)
         ptr=ptr->suivant;
        ptr->data = valeur;
    }
    return debut;
}

Noeud* modifierP(Noeud* debut,int pos,int valeur)
{
    Noeud* ptr = debut;
    int i;

    if(pos<=0 || pos>taille(debut))
    { printf("Invalid position!\n"); return debut; }

    if(debut==NULL)
    { printf("Nothing to delete , Empty List!\n"); return NULL; }
    else if(pos==1)
    { debut = modifierD(debut,valeur); }
    else if(pos==taille(debut))
    { debut = modifierF(debut,valeur); }
    else
    {
        for(int i=1 ; i<pos ; i++)
         ptr=ptr->suivant;
        ptr->data = valeur;
    }
    return debut;
}

Noeud* trier(Noeud* debut)
{
    Noeud* i;/*or Noeud* i,*j;*/
    Noeud* j;
    int tmp;

    if(debut == NULL)
    { printf("Nothing to modifiy , empty list!\n"); return NULL; }

     for (i=debut ; i!=NULL ; i=i->suivant)
     {
        for (j=i->suivant ; j!=NULL ; j=j->suivant)
        {
            if (i->data > j->data)
            {
                tmp = j->data;
                j->data = i->data;
                i->data = tmp;
            }
        }
    }
    return debut;
}

int main()
{
    Noeud* debut = NULL;
    int size;
    Noeud* find = NULL;

    printf("``````````Test ajouterD``````````\n");
    debut = ajouterD(debut,1);
    debut = ajouterD(debut,2);
    debut = ajouterD(debut,3);
    debut = ajouterD(debut,4);
    debut = ajouterD(debut,5);
    printf("\n");
    printf("``````````Test ajouterF``````````\n");
    debut = ajouterF(debut,10);
    debut = ajouterF(debut,20);
    debut = ajouterF(debut,30);
    debut = ajouterF(debut,40);
    debut = ajouterF(debut,50);
    printf("\n");

    printf("``````````Test affiche``````````\n");
    affiche(debut);
    printf("``````````Test afficheInverse``````````\n");
    afficheInverse(debut);
    printf("\n");

    printf("``````````Test taille``````````\n");
    size = taille(debut);
    printf("The list's length : %d\n",size);
    printf("\n");

    printf("``````````Test insertion``````````\n");
    debut = insertion(debut,3,1000);
    affiche(debut);
    printf("\n");

    printf("``````````Test rechercher``````````\n");
    find = rechercher(debut,30);/*available value*/
    if(find==NULL)
     printf("Value not found.\n");
    else
     printf("Value found.\n");

    find = rechercher(debut,456);/*value not available*/
    if(find==NULL)
     printf("Value not found.\n");
    else
     printf("Value found.\n");

    printf("\n");

    printf("``````````Test suppressionD``````````\n");
    debut = suppressionD(debut);
    affiche(debut);
    printf("``````````Test suppressionF``````````\n");
    debut = suppressionF(debut);
    affiche(debut);
    printf("``````````Test suppressionP``````````\n");
    debut = suppressionP(debut,4);
    affiche(debut);
    printf("\n");

    printf("``````````Test modifierD``````````\n");
    debut = modifierD(debut,100);
    affiche(debut);
    printf("``````````Test modifierF``````````\n");
    debut = modifierF(debut,200);
    affiche(debut);
    printf("``````````Test modifierP``````````\n");
    debut = modifierP(debut,4,300);
    affiche(debut);
    printf("\n");

    printf("``````````Test trier``````````\n");
    debut = trier(debut);
    affiche(debut);
    printf("\n");

    return 0;
}