#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<windows.h>
#include<time.h>

typedef struct PLAT{
    char nom[30];
    float prix;
    char categorie[10];
    int desc_position; // To track position in description file
}PLAT;

typedef struct LIST{
    PLAT dish;
    struct LIST* next;
}LIST;

FILE* desc;
char descMEAL[100];

// Function to get a description from file based on position
char* get_description(int position)
{
    static char buffer[100];
    FILE* f = fopen("descriptionRES.txt","rt");
    int i;

    if (f == NULL)
    return "No description available";

    for (i = 0; i <= position; i++)
    {
        if (fgets(buffer, sizeof(buffer), f) == NULL)
        {
            fclose(f);
            return "Description not found";
        }
    }
    fclose(f);
    return buffer;
}

LIST* createMEAL(int* desc_counter)
{
    LIST* meal = (LIST*)malloc(sizeof(LIST));

    if(!meal)
    {
        textcolor(4);
        cprintf("The system is under maintenance.\a\n"); Beep(750,800); exit(1);
    }

    desc = fopen("descriptionRES.txt","at+");
    if(desc==NULL)
    { textcolor(4); cprintf("The system is under maintenance.\a\n"); Beep(750,800); exit(1); }

    textcolor(9);
    cprintf("`````````````````Saisie d'information du plat`````````````````\n");
    printf("\n");
    textcolor(3);
    cprintf("Nom : ");
    fflush(stdin);
    fgets(meal->dish.nom,sizeof(meal->dish.nom),stdin);
    meal->dish.nom[strcspn(meal->dish.nom, "\n")] = 0; // Remove newline

    cprintf("Prix : ");
    scanf("%f",&meal->dish.prix);

    cprintf("Categorie ? ");
    fflush(stdin);
    fgets(meal->dish.categorie,sizeof(meal->dish.categorie),stdin);
    meal->dish.categorie[strcspn(meal->dish.categorie, "\n")] = 0; // Remove newline

    cprintf("Description (Ne depassez pas 100 caracteres):\n");
    printf("\n");
    memset(descMEAL,0,sizeof(descMEAL));
    fflush(stdin);
    fgets(descMEAL,sizeof(descMEAL),stdin);
    descMEAL[strcspn(descMEAL, "\n")] = 0; // Remove newline

    // Store the current position in file
    meal->dish.desc_position = *desc_counter;
    (*desc_counter)++;

    fprintf(desc,"%s\n",descMEAL);
    fclose(desc);

    printf("\n");
    meal->next = NULL;

    return meal;
}

LIST* ajouterD(LIST* RES, int* desc_counter)
{
    LIST* node = createMEAL(desc_counter);
    node->next = RES;
    RES = node;

    return RES;
}

LIST* ajouterF(LIST* RES, int* desc_counter)
{
    LIST* parkour = RES;
    LIST* node = createMEAL(desc_counter);

    if (RES == NULL) { return node; }

    while(parkour->next != NULL)
    { parkour = parkour->next; }

    parkour->next = node;
    return RES;
}

void displayMEAL(LIST* meal)
{
    if(meal == NULL)
    {
        textcolor(4);
        cprintf("Nothing to display!\n"); return;
    }

    textcolor(10);
    cprintf("Nom: %s\n", meal->dish.nom);
    cprintf("Prix: %.2f\n", meal->dish.prix);
    cprintf("Categorie: %s\n", meal->dish.categorie);
    cprintf("Description: %s\n", get_description(meal->dish.desc_position));
    printf("\n");
}

void displayMEALS(LIST* RES)
{
    LIST* parkour = RES;

    if(parkour!=NULL)
    {
        textcolor(11);
        cprintf("`````````````````Affichage des plats`````````````````\n");
        printf("\n");
        textcolor(2);
        cprintf("Nom");
        printf("\t\t");
        cprintf("Prix");
        printf("\t\t");
        cprintf("Categorie");
        printf("\t\t");
        cprintf("Description");
        printf("\t\t\n");
        while(parkour!=NULL)
        {
            textcolor(10);
            cprintf("%-15s",parkour->dish.nom);
            printf("\t");
            cprintf("%.2f",parkour->dish.prix);
            printf("\t");
            cprintf("%-10s",parkour->dish.categorie);
            printf("\t\t");
            cprintf("%s",get_description(parkour->dish.desc_position));
            printf("\n\n");
            parkour=parkour->next;
        }
        printf("\n");
    }
    else
    {
        textcolor(4);
        cprintf("Nothing to display!\n");
    }
}

