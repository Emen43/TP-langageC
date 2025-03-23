#include<stdio.h>
#include<stdlib.h>

typedef struct Noeud{
    int data;
    struct Noeud* suivant;
}Noeud;

Noeud* cree(int valeur)
{
    Noeud* node = (Noeud*)malloc(sizeof(Noeud));
    node->data=valeur;
    node->suivant=NULL;
    return node;
}

void affiche(Noeud* debut)
{
    Noeud* parkour = debut;
    while(parkour!=NULL)
    {
        printf("%d -> ",parkour->data);
        parkour=parkour->suivant;
    }
    printf("NULL\n");
}

Noeud* ajouterD(Noeud* debut,int valeur)
{
    Noeud* node = cree(valeur);

    if(debut != NULL)
     node->suivant = debut;
    debut = node;
    return debut;
}

Noeud* ajouterF(Noeud* debut,int valeur)
{
    Noeud* node = cree(valeur);

    if (debut == NULL) { return node; }

    Noeud* parkour = debut;
    while (parkour->suivant != NULL)
    { parkour = parkour->suivant; }

    parkour->suivant = node;
    return debut;
}

int taille(Noeud* debut)
{
    Noeud* parkour = debut;
    int counter = 0;
    while(parkour != NULL)
    {
        parkour=parkour->suivant;
        counter++;
    }
    return counter;
}

Noeud* insertion(Noeud* debut,int pos,int valeur)
{
    Noeud *node = (Noeud*)malloc(sizeof(Noeud));
    node = cree(valeur);
    Noeud* parkour = debut;
    if(pos>=1 && pos<=taille(debut))
    {
        for(int i=1 ; i<pos ; i++)
        {
            parkour=parkour->suivant;
        }
        node->suivant=parkour->suivant;
        parkour->suivant=node;
    }
    return debut;
}

void rechercher(Noeud* debut,int valeur)
{
    int trouve;
    Noeud* parkour = debut;

    while(parkour != NULL)
    {
        if(parkour->data == valeur)
        { trouve=1; break; }
        else
         { trouve=0; }
        parkour=parkour->suivant;
    }
    if(trouve==1)
    printf("Value founded.\n");
    else
    printf("Value not founded!\n");
}

Noeud* suppressionD(Noeud* debut)
{
    if(debut == NULL)
    { printf("The list is empty.\n"); return NULL; }

    Noeud* tmp = debut;
    debut = debut->suivant;
    free(tmp);
    return debut;
}

Noeud* suppressionF(Noeud* debut)
{
    if(debut == NULL)
    { printf("The list is empty.\n"); return NULL; }

    Noeud* tmp = debut;
    while(tmp->suivant->suivant!=NULL)
    {
        tmp = tmp->suivant;
    }
    free(tmp->suivant);
    tmp->suivant=NULL;
    return debut;
}

Noeud* suppressionP(Noeud* debut,int pos)////////////////
{
    Noeud* parkour = debut;
    Noeud* parkour2; 

    if((pos<1 || pos>taille(debut)))
    { printf("Invalid position.\n"); return debut; }
    if(pos == 1)
     debut = suppressionD(debut);
    else if(pos == taille(debut))
     debut = suppressionF(debut);
    else if(pos>=1 || pos<=taille(debut))
    {
        for(int i=0 ; i<pos-1 ; i++)
         parkour=parkour->suivant;
    }
    parkour2= parkour->suivant;
    parkour->suivant = parkour2->suivant;
    free(parkour2);
    return debut;
}

Noeud* modifierD(Noeud* debut,int valeur)
{
    if(debut==NULL)
    printf("Nothing to modify , list empty!\n");
    else
    debut->data=valeur;
    return debut;
}

Noeud* modifierF(Noeud* debut,int valeur)
{
    if(debut==NULL)
    printf("Nothing to modify , list empty!\n");
    else
    {
        Noeud* parkour = debut;
        while(parkour->suivant->suivant!=NULL)
         parkour=parkour->suivant;
        free(parkour->suivant);
        parkour->suivant=NULL;
    }
    return debut;
}

Noeud* modifierP(Noeud* debut,int pos,int valeur)
{
    Noeud* parkour = debut;
    int size = taille(debut);

    if(debut == NULL)
    {
        printf("The list is empty.\n");
        return NULL;
    }
    
    if(pos<1 || pos>size)
    {
        printf("Invalid position!\n");
        exit(1);
    }

    for(int i=1 ; i<pos ; i++)
    { parkour=parkour->suivant; }
    parkour->data = valeur;

    return debut;
}

int main()
{
    Noeud* debut = NULL;

    debut = ajouterD(debut,10);
    debut = ajouterD(debut,20);
    debut = ajouterD(debut,30);
    debut = ajouterD(debut,40);
    debut = ajouterD(debut,50);
    debut = ajouterD(debut,60);
    affiche(debut);
    printf("\n");

    printf("````````Adding few more values```````\n");
    debut = ajouterF(debut,1000);
    debut = ajouterF(debut,2000);
    debut = ajouterD(debut,3000);
    affiche(debut);
    printf("\n");

    printf("The list's length is %d\n",taille(debut));
    printf("\n");

    debut = insertion(debut,3,50000);
    printf("~~~~~~~~~~~~~~~After insert~~~~~~~~~~~~~~~~\n");
    affiche(debut);
    printf("\n");

    rechercher(debut,30);
    rechercher(debut,5674);
    printf("\n");

    debut = suppressionD(debut);
    printf("========After delete First=========\n");
    affiche(debut);
    printf("\n");

    debut = suppressionF(debut);
    printf("========After delete Last=========\n");
    affiche(debut);
    printf("\n");

    debut = suppressionP(debut,3);
    printf("========After delete Position=========\n");
    affiche(debut);
    printf("\n");

    debut = modifierD(debut,123);
    printf("---------After modification First---------\n");
    affiche(debut);
    printf("\n");

    debut = modifierF(debut,456);
    printf("---------After modification Last---------\n");
    affiche(debut);
    printf("\n");

    debut = modifierP(debut,3,789);
    printf("---------After modification Position---------\n");
    affiche(debut);
    printf("\n");

    return 0;
}