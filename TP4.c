#include<stdio.h>
#include<stdlib.h>

typedef struct Etudiant{
    int id;
    char nom[50];
    float moyenne;
    struct Etudiant* suivant;
    struct Etudiant* precedent;
}Etudiant;

Etudiant* cree_etudiant()
{
    Etudiant* node = (Etudiant*)malloc(sizeof(Etudiant));

    printf("ID : ");
    scanf("%d",&node->id);
    //getchar();
    printf("Nom : ");
    scanf(" %s",node->nom);
    printf("Moyenne : ");
    scanf("%f",&node->moyenne);
    node->suivant = NULL;
    node->precedent = NULL;
    printf("\t~~~~~~~~~~~~\n");

    return node;
}

int longueur(Etudiant* tete)
{
    int length = 0;
    Etudiant* ptr = tete;
    while(ptr!=NULL)
    {
        ptr=ptr->suivant;
        length++;
    }
    return length;
}

Etudiant* ajouter_position(Etudiant* tete,Etudiant* nouveau,int position)
{
    int i;

    if(position < 1 || position > longueur(tete))
    { printf("Invalid position!\n"); return tete; }

    if(position==1)
    {
        nouveau->suivant = tete;
        tete->precedent = nouveau;
        tete = nouveau;
        tete->precedent = NULL;
    }
    else if(position == longueur(tete))
    {
        Etudiant* ptr = tete;

        while(ptr->suivant != NULL)
        { ptr=ptr->suivant; }
        ptr->suivant = nouveau;
        nouveau->precedent = ptr;
        nouveau->suivant = NULL;
    }
    else
    {
        Etudiant* ptr = tete;

        for(i=1 ; i<position ; i++)
        { ptr=ptr->suivant; }
        nouveau->suivant = ptr->suivant;
        nouveau->precedent = ptr;
        ptr->suivant->precedent = nouveau;
        ptr->suivant = nouveau;
    }
    return tete;
}

Etudiant* supprimer_position(Etudiant* tete,int position)
{
    if(position < 1 || position > longueur(tete))
    { printf("Invalid position!\n"); return tete; }

    if(position==1)
    {
        Etudiant* ptr = tete;

        tete=tete->suivant;
        tete->precedent = NULL;
        free(ptr);
    }
    else if(position == longueur(tete))
    {
        Etudiant* ptr = tete;

        while(ptr->suivant->suivant != NULL)
        { ptr=ptr->suivant; }
        free(ptr->suivant);
        ptr->suivant = NULL;
    }
    else///////////////////////////////////////////////////////////////////////////////////
    {
        Etudiant* ptr = tete;
        Etudiant* tmp;
        int i;

        for(i=1 ; i<position ; i++)
        { ptr=ptr->suivant; }
        tmp=ptr->suivant;
        ptr->suivant = ptr->suivant->suivant;
        free(tmp);
    }
    return tete;
}

void afficher_liste(Etudiant* tete)
{
    Etudiant* ptr = tete;

    while(ptr!=NULL)
    {
        printf("ID : %d",ptr->id);
        printf("\nNom : ");
        puts(ptr->nom);/*displays and also '\n' automatically*/
        printf("Moyenne : %.2f",ptr->moyenne);
        printf("\n-----------------\n");
        ptr=ptr->suivant;
    }
    printf("\n");
}

Etudiant* derniere_cellule(Etudiant* tete)
{
    Etudiant* parkour = tete;

    while(parkour->suivant!=NULL)
    {
        parkour=parkour->suivant;
    }
    return parkour;
}

void afficher_liste_inverse(Etudiant* dernier)
{
    Etudiant* ptr = dernier;

    while(ptr!=NULL)
    {
        printf("\nID : %d",ptr->id);
        printf("\nNom : ");
        puts(ptr->nom);
        printf("Moyenne : %.2f",ptr->moyenne);
        printf("\n-----------------\n");
        ptr=ptr->precedent;
    }
    printf("NULL\n");
}

int chercher_etudiant(Etudiant* tete,int iD)
{
    Etudiant* parkour = tete;
    int find = 0;

    while(parkour!=NULL)
    {
        if(parkour->id == iD)
         return 1;
        parkour=parkour->suivant;
    }
    return find;
}

Etudiant* tri(Etudiant* tete)
{
    Etudiant* i;
    Etudiant* j;
    float tmp;

    if(tete == NULL)
    { printf("Nothing to modifiy , empty list!\n"); return NULL; }

     for(i=tete ; i!=NULL ; i=i->suivant)
     {
        for(j=i->suivant ; j!=NULL ; j=j->suivant)
        {
            if(i->moyenne > j->moyenne)
            {
                tmp = j->moyenne;
                j->moyenne = i->moyenne;
                i->moyenne = tmp;
            }
        }
    }
    return tete;
}

Etudiant* modifier_moyenne(Etudiant* tete,int position,float nouvelle_moyenne)
{
    if(position < 1 || position > longueur(tete))
    { printf("Invalid position!\n"); return tete; }

    if(position==1)
    {
        tete->moyenne = nouvelle_moyenne;
    }
    else if(position == longueur(tete))
    {
        Etudiant* ptr = tete;
        int i;

        while(ptr->suivant != NULL)
        { ptr=ptr->suivant; }
        ptr->moyenne = nouvelle_moyenne;
    }
    else
    {
        Etudiant* ptr = tete;
        int i;

        for(i=1 ; i<position ; i++)
        { ptr=ptr->suivant; }
        ptr->moyenne = nouvelle_moyenne;
    }
    return tete;
}

int main()
{
    Etudiant* tete = NULL;
    Etudiant* student1 = NULL;
    Etudiant* student2 = NULL;
    Etudiant* student3 = NULL;
    Etudiant* student4 = NULL;
    Etudiant* student5 = NULL;
    Etudiant* student6 = NULL;
    int found;

    printf("\t\t\t______Saisie d'information______\n");
    student1 = cree_etudiant();
    student2 = cree_etudiant();
    student3 = cree_etudiant();
    student4 = cree_etudiant();
    student5 = cree_etudiant();
    student6 = cree_etudiant();
    printf("\n");
    tete = student1;
    student1->suivant = student2;
    student2->precedent = student1;
    student2->suivant = student3;
    student3->precedent = student2;

    tete = ajouter_position(tete,student4,1);
    tete = ajouter_position(tete,student5,2);
    tete = ajouter_position(tete,student6,longueur(tete));

    printf("\t\t\t______Affichage des etudiants______\n");
    afficher_liste(tete);

    tete = supprimer_position(tete,1);
    tete = supprimer_position(tete,2);
    tete = supprimer_position(tete,longueur(tete));
    printf("\t\t\t______Affichage apres suppressions______\n");
    afficher_liste(tete);

    Etudiant* lastSTD = derniere_cellule(tete);
    printf("\t\t\t______Affichage inverse______\n");
    afficher_liste_inverse(lastSTD);

    found = chercher_etudiant(tete,33);
    printf("%d.\n",found);
    found = chercher_etudiant(tete,100);
    printf("%d.\n",found);

    tete = tri(tete);
    printf("\t\t\t______Affichage apres le tri______\n");
    afficher_liste(tete);

    tete = modifier_moyenne(tete,2,110.25);
    printf("\t\t\t______Affichage apres modification______\n");
    afficher_liste(tete);
    return 0;
}