LIST* ajoutA(LIST* RES, int* desc_counter)
{
    LIST* parkour = RES;
    LIST* node = createMEAL(desc_counter);
    char aftMEAL[30];

    textcolor(3);
    cprintf("Here is our meals:\n");
    displayMEALS(RES);

    cprintf("Insert after which meal ?\n");
    fflush(stdin);
    fgets(aftMEAL, sizeof(aftMEAL), stdin);
    aftMEAL[strcspn(aftMEAL, "\n")] = 0; // Remove newline

    while( parkour!=NULL && strcmp(parkour->dish.nom,aftMEAL)!=0 )
    { parkour=parkour->next; }

    if(parkour == NULL || strcmp(parkour->dish.nom,aftMEAL)!=0 )
    {
        textcolor(4);
        cprintf("%s has not been found!\n", aftMEAL);
        return RES;
    }

    if(node != NULL)
    {
        node->next = parkour->next;
        parkour->next = node;
    }
    return RES;
}

int Counter(LIST* RES)
{
    LIST* parkour = RES;
    int counter = 0;
    while(parkour != NULL)
    {
        parkour=parkour->next;
        counter++;
    }
    return counter;
}

LIST* modifier(LIST* RES)
{
    FILE* f = fopen("descriptionRES.txt", "r+");
    LIST* parkour = RES;
    int size = Counter(RES);
    long pos;
    int i;

    if(RES == NULL)
    { textcolor(4); cprintf("The system is under maintenance.\a\n"); Beep(750,800); exit(1); }

    textcolor(3);
    cprintf("Here's the meal's list :\n");
    displayMEALS(RES);

    cprintf("Type the position of the meal you want to modify : ");
    do{
        scanf("%d",&pos);
        if(pos<1 || pos>size)
        {
            textcolor(4);
            cprintf("Invalid position.\nType a valid position : ");
        }
    }while(pos<1 || pos>size);

    for(i=1 ; i<pos ; i++)
    { parkour=parkour->next; }

    textcolor(3);
    cprintf("\t\t\t\tYou can start modify now :\n");
    cprintf("Nom [%s] : ", parkour->dish.nom);
    fflush(stdin);
    fgets(parkour->dish.nom,sizeof(parkour->dish.nom),stdin);
    parkour->dish.nom[strcspn(parkour->dish.nom, "\n")] = 0;

    cprintf("Prix [%.2f] : ", parkour->dish.prix);
    scanf("%f",&parkour->dish.prix);

    cprintf("Categorie [%s] ? ", parkour->dish.categorie);
    fflush(stdin);
    fgets(parkour->dish.categorie,sizeof(parkour->dish.categorie),stdin);
    parkour->dish.categorie[strcspn(parkour->dish.categorie, "\n")] = 0;

    cprintf("Description [%s] :\n", get_description(parkour->dish.desc_position));
    fflush(stdin);
    fgets(descMEAL,sizeof(descMEAL),stdin);
    descMEAL[strcspn(descMEAL, "\n")] = 0;

    // Update description in file
    if (f != NULL) {
        fseek(f, 0, SEEK_SET);
        for (i = 0; i < parkour->dish.desc_position; i++) {
            while (fgetc(f) != '\n' && !feof(f));
        }
        pos = ftell(f);
        fseek(f, pos, SEEK_SET);
        fprintf(f, "%s\n", descMEAL);
        fclose(f);
    }

    return RES;
}

LIST* suppressionD(LIST* RES)
{
    LIST* tmp = RES;

    if(RES == NULL)
    { textcolor(4); cprintf("The system is under maintenance.\a\n"); Beep(750,800); exit(1); }

    RES = RES->next;
    free(tmp);
    return RES;
}

