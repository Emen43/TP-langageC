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

liste* creer_produit()
{ 
    liste* node = (liste*)malloc(sizeof(liste));

    if(!node)//or if(node == NULL)
    {
        printf("Not enough memory!\a\n"); return NULL;
    }

    node->cellule.Nom_Produit = (char*)malloc(100*sizeof(char));

    printf("Saisir le nom du produit : ");
    scanf(" %s",node->cellule.Nom_Produit);
    printf("Saisir la reference : ");
    scanf(" %s",node->cellule.reference);
    printf("Saisir le prix : ");
    scanf("%f",&node->cellule.Montant);
    //getchar();
    printf("Saisir la date :\n");
    printf("\tJour : ");
    scanf(" %s",node->cellule.DateAchat.jour);
    printf("\tMois : ");
    scanf(" %s",node->cellule.DateAchat.mois);
    printf("\tAnnee : ");
    scanf(" %s",node->cellule.DateAchat.annee);
    node->psuiv = NULL;
    free(node->cellule.Nom_Produit);

    return node;
}

void afficher_produit(liste* produit)
{
    liste* parkour = produit;

    if(produit==NULL)
    {
        printf("Nothing to display!\n"); return;
    }

    printf("\tNom du produit : ");
    puts(parkour->cellule.Nom_Produit);
    printf("\tReference : ");
    puts(parkour->cellule.reference);
    printf("\tMontant : ");
    printf("%.2f",parkour->cellule.Montant);
    printf("\n\tDate d'achat :\n");
    printf(" Jour : ");
    printf("%s  ",parkour->cellule.DateAchat.jour);
    printf(" Mois : ");
    printf("%s  ",parkour->cellule.DateAchat.mois);
    printf(" Annee : ");
    printf("%s\n",parkour->cellule.DateAchat.annee);

    printf("\n");
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
    if(*tete == NULL)
    { printf("The list is empty.\n"); return; }

    if( (*tete)->psuiv == NULL )
    {
        free(*tete);
        *tete = NULL;
        return;
    }

    liste* tmp = *tete;
    while(tmp->psuiv->psuiv!=NULL)
    {
        tmp = tmp->psuiv;
    }
    free(tmp->psuiv);
    tmp->psuiv=NULL;
}

liste* rembourser(liste* tete,const char* refer)
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
    int isEmpty;
    const char* refer = "Tester";

    printf("Initialisation d'une liste vide\n");
    tete = creer_liste_produits();
    printf("\n");

    isEmpty = est_vide(tete);
    printf("%d.\n",isEmpty);
    afficher_produit(tete);
    printf("------------------------\n");

    tete = ajouter_debut(tete);
    tete = ajouter_debut(tete);
    tete = ajouter_debut(tete);
    ajouter_fin(&tete);
    ajouter_fin(&tete);
    ajouter_fin(&tete);
    afficher_produits(tete);
    printf("------------------------\n");

    date theDT;
    printf("Saisir la date pour filtrer:\n");
    printf("\tJour : ");
    scanf(" %s",theDT.jour);
    printf("\tMois : ");
    scanf(" %s",theDT.mois);
    printf("\tAnnee : ");
    scanf(" %s",theDT.annee);
    filtrer_date(tete,theDT);

    tete = supprimer_debut(tete);
    supprimer_fin(&tete);
    tete = rembourser(tete,refer);

    return 0;
}
