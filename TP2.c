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

liste* creer_liste_produits(liste* tete)
{
    tete = NULL;
    return tete;
}

int est_vide(liste* tete)
{
    if(tete==NULL)
    return 1;
    else
    return 0;
}

liste* creer_produit(liste* tete,char prdctName[],char ref[],float price,date boughtDate)
{
    liste* node = (liste*)malloc(sizeof(liste));

    strcpy(node->cellule.Nom_Produit,prdctName);
    strcpy(node->cellule.reference,ref);
    node->cellule.Montant = price;
    node->cellule.DateAchat = boughtDate;
    node->psuiv = NULL;

    return node;
}

void afficher_produit(liste* produit)
{
    if(produit==NULL)
    printf("Nothing to display.\n\a");
    else
    {
        printf("~~~~~~Information du produit~~~~~~\n");
        printf("Nom du produit : ");
        puts(produit->cellule.Nom_Produit);
        printf("Reference : ");
        puts(produit->cellule.reference);
        printf("Montant : ");
        printf("%f",produit->cellule.Montant);
        printf("Date d'achat : ");
        printf(" Jour : %s",produit->cellule.DateAchat.jour);
        printf(" |");
        printf(" Mois : %s",produit->cellule.DateAchat.mois);
        printf(" |");
        printf(" Annee : %s",produit->cellule.DateAchat.annee);
        printf("\n");
    }
}

liste* ajouter_debut(liste* tete)
{
    liste* tmp = NULL;
    char* prodcName;// is equivalent to : char prodcName[];
    char refer[100];
    float pRICE;
    date buyDate;

    printf("Saisir le nom du produit : ");
    scanf(" %[^\n]",prodcName);
    printf("Saisir la reference : ");
    scanf(" %[^\n]",refer);
    printf("Saisir le prix : ");
    scanf("%f",&pRICE);
    printf("Saisir la date : ");
    printf("\tJour : ");
    scanf(" %[^\n]",buyDate.jour);
    printf("\tMois : ");
    scanf(" %[^\n]",buyDate.mois);
    printf("\tAnnee : ");
    scanf(" %[^\n]",buyDate.annee);
    tmp = creer_produit(tete,*prodcName,*refer,pRICE,buyDate);

    tmp->psuiv = tete;
    tete = tmp;

    return tete;
}

void ajouter_fin(liste** tete)
{
    liste* tmp = NULL;
    char* prodcName;// is equivalent to : char prodcName[];
    char refer[100];
    float pRICE;
    date buyDate;

    printf("Saisir le nom du produit : ");
    scanf(" %[^\n]",prodcName);
    printf("Saisir la reference : ");
    scanf(" %[^\n]",refer);
    printf("Saisir le prix : ");
    scanf("%f",&pRICE);
    printf("Saisir la date : ");
    printf("\tJour : ");
    scanf(" %[^\n]",buyDate.jour);
    printf("\tMois : ");
    scanf(" %[^\n]",buyDate.mois);
    printf("\tAnnee : ");
    scanf(" %[^\n]",buyDate.annee);
    tmp = creer_produit(tete,*prodcName,*refer,pRICE,buyDate);

    liste* parkour = tete;
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
            if(parkour->cellule.DateAchat == dt)
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
    { printf("The list is empty.\n"); return NULL; }

    liste* tmp = tete;
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
                tete = supprimer_fin(tete);
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
    return 0;
}