LIST* suppressionF(LIST* RES)
{
    LIST* tmp = RES;

    if(RES == NULL)
    { textcolor(4); cprintf("The system is under maintenance.\a\n"); Beep(750,800); exit(1); }

    if(RES->next == NULL) {
        free(RES);
        return NULL;
    }

    while(tmp->next->next!=NULL)
    {
        tmp = tmp->next;
    }
    free(tmp->next);
    tmp->next=NULL;
    return RES;
}

LIST* suppressionM(LIST* RES, char* nom)
{
    LIST* curr = RES;

    if(RES == NULL)
    { textcolor(4); cprintf("The system is under maintenance.\a\n"); Beep(750,800); exit(1); }


    while(curr != NULL && strcmp(curr->dish.nom, nom) != 0) {
        curr = curr->next;
    }

    if(curr == NULL) {
        textcolor(4);
        cprintf("%s not found!\n", nom);
        return RES;
    }

    free(curr);
    return RES;
}

LIST* triCroissant(LIST* RES)
{
    LIST *sorted = NULL;
    LIST *current = RES;
    LIST *next = NULL;
    LIST *temp = NULL;

    if(RES == NULL || RES->next == NULL) {
        return RES;
    }

    while(current != NULL) {
        LIST *next = current->next;

        if(sorted == NULL || strcmp(current->dish.nom, sorted->dish.nom) < 0) {
            current->next = sorted;
            sorted = current;
        } else {
            LIST *temp = sorted;
            while(temp->next != NULL && strcmp(current->dish.nom, temp->next->dish.nom) > 0) {
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }

        current = next;
    }

    return sorted;
}

void searchByName(LIST* RES, char* name) {
    LIST* temp = RES;
    int found = 0;

    while(temp != NULL) {
        if(strcmp(temp->dish.nom, name) == 0) {
            displayMEAL(temp);
            found = 1;
        }
        temp = temp->next;
    }

    if(!found) {
        textcolor(4); cprintf("No meal found with name: %s\n", name);
    }
}

void searchByCategory(LIST* RES, char* category) {
    LIST* temp = RES;
    int found = 0;

    while(temp != NULL) {
        if(strcmp(temp->dish.categorie, category) == 0) {
            displayMEAL(temp);
            found = 1;
        }
        temp = temp->next;
    }

    if(!found) {
        textcolor(4); cprintf("No meal found in category: %s\n", category);
    }
}

int main()
{
    LIST* RES = NULL;
    int mp,gr,c1,c3,c4;
    int desc_counter = 0; // To track descriptions in file
    time_t currentTime;
    struct tm* localTime;
    char category[10];

    //textbackground(15);
    textcolor(12);
    clrscr();
    printf("\t\t\t\t");
    cprintf("~~~~~~~~~~~~~~~~~~~~WELCOME\a~~~~~~~~~~~~~~~~~~~~\n");
    textcolor(13);

    // Get the current time
    currentTime = time(NULL);
    // Convert the current time to local time
    localTime = localtime(&currentTime);
    // Print the current time
    cprintf("The current time is: %02d:%02d:%02d\n",localTime->tm_hour,localTime->tm_min,localTime->tm_sec);

    menuP:
    textcolor(6);
    do{
        printf("\t\t\t\t\t");
        cprintf("1 -> Gestion des restaurants.\n");
        printf("\n");
        printf("\t\t\t\t\t");
        cprintf("2 -> Quitter.\n");
        printf("\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t\t\t ");
        cprintf("Choix : ");
        scanf("%d",&mp);
    }while(mp!=1 && mp!=2);

    switch(mp)
    {
        textcolor(14);
        case 1:
         printf("\n\t\t\t\t\t");
         cprintf("__________Gestion des restaurants__________\n");
         printf("\n");
         start:
         clrscr();
         textcolor(14);
         printf("\n");
         cprintf("1 -> Ajout de plats\n");
         printf("\n");
         cprintf("2 -> Modification des plats\n");
         printf("\n");
         cprintf("3 -> Suppression des plats\n");
         printf("\n");
         cprintf("4 -> Recherche des plats\n");
         printf("\n");
         cprintf("5 -> Afficher les plats\n");
         printf("\n");
         cprintf("6 -> Gerer les categories de plats\n");
         printf("\n");
         cprintf("7 -> Options de tri personnalisees\n");
         printf("\n");
         cprintf("8 -> MENU principal\n");
         printf("\n");
         printf("\n");
         printf("\t\t\t\t\t\t\t\t\t\t\t\t ");
         cprintf("Choix : ");
         scanf("%d",&gr);

         switch(gr)
         {
            case 1:
             textcolor(14);
             do{
                 cprintf("1 : Ajout au debut\n");
                 printf("\n");
                 cprintf("2 : Ajout a la fin\n");
                 printf("\n");
                 cprintf("3 : Ajout apres un plat specifique\n");
                 printf("\n");
                 cprintf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t ");
                 cprintf("Choix : ");
                 scanf("%d",&c1);
                 if(c1<1 || c1>3)
                 {
                    printf("Choix Invalide!\a\n");
                    getch();
                 }
             }while(c1<1 || c1>3);

              if(c1 == 1)
                RES = ajouterD(RES, &desc_counter);
              else if(c1 == 2)
                RES = ajouterF(RES, &desc_counter);
              else if(c1 == 3)
                RES = ajoutA(RES, &desc_counter);
              goto start;
            break;

            case 2:
              RES = modifier(RES);
              goto start;
            break;

            case 3:
             textcolor(14);
             do{
                 cprintf("1 : Suppression au debut\n");
                 printf("\n");
                 cprintf("2 : Suppression a la fin\n");
                 printf("\n");
                 cprintf("3 : Suppression d'un plat specifique\n");
                 printf("\n");
                 cprintf("4 : Retour\n");
                 printf("\n");
                 cprintf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t ");
                 cprintf("Choix : ");
                 scanf("%d",&c3);
                 if(c3<1 || c3>4)
                  printf("Choix Invalide!\a\n");
             }while(c3<1 || c3>4);

              if(c3 == 1)
                RES = suppressionD(RES);
              else if(c3 == 2)
                RES = suppressionF(RES);
              else if(c3 == 3) {
                char name[30];
                printf("Enter meal name to delete: ");
                fflush(stdin);
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = 0;
                RES = suppressionM(RES, name);
              }
              else if(c3 == 4)
               goto start;
              goto start;
            break;

            case 4:
             textcolor(14);
             do{
                 cprintf("1 : Par nom du plat\n");
                 printf("\n");
                 cprintf("2 : Par categorie\n");
                 printf("\n");
                 cprintf("3 : Recherche avancee\n");
                 printf("\n");
                 cprintf("4 : Retour\n");
                 printf("\n");
                 cprintf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t ");
                 cprintf("Choix : ");
                 scanf("%d",&c4);
                 if(c4<1 || c4>4)
                 {
                     textcolor(5);
                     cprintf("Choix Invalide!\a\n");
                 }
             }while(c4<1 || c4>4);

              if(c4 == 1) {
                char name[30];
                textcolor(2);
                cprintf("Enter meal name to search: ");
                fflush(stdin);
                fgets(name,sizeof(name),stdin);
                name[strcspn(name,"\n")] = 0;
                searchByName(RES,name);
              }
              else if(c4 == 2) {
                textcolor(2);
                cprintf("Enter category to search: ");
                fflush(stdin);
                fgets(category,sizeof(category),stdin);
                category[strcspn(category,"\n")] = 0;
                searchByCategory(RES,category);
              }
              else if(c4 == 3) {
                textcolor(5);
                cprintf("What ?\n");
              }
              else if(c4 == 4)
              goto start;
            break;

            case 5:
              displayMEALS(RES);
              getch();
              goto start;
            break;

            case 6:
              textcolor(5);
              cprintf("What ?\n");
              getch();
              goto start;
            break;

            case 7:
              textcolor(2);
              RES = triCroissant(RES);
              cprintf("Meals sorted alphabetically\n");
              displayMEALS(RES);
              getch();
              goto start;
            break;

            case 8:
             goto menuP;
            break;

            default:
             textcolor(4);
             cprintf("Choix Invalide!\a\n");
             getch();
             goto start;
            break;
         }
        break;

        default:
         textcolor(12);
         printf("\n");
         printf("\n\t\t\t\t\t");
         cprintf("~~~~~~~~~~Have a good day!~~~~~~~~~~\a\n");
         getch();
        break;
    }
    return 0;
}
