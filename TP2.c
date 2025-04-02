#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Date{
    char jour[3];
    char mois[3];
    char annee[5];
}date;

typedef struct Produit{
    char* Nom_Produit;
    char reference[100];
    float Montant;
    date DateAchat;
}produit;

typedef struct Liste{
    produit cellule;
    struct Liste* psuiv;
}liste;

/*------------------------------------------------------------------------------------*/

liste* creer_liste_produits()
{
    return NULL;
}

int est_vide(liste* tete)
{
    if(tete==NULL)
    return 1;
    else
    return 0;
    //or return (tete == NULL)
}

void viderBuffer()
{
    int c;
    while( (c=getchar())!='\n' && c!=EOF);
}

liste* creer_produit()
{ 
    liste* node = (liste*)malloc(sizeof(liste));
    char prodcName[100];// is equivalent to : char prodcName[];
    char refer[100];
    float pRICE;
    date buyDate;

    if(!node)//or if(node == NULL)
    {
        printf("Not enough memory!\n"); return NULL;
    }

    printf("Saisir le nom du produit : ");
     scanf("%99s",prodcName);
    printf("Saisir la reference : ");
     scanf("%99s",refer);
    printf("Saisir le prix : ");
     scanf("%f",&pRICE);
    printf("Saisir la date :\n");
    printf("\tJour : ");
     scanf("%2s",buyDate.jour);
    printf("\tMois : ");
     scanf("%2s",buyDate.mois);
    printf("\tAnnee : ");
     scanf("%4s",buyDate.annee);
    printf("\n");

    strcpy(node->cellule.Nom_Produit,prodcName);
    strcpy(node->cellule.reference,refer);
    node->cellule.Montant = pRICE;
    strcpy(node->cellule.DateAchat.jour,buyDate.jour);
    strcpy(node->cellule.DateAchat.mois,buyDate.mois);
    strcpy(node->cellule.DateAchat.annee,buyDate.annee);
    node->psuiv = NULL;

    return node;
}

void afficher_produit(liste* produit)
{
    liste* parkour = produit;
    if(produit==NULL)
    printf("Nothing to display.\n\a");
    else
    {
        printf("\tNom du produit : ");
        puts(parkour->cellule.Nom_Produit);
        printf("\tReference : ");
        puts(parkour->cellule.reference);
        printf("\tMontant : ");
        printf("%f",parkour->cellule.Montant);
        printf("\tDate d'achat : ");
        printf(" Jour : ");
        printf("%s  ",parkour->cellule.DateAchat.jour);
        printf(" Mois : ");
        printf("%s  ",parkour->cellule.DateAchat.mois);
        printf(" Annee : ");
        printf("%s\n",parkour->cellule.DateAchat.annee);
    }
}

liste* ajouter_debut(liste* tete)
{
    liste* tmp = NULL;
    
    tmp = creer_produit();
    tmp->psuiv = tete;
    tete = tmp;

    return tete;
}

void ajouter_fin(liste** tete)
{
    liste* tmp = NULL;
    liste* parkour = *tete;

    tmp = creer_produit();
    while (parkour->psuiv != NULL)
    { parkour = parkour->psuiv; }
    parkour->psuiv = tmp;
}

//Remarque sur le temps d'execution : code full of errors

void afficher_produits(liste* tete)
{
    liste* parkour = tete;

    if(parkour!=NULL)
    {
        printf("======Affichage des produits======\n");
        while(parkour!=NULL)
        {
            afficher_produit(parkour);
            parkour=parkour->psuiv;
        }
    }
    else
    printf("Nothing to display! Empty list.\n");
}

int longueur(liste* tete)
{
    liste* parkour = tete;
    int counter = 0;
    while(parkour != NULL)
    {
        parkour=parkour->psuiv;
        counter++;
    }
    return counter;
}

void filtrer_date(liste* tete,date dt)
{
    liste* parkour = tete;

    if(parkour!=NULL)
    {
        printf("\t\t`````` Affichage des produits de la date : %s/%s/%s ``````\n",dt.jour,dt.mois,dt.annee);
        while(parkour!=NULL)
        {
            if( strcmp(parkour->cellule.DateAchat.jour,dt.jour)==0 && strcmp(parkour->cellule.DateAchat.mois,dt.mois)==0 && strcmp(parkour->cellule.DateAchat.annee,dt.annee)==0 )
            {
                printf("\tNom du produit : ");
                 puts(parkour->cellule.Nom_Produit);
                printf("\tReference : ");
                 puts(parkour->cellule.reference);
                printf("\tMontant : ");
                 printf("%f",parkour->cellule.Montant);
                printf("\tDate d'achat jour/mois/annee : ");
                 printf("%s/%s/%s\n",parkour->cellule.DateAchat.jour,parkour->cellule.DateAchat.mois,parkour->cellule.DateAchat.annee);
            }
            parkour=parkour->psuiv;
        }
    }
    else
    printf("No product found based on the date provided !\a\n");
}

liste* supprimer_debut(liste* tete)
{
    if(tete == NULL)
    { printf("The list is empty.\n"); return NULL; }

    liste *tmp = tete;
    tete = tete->psuiv;
    free(tmp);
    return tete;
}

void supprimer_fin(liste** tete)
{
    if(tete == NULL)
    { printf("The list is empty.\n"); }

    liste* tmp = *tete;
    while(tmp->psuiv->psuiv!=NULL)
    {
        tmp = tmp->psuiv;
    }
    free(tmp->psuiv);
    tmp->psuiv=NULL;
}

liste* rembourser(liste* tete,char* refer)
{
    liste* parkour = tete;
    liste* ptr = tete;

    if(parkour==NULL)
    { printf("Rien a rembourser!\a\n"); return tete; }
    else
    {
        while(parkour!=NULL)
        {
            if( strcmp(tete->cellule.reference,refer) == 0 )
            tete = supprimer_debut(tete);
            else if( parkour->psuiv->psuiv == NULL )
            {
                if( strcmp(parkour->psuiv->cellule.reference,refer) == 0 )
                supprimer_fin(&tete);
            }
            else
            {
                if( strcmp(parkour->psuiv->cellule.reference,refer) == 0 )
                {
                    ptr = parkour->psuiv;
                    parkour->psuiv = ptr->psuiv;
                    free(ptr);
                }
            }
            parkour=parkour->psuiv;
        }
    }
    return tete;
}

int main()
{
    liste* tete = NULL;
    int empty;
    printf("Initialisation d'une liste vide\n");
    tete = creer_liste_produits();

    empty = est_vide(tete);

    tete = creer_produit(tete);

    afficher_produit(tete);

    tete = ajouter_debut(tete);// it fails to allocate
    //tete = ajouter_debut(tete);
    /*ajouter_fin(tete);
    ajouter_fin(tete);

    afficher_produits(tete);*/
    return 0;
}
